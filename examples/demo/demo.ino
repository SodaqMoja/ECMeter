#include "ECMeter.h"
#include <Wire.h>

void setup() 
{                
  Serial.begin(9600);
  
  //Reduce I2C clock speed to 12.5Khz, this way we can communicate over long wires
  //Put this in setup() 
  TWBR = 158;  
  TWSR |= bit (TWPS0); 
}

void loop() 
{  
  //Read temperature in celsius
  Serial.print("Temperature: ");
  Serial.print(readTemperature(), 1);
  Serial.println(" C");
  
  //Read on-board voltage
  Serial.print("System voltage: ");
  Serial.print(readSystemVoltage(), 3);
  Serial.println(" V");
  
  //Read resistance across probes
  Serial.print("Resistance: ");
  Serial.print(readResistance(), 0);
  Serial.println(" Ohms");
  
  //Read conductivity
  Serial.print("Conductivity: ");
  Serial.print(readConductivity(), 0);
  Serial.println(" uS");
  
  Serial.println();

  delay(2000);
}