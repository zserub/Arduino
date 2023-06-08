// #include <TimeLib.h>

#define Red_Pin 6
#define Green_Pin 5
#define Blue_Pin 3

int i = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(Red_Pin, OUTPUT);
    pinMode(Green_Pin, OUTPUT);
    pinMode(Blue_Pin, OUTPUT);
    // setTime(0, 0, 0, 29, 9, 2021); //hour, minute, sec, day, month, year
}

void loop()
{
    sunset();
}

void sunset()
{
    int timeBasedColors[3];
    // int timeinSeconds;

    // timeinSeconds = minute() * 60 + second();

    // RED calcultaion
    // timeBasedColors[0] = 255 - timeinSeconds;
    if (i <= 205)
    {
        timeBasedColors[0] = 255;
    }
    else if (i < 255)
    {
        timeBasedColors[0] = 255 - int((i - 205) * 5.1);
    }
    else
    {
        timeBasedColors[0] = 0;
    }

    // GREEN calc
    // timeBasedColors[1] = 122 - int(timeinSeconds * 0.75);
    if (i <= 252)
    {
        timeBasedColors[1] = 126 - int(i / 2);
    }
    else
    {
        timeBasedColors[1] = 0;
    }

    // BlUE calc
    // timeBasedColors[2] = 33 - int(timeinSeconds * 0.5);
    if (i <= 66)
    {
        timeBasedColors[2] = 33 - int(i / 2);
    }
    else if (i >= 140 && i <= 190)
    {
        timeBasedColors[2] = int((i - 140) / 5);
    }
    else if (i > 190 && i <= 240)
    {
        timeBasedColors[2] = int((255 - i) / 5);
    }
    else
    {
        timeBasedColors[2] = 0;
    }

    Send_to_Pins(timeBasedColors[0], timeBasedColors[1], timeBasedColors[2]);

    if (i <= 300)
    {
        i++;
    }
    else
    {
        i = 0;
    }
    delay(100);
}

void Send_to_Pins(int Red_Value, int Green_Value, int Blue_Value)
{
    analogWrite(Red_Pin, Red_Value);
    analogWrite(Green_Pin, Green_Value);
    analogWrite(Blue_Pin, Blue_Value);

    Serial.print(Red_Value);
    Serial.print("\t");
    Serial.print(Green_Value);
    Serial.print("\t");
    Serial.println(Blue_Value);
}