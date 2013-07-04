/*
 * Copyright 2012 Google Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Danger Will Robinson! Bank 0 (GPIOs 0-31) seems to be fairly stable. Most
 * ICH versions have more, but decoding the matrix that describes them is
 * absurdly complex and constantly changing. We'll provide Bank 1 and Bank 2,
 * but they will ONLY work for certain unspecified chipsets because the offset
 * from GPIOBASE changes randomly. Even then, many GPIOs are unimplemented or
 * reserved or subject to arcane restrictions.
 */

#include <assert.h>
#include <libpayload.h>
#include <pci.h>
#include <stdint.h>

#include "base/list.h"
#include "drivers/gpio/gpio.h"
#include "drivers/gpio/pch.h"

#define NUM_GPIO_BANKS 3
// IO ports for controlling the banks of GPIOS.
//                                    bank:   0     1     2
static uint8_t gpio_use_start[NUM_GPIO_BANKS] = { 0x00, 0x30, 0x40 };
static uint8_t gpio_io_start[NUM_GPIO_BANKS]  = { 0x04, 0x34, 0x44 };
static uint8_t gpio_lvl_start[NUM_GPIO_BANKS] = { 0x0c, 0x38, 0x48 };

/* Functions for manipulating GPIO regs. */

static uint32_t pch_gpiobase(void)
{
	static const uint32_t dev = PCI_DEV(0, 0x1f, 0);
	static const uint8_t pci_cfg_gpiobase = 0x48;

	static uint32_t base = ~(uint32_t)0;
	if (base != ~(uint32_t)0)
		return base;

	base = pci_read_config32(dev, pci_cfg_gpiobase);
	// Drop the IO space bit.
	base &= ~0x1;
	return base;
}

static int pch_gpio_set(unsigned bank, unsigned bit, uint8_t *bases, int val)
{
	uint16_t addr = pch_gpiobase() + bases[bank];
	uint32_t reg = inl(addr);
	reg = (reg & ~(1 << bit)) | ((val & 1) << bit);
	outl(addr, reg);
	return 0;
}

static int pch_gpio_get(unsigned bank, unsigned bit, uint8_t *bases)
{
	uint32_t reg = inl(pch_gpiobase() + bases[bank]);
	return (reg >> bit) & 1;
}


/* Interface functions for manipulating a GPIO. */

static int pch_gpio_get_value(GpioOps *me)
{
	assert(me);
	PchGpio *gpio = container_of(me, PchGpio, ops);
	if (!gpio->dir_set) {
		if (pch_gpio_set(gpio->bank, gpio->bit, gpio_io_start, 1) < 0)
			return -1;
		gpio->dir_set = 1;
	}
	return pch_gpio_get(gpio->bank, gpio->bit, gpio_lvl_start);
}

static int pch_gpio_set_value(GpioOps *me, unsigned value)
{
	assert(me);
	PchGpio *gpio = container_of(me, PchGpio, ops);
	if (!gpio->dir_set) {
		if (pch_gpio_set(gpio->bank, gpio->bit, gpio_io_start, 0) < 0)
			return -1;
		gpio->dir_set = 1;
	}
	return pch_gpio_set(gpio->bank, gpio->bit, gpio_lvl_start, value);
}

static int pch_gpio_use(PchGpio *me, unsigned use)
{
	assert(me);
	return pch_gpio_set(me->bank, me->bit, gpio_use_start, use);
}


/* Functions to allocate and set up a GPIO structure. */

PchGpio *new_pch_gpio(unsigned bank, unsigned bit)
{
	if (bank >= NUM_GPIO_BANKS || bit >= 32) {
		printf("GPIO parameters (%d, %d) out of bounds.\n", bank, bit);
		return NULL;
	}

	PchGpio *gpio = malloc(sizeof(*gpio));
	if (!gpio) {
		printf("Failed to allocate pch gpio object.\n");
		return NULL;
	}
	memset(gpio, 0, sizeof(*gpio));
	gpio->use = &pch_gpio_use;
	gpio->bank = bank;
	gpio->bit = bit;
	return gpio;
}

PchGpio *new_pch_gpio_input(unsigned bank, unsigned bit)
{
	PchGpio *gpio = new_pch_gpio(bank, bit);
	if (!gpio)
		return NULL;

	gpio->ops.get = &pch_gpio_get_value;
	return gpio;
}

PchGpio *new_pch_gpio_output(unsigned bank, unsigned bit)
{
	PchGpio *gpio = new_pch_gpio(bank, bit);
	if (!gpio)
		return NULL;

	gpio->ops.set = &pch_gpio_set_value;
	return gpio;
}
