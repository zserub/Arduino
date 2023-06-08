float fract(float x) { return x - int(x); }

float mix(float a, float b, float t) { return a + (b - a) * t; }

float *hsv2rgb(float h, float s, float b, float *rgb)
{
  h = h / 360;
  s = s / 100;
  b = b / 100;
  rgb[0] = b * mix(1.0, constrain(abs(fract(h + 1.0) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
  rgb[1] = b * mix(1.0, constrain(abs(fract(h + 0.6666666) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
  rgb[2] = b * mix(1.0, constrain(abs(fract(h + 0.3333333) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
  return rgb;
}

void setColor(float *rgb)
{
  analogWrite(redPin, (int)((1.0 - rgb[0]) * 255));
  analogWrite(greenPin, (int)((1.0 - rgb[1]) * 255));
  analogWrite(bluePin, (int)((1.0 - rgb[2]) * 255));
}