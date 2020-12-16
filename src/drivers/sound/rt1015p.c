// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * rt1015p.c - driver for RT1015Q audio amplifier in auto mode
 *
 * Copyright 2020 Google Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 */

#include <libpayload.h>

#include "base/container_of.h"
#include "rt1015p.h"

static int rt1015p_enable(SoundRouteComponentOps *me)
{
	rt1015pCodec *codec = container_of(me, rt1015pCodec, component.ops);
	int r;

	r = gpio_set(codec->sdb, 1);

	/*
	 * When the system first boots, SDB and BCLK (from I2S) are set,
	 * rt1015p needs 500ms for calibration.
	 */
	if (!codec->calibrated) {
		mdelay(500);
		codec->calibrated = 1;
	}
	return r;
}

static int rt1015p_disable(SoundRouteComponentOps *me)
{
	rt1015pCodec *codec = container_of(me, rt1015pCodec, component.ops);

	/*
	 * The amplifier has a small buffer to queue a few ms audio data and it
	 * will stop to receive the audio data when SDB falling.
	 * The rt10105p has a workaround solution to extend the SDB signal to
	 * pad I2S 0 data into internal buffer, so the amp won't output a
	 * unexpected signal on next audio stream.
	 * As a result, we have to wait 10ms before setting SDB to low otherwise
	 * there will be a pop noise sound.
	 */
	mdelay(10);

	return gpio_set(codec->sdb, 0);
}

rt1015pCodec *new_rt1015p_codec(GpioOps *ops)
{
	rt1015pCodec *codec = xzalloc(sizeof(*codec));

	codec->sdb = ops;
	codec->component.ops.enable = &rt1015p_enable;
	codec->component.ops.disable = &rt1015p_disable;

	return codec;
}
