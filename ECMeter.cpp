/*! \file ECMeter.cpp
 * \brief This file contains the class implementation of ECMeter.
 *
 * The ECMeter uses the MPC3428, a 4 channel ADC with I2C interface.
 */

/*
 * Copyright (c) 2014 Nick Leijenhorst.  All rights reserved.
 *
 * This file is part of ECMeter.
 *
 * ECMeter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or(at your option) any later version.
 *
 * ECMeter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ECMeter.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <Arduino.h>
#include <Wire.h>

#include "ECMeter.h"

//! I2C address of the ECMeter
#define EC_ADDR 0x6D

//! \name Channel selection
//@{
#define CH1     0B00000000      //!< Used for: Conductivity measurement
#define CH2     0B00100000      //!< Not connected
#define CH3     0B01000000      //!< Used for: Temperature
#define CH4     0B01100000      //!< Used for: System voltage
//@}

//! \name READY bit
//@{
#define RDY     0B10000000
//@}

//! \name Continuous Conversion or One Shot
//@{
#define CONTCONV 0B00010000
#define ONESHOT  0B00000000
//@}

//! \name Sample Rate Selection
//@{
#define BIT12   0B00000000
#define BIT14   0B00000100
#define BIT16   0B00001000
//@}

//! \name Gain selection
//@{
#define GAIN1   0B00000000
#define GAIN2   0B00000001
#define GAIN4   0B00000010
#define GAIN8   0B00000011
//@}

const float ECMeter::calibrationVal = 0.049;

ECMeter::ECMeter()
{
}

/*! \brief Read the raw value from the ADC channel
 *
 * The configuration register layout looks like this:
 * \verbatim
 * (!RDY | CHANNEL | O/C | RESOLUTION | GAIN)
 *
 * bit 7:       Ready bit, will start new conversion
 * bit 6-5:     Channel selection bit
 * bit 4:       Conversion mode bit, set to 0 for one-shot conversion, 1 for continuous conversion
 * bit 3-2:     Sample rate/resolution bit
 * bit 1-0:     PGA gain selection
 * \endverbatim
 */
int16_t ECMeter::readChannel(uint8_t channel)
{
  Wire.beginTransmission(EC_ADDR);
  Wire.write(RDY | (channel << 5) | ONESHOT | BIT16 | GAIN1); //write configuration register
  Wire.endTransmission();

  delay(75); //delay 75ms to give the ADC time to convert

  Wire.requestFrom(EC_ADDR, 3); //request 3 bytes

  uint8_t h = Wire.read(); //high bits
  uint8_t l = Wire.read(); //low bits
  uint8_t r = Wire.read(); //configuration register
  // TODO We should wait until RDY

  int16_t val = ((uint16_t) h << 8) | l; //merge into 16-bit integer
  return val;
}

/*
 * Read the analog voltage of the specified channel
 */
float ECMeter::readChannelVoltage(uint8_t channel)
{
  int16_t val = readChannel(channel);
  return val * 2.048 / 32768.0; //calculate voltage
}

/*! \brief Reads the temperature of the PCB (and surrounding temperature)
*/
float ECMeter::readTemperature()
{
  float voltage = readChannelVoltage(2);
  return (voltage - 0.5) * 100;
}

/*
Reads the voltage of the system, typically 3.3 volt
*/
float ECMeter::readSystemVoltage()
{
  float voltage = readChannelVoltage(3);
  return voltage * 3.05;
}

/*
Read resistance across probes

The conductivity/resistivity can be calibrated by editing the calibration value in ECMeter.h
If the resistance reads too low, increase the value of 'calibrationVal' and vice versa

returns -1 if reading is invalid (when no resistor is connected for example)
*/
float ECMeter::readResistance()
{
  float voltage = readChannelVoltage(0);
  float gain = voltage / calibrationVal;
  float resistance = 1000.0 / (gain - 1.0);

  if (resistance < -1)
    resistance = -1;

  return resistance;
}

/*
Will convert a resistivity measurement into a conductivity measurement and apply calibration
Returns conductivity in micro Siemens
*/
float ECMeter::readConductivity()
{
  return (1 / readResistance() * 0.3453) * 1000000;
}
