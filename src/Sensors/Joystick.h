#pragma once

#include <Arduino.h>
#include "Filter\MinFilter.h"
#include "Filter\KalmanFilter.h"
#include "Math\Mathematics.h"
#include "Math\Vector2D.h"

class Joystick{
    private:

    static bool IsPolar;
    static uint8_t sensitivity;
    static float previousReadingX;
    static float previousReadingY;
    static float xMax;
    static float yMax;
    static float changeX;
    static float changeY;
    static float amplitudeX;
    static float amplitudeY;
    static float truncateX;
    static float truncateY;
    static uint32_t previousMillis;

    static uint8_t X; //X pin
    static uint8_t Y; //Y pin

    static MinFilter<50> MinF;
    static KalmanFilter<5> mv;
    static KalmanFilter<5> out;
    static KalmanFilter<5> Final;

    public:

    //X = magnitude, Y = angle (default)
    Vector2D posPolar = Vector2D(0.0f, 0.0f);

    //X = X position, Y = Y position (Calculate parameter set to false)
    Vector2D posRectangular = Vector2D(0.0f, 0.0f);

    void Initialize(uint8_t sensitivity){
        this->sensitivity = sensitivity;
        pinMode(X, INPUT);
        pinMode(Y, INPUT);
    }

    void SetSensitivity(float sensitivity){
        this->sensitivity = sensitivity;
    }

    void SetPins(uint8_t X, uint8_t Y){
        this->X = X;
        this->Y = Y;
    }

    uint8_t getPinX(){
        return this->X;
    }

    uint8_t getPinY(){
        return this->Y;
    }

    float readX(){
        if(digitalRead(X)) return analogRead(X);
        else return 0.0f;
    }

    float readY(){
        if(digitalRead(Y)) return analogRead(Y);
        else return 0.0f;
    }

    //updates both polar and rectangular form, just access the Vector2D objects designated posPolar and posRectangular
    void Calculate(){
        float readX = analogRead(X);
        float readY = analogRead(Y);

        if((readX >= 0.01f * sensitivity * xMax) || (changeX == 0.0f)) changeX = readX - previousReadingX;
        else if(changeX != 0.0f){
            float dTx = ((float)millis() - (float)previousMillis) / 1000.0f;
            float changeRateX = changeX / dTx;
            amplitudeX = mv.Filter(changeRateX);
            float minimumX = MinF.Filter(amplitudeX);
            float normalizedX = Mathematics::Constrain(amplitudeX - minimumX - 20000, 0.0f, 40000.0f);
            truncateX = out.Filter(normalizedX / 100.0f);
            previousReadingX = readX;
            previousMillis = millis();
        }
        
        if((readY >= 0.01f * sensitivity * yMax) || (changeY == 0.0f)) changeY = readY - previousReadingY;
        else if(changeY != 0.0f){
            float dTy = ((float)millis() - (float)previousMillis) / 1000.0f;
            float changeRateY = changeY / dTy;
            amplitudeY = mv.Filter(changeRateY);
            float minimumY = MinF.Filter(amplitudeY);
            float normalizedY = Mathematics::Constrain(amplitudeY - minimumY - 20000, 0.0f, 40000.0f);
            truncateY = out.Filter(normalizedY / 100.0f);
            previousReadingY = readY;
            previousMillis = millis();
        }

        if(readX > xMax) xMax = readX;
        if(readY > yMax) yMax = readY;

        posPolar.X = Mathematics::Constrain(sqrtf(powf(Mathematics::Constrain(fabs(truncateY), 0.0f, 1.0f), 2) + powf(Mathematics::Constrain(fabs(truncateX), 0.0f, 1.0f), 2)), 0.0f, 1.0f);
        posPolar.Y = atan(Mathematics::Constrain(truncateY, -1.0f, 1.0f) / (Mathematics::Constrain(truncateX, -1.0f, 1.0f))) * 180.0f / PI;
        if(truncateX < 0.0f || (truncateY < 0.0f && truncateX < 0.0f)) posPolar.Y += 180.0f;
        else if(truncateY < 0.0f) posPolar.Y += 360.0f;
        posPolar.Y = Mathematics::Constrain(posPolar.Y, 0.0f, 360.0f);

        posRectangular.X = Mathematics::Constrain(truncateX, -1.0f, 1.0f);
        posRectangular.Y = Mathematics::Constrain(truncateY, -1.0f, 1.0f);
    }
};

uint8_t Joystick::X; //X pin
uint8_t Joystick::Y; //Y pin

bool Joystick::IsPolar;
uint8_t Joystick::sensitivity = 100;
float Joystick::previousReadingX = 0.0f;
float Joystick::previousReadingY = 0.0f;
float Joystick::xMax = 0.0f;
float Joystick::yMax = 0.0f;
float Joystick::changeX;
float Joystick::changeY;
float Joystick::amplitudeX = 1.0f;
float Joystick::amplitudeY = 1.0f;
float Joystick::truncateX;
float Joystick::truncateY;
uint32_t Joystick::previousMillis;

MinFilter<50> Joystick::MinF = MinFilter<50>();
KalmanFilter<5> Joystick::mv = KalmanFilter<5>(0.2f);
KalmanFilter<5> Joystick::out = KalmanFilter<5>(0.2f);
KalmanFilter<5> Joystick::Final = KalmanFilter<5>();