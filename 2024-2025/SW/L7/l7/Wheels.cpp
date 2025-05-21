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
    printDistance();
    printAngle();
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
  this->setSpeed(100);
  this->forward();
  uint8_t current_cm = 0;
  bool animation = true;
  while (current_cm != cm) {
    current_cm++;
    distance = cm - current_cm;
    if(distance<0) distance = 0;
    delay(60);
    lcd.setCursor(0, 0);
    lcd.print("                ");
    printDistance();
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
  }
  distance = 0;
  printDistance();
  this->stop();
}

void Wheels::goBack(const uint8_t cm){
  this->setSpeed(100);
  this->back();
  uint8_t current_cm = 0;
  bool animation = true;
  while (current_cm != cm) {
    current_cm++;
    distance = cm - current_cm;
    if(distance<0) distance = 0;
    delay(60);
    lcd.setCursor(0, 0);
    lcd.print("                ");
    printDistance();
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
  }
  distance = 0;
  printDistance();
  this->stop();
}

void Wheels::goforward2(const uint8_t cm){
  cnt0 = 0; 
  cnt1 = 0;
  this->setSpeed(200);
  this->forward();
  uint8_t current_cm = (cnt1+cnt0)/3;
  bool animation = true;
  while (current_cm <= cm) {
    distance = cm - current_cm;
    if(distance<0) distance = 0;
    lcd.setCursor(0, 0);
    lcd.print("                ");
    printDistance();
    printAngle();
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
  }
  distance = 0;
  printDistance();
  this->stop();
}

void Wheels::goBack2(const uint8_t cm){
  cnt0 = 0; 
  cnt1 = 0;
  this->setSpeed(250);
  this->back();
  double current_cm = (cnt1+cnt0)/3;
  double last_cm = 0;
  double current_millis = millis();
  double last_millis = current_millis;
  bool animation = true;
  while (current_cm <= cm) {
    distance = cm - current_cm;
    if(distance<0) distance = 0;
    lcd.setCursor(0, 0);
    lcd.print("                ");
    printDistance();
    printAngle();
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

    current_millis = millis();

    //Serial.println((current_cm-last_cm));
    //Serial.println((current_millis-last_millis)/50);
    Serial.println((current_cm-last_cm)/((current_millis-last_millis)/50));

    last_cm = current_cm;
    last_millis = current_millis;
  }
  distance = 0;
  printDistance();
  this->stop();
}

void Wheels::goLeft(const uint8_t angle) {
    stop();
    setSpeed(200);
    forwardLeft();
    backRight();
    delay(500);
    stop();
}

void Wheels::goRight(const uint8_t angle) {
    stop();
    setSpeed(200);
    forwardRight();
    backLeft();
    delay(500);
    stop();
}

void Wheels::goAvoiding() {
    int firstAvgDistance;
    int secondAvgDistance;
    int i=0;
    stop();
    setSpeed(200);
    forward();
    updateAngle(90);
    while(true){
        updateDistance();
        if(distance <= 20){
            stop();
            firstAvgDistance = 0;
            secondAvgDistance = 0;
            i=0;
            while(i<18){
                updateAngle((angle+15)%180);
                Serial.println(distance);
                if(i<9){
                    firstAvgDistance+=distance;
                } else{
                    secondAvgDistance+=distance;
                }
                i++;
            }
            if(firstAvgDistance<secondAvgDistance){
                goRight(30);
                updateAngle(75);
            }else{
                goLeft(30);
                updateAngle(105);
            }
            delay(50);
        } else {
            setSpeed(200);
            forward();
        }
        updateAngle((angle+15)%180);
        Serial.println(distance);
    }
    stop();

}

void Wheels::printDistance(){
    lcd.setCursor(0, 0);
    lcd.print(distance);
    lcd.print("cm");   
}

void Wheels::printAngle(){
    lcd.setCursor(5,0);
    lcd.print(angle);
    lcd.print("*");
}

void Wheels::printDistanceAndAngle(){
    printDistance();
    printAngle();
}

void Wheels::updateDistance(){
    unsigned long tot;
    serwo.write(angle);
    digitalWrite(TRIG, HIGH);
    delay(10);
    digitalWrite(TRIG, LOW);
    tot = pulseIn(ECHO, HIGH);
    distance = tot/58;
    printDistance();
}

void Wheels::updateAngle(const uint8_t newangle){
    angle = newangle;
    serwo.write(angle);
    printAngle();
    delay(10);
    updateDistance();
}