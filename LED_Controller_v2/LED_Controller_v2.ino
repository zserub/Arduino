/*
 Name:    LED_Control.ino
 Created: 2021-07-30 12:43:58
 Author:  Zsedely Ruben
*/
#include <TimeLib.h>
#include <IRremote.h>

#define Red_Pin 6
#define Green_Pin 5
#define Blue_Pin 3

const int receiver = 2; // Signal Pin of IR receiver to Arduino Digital Pin

/*GLOBAL VARIABLES*/ #pragma region;
int RGB_gv[3] = {255, 255, 255};
int RGBglobalValues[3] = {255, 255, 255};
unsigned char select_program = '0'; //A is jump3, B is jump7, C is fade3, D is fade7,
                                    // E is Flash, F is record, Z is auto

int speed = 1000;
int iteration = 0;

// Color correction table
/*const uint8_t PROGMEM gamma8[] = {
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
    215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255};*/
#pragma endregion

/*Tranzient functions*/ #pragma region;

void Send_to_Pins(int Red_Value, int Green_Value, int Blue_Value)
{

    RGBglobalValues[0] = Red_Value;
    RGBglobalValues[1] = Green_Value;
    RGBglobalValues[2] = Blue_Value;

    // analogWrite(Red_Pin, Red_Value);
    // analogWrite(Green_Pin, Green_Value);
    // analogWrite(Blue_Pin, Blue_Value);

    analogWrite(Red_Pin, Red_Value);
    analogWrite(Green_Pin, (Green_Value));
    analogWrite(Blue_Pin, (Blue_Value));

    Serial.print(Red_Value);
    Serial.print("\t");
    Serial.print(Green_Value);
    Serial.print("\t");
    Serial.println(Blue_Value);
}
#pragma endregion

class DIY_Color_Variables
{
public:
    int R[6];
    int G[6];
    int B[6];
    DIY_Color_Variables(/*int r[6], int g[6], int b[6]*/)
    {
        for (int i = 0; i < 6; i++)
        {
            R[i] = 0;
            G[i] = 0;
            B[i] = 0;
        }
    }
    ~DIY_Color_Variables()
    {
        for (int i = 0; i < 6; i++)
        {
            R[i] = 0;
            G[i] = 0;
            B[i] = 0;
        }
    }
    void catch_DIY_button(long IR_code)
    {
        switch (IR_code)
        {
        case 0xF30CFF00:
            burn_DIY(1);
            break; //DIY1
        case 0xF20DFF00:
            burn_DIY(2);
            break; //DIY2
        case 0xF10EFF00:
            burn_DIY(3);
            break; //DIY3
        case 0xF708FF00:
            burn_DIY(4);
            break; //DIY4
        case 0xF609FF00:
            burn_DIY(5);
            break; //DIY5
        case 0xF50AFF00:
            burn_DIY(6);
            break; //DIY6
        }
    }
    void burn_DIY(int serialnumber)
    {
        Serial.print("DIY");
        Serial.print(serialnumber);

        R[serialnumber - 1] = RGBglobalValues[0];
        G[serialnumber - 1] = RGBglobalValues[1];
        B[serialnumber - 1] = RGBglobalValues[2];

        Serial.println(" burned successfully");
        Serial.print("R: ");
        Serial.println(R[serialnumber - 1]);
        Serial.print("G: ");
        Serial.println(G[serialnumber - 1]);
        Serial.print("B: ");
        Serial.println(B[serialnumber - 1]);

        select_program = '0';
    }
    /*DIY Functions*/ #pragma region;
    void DIY1()
    {
        Send_to_Pins(R[0], G[0], B[0]);
    }
    void DIY2()
    {
        Send_to_Pins(R[1], G[1], B[1]);
    }
    void DIY3()
    {
        Send_to_Pins(R[2], G[2], B[2]);
    }
    void DIY4()
    {
        Send_to_Pins(R[3], G[3], B[3]);
    }
    void DIY5()
    {
        Send_to_Pins(R[4], G[4], B[4]);
    }
    void DIY6()
    {
        Send_to_Pins(R[5], G[5], B[5]);
    }
#pragma endregion
};
DIY_Color_Variables *DIY_Color_object = new DIY_Color_Variables();

//SETUP
void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(Red_Pin, OUTPUT);
    pinMode(Green_Pin, OUTPUT);
    pinMode(Blue_Pin, OUTPUT);
    pinMode(receiver, INPUT);        //Set pin d2 to input using the buildin pullup resistor
    setTime(17, 42, 0, 2, 1, 2022); //hour, min, sec, day, month, year
    ClockDisplay();
    IrReceiver.begin(receiver, ENABLE_LED_FEEDBACK); // Start the receiver
    Serial.println("IR Receiver ON");
} /*--( end setup )---*/

//MAIN
void loop()
{
    IR_sensing();

    switch (select_program)
    {
    case 'A':
        jump3();
        break;
    case 'B':
        jump7();
        break;
    case 'C':
        fade3();
        break;
    case 'D':
        fade7();
        break;
    case 'E':
        Flash();
        break;
    case 'F':
        DIY_Color_object->catch_DIY_button(IrReceiver.decodedIRData.decodedRawData);
        break;
    case 'Z': //auto
        sunset();
        break;
    case '0':
        break;
    default:
        Serial.println("Error: Undefind char");
    }
} /* --(end main loop )-- */

//Remote control function calls
void translateIR()
{
    bool modifier_button = false; // takes action based on IR code received

    switch (IrReceiver.decodedIRData.decodedRawData)
    {

    case 0xBF40FF00:
        Serial.println("POWER OFF");
        Send_to_Pins(0, 0, 0);
        // Going_To_Sleep();
        break;

        //Colors
    case 0xA758FF00:
        Serial.println("Red");
        Red();
        break;

    case 0xA659FF00:
        Serial.println("Green");
        Green();
        break;

    case 0xBA45FF00:
        Serial.println("Blue");
        Blue();
        break;

    case 0xBB44FF00:
        Serial.println("White");
        White();
        break;

    case 0xAB54FF00:
        Serial.println("Reddish_Orange");
        Reddish_Orange();
        break;

    case 0xAA55FF00:
        Serial.println("Pale_Green");
        Pale_Green();
        break;

    case 0xB649FF00:
        Serial.println("Pale_Blue");
        Pale_Blue();
        break;

    case 0xB748FF00:
        Serial.println("Warm_White");
        Warm_White();
        break;

    case 0xAF50FF00:
        Serial.println("Orange");
        Orange();
        break;

    case 0xAE51FF00:
        Serial.println("Greenish_Blue");
        Greenish_Blue();
        break;

    case 0xB24DFF00:
        Serial.println("Purple");
        Purple();
        break;

    case 0xB34CFF00:
        Serial.println("Sligtly_Warm_White");
        Sligtly_Warm_White();
        break;

    case 0xE31CFF00:
        Serial.println("Pale_Orange");
        Pale_Orange();
        break;

    case 0xE21DFF00:
        Serial.println("Bluish_Green");
        Bluish_Green();
        break;

    case 0xE11EFF00:
        Serial.println("Pale_Purple");
        Pale_Purple();
        break;

    case 0xE01FFF00:
        Serial.println("Sligtly_Cold_White");
        Sligtly_Cold_White();
        break;

    case 0xE718FF00:
        Serial.println("Yellow");
        Yellow();
        break;

    case 0xE619FF00:
        Serial.println("Dark_Bluish_Green");
        Dark_Bluish_Green();
        break;

    case 0xE51AFF00:
        Serial.println("Pink");
        Pink();
        break;

    case 0xE41BFF00:
        Serial.println("Cold_White");
        Cold_White();
        break;

        //Modifiers
    case 0xEB14FF00:
        Serial.println("Red_Up");
        Red_Up();
        break;

    case 0xEF10FF00:
        Serial.println("Red_Down");
        Red_Down();
        break;

    case 0xEA15FF00:
        Serial.println("Green_Up");
        Green_Up();
        break;

    case 0xEE11FF00:
        Serial.println("Green_Down");
        Green_Down();
        break;

    case 0xE916FF00:
        Serial.println("Blue_Up");
        Blue_Up();
        break;

    case 0xED12FF00:
        Serial.println("Blue_Down");
        Blue_Down();
        break;

    case 0xA35CFF00:
        Serial.println("Lights_Up");
        modifier_button = true;
        Lights_Up();
        break;

    case 0xA25DFF00:
        Serial.println("Lights_Down");
        modifier_button = true;
        Lights_Down();
        break;

    case 0xE817FF00:
        Serial.println("Quick");
        modifier_button = true;
        quick();
        break;

    case 0xEC13FF00:
        Serial.println("slow");
        modifier_button = true;
        slow();
        break;

        //Programs
    case 0xFB04FF00:
        Serial.println("jump3");
        RGB_gv[0] = 255;
        RGB_gv[1] = 255;
        RGB_gv[2] = 255;
        modifier_button = true;
        select_program = 'A';
        break;
    case 0xFA05FF00:
        Serial.println("jump7");
        RGB_gv[0] = 255;
        RGB_gv[1] = 255;
        RGB_gv[2] = 255;
        modifier_button = true;
        select_program = 'B';
        break;
    case 0xF906FF00:
        Serial.println("fade3");
        modifier_button = true;
        select_program = 'C';
        break;
    case 0xF807FF00:
        Serial.println("fade7");
        modifier_button = true;
        select_program = 'D';
        break;
    case 0xF40BFF00:
        Serial.println("Flash");
        modifier_button = true;
        select_program = 'E';
        break;

        //DIY
    case 0xF30CFF00:
        Serial.println("DIY1");
        DIY_Color_object->DIY1();
        break; //DIY1
    case 0xF20DFF00:
        Serial.println("DIY2");
        DIY_Color_object->DIY2();
        break; //DIY2
    case 0xF10EFF00:
        Serial.println("DIY3");
        DIY_Color_object->DIY3();
        break; //DIY3
    case 0xF708FF00:
        Serial.println("DIY4");
        DIY_Color_object->DIY4();
        break; //DIY4
    case 0xF609FF00:
        Serial.println("DIY5");
        DIY_Color_object->DIY5();
        break; //DIY5
    case 0xF50AFF00:
        Serial.println("DIY6");
        DIY_Color_object->DIY6();
        break; //DIY6

    case 0xBE41FF00: //Record
        Serial.println("Record");
        modifier_button = true;
        record();
        break;

    case 0xF00FFF00: //auto
        Serial.println("auto");
        modifier_button = true;
        select_program = 'Z';
        break;

    case 0:
        Serial.println("noise");
        break;

    default:
        Serial.println(" Error: button is not declaired");
    } // End Case

    set_program(modifier_button);

    delay(100); // Do not get immediate repeat

} //END translateIR

/*Basic Colors*/ #pragma region;
void Red()
{
    //FF1AE5
    Send_to_Pins(255, 0, 0);
}

void Green()
{
    //FF9A65
    Send_to_Pins(0, 255, 0);
}

void Blue()
{
    //FFA25D
    Send_to_Pins(0, 0, 255);
}

void White()
{
    //FF22DD
    Send_to_Pins(255, 191, 128);
}

void Reddish_Orange()
{
    //FF2AD5
    // Send_to_Pins(255, 69, 0);
    Send_to_Pins(255, 25, 0);
}

void Pale_Green()
{
    //FFAA55
    // Send_to_Pins(0, 255, 127);
    Send_to_Pins(0, 255, 25);
}

void Pale_Blue()
{ //dodger blue
    //FF926D
    // Send_to_Pins(30, 144, 255);
    Send_to_Pins(0, 142, 255);
}

void Warm_White()
{
    //FF12ED
    // Send_to_Pins(255, 191, 127);
    Send_to_Pins(255, 77, 8);
}

void Orange()
{
    //FF0AF5
    Send_to_Pins(255, 68, 0);
}

void Greenish_Blue()
{ //aqua marine
    //FF8A75
    // Send_to_Pins(127, 255, 212);
    Send_to_Pins(127, 255, 90);
}

void Purple()
{
    //FFB24D
    Send_to_Pins(128, 0, 128);
}

void Sligtly_Warm_White()
{
    //FF32CD
    // Send_to_Pins(253, 244, 220);
    Send_to_Pins(255, 122, 33);
}

void Pale_Orange()
{ //Coral
    //FF38C7
    // Send_to_Pins(255, 127, 80);
    Send_to_Pins(255, 87, 13);
}

void Bluish_Green()
{ //light sea green
    //FFB847
    // Send_to_Pins(32, 178, 170);
    Send_to_Pins(43, 255, 89);
}

void Dark_Bluish_Green()
{ //corn flower blue
    //FF9867
    Send_to_Pins(0, 230, 128);
}

void Pale_Purple()
{ //blue violet
    //FF7887
    Send_to_Pins(255, 40, 155);
}

void Sligtly_Cold_White()
{
    //FFF807
    // Send_to_Pins(244, 255, 250);
    Send_to_Pins(255, 242, 215);
}

void Yellow()
{
    //FF18E7
    // Send_to_Pins(255, 255, 0);
    Send_to_Pins(255, 128, 0);
}

void Pink()
{ //true pink
    //FF58A7
    // Send_to_Pins(255, 192, 203);
    Send_to_Pins(255, 77, 77);
}

void Cold_White()
{
    //FFD827
    // Send_to_Pins(212, 235, 255);
    Send_to_Pins(255, 255, 255);
}
#pragma endregion

/*Color Arrows*/ #pragma region;
void Red_Up()
{
    //FF28D7
    RGBglobalValues[0] += 25;
    if (RGBglobalValues[0] > 255)
    {
        RGBglobalValues[0] = 255;
    }
    Send_to_Pins(RGBglobalValues[0], RGBglobalValues[1], RGBglobalValues[2]);
}

void Red_Down()
{
    //FF08F7
    RGBglobalValues[0] -= 25;
    if (RGBglobalValues[0] < 0)
    {
        RGBglobalValues[0] = 0;
    }
    Send_to_Pins(RGBglobalValues[0], RGBglobalValues[1], RGBglobalValues[2]);
}

void Green_Up()
{
    //FFA857
    RGBglobalValues[1] += 25;
    if (RGBglobalValues[1] > 255)
    {
        RGBglobalValues[1] = 255;
    }
    Send_to_Pins(RGBglobalValues[0], RGBglobalValues[1], RGBglobalValues[2]);
}

void Green_Down()
{
    //FF8877
    RGBglobalValues[1] -= 25;
    if (RGBglobalValues[1] < 0)
    {
        RGBglobalValues[1] = 0;
    }
    Send_to_Pins(RGBglobalValues[0], RGBglobalValues[1], RGBglobalValues[2]);
}

void Blue_Up()
{
    //FF6897
    RGBglobalValues[2] += 25;
    if (RGBglobalValues[2] > 255)
    {
        RGBglobalValues[2] = 255;
    }
    Send_to_Pins(RGBglobalValues[0], RGBglobalValues[1], RGBglobalValues[2]);
}

void Blue_Down()
{
    //FF48B7
    RGBglobalValues[2] -= 25;
    if (RGBglobalValues[2] < 0)
    {
        RGBglobalValues[2] = 0;
    }
    Send_to_Pins(RGBglobalValues[0], RGBglobalValues[1], RGBglobalValues[2]);
}
#pragma endregion

/*Power of lights*/ #pragma region;
void Lights_Up()
{
    //FF3AC5
    for (int i = 0; i < 3; i++)
    {

        RGB_gv[i] += 50;
        RGBglobalValues[i] += 50;

        if (RGB_gv[i] > 255)
        {
            RGB_gv[i] = 255;
        }
        if (RGBglobalValues[i] > 255)
        {
            RGBglobalValues[i] = 255;
        }
    }

    if (select_program == '0')
    {
        Send_to_Pins(RGBglobalValues[0], RGBglobalValues[1], RGBglobalValues[2]);
    }
}

void Lights_Down()
{
    //FFBA45
    for (int i = 0; i < 3; i++)
    {

        RGB_gv[i] -= 50;
        RGBglobalValues[i] -= 50;

        if (RGB_gv[i] < 0)
        {
            RGB_gv[i] = 0;
        }
        if (RGBglobalValues[i] < 0)
        {
            RGBglobalValues[i] = 0;
        }
    }

    if (select_program == '0')
    {
        Send_to_Pins(RGBglobalValues[0], RGBglobalValues[1], RGBglobalValues[2]);
    }
}
#pragma endregion

/*predefined programs*/ #pragma region;
void jump3()
{
    //FB04FF00

    Send_to_Pins(RGB_gv[0], 0, 0);
    delay(speed);
    Send_to_Pins(0, RGB_gv[1], 0);
    delay(speed);
    Send_to_Pins(0, 0, RGB_gv[2]);
    delay(speed);
}

void jump7()
{
    //FB04FF00

    Send_to_Pins(RGB_gv[0], 0, 0);
    delay(speed);
    Send_to_Pins(RGB_gv[0], RGB_gv[1], 0);
    delay(speed);
    Send_to_Pins(0, RGB_gv[1], 0);
    delay(speed);
    Send_to_Pins(0, RGB_gv[1], RGB_gv[2]);
    delay(speed);
    Send_to_Pins(0, 0, RGB_gv[2]);
    delay(speed);
    Send_to_Pins(RGB_gv[0], 0, RGB_gv[2]);
    delay(speed);
    Send_to_Pins(RGB_gv[0], RGB_gv[1], RGB_gv[2]);
    delay(speed);
}

void fade3()
{
    int R_fade_value;
    int G_fade_value;
    int B_fade_value;

    if (iteration < 100)
    {
        B_fade_value = 255 - (iteration * 2.55);
        R_fade_value = iteration * 2.55;
    }

    if (iteration >= 100 && iteration < 200)
    {
        R_fade_value = 255 - ((iteration - 100) * 2.55);
        G_fade_value = (iteration - 100) * 2.55;
    }

    if (iteration >= 200 && iteration < 300)
    {
        G_fade_value = 255 - ((iteration - 200) * 2.55);
        B_fade_value = (iteration - 200) * 2.55;
    }

    iteration++;

    if (iteration >= 300)
    {
        iteration = 0;
    }

    Send_to_Pins(R_fade_value, G_fade_value, B_fade_value);
    delay((speed / 25));
}

void fade7()
{
    int R_fade_value;
    int G_fade_value;
    int B_fade_value;

    if (iteration < 100)
    {                                            //RED LIGHT
        B_fade_value = 255 - (iteration * 2.55); //Blue fade away
    }

    if (iteration >= 100 && iteration < 200)
    {                                            //ORANGE LIGHT
        G_fade_value = (iteration - 100) * 2.55; //Green increasing
    }

    if (iteration >= 200 && iteration < 300)
    {                                                    //GREEN LIGHT
        R_fade_value = 255 - ((iteration - 200) * 2.55); //Red fade away
    }

    if (iteration >= 300 && iteration < 400)
    {                                            //GREENISH BLUE LIGHT
        B_fade_value = (iteration - 300) * 2.55; //Blue increasing
    }

    if (iteration >= 400 && iteration < 500)
    {                                                    //BLUE LIGHT
        G_fade_value = 255 - ((iteration - 400) * 2.55); //Green fade away
    }

    if (iteration >= 500 && iteration < 600)
    {                                            //PURPLE LIGHT
        R_fade_value = (iteration - 500) * 2.55; //Red increasing
    }

    iteration++;

    if (iteration >= 600)
    {
        iteration = 0;
    }

    Send_to_Pins(R_fade_value, G_fade_value, B_fade_value);
    delay((speed / 25));
}

void Flash()
{
    White();
    delay(speed);
    Send_to_Pins(0, 0, 0);
    delay(speed);
}
#pragma endregion

/*Modifiers*/ #pragma region;
void quick()
{
    speed -= 250;
    if (speed < 250)
    {
        speed = 250;
    }
}

void slow()
{
    speed += 250;
    if (speed > 2000)
    {
        speed = 2000;
    }
}
#pragma endregion;

void IR_sensing() //Read the incoming signes
{
    if (IrReceiver.decode())
    {
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
        if (select_program != 'F')
        {
            translateIR();
        }
        delay(250);
        IrReceiver.resume();
        //got_command = false;
    }
}

void set_program(bool &in_modifier_button) //if I use modifier button on the controller, then the predifined programs may not be interrupted
{
    if (IrReceiver.decodedIRData.decodedRawData != 0 && in_modifier_button == false)
    {
        select_program = '0';
    }
}

void record()
{
    Serial.println("Record started. Select a DIY button!");
    select_program = 'F';
}

void sunset()
{
    int timeBasedColors[3];
    int timeinSeconds;

    if (hour() < 20)
    {
        timeinSeconds = 0;
        Send_to_Pins(255, 126, 33);
    }

    if (hour() >= 20)
    {
        timeinSeconds = hour() - 20 + minute() * 60 + second();
    }

    if ((timeinSeconds % 28) == 0 && timeinSeconds < 7140)
    {
        int dividedTime = timeinSeconds / 28;
        // RED calcultaion
        // timeBasedColors[0] = 255 - timeinSeconds / 28;
        if (dividedTime <= 205)
        {
            timeBasedColors[0] = 255;
        }
        else if (dividedTime < 255)
        {
            timeBasedColors[0] = 255 - int((dividedTime - 205) * 5.1);
        }
        else
        {
            timeBasedColors[0] = 0;
        }

        // GREEN calc
        // timeBasedColors[1] = 122 - (timeinSeconds / 28);
        if (dividedTime <= 252)
        {
            timeBasedColors[1] = 126 - int(dividedTime / 2);
        }
        else
        {
            timeBasedColors[1] = 0;
        }

        // BlUE calc
        // timeBasedColors[2] = 33 - (timeinSeconds / 28);
        if (dividedTime <= 66)
        {
            timeBasedColors[2] = 33 - int(dividedTime / 2);
        }
        else if (dividedTime >= 140 && dividedTime <= 190)
        {
            timeBasedColors[2] = int((dividedTime - 140) / 5);
        }
        else if (dividedTime > 190 && dividedTime <= 240)
        {
            timeBasedColors[2] = int((255 - dividedTime) / 5);
        }
        else
        {
            timeBasedColors[2] = 0;
        }

        Send_to_Pins((timeBasedColors[0] / 3), (timeBasedColors[1] / 3), (timeBasedColors[2] / 3));
    }

    if (timeinSeconds >= 7140)
    {
        Send_to_Pins(0, 0, 0);
        select_program = '0';
    }

    delay(500);
}

void ClockDisplay()
{
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.print(second());
    Serial.print("\t");
    Serial.print(year());
    Serial.print("-");
    Serial.print(month());
    Serial.print("-");
    Serial.print(day());
    Serial.println();
}
