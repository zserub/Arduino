const int range = 256;

void motorControl(int x, int y) {
  Serial.print("x: ");
  Serial.println(x);
  Serial.print("y: ");
  Serial.println(y);

  // Map X and Y joystick values to the range -range/2 to range/2-1
  int mappedX = x - (range / 2);
  int mappedY = y - (range / 2);
  Serial.print("mappedX: ");
  Serial.println(mappedX);
  Serial.print("mappedY: ");
  Serial.println(mappedY);

  // Calculate motor speeds
  int LeftM_Speed = 2 * (mappedY + mappedX);
  int RightM_Speed = 2 * (mappedY - mappedX);

  // Constrain motor speeds to valid range (-range to range-1)
  LeftM_Speed = constrain(LeftM_Speed, -range + 1, range - 1);
  RightM_Speed = constrain(RightM_Speed, -range + 1, range - 1);

  Serial.print("LeftM_Speed: ");
  Serial.println(LeftM_Speed);
  Serial.print("RightM_Speed: ");
  Serial.println(RightM_Speed);
}

void setup() {
  Serial.begin(9600);
  int x = 255;  // Manually set x value (0-255)
  int y = 128;    // Manually set y value (0-255)

  motorControl(x, y);
}

void loop() {
}
