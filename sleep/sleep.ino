#include <avr/sleep.h>

#define ledPin 4

char msg;
int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;
bool isSleeping = false;

void wakeUp()
{
  if (isSleeping == true)
  {
    sleep_disable();                   //Disable sleep mode
    Serial.println("Interrupt Fired"); //Print message to serial monitor
    isSleeping = false;
  }
}

void setup()
{
  pinMode(2, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(3), wakeUp, CHANGE);
}

void loop()
{
  readButton_Db();
  readMessage();
}

void Going_To_Sleep()
{
  isSleeping = true;
  Serial.println("Going to Sleep");
  digitalWrite(ledPin, LOW); //turning LED off
  delay(500);                //wait a second to allow the led to be turned off before going to sleep
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu(); //go to sleep
}

void readButton_Db()
{
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = 50;
  int reading = digitalRead(2);
  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {

    if (reading != buttonState)
    {
      buttonState = reading;

      if (buttonState == HIGH)
      {
        ledState = !ledState;
      }
    }
  }
  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}

void readMessage()
{
  if (Serial.available() > 0)
  {
    msg = Serial.read();
    if (msg == 's')
    {
      Going_To_Sleep();
    }
    else
    {
      Serial.println("invalid command");
    }
  }
}
