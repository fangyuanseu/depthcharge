/*
 * Copyright (c) 2012 The Chromium OS Authors.
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

#include <libpayload.h>

#include "base/init_funcs.h"
#include "base/timestamp.h"
#include "drivers/input/input.h"
#include "vboot/stages.h"
#include "vboot/util/acpi.h"
#include "vboot/util/commonparams.h"

int main(void)
{
	// Let the world know we're alive.
	outb(0xaa, 0x80);

	// Initialize some consoles.
	serial_init();
	cbmem_console_init();
	input_init();

	printf("\n\nStarting read-only depthcharge...\n");

	// Set up time keeping.
	timestamp_init();

	// Run any generic initialization functions that are compiled in.
	if (run_init_funcs())
		halt();

	// Set up the common param structure.
	if (common_params_init())
		halt();

	// Initialize vboot.
	if (vboot_init())
		halt();

	// Select firmware.
	if (vboot_select_firmware())
		halt();

	// Update the crossystem data in the ACPI tables.
	if (acpi_update_data())
		halt();

	usb_initialize();

	// Select a kernel and boot it.
	if (vboot_select_and_load_kernel())
		halt();

	// We should never get here.
	printf("Got to the end!\n");
	halt();
	return 0;
}
