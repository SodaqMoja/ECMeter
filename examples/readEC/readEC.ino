//This example prints the current EC value in uS every second

#include <ECMeter.h>

double reading = 0;

void setup(void) 
{
  Serial.begin(9600);
  delay(100);
}

void loop(void)
{
  reading = 0;
  
  for(int i = 0; i < 10; i++)
  {
    reading += getEC();
    delay(250);
  }
  
  Serial.println(reading/10.0);
}