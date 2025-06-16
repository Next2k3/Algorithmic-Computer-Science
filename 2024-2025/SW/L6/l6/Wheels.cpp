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
    /*
    lcd.setCursor(0,1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print(speedLeft);
    */
    SET_MOVEMENT(pinsLeft, HIGH, LOW);
}

void Wheels::forwardRight() 
{
    /*
    lcd.setCursor(12,1);
    lcd.print("    ");
    lcd.setCursor(12,1);
    lcd.print(speedRight);
    */
    SET_MOVEMENT(pinsRight, HIGH, LOW);
}

void Wheels::backLeft()
{
    /*
    lcd.setCursor(0,1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print(-speedLeft);
    */
    SET_MOVEMENT(pinsLeft, LOW, HIGH);
}

void Wheels::backRight()
{
    /*
    lcd.setCursor(12,1);
    lcd.print("    ");
    lcd.setCursor(12,1);
    lcd.print(-speedRight);
    */
    SET_MOVEMENT(pinsRight, LOW, HIGH);
}

void Wheels::forward()
{
    this->forwardLeft();
    this->forwardRight();
    //printDistance();
    //printAngle();
}

void Wheels::back()
{
    this->backLeft();
    this->backRight();
}

void Wheels::stopLeft()
{
    /*
    lcd.setCursor(0,1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print("0   ");
    */
    SET_MOVEMENT(pinsLeft, LOW, LOW);
}

void Wheels::stopRight()
{
    /*
    lcd.setCursor(12,1);
    lcd.print("    ");
    lcd.setCursor(12,1);
    lcd.print("   0");
    */
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
    setSpeed(250);
    forwardLeft();
    delay(angle*25);
}

void Wheels::goRight(const uint8_t angle) {
    stop();
    setSpeed(250);
    forwardRight();
    delay(angle*25);
}

void Wheels::goLeft2(const uint8_t angle) {
    stop();
    setSpeed(200);
    forwardRight();
    delay(angle*25);
    forward();
}

void Wheels::goRight2(const uint8_t angle) {
    stop();
    setSpeed(200);
    forwardLeft();
    delay(angle*25);
    forward();
}

int Wheels::srednia(){
    return (distances[0]+distances[1]+distances[2]+distances[3]+distances[4])/5;
}

void Wheels::goAvoiding3() {
    Serial.println(status);
    switch(status){
        case 0:
            updateAngle(90);
            for(int i=0;i<5;i++){
                updateDistance();
            }
            setSpeed(200);
            forward();
            status=1;
            break;
        case 1:
            updateAngle(90);
            updateDistance();
            if(srednia()<=50){
                goLeft2(90);
                status=2;
            }
            break;
        case 2:
            updateAngle(90);
            updateDistance();
            if(srednia()<=50){
                goRight2(90);
                status=3;
            }
            break;
        case 3:
            updateAngle(90);
            updateDistance();
            if(srednia()<=50){
                goRight2(90);
                status=4;
            }
            break;
        case 4:
            updateAngle(180);
            updateDistance();
            if(srednia()<=100){
                delay(500);
                goRight(90);
            }
            delay(1000);
            stop();
            break;
    }
}

void Wheels::goAvoiding2() {
    updateAngle((angle+15)%180);
    updateDistance();
    if(distance < 25) {
        if(angle < 90){
            goRight(30);
            updateAngle(45);
            right++;
        }else {
            goLeft(30);
            updateAngle(135);
            left++;
        }
    } else if(left > 0 || right > 0){
            if(left < right){
                goLeft(30);
                updateAngle(135);
                right--;
            } else {
                goRight(30);
                updateAngle(45);
                left--;
            }
    }else {
        if (cnt0 !=0 && cnt1 !=0){
            if(cnt0/cnt1>=1.2){
                goRight(15);
                Serial.println("1");
            }
            if(cnt0/cnt1<=1.1) {
                goLeft(15);
                Serial.println("2");
            }
        }
        setSpeed(200);
        forward();
    }
    Serial.print(cnt0);
    Serial.print(" ");
    Serial.println(cnt1);
}

void Wheels::goAvoiding() {
    int firstAvgDistance;
    int secondAvgDistance;
    int i=0;
    stop();
    setSpeed(200);
    forward();
    updateAngle(90);
    while(distance > 0){
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
                goRight2(30);
                updateAngle(75);
            }else{
                goLeft2(30);
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
    distances[i] = distance;
    i= (i+1)%5;
    printDistance();
    Serial.println(distance);
}

void Wheels::updateAngle(const uint8_t newangle){
    angle = newangle;
    serwo.write(angle);
    printAngle();
    delay(10);
}