#include "ECMeter.h"
#include <Wire.h>

ECMeter ecm;

void setup() 
{                
  Serial.begin(9600);

  /*
   * Wire.begin will initialize the TWI, and it sets the bitrate to 100kHz
   * This is hardcoded in twi_init (twi.c).
   * So, we first let the standard Arduino Wire do its setup and then we
   * change the bitrate to what we want.
   */
  Wire.begin();

  /*
   * Set I2C clock
   * First we set the Prescaler Value bits to 1, which results in value 4^1 => 4.
   * Next we set the TWBR value. This is the formula we use:
   * \verbatim
   *     TWBR = ((F_CPU / TWI_FREQ) - 16) / 2 / 4^1;
   * \endverbatim
   * Notice that the 1 is what we set in PS1,PS0 in TWSR.
   */
#define TWI_FREQ 10000
#define TWBR_VAL ((F_CPU / TWI_FREQ) - 16) / 2 / 4
  bitSet(TWSR, TWPS0);
  bitClear(TWSR, TWPS1);
  TWBR = TWBR_VAL;

  /*
   * This is just some diagnostic for debugging.
   */
  Serial.print("TWBR: ");
  Serial.println(TWBR_VAL);
  Serial.print("TWI bitrate: ");
  Serial.println(TWI_FREQ);
}

void loop() 
{  
  Serial.println();

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

  delay(2000);
}
