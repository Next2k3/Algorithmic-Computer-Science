#include "Wheels.h"

#include <LiquidCrystal_I2C.h>

byte LCDAddress = 0x27;

LiquidCrystal_I2C lcd(LCDAddress, 16, 2);

Wheels w;
volatile char cmd;

uint8_t arrowRight[8] =
{
    0b01000,
    0b01100,
    0b00110,
    0b11111,
    0b11111,
    0b00110,
    0b01100,
    0b01000
};

uint8_t arrowLeft[8] =
{
    0b00010,
    0b00110,
    0b01100,
    0b11111,
    0b11111,
    0b01100,
    0b00110,
    0b00010
};


void setup() {
  // put your setup code here, to run once:
  w.attach(4,5,3,8,9,10);
  
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, arrowRight);
  lcd.createChar(1, arrowLeft);
}

void loop() {
  while(Serial.available())
  {
    cmd = Serial.read();
    switch(cmd)
    {
      case 'w': w.forward(); break;
      case 'x': w.back(); break;
      case 'a': w.forwardLeft(); break;
      case 'd': w.forwardRight(); break;
      case 'z': w.backLeft(); break;
      case 'c': w.backRight(); break;
      case 's': w.stop(); break;
      case '1': w.setSpeedLeft(75); break;
      case '2': w.setSpeedLeft(200); break;
      case '9': w.setSpeedRight(75); break;
      case '0': w.setSpeedRight(200); break;
      case '5': w.setSpeed(100); break;
      case 'W': w.goforward(15); break;
      case 'X': w.goBack(15); break;
    }
  }
}
