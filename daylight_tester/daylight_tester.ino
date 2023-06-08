/*
Created 2021.09.27
Arduino LED controller auto mode for sunrise and sunset imitation
*/
#include <TimeLib.h>

#define Red_Pin 6
#define Green_Pin 5
#define Blue_Pin 3

bool trigger_in = false;
bool trigger_out = false;

void setup()
{
  Serial.begin(9600);
  setTime(5, 59, 55, 29, 9, 2021); //hour, minute, sec, day, month, year
  Send_to_Pins(0, 0, 0);
}

void loop()
{
  // Show time in every minute
  // if (second() == 0)
  // {
  //   ClockDisplay();
  // }
  for (int i = 1; i < 25; i++)
  {
  SPWM_25(i, 1);
  // delay(500);
  }

  // SPWM_25(25, 3);
  // SPWM_25(1, 3);

  Serial.println("cycle ends");
  // sunrise();
  delay(1000);
}

void Send_to_Pins(int Red_Value, int Green_Value, int Blue_Value)
{
  analogWrite(Red_Pin, Red_Value);
  analogWrite(Green_Pin, Green_Value);
  analogWrite(Blue_Pin, Blue_Value);
}

void sunrise()
{
  // if (trigger_in == false)

  if (hour() == 6)
  {
    // Serial.println("time to wake up!");
    Send_to_Pins(morning_color_flow('R'), morning_color_flow('G'), morning_color_flow('B'));
    trigger_in = true;
    trigger_out = false;
  }

  if (hour() == 18)
  {
    Send_to_Pins(255, 255, 255);
    trigger_in = true;
    trigger_out = false;
  }
  // }

  if (trigger_out == false)
  {

    if (hour() == 7)
    {
      Serial.println("sunrise section ends");
      Send_to_Pins(0, 0, 0);
      trigger_in = false;
      trigger_out = true;
    }

    if (hour() == 22)
    {
      Send_to_Pins(0, 0, 0);
      trigger_in = false;
      trigger_out = true;
    }
  }
}
void ClockDisplay()
{
  Serial.print(hour());
  Serial.print(":");
  if (minute() < 10)
  {
    Serial.print("0");
    Serial.print(minute());
  }
  else
  {
    Serial.print(minute());
  }
  // Serial.print(":");
  //Serial.print(second());
  Serial.print("\t");
  Serial.print(year());
  Serial.print("-");
  Serial.print(month());
  Serial.print("-");
  Serial.print(day());
  Serial.println();
}

int morning_color_flow(char color)
{
  if (trigger_in == true)
  {
    for (int i = 0; i < 250; i++)
    {
      SPWM_25(i, 0.04);
    }
  }

  // switch (color)
  // {
  // case 'R':
  //   return 4.25 * second();
  //   // break;

  // case 'G':
  //   return 1.5 * second();
  //   // break;

  // case 'B':
  //   return 0.5 * second();
  //   // break;

  // default:
  //   Serial.println("Error: invalid character in morning_color_flow");
  //   break;
  // }
}

void SPWM_25(int duty, int time) //duty is 0-250 what is 25%, so 1 = 0.1% ; frequency 1 kHz;   time is in seconds
{
  for (int i = 0; i < (time * 1000); i++)
  {
    digitalWrite(Red_Pin, HIGH);
    digitalWrite(Green_Pin, HIGH);
    digitalWrite(Blue_Pin, HIGH);

    delayMicroseconds(duty);

    digitalWrite(Red_Pin, LOW);
    digitalWrite(Green_Pin, LOW);
    digitalWrite(Blue_Pin, LOW);

    delayMicroseconds(1000 - duty);
  }
}
