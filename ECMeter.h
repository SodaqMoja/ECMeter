/*! \file ECMeter.h
 * \brief This file contains the class definition of ECMeter.
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

#ifndef EC_H
#define EC_H

#include <stdint.h>

/*! ECMeter class */
class ECMeter
{
public:
  ECMeter();

  float readTemperature();
  float readSystemVoltage();
  float readResistance();
  float readConductivity();
private:
  int16_t readChannel(uint8_t channel);
  float readChannelVoltage(uint8_t channel);

  static const float calibrationVal;
};

#endif
