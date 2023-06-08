int greenPin=25, redPin= 33, bluePin=32;      /*RGB LED pins defined*/
void setup() {
  pinMode(redPin, OUTPUT);    /*Red pin defined as output*/
  pinMode(greenPin, OUTPUT);   /*Green pin defined as output*/
  pinMode(bluePin, OUTPUT);  /*Blue pin defined as output*/
}
void loop() {
  RGB_output(255, 0, 0); //Set RGB color to Red
  delay(1000);
  RGB_output(0, 255, 0); //Set RGB color to lime
  delay(1000);
  RGB_output(0, 0, 255); //Set RGB color to blue
  delay(1000);
  RGB_output(255, 255, 255); //Set RGB color to white
  delay(1000);
  RGB_output(128, 0, 0); //Set RGB color to maroon
  delay(1000);
  RGB_output(0, 128 , 0); //Set RGB color to green
  delay(1000);
  RGB_output(128, 128, 0); //Set RGB color to olive
  delay(1000);
  RGB_output(0, 0, 0); //Set RGB color to black
  delay(1000);
}
void RGB_output(int redLight, int greenLight, int blueLight)
  {
    analogWrite(redPin, redLight); //write analog values to RGB
    analogWrite(greenPin, greenLight);
    analogWrite(bluePin, blueLight);
}