#include <Arduino.h>

#include "Wheels.h"

#define SET_MOVEMENT(side,f,b) digitalWrite( side[0], f);\
                               digitalWrite( side[1], b)


Wheels::Wheels() 
{
}

void Wheels::attachRight(int pF, int pB, int pS)
{
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsRight[0] = pF;
    this->pinsRight[1] = pB;
    this->pinsRight[2] = pS;
}


void Wheels::attachLeft(int pF, int pB, int pS)
{
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsLeft[0] = pF;
    this->pinsLeft[1] = pB;
    this->pinsLeft[2] = pS;
}

void Wheels::setSpeedRight(uint8_t s)
{
    analogWrite(this->pinsRight[2], s);
    speedRight = s;
}

void Wheels::setSpeedLeft(uint8_t s)
{
    analogWrite(this->pinsLeft[2], s);
    speedLeft = s;
}

void Wheels::setSpeed(uint8_t s)
{
    setSpeedLeft(s);
    setSpeedRight(s);
}

void Wheels::attach(int pRF, int pRB, int pRS, int pLF, int pLB, int pLS)
{
    this->attachRight(pRF, pRB, pRS);
    this->attachLeft(pLF, pLB, pLS);
}

void Wheels::forwardLeft() 
{
    lcd.setCursor(0,1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print(speedLeft);
    SET_MOVEMENT(pinsLeft, HIGH, LOW);
}

void Wheels::forwardRight() 
{
    lcd.setCursor(12,1);
    lcd.print("    ");
    lcd.setCursor(12,1);
    lcd.print(speedRight);
    SET_MOVEMENT(pinsRight, HIGH, LOW);
}

void Wheels::backLeft()
{
    lcd.setCursor(0,1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print(-speedLeft);
    SET_MOVEMENT(pinsLeft, LOW, HIGH);
}

void Wheels::backRight()
{
    lcd.setCursor(12,1);
    lcd.print("    ");
    lcd.setCursor(12,1);
    lcd.print(-speedRight);
    SET_MOVEMENT(pinsRight, LOW, HIGH);
}

void Wheels::forward()
{
    this->forwardLeft();
    this->forwardRight();
}

void Wheels::back()
{
    this->backLeft();
    this->backRight();
}

void Wheels::stopLeft()
{
    lcd.setCursor(0,1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print("0   ");
    SET_MOVEMENT(pinsLeft, LOW, LOW);
}

void Wheels::stopRight()
{
    lcd.setCursor(12,1);
    lcd.print("    ");
    lcd.setCursor(12,1);
    lcd.print("   0");
    SET_MOVEMENT(pinsRight, LOW, LOW);
}

void Wheels::stop()
{
    lcd.setCursor(4, 1);
    lcd.print("        ");
    this->stopLeft();
    this->stopRight();
}

void Wheels::goforward(const uint8_t cm){
  cnt0 = 0; 
  cnt1 = 0;
  this->setSpeed(200);
  this->forward();
  uint8_t current_cm = (cnt1+cnt0)/3;
  bool animation = true;
  while (current_cm <= cm) {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(cm - current_cm);
    lcd.print("cm");
    lcd.setCursor(4, 1);
    if (animation) lcd.print(" ");
    lcd.write(0);
    lcd.print(" ");
    lcd.write(0);
    lcd.print(" ");
    lcd.write(0);
    lcd.print(" ");
    lcd.write(0);
    if (!animation) lcd.print(" ");
    animation = !animation;
    current_cm = (cnt1+cnt0)/3;
    Serial.print(cnt0/1.5);
    Serial.print(" ");
    Serial.println(cnt1/1.5);
  }
  this->stop();
}

void Wheels::goBack(const uint8_t cm){
  cnt0 = 0; 
  cnt1 = 0;
  this->setSpeed(200);
  this->back();
  uint8_t current_cm = (cnt1+cnt0)/3;
  bool animation = true;
  while (current_cm <= cm) {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(current_cm - cm);
    lcd.print("cm");
    lcd.setCursor(4, 1);
    if (animation) lcd.print(" ");
    lcd.write(1);
    lcd.print(" ");
    lcd.write(1);
    lcd.print(" ");
    lcd.write(1);
    lcd.print(" ");
    lcd.write(1);
    if (!animation) lcd.print(" ");
    animation = !animation;
    current_cm = (cnt1+cnt0)/3;
    Serial.print(cnt0/1.5);
    Serial.print(" ");
    Serial.println(cnt1/1.5);
  }
  this->stop();
}
