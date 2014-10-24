//This example prints the current temperature every second

#include <ECMeter.h>

void setup(void) 
{
  Serial.begin(9600);
  delay(100);
}

void loop(void)
{
  Serial.println(getTemperature(),1);
  delay(1000);
}
