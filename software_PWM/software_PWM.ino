#define Red_pin 6
#define Green_pin 5
#define Blue_pin 3

void setup()
{    
  pinMode(Red_pin, OUTPUT);
  pinMode(Green_pin, OUTPUT);
  pinMode(Blue_pin, OUTPUT);
}

void loop()
{
      SPWM(250, 10);
//     for (int i = 0; i < 250; i++)
//     {
//       SPWM(i, 0.04);
//     } 
  delay(3000);
}

void SPWM(int duty, float time) //duty is 0-250 what is 25%, so 1 = 0.1% ; frequency 1 kHz;   time is in seconds
{
  for (int i = 0; i < (time * 1000); i++)
  {
    digitalWrite(Red_pin, HIGH);
    digitalWrite(Green_pin, HIGH);
    digitalWrite(Blue_pin, HIGH);

    delayMicroseconds(duty);

    digitalWrite(Red_pin, LOW);
    digitalWrite(Green_pin, LOW);
    digitalWrite(Blue_pin, LOW);

    delayMicroseconds(1000 - duty);
  }
}
