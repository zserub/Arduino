/**
 * @brief 7-segment display utility
 * @date 2022-04-09
 * @version 1.1
 */
const int SEG_A = 2;
const int SEG_B = 3;
const int SEG_C = 4;
const int SEG_D = 5;
const int SEG_E = 6;
const int SEG_F = 7;
const int SEG_G = 8;
const int SEG_DP = 9;

const char COMMON_ANODE = 'a';
const char COMMON_CATHODE = 'c';

const byte LOOKUP_TABLE[] = {
  /*0*/ 0b11111100,
  /*1*/ 0b01100000,
  /*2*/ 0b11011010,
  /*3*/ 0b11110010,
  /*4*/ 0b01100110,
  /*5*/ 0b10110110,
  /*6*/ 0b10111110,
  /*7*/ 0b11100000,
  /*8*/ 0b11111110,
  /*9*/ 0b11110110,
  /*A*/ 0b11101110,
  /*b*/ 0b00111110,
  /*C*/ 0b10011100,
  /*c*/ 0b00011010,
  /*d*/ 0b01111010,
  /*E*/ 0b10011110,
  /*F*/ 0b10001110,
  /*H*/ 0b01101110,
  /*h*/ 0b00101110,
  /*L*/ 0b00011100,
  /*l*/ 0b00001100,
  /*o*/ 0b00111010,
  /*P*/ 0b11001110,
};

void setup() {
  Serial.begin(9600);
  for (int i = SEG_A; i <= SEG_DP; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);  // turn off all segments
  }
}

void loop() {
  if (Serial.available() > 0) {
    // char incomingChar = Serial.read();
    String incomingData = Serial.readStringUntil(' ');
    incomingData.trim();
    char incomingChar = incomingData.charAt(0);
    UpdateDisplay(GetSegmentValue(incomingChar));
  }
}

// Update the display
void UpdateDisplay(byte eightBits) {
  int thisBit = 7;  // eight bits in a byte counting from 0
  for (int i = SEG_A; i <= SEG_G; i++) {
    byte lightSegment = bitRead(eightBits, thisBit--);
    if (COMMON_ANODE == 'a') {
      digitalWrite(i, !lightSegment);
    } else {
      digitalWrite(i, lightSegment);
    }
  }
  bool lightDP = bitRead(eightBits, 7 - SEG_DP);
  if (COMMON_ANODE == 'a') {
    digitalWrite(SEG_DP, !lightDP);
  } else {
    digitalWrite(SEG_DP, lightDP);
  }
}

/**
 * @brief Get the Segment Value object
 * 
 * @param c 
 * @return byte 
 */
byte GetSegmentValue(char c) {
  byte value = 0;
  switch (c) {
    case '0':
      value = LOOKUP_TABLE[0];
      break;
    case '1':
      value = LOOKUP_TABLE[1];
      break;
    case '2':
      value = LOOKUP_TABLE[2];
      break;
    case '3':
      value = LOOKUP_TABLE[3];
      break;
    case '4':
      value = LOOKUP_TABLE[4];
      break;
    case '5':
      value = LOOKUP_TABLE[5];
      break;
    case '6':
      value = LOOKUP_TABLE[6];
      break;
    case '7':
      value = LOOKUP_TABLE[7];
      break;
    case '8':
      value = LOOKUP_TABLE[8];
      break;
    case '9':
      value = LOOKUP_TABLE[9];
      break;
    case 'A':
      value = LOOKUP_TABLE[10];
      break;
    case 'b':
      value = LOOKUP_TABLE[11];
      break;
    case 'C':
      value = LOOKUP_TABLE[12];
      break;
    case 'c':
      value = LOOKUP_TABLE[13];
      break;
    case 'd':
      value = LOOKUP_TABLE[14];
      break;
    case 'E':
      value = LOOKUP_TABLE[15];
      break;
    case 'F':
      value = LOOKUP_TABLE[16];
      break;
    case 'H':
      value = LOOKUP_TABLE[17];
      break;
    case 'h':
      value = LOOKUP_TABLE[18];
      break;
    case 'L':
      value = LOOKUP_TABLE[19];
      break;
    case 'l':
      value = LOOKUP_TABLE[20];
      break;
    case 'o':
      value = LOOKUP_TABLE[21];
      break;
    case 'P':
      value = LOOKUP_TABLE[22];
      break;
    default:
      value = 0;
      break;
  }
  return value;
}