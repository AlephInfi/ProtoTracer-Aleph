#include <Arduino.h>
#include <Stepper.h>
#include <math.h>
#include "EEPROMHandler.h"

/**
 * @brief 
 * sStepper class stores two motors, controlling one or two ears on either side of the protogen head.
 * Left stepper for left, right stepper for right. There are four general emotions which apply to 
 * defined faces, but is interchangeable if desired. Just use any four modes, or you can manually set
 * a rotation angle using rotate().
 * 
 * This stepper class is designed for use with the Teensy, and pins may be changed around as long as 
 * a free pin with PWM capabilities is available. It is recommended each stepper be driven seperately
 * by an external power supply such as a dedicated battery. You can drive your ears with any setup that 
 * uses a pulley system (as I have).
*/
class sStepper{
    private:

    // Pins for left and right stepper, respectively
    static uint8_t aa; //24
    static uint8_t bb; //25

    static uint8_t cc; //28
    static uint8_t dd; //29

    #define StepsInRevolution 200 // Steps in a revolution for NEMA-17 w/ A4988 board
    static uint8_t StepperSpeed; // Default rotation speed

    static Stepper Left;
    static Stepper Right;

    static bool bhappy, bmad, bscared, bsad, wiggle;
    static int16_t rSteps; //current location
    static int16_t lSteps; //current location

    public:
        enum Modes{
            happy,
            mad,
            scared,
            sad
        };

        void Initialize(uint8_t Motor1Pin1, uint8_t Motor1Pin2, uint8_t Motor2Pin1, uint8_t Motor2Pin2){
            this->aa = Motor1Pin1;
            this->bb = Motor1Pin2;
            this->cc = Motor2Pin1;
            this->dd = Motor2Pin2;

            Left.setSpeed(StepperSpeed);
            Right.setSpeed(StepperSpeed);
        }

        /** Rotate both steppers by "deg" degrees:
         * @param deg How many degrees you want to rotate.
         * @param t How much time it should take, milliseconds.
         * 
         * @brief 
         * Rotates the stepper an additional amount instead of setting to a specific rotation
         * tSteps = dy / dx
         */
        void rotate(int degl, int degr, uint16_t t){
            int ltSteps = (int)(StepsInRevolution * degl / 360); // Total steps left 
            int rtSteps = (int)(StepsInRevolution * degr / 360); // Total steps right
            Left.setSpeed(600 * ltSteps / t);
            Right.setSpeed(600 * rtSteps / t);
            if(degl != 0){
                Left.step(ltSteps);
                lSteps = ltSteps;
            }
            if(degr != 0){
                Right.step(rtSteps);
                rSteps = rtSteps;
            }
        }
        
        /**set to a specified rotation instead of just adding to current rotation
         * tSteps = (y2 - y1) / dx
         */
        void SetStep(int degl, int degr, uint16_t t){
            int ltSteps = (int)(StepsInRevolution * degl / 360) - lSteps; // Total steps left
            int rtSteps = (int)(StepsInRevolution * degr / 360) - rSteps; // Total steps right
            Left.setSpeed(600 * ltSteps / t);
            Right.setSpeed(600 * rtSteps / t);
            Left.step(ltSteps);
            lSteps = ltSteps;
            Right.step(rtSteps);
            rSteps = rtSteps;
        }
        
        //For use with calibration: sets steps taken for both motors to be 0. Used for initial calibration, does not rotate motors.
        void CalibrateRotation(){
            lSteps = 0;
            rSteps = 0;
        }

        /** Set to happy, mad, scared, or sad over 't' ms.
         * @param mode Choose from happy, mad, scared, sad
         */
        void emotion(Modes mode, uint16_t t){
            switch(mode){
                case happy: 
                    rotate(((int)(rSteps * 360 / StepsInRevolution) - 90), ((int)(rSteps * 360 / StepsInRevolution) + 90), t);
                case mad:
                    rotate(180, 180, t);
                case scared:
                    rotate(-180, -180, t);
                case sad:
                    rotate(360, 360, t);
            }
        }
};

uint8_t sStepper::aa;
uint8_t sStepper::bb;
uint8_t sStepper::cc;
uint8_t sStepper::dd;
uint8_t sStepper::StepperSpeed = 120;
Stepper sStepper::Left = Stepper(StepsInRevolution, aa, bb);
Stepper sStepper::Right = Stepper(StepsInRevolution, cc, dd);
bool sStepper::bhappy, sStepper::bmad, sStepper::bscared, sStepper::bsad, sStepper::wiggle = false;
int16_t sStepper::rSteps = 0;
int16_t sStepper::lSteps = 0;