#ifndef EC_H
#define EC_H

class ECMeter
{
public:
  ECMeter();

  float readTemperature();
  float readSystemVoltage();
  float readResistance();
  float readConductivity();
private:
  float readChannel(uint8_t channel);

  static const float calibrationVal;
};

#endif
