#pragma once

#include <iostream>
#include <Arduino.h>
#include "Controllers\SmartMatrixHUB75.h"

class Pupil{
    private:

    float pSize = 0.5f;
    float posH = 0.5f;
    float posV = 0.5f;

    public:

    void Initialize(float dilation){

    };

    //dimensions 11 length, 16 height
    const uint8_t original[176] = {
                        0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,
                        0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,
                        0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,
                        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
                        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
                        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
                        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
                        0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,
                        0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,
                        0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0 
                        };
    uint8_t pupil[176] = {
                        0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,
                        0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,
                        0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,
                        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
                        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
                        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
                        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
                        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
                        0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,
                        0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,
                        0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0 
                        };

    //set values and array back to original
    void reset(){
        pSize = 0.5f;
        posH = 0.5f;
        posV = 0.5f;

        for(int i=0; i<176; i++){
            pupil[i] = original[i];
        }
    }

//Updates the pupil location and dilation over set time. Format: pupil(<horizontal pos>, <vertical pos>, <dilation>, <time in milliseconds>)
    void pupil(float h, float v, float d, uint16_t t){

    };

//Updates pupil location based on joystick. 
    void pupilSense(){
/*setup:
    1. get sensor values
    2. convert raw to left and right, rough float value
    3. pupils need to be in line, not mirrored
    4. sync L/R on sensor with Horiz/vert pupil
*/
    };

    //Dilation MUST be an integer, 1-5 with 5 being fully dilated
    void pDil(int d, uint16_t t){
        for(int c=0; c<d; c++){
            unsigned long pt = millis(); //present time
            unsigned long st = 0; //stored time (past)

            if(pt-st >= (int)(t/d)){
                st = pt;
                //increase dilation
                for(int i=1; i<176; i+=(d+11)){
                    if(pupil[i] = 1)pupil[i] = 0;
                }
                pt == 0;
            }
        }
    };
};

