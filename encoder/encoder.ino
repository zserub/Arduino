#define S1 3
#define S2 2
const int LED[6] = {9, 4, 5, 6, 7, 8};
void setup()
{
  // put your setup code here, to run once:

  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
  pinMode(LED[4], OUTPUT);
  pinMode(LED[5], OUTPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  attachInterrupt(digitalPinToInterrupt(S1), left_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(S2), right_encoder, CHANGE);
}

void loop()
{
  // put your main code here, to run repeatedly:
}

void right_encoder()
{
  digitalWrite(LED[2], HIGH);
}
void left_encoder()
{
  digitalWrite(LED[3], HIGH);
}
