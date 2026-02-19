/*
 * File:   eeprom.c
 * Author: User
 *
 * Created on 9 December, 2024, 11:48 AM
 */


#include <xc.h>
#include "timer.h"


void ex_eeprom_write(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
    for(int i = 0; i < 3000; i++);
}

unsigned char ex_eeprom_read(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVE_READ);
    
	data = i2c_read();
	i2c_stop();

	return data;
}


