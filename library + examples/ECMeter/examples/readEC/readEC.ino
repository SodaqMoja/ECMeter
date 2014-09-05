//This example prints the current EC value in uS every second

#include <ECMeter.h>

void setup(void) 
{
  Serial.begin(9600);
  delay(100);
}

void loop(void)
{
  Serial.println(getEC());
  delay(1000);
}
