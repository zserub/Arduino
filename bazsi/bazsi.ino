//KnightRider 6 LED controll; PWM
const int LEDs[6] = { 3, 5, 6, 9, 10, 11 };
int values[6]; //= { 85, 170, 254, 170, 85, 1 };
double x[6] = { -2.5, -1.5, -0.5, 0.5, 1.5, 2.5 };
//bool direction = true;

//Curve calculation
double exp_fv(double a, int b) {
    b = (exp(-((a - 3) * (a - 3)) / 1)) * 255;
    return b;
}
void adjust_PWM(int d) {

    values[d] = exp_fv(x[d], 0);
    analogWrite(LEDs[d], values[d]);
}

void setup() {}

void loop() {

    for (int i = 0; i < 600; i++) {

        for (int j = 0; j < 6; j++) {

            x[j] += 0.01;
            adjust_PWM(j);
        }

        delay(1);
    }

    for (int i = 600; i > 0; i--) {

        for (int j = 0; j < 6; j++) {

            x[j] -= 0.01;
            adjust_PWM(j);
        }

        delay(1);
    }
}
