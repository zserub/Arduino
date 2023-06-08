#include <elapsedMillis.h>
elapsedMillis buzzTime;

// Example code KY012 active buzzer
int speakerPin = 12;
void setup()
{
  pinMode(speakerPin, OUTPUT);
}
void loop()
{
  buzzer(); // Call the buzzer function repeatedly in the loop
}

void buzzer()
{
  static int state = 0;

  if (state == 4 && buzzTime >= 2000 + 125 * 3)
  {
    state = 0;
  }
  else if (state == 3 && buzzTime >= 125 * 3)
  {
    analogWrite(speakerPin, 0);
    state = 4;
  }
  else if (state == 2 && buzzTime >= 125 * 2)
  {
    analogWrite(speakerPin, 50);
    state = 3;
  }
  else if (state == 1 && buzzTime >= 125)
  {
    analogWrite(speakerPin, 0);
    state = 2;
  }
  else if (state == 0)
  {
    analogWrite(speakerPin, 50);
    state = 1;
    buzzTime = 0;
  }
}