/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2012 Advanced Micro Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/io.h>
#include <stdint.h>
#include "w83627dhg.h"

void pnp_enter_ext_func_mode(pnp_devfn_t dev)
{
	u16 port = dev >> 8;
	outb(0x87, port);
	outb(0x87, port);
}

void pnp_exit_ext_func_mode(pnp_devfn_t dev)
{
	u16 port = dev >> 8;
	outb(0xaa, port);
}

/**
 * Select Pin 89, Pin 90 function as I2C interface SDA, SCL.
 *  {Pin 89, Pin 90} function can be selected as {GP33, GP32}, or
 *  {RSTOUT3#, RSTOUT2#} or {SDA, SCL}
 */
void w83627dhg_enable_i2c(pnp_devfn_t dev)
{
	u8 val;

	pnp_enter_ext_func_mode(dev);
	pnp_set_logical_device(dev);

	val = pnp_read_config(dev, 0x2A);
	val |= 1 << 1;
	pnp_write_config(dev, 0x2A, val);

	pnp_exit_ext_func_mode(dev);
}

void w83627dhg_set_clksel_48(pnp_devfn_t dev)
{
	u8 reg8;

	pnp_enter_ext_func_mode(dev);
	reg8 = pnp_read_config(dev, 0x24);
	reg8 |= (1 << 6); /* Set CLKSEL (clock input on pin 1) to 48MHz. */
	pnp_write_config(dev, 0x24, reg8);
	pnp_exit_ext_func_mode(dev);
}
