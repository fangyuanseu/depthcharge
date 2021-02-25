/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __DRIVERS_GPIO_MT8195_H__
#define __DRIVERS_GPIO_MT8195_H__

#include <stdint.h>

enum {
	MAX_GPIO_REG_BITS = 32,
	MAX_EINT_REG_BITS = 32,
};

enum {
	GPIO_BASE = 0x10005000,
	EINT_BASE = 0x1000B000,
};

enum {
	PAD_GPIO_00 = 0,
	PAD_GPIO_01 = 1,
	PAD_GPIO_02 = 2,
	PAD_GPIO_03 = 3,
	PAD_GPIO_04 = 4,
	PAD_GPIO_05 = 5,
	PAD_GPIO_06 = 6,
	PAD_GPIO_07 = 7,
	PAD_SDA0 = 8,
	PAD_SCL0 = 9,
	PAD_SDA1 = 10,
	PAD_SCL1 = 11,
	PAD_SDA2 = 12,
	PAD_SCL2 = 13,
	PAD_SDA3 = 14,
	PAD_SCL3 = 15,
	PAD_SDA4 = 16,
	PAD_SCL4 = 17,
	PAD_DPTX_HPD = 18,
	PAD_PCIE_WAKE_N = 19,
	PAD_PCIE_PERESET_N = 20,
	PAD_PCIE_CLKREQ_N = 21,
	PAD_CMMCLK0 = 22,
	PAD_CMMCLK1 = 23,
	PAD_CMMCLK2 = 24,
	PAD_CMMRST = 25,
	PAD_CMMPDN = 26,
	PAD_HDMIRX_HTPLG = 27,
	PAD_HDMIRX_PWR5V = 28,
	PAD_HDMIRX_SCL = 29,
	PAD_HDMIRX_SDA = 30,
	PAD_HDMITX_PWR5V = 31,
	PAD_HDMITX_HTPLG = 32,
	PAD_HDMITX_CEC = 33,
	PAD_HDMITX_SCL = 34,
	PAD_HDMITX_SDA = 35,
	PAD_PMIC_RTC32K_CK = 36,
	PAD_PMIC_WATCHDOG = 37,
	PAD_PMIC_SRCLKEN_IN0 = 38,
	PAD_PMIC_SRCLKEN_IN1 = 39,
	PAD_PWRAP_SPI_CSN = 40,
	PAD_PWRAP_SPI_CK = 41,
	PAD_PWRAP_SPI_MO = 42,
	PAD_PWRAP_SPI_MI = 43,
	PAD_SPMI_M_SCL = 44,
	PAD_SPMI_M_SDA = 45,
	PAD_I2SIN_MCK = 46,
	PAD_I2SIN_BCK = 47,
	PAD_I2SIN_WS = 48,
	PAD_I2SIN_D0 = 49,
	PAD_I2SO1_MCK = 50,
	PAD_I2SO1_BCK = 51,
	PAD_I2SO1_WS = 52,
	PAD_I2SO1_D0 = 53,
	PAD_I2SO1_D1 = 54,
	PAD_I2SO1_D2 = 55,
	PAD_I2SO1_D3 = 56,
	PAD_I2SO2_MCK = 57,
	PAD_I2SO2_BCK = 58,
	PAD_I2SO2_WS = 59,
	PAD_I2SO2_D0 = 60,
	PAD_DMIC1_SCK = 61,
	PAD_DMIC1_DAT = 62,
	PAD_DMIC2_SCK = 63,
	PAD_DMIC2_DAT = 64,
	PAD_PCM_DO = 65,
	PAD_PCM_CLK = 66,
	PAD_PCM_DI = 67,
	PAD_PCM_SYNC = 68,
	PAD_AUD_CLK_MOSI = 69,
	PAD_AUD_SYNC_MOSI = 70,
	PAD_AUD_DAT_MOSI0 = 71,
	PAD_AUD_DAT_MOSI1 = 72,
	PAD_AUD_DAT_MISO0 = 73,
	PAD_AUD_DAT_MISO1 = 74,
	PAD_AUD_DAT_MISO2 = 75,
	PAD_SCP_VREQ_VAO = 76,
	PAD_DGI_D0 = 77,
	PAD_DGI_D1 = 78,
	PAD_DGI_D2 = 79,
	PAD_DGI_D3 = 80,
	PAD_DGI_D4 = 81,
	PAD_DGI_D5 = 82,
	PAD_DGI_D6 = 83,
	PAD_DGI_D7 = 84,
	PAD_DGI_D8 = 85,
	PAD_DGI_D9 = 86,
	PAD_DGI_D10 = 87,
	PAD_DGI_D11 = 88,
	PAD_DGI_D12 = 89,
	PAD_DGI_D13 = 90,
	PAD_DGI_D14 = 91,
	PAD_DGI_D15 = 92,
	PAD_DGI_HSYNC = 93,
	PAD_DGI_VSYNC = 94,
	PAD_DGI_DE = 95,
	PAD_DGI_CK = 96,
	PAD_DISP_PWM0 = 97,
	PAD_UART0_TXD = 98,
	PAD_UART0_RXD = 99,
	PAD_UART1_RTS = 100,
	PAD_UART1_CTS = 101,
	PAD_UART1_TXD = 102,
	PAD_UART1_RXD = 103,
	PAD_KPROW0 = 104,
	PAD_KPROW1 = 105,
	PAD_KPCOL0 = 106,
	PAD_KPCOL1 = 107,
	PAD_DSI_LCM_RST = 108,
	PAD_DSI_DSI_TE = 109,
	PAD_MSDC1_CMD = 110,
	PAD_MSDC1_CLK = 111,
	PAD_MSDC1_DAT0 = 112,
	PAD_MSDC1_DAT1 = 113,
	PAD_MSDC1_DAT2 = 114,
	PAD_MSDC1_DAT3 = 115,
	PAD_EMMC_DAT7 = 116,
	PAD_EMMC_DAT6 = 117,
	PAD_EMMC_DAT5 = 118,
	PAD_EMMC_DAT4 = 119,
	PAD_EMMC_RSTB = 120,
	PAD_EMMC_CMD = 121,
	PAD_EMMC_CLK = 122,
	PAD_EMMC_DAT3 = 123,
	PAD_EMMC_DAT2 = 124,
	PAD_EMMC_DAT1 = 125,
	PAD_EMMC_DAT0 = 126,
	PAD_EMMC_DSL = 127,
	PAD_USB_IDDIG = 128,
	PAD_USB_DRV_VBUS = 129,
	PAD_USB_IDDIG_1P = 130,
	PAD_USB_DRV_VBUS_1P = 131,
	PAD_SPIM0_CSB = 132,
	PAD_SPIM0_CLK = 133,
	PAD_SPIM0_MO = 134,
	PAD_SPIM0_MI = 135,
	PAD_SPIM1_CSB = 136,
	PAD_SPIM1_CLK = 137,
	PAD_SPIM1_MO = 138,
	PAD_SPIM1_MI = 139,
	PAD_SPIM2_CSB = 140,
	PAD_SPIM2_CLK = 141,
	PAD_SPIM2_MO = 142,
	PAD_SPIM2_MI = 143,
	GPIO_NUM,
};

typedef struct {
	GpioValRegs dir[7];
	uint8_t rsv00[144];
	GpioValRegs dout[7];
	uint8_t rsv01[144];
	GpioValRegs din[7];
	uint8_t rsv02[144];
	GpioValRegs mode[28];
} GpioRegs;

typedef struct {
	uint32_t sta[16];
	uint32_t ack[16];
} EintRegs;

#endif /* __DRIVERS_GPIO_MT8195_H__ */
