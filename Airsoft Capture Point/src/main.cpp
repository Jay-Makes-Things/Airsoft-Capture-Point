#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <SPI.h>
#include <RotaryEncoder.h>

void display_time(); //declaring display time function
void display_scoreRed(); //declearing display red team score function
void display_scoreBlue(); //decleating display blue team score function
void blueWin(); //declearing blue team win condition
void redWin(); //declearing red team win condition
void draw(); //declearing draw condition
void enterTime(); //declearing user definded game time function

//define GPIO pins
#define I2C_SDA 21 //I2C Data Pin
#define I2C_SCL 22 //I2C Clock Pin
#define pin_red 34 //red team switch pin
#define pin_netural 39 //netrual switch pin
#define pin_blue 36 //blue team switch pin
#define encoderA 32 //rotary encoder pin A
#define encoderB 25 //rotary encoder pin B
#define encoderButton 27 //rotary encoder button

//define ints
int value_time = 99;
int value_scoreRed = 0000;
int value_scoreBlue = 0000;

//define display prefixes
Adafruit_AlphaNum4 red_display = Adafruit_AlphaNum4();
Adafruit_AlphaNum4 blue_display = Adafruit_AlphaNum4();
Adafruit_AlphaNum4 white_display = Adafruit_AlphaNum4();

void setup() {
 // put your setup code here, to run once:
  
  Serial.begin(9600); //start serial port
  RotaryEncoder encoder(encoderA, encoderB, RotaryEncoder::LatchMode::TWO03);

 //Set-up & start I2C interface

  delay(250);
 
  Wire.begin(I2C_SDA, I2C_SCL);

  //start LED displays

  Serial.println("Starting Displays...");

  delay(100);
  red_display.begin (0x70); //Start Red LED display
  delay(100);
  blue_display.begin (0x71); //Start Blue LED display
  delay(100);
  white_display.begin (0x72); //Start White LED display

  //setup GPIO pin modes

  pinMode(pin_red, INPUT);
  pinMode(pin_netural, INPUT);
  pinMode(pin_blue, INPUT);
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
  pinMode(encoderButton, INPUT);

  //display test

  Serial.println ("Display Test Started...");

  red_display.writeDigitAscii(0, 'R');
  red_display.writeDigitAscii(1, 'E');
  red_display.writeDigitAscii(2, 'D');
  red_display.writeDigitAscii(3, '0');

  red_display.writeDisplay();

  delay(200);

  blue_display.writeDigitAscii(0, 'B');
  blue_display.writeDigitAscii(1, 'L');
  blue_display.writeDigitAscii(2, 'U');
  blue_display.writeDigitAscii(3, 'E');

  blue_display.writeDisplay();

  delay(200);

  white_display.writeDigitAscii(0, 'T');
  white_display.writeDigitAscii(1, 'I');
  white_display.writeDigitAscii(2, 'M');
  white_display.writeDigitAscii(3, 'E');

  white_display.writeDisplay();

  delay(1000);

  red_display.clear();

  delay(200);
  
  blue_display.clear();

  delay(200);

  white_display.clear();

  delay(200);

  Serial.println("Display Test Complete");
}

void loop() {
  //checks if there is still time remaining then reads which teams switch is high and adds a point to that team then subtracts from the time int
  //if no time remaining displays winning team

  if (value_time > 0)
  {
    if (digitalRead(pin_blue) == HIGH)
    {
      value_time = value_time-1;
      value_scoreBlue = value_scoreBlue+1;
    }
    else if (digitalRead(pin_red) == HIGH)
    {
      value_time = value_time-1;
      value_scoreRed = value_scoreRed+1;
    }
    else {
      value_time = value_time-1;
    }

    

  display_time();
  display_scoreRed();
  display_scoreBlue();
  Serial.println("----------------");
  Serial.print("Red Score: ");
  Serial.println(value_scoreRed);
  Serial.print("Blue Score: ");
  Serial.println(value_scoreBlue);
  Serial.print("Time Remaining: ");
  Serial.println(value_time);

  delay(1000);

  }
 
else {
  display_time();
  display_scoreRed();
  display_scoreBlue();

  if (value_scoreBlue > value_scoreRed)
  {
    blueWin();
    Serial.println("Blue Team Wins!");
  }

  else if (value_scoreRed > value_scoreBlue) 
  {
    redWin();
    Serial.println("Red Team Wins!");
  }
  
  else {
    draw();
    Serial.println("Its a Draw!");
  }

}

}

void display_time() {

char Char_bufferW [16];
itoa(value_time, Char_bufferW, 10);

white_display.clear();

white_display.writeDigitAscii(0,Char_bufferW[0]);
white_display.writeDigitAscii(1,Char_bufferW[1]);
white_display.writeDigitAscii(2,Char_bufferW[2]);
white_display.writeDigitAscii(3,Char_bufferW[3]);

white_display.writeDisplay();

}

void display_scoreRed() {

char Char_bufferR [16];
itoa(value_scoreRed, Char_bufferR, 10);

red_display.clear();

red_display.writeDigitAscii(0,Char_bufferR[0]);
red_display.writeDigitAscii(1,Char_bufferR[1]);
red_display.writeDigitAscii(2,Char_bufferR[2]);
red_display.writeDigitAscii(3,Char_bufferR[3]);

red_display.writeDisplay();

}

void display_scoreBlue() {

char Char_bufferB [16];
itoa(value_scoreBlue, Char_bufferB, 10);

blue_display.clear();

blue_display.writeDigitAscii(0,Char_bufferB[0]);
blue_display.writeDigitAscii(1,Char_bufferB[1]);
blue_display.writeDigitAscii(2,Char_bufferB[2]);
blue_display.writeDigitAscii(3,Char_bufferB[3]);

blue_display.writeDisplay();

}

void blueWin() {

  red_display.writeDigitAscii(0, 'L');
  red_display.writeDigitAscii(1, 'O');
  red_display.writeDigitAscii(2, 'S');
  red_display.writeDigitAscii(3, 'E');

  red_display.writeDisplay();

  blue_display.writeDigitAscii(0, 'W');
  blue_display.writeDigitAscii(1, 'I');
  blue_display.writeDigitAscii(2, 'N');
  blue_display.writeDigitAscii(3, ' ');

  blue_display.writeDisplay();

  delay(1000);

  display_scoreBlue();
  display_scoreRed();

  delay(1000);
}

void redWin() {

  red_display.writeDigitAscii(0, 'W');
  red_display.writeDigitAscii(1, 'I');
  red_display.writeDigitAscii(2, 'N');
  red_display.writeDigitAscii(3, ' ');

  red_display.writeDisplay();

  blue_display.writeDigitAscii(0, 'L');
  blue_display.writeDigitAscii(1, 'O');
  blue_display.writeDigitAscii(2, 'S');
  blue_display.writeDigitAscii(3, 'E');

  blue_display.writeDisplay();

  delay(1000);

  display_scoreBlue();
  display_scoreRed();

  delay(1000);
}

void draw() {

   red_display.writeDigitAscii(0, 'D');
  red_display.writeDigitAscii(1, 'R');
  red_display.writeDigitAscii(2, 'A');
  red_display.writeDigitAscii(3, 'W');

  red_display.writeDisplay();

  blue_display.writeDigitAscii(0, 'D');
  blue_display.writeDigitAscii(1, 'R');
  blue_display.writeDigitAscii(2, 'A');
  blue_display.writeDigitAscii(3, 'W');

  blue_display.writeDisplay();

  delay(1000);

  display_scoreBlue();
  display_scoreRed();

  delay(1000);
}

void enterTime() {

  while (value_time < 0)
  {


  }
  
}