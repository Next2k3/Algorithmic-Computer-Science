#include "Wheels.h"

#include <LiquidCrystal_I2C.h>
#include "TimerOne.h"
#include "PinChangeInterrupt.h"

#define INTINPUT0 A0
#define INTINPUT1 A1

extern uint8_t speedLeft;
extern uint8_t speedRight;

#define BEEPER 13

byte LCDAddress = 0x27;

LiquidCrystal_I2C lcd(LCDAddress, 16, 2);

Wheels w;
volatile char cmd;

long int intPeriod = 500000;

volatile int cnt0, cnt1;

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
  w.attach(2,4,3,5,7,6);
  
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, arrowRight);
  lcd.createChar(1, arrowLeft);

  pinMode(BEEPER, OUTPUT);
  Timer1.initialize();
  TimerUpdate();

  pinMode(INTINPUT0, INPUT);
  pinMode(INTINPUT1, INPUT);

  cnt0=0;
  cnt1=0;

  PCICR  = 0x02; 
  PCMSK1 = 0x03;  
}

void loop() {
  while(Serial.available())
  {
    cmd = Serial.read();
    switch(cmd)
    {
      case 'w': w.forward(); break;
      case 'x': 
        intPeriod = 500000;
        TimerUpdate();
        w.back(); 
        break;
      case 'a': w.forwardLeft(); break;
      case 'd': w.forwardRight(); break;
      case 'z': w.backLeft(); break;
      case 'c': w.backRight(); break;
      case 's': w.stop(); 
        Timer1.detachInterrupt();
        break;
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

void TimerUpdate() {
  Timer1.detachInterrupt();
  Timer1.attachInterrupt(doBeep, intPeriod);
}

void doBeep() {
  digitalWrite(BEEPER, digitalRead(BEEPER) ^ 1);
}

ISR(PCINT1_vect) {
  if(digitalRead(INTINPUT0))
    cnt0++;
  else if(digitalRead(INTINPUT1))
    cnt1++;
}