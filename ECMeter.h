#ifndef EC_H
#define EC_H

#include <inttypes.h>

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
