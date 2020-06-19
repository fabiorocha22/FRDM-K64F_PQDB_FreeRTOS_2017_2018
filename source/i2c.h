/*
 * i2c.h
 *
 *  Created on: 26/02/2018
 *      Author: fabio
 */

#ifndef SOURCE_I2C_H_
#define SOURCE_I2C_H_

void i2cInit(void);
unsigned char i2cWriteByte(unsigned char send_start, unsigned char send_stop, unsigned char byte);
unsigned char i2cReadByte(unsigned char nack, unsigned char send_stop);

#endif /* SOURCE_I2C_H_ */
