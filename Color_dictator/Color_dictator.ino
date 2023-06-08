#define Red_Pin 6
#define Green_Pin 5
#define Blue_Pin 3

// Color correction table
const uint8_t PROGMEM RedLookupTable[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
    2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5,
    5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
    10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
    25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
    37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
    51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
    69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
    90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
    115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
    144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
    177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
    215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255};

const uint8_t PROGMEM GreenLookupTable[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4,
    4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8,
    8, 8, 9, 9, 9, 9, 9, 10, 10, 10, 11, 11, 12, 12,
    13, 13, 13, 13, 14, 14, 15, 15, 16, 16, 16, 16, 17,
    17, 18, 19, 19, 20, 20, 20, 21, 21, 22, 23, 23, 24,
    24, 25, 25, 26, 27, 27, 27, 28, 29, 30, 31, 31, 31,
    32, 33, 34, 35, 35, 36, 37, 38, 38, 39, 39, 40, 41,
    42, 43, 44, 45, 45, 46, 47, 48, 49, 49, 50, 52, 53,
    53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 64, 64, 65,
    67, 67, 68, 70, 71, 72, 73, 75, 75, 77, 78, 79, 80,
    82, 82, 84, 85, 86, 88, 89, 90, 92, 93, 94, 96, 97,
    99, 100, 101, 103, 104, 106, 107, 108, 110, 111, 113,
    115, 116, 118, 119, 121, 122, 124, 125, 127, 129, 131,
    133, 134, 136, 137, 139, 141, 143, 144, 146, 148, 150,
    151, 154, 155, 157, 159, 161, 163, 165, 167, 169, 171,
    173, 175, 176, 179, 181, 183, 185, 187, 189, 191, 194,
    195, 198, 200};

const uint8_t PROGMEM BlueLookupTable[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 7, 7,
    7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 12, 12, 12, 12, 13, 13,
    13, 13, 14, 15, 15, 15, 15, 16, 16, 16, 17, 18, 18, 18, 19, 19, 19, 20, 21,
    21, 21, 22, 22, 23, 24, 24, 24, 25, 26, 26, 27, 27, 28, 29, 29, 30, 30, 30,
    31, 32, 33, 33, 34, 35, 35, 36, 36, 37, 38, 38, 39, 40, 41, 41, 42, 43, 44,
    44, 45, 46, 47, 47, 48, 49, 50, 50, 52, 52, 53, 54, 55, 56, 57, 58, 58, 60,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 77, 77, 78,
    80, 81, 82, 83, 84, 85, 86, 88, 89, 90, 91, 92, 94, 95, 96, 97, 98, 100, 102,
    103, 104, 105, 106, 108, 109, 111, 112, 113, 115, 116, 117, 119, 120, 122,
    123, 125, 126, 128, 129, 131, 133, 134, 136, 137, 139, 140, 142, 143, 145,
    147, 148, 150, 151, 153, 155};

int RGBglobalValues[3] = {0, 0, 0};

void setup()
{
  Serial.begin(9600);
  pinMode(Red_Pin, OUTPUT);
  pinMode(Green_Pin, OUTPUT);
  pinMode(Blue_Pin, OUTPUT);
}

void loop()
{
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
  char *convertedCommand = command.c_str();
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
  // analogWrite(Red_Pin, Red_Value);
  // analogWrite(Green_Pin, Green_Value);
  // analogWrite(Blue_Pin, Blue_Value);

  analogWrite(Red_Pin, pgm_read_byte(&RedLookupTable[Red_Value]));
  analogWrite(Green_Pin, pgm_read_byte(&GreenLookupTable[Green_Value])); //color correction
  analogWrite(Blue_Pin, pgm_read_byte(&BlueLookupTable[Blue_Value]));

  Serial.println("linear and converted values:");
  Serial.print(Red_Value);
  Serial.print("\t");
  Serial.println(pgm_read_byte(&RedLookupTable[Red_Value]));

  Serial.print(Green_Value);
  Serial.print("\t");
  Serial.println(pgm_read_byte(&GreenLookupTable[Green_Value]));

  Serial.print(Blue_Value);
  Serial.print("\t");
  Serial.println(pgm_read_byte(&BlueLookupTable[Blue_Value]));
}
