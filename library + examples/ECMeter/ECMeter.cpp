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

double getEC()
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

	double v = (double) t * 2.048/32768.0; //Get voltage
	double gain = v / 0.05; //Calculate gain
	
	double resistance = 1000.0/(gain-1.0); //Get resistance across probes
	double microsiemens = (1.0/resistance) * 1000000.0; //Convert to microsiemens

	return (microsiemens * 0.285); 
}



double getResistance()
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

	double v = (double) t * 2.048/32768.0; //Get voltage
	double gain = v / 0.05; //Calculate gain
	
	double resistance = 1000.0/(gain-1.0); //Get resistance across probes
	
	return resistance;
}

double getTemperature()
{
	return (getChannel2()-0.5) * 100;
}