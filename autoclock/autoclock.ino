#include <TimeLib.h>

#define led 3
unsigned long pctime = 0;

void setup()
{
  Serial.begin(9600);

  setTime(9, 40, 0, 19, 9, 2021);
  // Serial.println(now());
}

void loop()
{
  if ((second() % 2) == 0)
  {
    ClockDisplay();
  }
  delay(1000);
}

void ClockDisplay()
{
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print("\t");
  Serial.print(year());
  Serial.print("-");
  Serial.print(month());
  Serial.print("-");
  Serial.print(day());
  Serial.println();
}
