#include <Arduino.h>
#include <Stepper.h>
#include <math.h>

class sStepper{
    private:

    #define aa 24
    #define bb 25
    #define cc 28
    #define dd 29

    #define ee 14
    #define ff 37
    #define gg 36
    #define hh 33

    #define StepsInRevolution 2025
    uint16_t StepperSpeed = 200;

    Stepper Left = Stepper(StepsInRevolution, aa, bb, cc, dd);
    Stepper Right = Stepper(StepsInRevolution, ee, ff, gg, hh);

    bool bhappy, bmad, bscared, bsad = false;

    public:
        enum Modes{
            happy,
            mad,
            scared,
            sad
        };

        uint16_t GetSpeed(){
            return StepperSpeed;
        }

        void setSpeeds(uint16_t speed){
            StepperSpeed = speed;
            Left.setSpeed(StepperSpeed);
            Right.setSpeed(StepperSpeed);
        }

        /** Rotate Stepper by "deg" degrees:
         * @param deg How many degrees you want to rotate.
         * @param t How much time it should take, milliseconds.
         * 
         * @brief 
         * Small steps being off can influence rotation of ears, causing damage. To solve this issue, the number of 
         * total steps taken is monitored so that at the end of a movement, the ears can move back to exactly 
         * where they started.
         */
        void rotate(int deg, uint16_t t){
            int tSteps = (int)((StepsInRevolution / 360) * deg); // Total steps. Not as important as the actual amount of steps taken
            int StepsTaken = 0;
            float ratio = t / tSteps;
            for(uint16_t T = 0; T < tSteps; T++){
                Left.step(1);
                Right.step(1);
                StepsTaken += 1;
                while((millis()) < (uint32_t)(10.0f * ratio)){}; // While millis() is less than the millisecond gap to next step
            }
        }

        /** Set to happy, mad, scared, or sad over 't' ms. If curve set to true, movement will be smooth. If not, linear rotation.
         * @param mode Choose from happy, mad, scared, sad
         */
        void emotion(Modes mode, uint16_t t){
            if(mode == happy){
                if(bhappy) return;
                rotate(45, t);
                bmad = false;
                bscared = false;
                bsad = false;
                bhappy = true;
            }
            else if(mode == mad){
                if(bmad) return;
                rotate(45, t);
                bmad = true;
                bscared = false;
                bsad = false;
                bhappy = false;
            }
            else if(mode == scared){
                if(bscared) return;
                rotate(45, t);
                bmad = false;
                bscared = true;
                bsad = false;
                bhappy = false;
            }
            else if(mode == sad){
                if(bsad) return;
                rotate(45, t);
                bmad = false;
                bscared = false;
                bsad = true;
                bhappy = false;
            }   
        }
};