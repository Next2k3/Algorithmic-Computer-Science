#include "Wheels.h"

#include <LiquidCrystal_I2C.h>
#include "PinChangeInterrupt.h"
#include <Servo.h>
#include <IRremote.hpp>

#define INTINPUT0 A0
#define INTINPUT1 A1

#define TRIG A3
#define ECHO A2

#define SERVO 11

#define ONE 0xBA45FF00
#define TWO 0xB946FF00
#define THREE 0xB847FF00
#define FOUR 0xBB44FF00
#define FIVE 0xBF40FF00
#define SIX 0xBC43FF00
#define SEVEN 0xF807FF00
#define EIGHT 0xEA15FF00
#define NINE 0xF609FF00
#define ZERO 0xE619FF00

#define UP 0xE718FF00
#define LEFT 0xF708FF00
#define RIGHT 0xA55AFF00
#define DOWN 0xAD52FF00
#define OK 0xE31CFF00

#define STAR 0xE916FF00
#define HASHTAG 0xF20DFF00

Servo serwo;

extern uint8_t speedLeft;
extern uint8_t speedRight;

byte LCDAddress = 0x27;
LiquidCrystal_I2C lcd(LCDAddress, 16, 2);

Wheels w;
volatile char cmd;

long int intPeriod = 500000;
volatile int cnt0, cnt1;

uint8_t arrowRight[8] = {
    0b01000,
    0b01100,
    0b00110,
    0b11111,
    0b11111,
    0b00110,
    0b01100,
    0b01000
};

uint8_t arrowLeft[8] = {
    0b00010,
    0b00110,
    0b01100,
    0b11111,
    0b11111,
    0b01100,
    0b00110,
    0b00010
};

#define IR_RECEIVE_PIN 2

const char correctPin[] = "1234";
char enteredPin[5] = {0};
byte pinIndex = 0;
bool pin = true;
bool avoiding = false;

void setup() {
  w.attach(3, 7, 5, 8, 12, 6);
  pinMode(TRIG, OUTPUT);   
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  serwo.attach(SERVO);
  serwo.write(90);
  delay(15);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, arrowRight);
  lcd.createChar(1, arrowLeft);
  pinMode(INTINPUT0, INPUT);
  pinMode(INTINPUT1, INPUT);
  cnt0 = 0;
  cnt1 = 0;
  PCICR  = 0x02; 
  PCMSK1 = 0x03;
  lcd.setCursor(0, 0);
  lcd.print("Enter PIN:");
}

void loop() {
  if (IrReceiver.decode()) {
    uint32_t rawCode = IrReceiver.decodedIRData.decodedRawData;

    int digit = decodeNumbers(rawCode);

    if (digit >= 0 && digit <= 9 && pinIndex < 4) {
      enteredPin[pinIndex] = digit + '0';
      lcd.setCursor(pinIndex, 1);
      lcd.print('*');
      pinIndex++;
    }

    if (pinIndex == 4) {
      enteredPin[4] = '\0';
      if (strcmp(enteredPin, correctPin) == 0) {
        lcd.setCursor(0, 0);
        lcd.print("PIN OK         ");
        pin = true;
      } else {
        lcd.setCursor(0, 0);
        lcd.print("WRONG PIN      ");
        pin = false;
      }
      delay(2000);
      lcd.setCursor(0, 0);
      lcd.print("Enter PIN:     ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      pinIndex = 0;
    }

    if(pin){
      switch (rawCode) {
        case UP:     w.setSpeed(250); w.forward(); break;
        case DOWN:   w.setSpeed(250); w.back(); break;
        case LEFT:   w.setSpeed(250); w.forwardRight(); break;
        case RIGHT:  w.setSpeed(250); w.forwardLeft(); break;
        case OK:     w.setSpeed(250); w.stop(); avoiding = false; break;
        case STAR:   w.goAvoiding3(); avoiding = true; break;
        case HASHTAG: break;
        default: break;
      }
    }

    IrReceiver.resume();
  }
  if(avoiding) {
      w.goAvoiding3();
    }
}

ISR(PCINT1_vect) {
  if (digitalRead(INTINPUT0))
    cnt0++;
  else if (digitalRead(INTINPUT1))
    cnt1++;
}

int8_t decodeNumbers(uint32_t code) {
  switch (code) {
    case ONE: return 1;
    case TWO: return 2;
    case THREE: return 3;
    case FOUR: return 4;
    case FIVE: return 5;
    case SIX: return 6;
    case SEVEN: return 7;
    case EIGHT: return 8;
    case NINE: return 9;
    case ZERO: return 0;
    default: return -1;
  }
}