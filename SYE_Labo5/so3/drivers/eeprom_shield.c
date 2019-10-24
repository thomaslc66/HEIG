/*
 *
 * ----- SO3 Smart Object Oriented (SOO) Operating System -----
 *
 * Copyright (c) 2016,2017 Sootech SA, Switzerland
 * Copyright (c) 2014, 2015, 2016, 2017 REDS Institute, HEIG-VD, Switzerland
 * 
 * This software is released under the MIT License whose terms are defined hereafter.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 * Contributors:
 *
 * - August 2015: Raphaël Buache
 */

#include "so3_i2c.h"


#define I2C_BASE_ADDRESS 0x50
#define BLOCK_0_SELECT 0x0
#define BLOCK_1_SELECT 0x1

#define MAX_ADDR (256*2-1)
#define BLOCK_1_ADDR_BEGIN 256

int read_byte_eeprom(int address,char *byte){

	char received;
	char i2c_address = I2C_BASE_ADDRESS;

	if (address > MAX_ADDR)
		return -1;

	if (address >= BLOCK_1_ADDR_BEGIN)
		i2c_address |= BLOCK_1_SELECT;

	a20_i2c_ops.i2c_start_bit();

	a20_i2c_ops.i2c_send_ctrl(i2c_address,0);

	a20_i2c_ops.i2c_write_byte(address & 0xff);

	a20_i2c_ops.i2c_start_bit();

	a20_i2c_ops.i2c_send_ctrl(i2c_address,1);

	*byte = a20_i2c_ops.i2c_read_byte(0);

	a20_i2c_ops.i2c_stop_bit();

	return 0;
}

int write_byte_eeprom(int address, char byte){

	char i2c_address = I2C_BASE_ADDRESS;

	if (address > MAX_ADDR)
		return -1;

	if (address >= BLOCK_1_ADDR_BEGIN)
		i2c_address |= BLOCK_1_SELECT;

	a20_i2c_ops.i2c_start_bit();

	a20_i2c_ops.i2c_send_ctrl(i2c_address,0);

	a20_i2c_ops.i2c_write_byte(address & 0xff);

	a20_i2c_ops.i2c_write_byte(byte);

	a20_i2c_ops.i2c_stop_bit();

	return 0;
}
