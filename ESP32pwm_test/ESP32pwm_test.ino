#include <pwmWrite.h>

#define RedPin 14
#define GreenPin 12
#define BluePin 27
Pwm pwm = Pwm();

int RGBglobalValues[3] = {0, 0, 0};

void setup() {
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  Serial.begin(9600);
  // pwm.pause();
  // pwm.write(RedPin, 1, 1000, 10);
  // pwm.write(GreenPin, 1, 1000, 10);
  // pwm.write(BluePin, 1, 1000, 10);
  // pwm.resume();
  // pwm.printConfig();
}

void loop() {
while (Serial.available())
  {
    Serial.print("readed string: ");
    String readedData = Serial.readString(); // read the incoming data as string
    Serial.println(readedData);
    ExecuteCommand(readedData);
  }
}

void ExecuteCommand(String command)
{
  char color;
  int value;
  char *convertedCommand = const_cast<char*>(command.c_str());
  // Returns first token
  char *token = strtok(convertedCommand, ":");

  // Keep printing tokens while one of the
  // delimiters present in str[].
  bool counter = false;
  while (token != NULL)
  {
    if (counter == false)
    {
      color = token[0];
      // strcpy(color, token.c_str());
      Serial.print("Color: ");
      Serial.print(color);
    }
    if (counter == true)
    {
      String convertedToken = String(token);
      value = convertedToken.toInt();
      Serial.print("\tValue: ");
      Serial.println(value);
    }

    // Serial.print(token);
    token = strtok(NULL, ":");
    counter = true;
  }

  switch (color)
  {
  case 'R':
    RGBglobalValues[0] = value;
    break;

  case 'G':
    RGBglobalValues[1] = value;
    break;

  case 'B':
    RGBglobalValues[2] = value;
    break;

  default:
    Serial.println("Error: Unknown command");
    break;
  }

  Send_to_Pins(RGBglobalValues[0], RGBglobalValues[1], RGBglobalValues[2]);
}

void Send_to_Pins(int Red_Value, int Green_Value, int Blue_Value)
{
  pwm.write(RedPin, Red_Value, 1000, 10);
  pwm.write(GreenPin, Green_Value, 1000, 10);
  pwm.write(BluePin, Blue_Value, 1000, 10);
}