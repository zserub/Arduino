void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  if (Serial.available() > 0)
  {
    char commandID = Serial.read();
    switch (commandID)
    {
      case 'a': digitalWrite(LED_BUILTIN, HIGH); break;
      case '0': digitalWrite(LED_BUILTIN, LOW); break;
      default : break;
    }
  }
}
