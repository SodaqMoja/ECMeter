#ifndef EC_H
#define EC_H

//Channel selection
#define CH1 	0B00000000	//Conductivity measurement
#define CH2 	0B00100000	//Not connected
#define CH3 	0B01000000	//Temperature
#define CH4 	0B01100000	//System voltage

#define RDY 	0B10000000
#define ONESHOT 0B00000000

//Resolution selection
#define BIT12 	0B00000000
#define BIT14 	0B00000100
#define BIT16 	0B00001000

//Gain selection
#define GAIN1 	0B00000000
#define GAIN2 	0B00000001
#define GAIN4 	0B00000010
#define GAIN8 	0B00000011

const float calibrationVal = 0.049;

float readChannel(uint8_t CHANNEL);
float readTemperature();
float readSystemVoltage();
float readResistance();
float readConductivity();

#endif
