#include <Arduino.h>
#include <Wire.h>

#include "ECMeter.h"

//I2C address of ECMeter
#define EC_ADDR 0x6D

ECMeter::ECMeter()
{
}

/*
This method returns the analog voltage on any channel given.
The configuration register layout looks like this:

(RDY | CHANNEL | O/C | RESOLUTION | GAIN)

bit 7:		Ready bit, will start new conversion
bit 6-5:	Channel selection bit
bit 4:		Conversion mode bit, set to 0 for one-shot conversion, 1 for continuous conversion
bit 3-2:	Sample rate/resolution bit
bit 1-0:	PGA gain selection
*/
float ECMeter::readChannel(uint8_t CHANNEL)
{
	Wire.beginTransmission(EC_ADDR);
	Wire.write(RDY | CHANNEL | ONESHOT | BIT16 | GAIN1); //write configuration register
	Wire.endTransmission();
	
	delay(75); //delay 75ms to give the ADC time to convert
	
	Wire.requestFrom(EC_ADDR, 3); //request 3 bytes

	uint8_t h = Wire.read(); //high bits
	uint8_t l = Wire.read(); //low bits
	uint8_t r = Wire.read(); //configuration register

	uint16_t val = (h << 8) | l; //merge into 16-bit integer
	return (float)(val * (2.048/32768)); //calculate voltage
}

/*
Reads the temperature of the PCB (and surrounding temperature)
*/
float ECMeter::readTemperature()
{
	float voltage = readChannel(CH3);
	return (voltage - 0.5)*100;
}

/*
Reads the voltage of the system, typically 3.3 volt
*/
float ECMeter::readSystemVoltage()
{
	float voltage = readChannel(CH4);
	return voltage*3.05;
}

/*
Read resistance across probes

The conductivity/resistivity can be calibrated by editing the calibration value in ECMeter.h
If the resistance reads too low, increase the value of 'calibrationVal' and vice versa

returns -1 if reading is invalid (when no resistor is connected for example)
*/
float ECMeter::readResistance()
{
	float voltage = readChannel(CH1);
	float gain = voltage / calibrationVal;
	float resistance = 1000.0/(gain-1.0);
	
	if(resistance < -1)
		resistance = -1;
		
	return resistance;
}

/*
Will convert a resistivity measurement into a conductivity measurement and apply calibration
Returns conductivity in micro Siemens
*/
float ECMeter::readConductivity()
{
	return (1/readResistance() * 0.3453) * 1000000;
}
