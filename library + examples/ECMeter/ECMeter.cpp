#include "ECMeter.h"
#include "../SoftI2CMaster/SoftI2CMaster.h"

double systemVoltage;

void setVoltage(double voltage)
{
	systemVoltage = voltage;
}

double getVoltage()
{
	return systemVoltage;
}

double getChannel2()
{
  	i2c_start(ADDR|I2C_WRITE);
	i2c_write(0xA8);

  	i2c_rep_start(ADDR|I2C_READ);
  	
	byte h = i2c_read(false);
  	byte l = i2c_read(false);
  	byte r = i2c_read(true);
  
    i2c_stop();
  
  	long t = h << 8 |  l;
  	
	if (t >= 32768) t = 65536l - t;
  	
	double v = (double) t * 2.048/32768.0;

	return v;
}

double getChannel1()
{
  	i2c_start(ADDR|I2C_WRITE);
	i2c_write(0x88);

  	i2c_rep_start(ADDR|I2C_READ);
  	
	byte h = i2c_read(false);
  	byte l = i2c_read(false);
  	byte r = i2c_read(true);
  
    i2c_stop();
  
  	long t = h << 8 |  l;
  	
	if (t >= 32768) t = 65536l - t;
  	
	double v = (double) t * 2.048/32768.0;

	return v;
}

int getEC()
{
  	i2c_start(ADDR|I2C_WRITE);
	i2c_write(0x88);

  	i2c_rep_start(ADDR|I2C_READ);
  	
	byte h = i2c_read(false);
  	byte l = i2c_read(false);
  	byte r = i2c_read(true);
  
    i2c_stop();
  
  	long t = h << 8 |  l;
  	
	if (t >= 32768) t = 65536l - t;
  	
	double v = (double)t * 0.88;
	
	int i = (int)v - 80;
	
	if(i < 0)
	{
		i = 0;
	}

	return i;
}

double getTemperature()
{
	return (getChannel2()-0.5) * 100;
}