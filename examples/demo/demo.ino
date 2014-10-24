#include "ECMeter.h"
#include <Wire.h>

void setup() 
{                
  Serial.begin(9600);  
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
  
  Serial.println();

  delay(2000);
}
