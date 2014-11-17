#include "ECMeter.h"
#include <Wire.h>

ECMeter ecm;

void setup() 
{                
  Serial.begin(9600);
  
  //Set I2C clock to 10Khz
  bitSet(TWSR, TWPS0); 
  bitClear(TWSR, TWPS1);  
  TWBR = 98;
}

void loop() 
{  
  //Read temperature in celsius
  Serial.print("Temperature: ");
  Serial.print(ecm.readTemperature(), 1);
  Serial.println(" C");
  
  //Read on-board voltage
  Serial.print("System voltage: ");
  Serial.print(ecm.readSystemVoltage(), 3);
  Serial.println(" V");
  
  //Read resistance across probes
  Serial.print("Resistance: ");
  Serial.print(ecm.readResistance(), 0);
  Serial.println(" Ohms");
  
  //Read conductivity
  Serial.print("Conductivity: ");
  Serial.print(ecm.readConductivity(), 0);
  Serial.println(" uS");
  
  Serial.println();

  delay(2000);
}