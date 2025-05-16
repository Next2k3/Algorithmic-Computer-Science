/* 
 * prosta implementacja klasy obsługującej 
 * silniki pojazdu za pośrednictwem modułu L298
 *
 * Sterowanie odbywa się przez:
 * 1)  powiązanie odpowiednich pinów I/O Arduino metodą attach() 
 * 2)  ustalenie prędkości setSpeed*()
 * 3)  wywołanie funkcji ruchu
 *
 * TODO:
 *  - zabezpieczenie przed ruchem bez attach()
 *  - ustawienie domyślnej prędkości != 0
 */


#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#ifndef Wheels_h
#define Wheels_h


#define TRIG A3
#define ECHO A2

#define SERVO 9

extern Servo serwo;

extern LiquidCrystal_I2C lcd;

extern volatile int cnt0, cnt1;

class Wheels {
    public: 
        Wheels();
        /*
         *  pinForward - wejście "naprzód" L298
         *  pinBack    - wejście "wstecz" L298
         *  pinSpeed   - wejście "enable/PWM" L298
         */
        void attachRight(int pinForward, int pinBack, int pinSpeed);
        void attachLeft(int pinForward, int pinBack, int pinSpeed);
        void attach(int pinRightForward, int pinRightBack, int pinRightSpeed,
                    int pinLeftForward, int pinLeftBack, int pinLeftSpeed);
        void forward();
        void forwardLeft();
        void forwardRight();
        void back();
        void backLeft();
        void backRight();
        void stop();
        void stopLeft();
        void stopRight();
        void goforward(const uint8_t);
        void goBack(const uint8_t);
        void goforward2(const uint8_t);
        void goBack2(const uint8_t);
        void goLeft(const uint8_t);
        void goRight(const uint8_t);
        void goAvoiding();

        void setSpeed(uint8_t);
        void setSpeedRight(uint8_t);
        void setSpeedLeft(uint8_t);

        void updateDistance();
        void updateAngle(uint8_t);

        void printDistance();
        void printAngle();
        void printDistanceAndAngle();
        uint8_t angle = 0;
    private: 
        int pinsRight[3];
        int pinsLeft[3];
        uint8_t distance = 0;
        uint8_t speedLeft = 0;
        uint8_t speedRight = 0;
        int distances[5];
        bool isStop = false;
        
};



#endif
