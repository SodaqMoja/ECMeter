#ifndef EC_H
#define EC_H

#define NO_INTERRUPT 1
#define I2C_TIMEOUT 1000

#define SDA_PORT PORTD
#define SDA_PIN 5
#define SCL_PORT PORTD
#define SCL_PIN 4
#define ADDR 0xD0

double getVoltage();
void setVoltage(double voltage);
double getChannel1();
double getChannel2();
double getTemperature();
int getEC();

#endif