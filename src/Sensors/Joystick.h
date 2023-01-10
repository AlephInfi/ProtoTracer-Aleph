#pragma once

#include <Arduino.h>
#include "Math\Mathematics.h"
#include "Math\Vector2D.h"
#include "Filter\KalmanFilter.h"

class Joystick{
    private:

    bool IsPolar;
    uint8_t sensitivity = 100;

    static float xMax;
    static float yMax;

    static float minX;
    static float minY;

    static uint8_t X; //X pin
    static uint8_t Y; //Y pin

    static float previousReadX;
    static float previousReadY;
    static long previousMillis;

    static long IntervalMillis;
    static long Interval2Millis;
    static long Interval3Millis;

    static KalmanFilter<10> FilterX;
    static KalmanFilter<10> FilterY;

    public:

    static Vector2D posPolar; //X = magnitude, Y = angle (default)
    static Vector2D posRectangular; //X = X position, Y = Y position (Calculate parameter set to false)

    //Sensitivity from 0-100
    void Initialize(uint8_t X, uint8_t Y, uint8_t sensitivity){
        if(sensitivity > 100) sensitivity = 100;
        this->sensitivity = sensitivity;
        this->X = X;
        this->Y = Y;
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

    //avoid including innaccurate readings through Kalman Filter
    static void Calculate(){
        float readX = FilterX.Filter(analogRead(X));
        float readY = FilterY.Filter(analogRead(Y));

        float dT = millis() - previousMillis;
        float dX = 0;
        float dY = 0;

        if(millis() - Interval3Millis >= 100){
            float tempX = FilterX.Filter(analogRead(X));
            float tempY = FilterY.Filter(analogRead(Y));
            dX = (tempX - previousReadX);
            dY = (tempY - previousReadY);

            Interval3Millis = millis();
        }
    
        previousMillis = millis();
        previousReadX = readX;
        previousReadY = readY;

        if(millis() - IntervalMillis > 1000){
            if((dX < 50) && (dY < 50)){
                if(readX > xMax) xMax = readX;
                if(readY > yMax) yMax = readY;

                if(readX < minX) minX = readX;
                if(readY < minY) minY = readY;
            }

            IntervalMillis = millis();
        }

        if(dX < 50.0f || dY < 50.0f){ 
            readX = Mathematics::Constrain(Mathematics::Map(readX, minX, xMax, -1.0f, 1.0f), -1.0f, 1.0f);
            readY = Mathematics::Constrain(Mathematics::Map(readY, minY, yMax, -1.0f, 1.0f), -1.0f, 1.0f);

            posPolar.X = Mathematics::Constrain((powf(readX, 2) + powf(readY, 2)), 0.0f, 1.0f);
            posPolar.Y = atan( readY / readX ) * 180.0f / PI;
            if(readX < 0.0f || (readY < 0.0f && readX < 0.0f)) posPolar.Y += 180.0f;
            else if(readY < 0.0f) posPolar.Y += 360.0f;

            posRectangular.X = readX;
            posRectangular.Y = readY;
        }
    }

    static float GetXMax(){
        return xMax;
    }

    static float GetYMax(){
        return yMax;
    }

    static float GetXMin(){
        return minX;
    }

    static float GetYMin(){
        return minY;
    }

    static float GetUnfilteredX(){
        return previousReadX;
    }
    static float GetUnfilteredY(){
        return previousReadY;
    }
};

uint8_t Joystick::X; //X pin
uint8_t Joystick::Y; //Y pin

Vector2D Joystick::posPolar = Vector2D(0.0f, 0.0f);
Vector2D Joystick::posRectangular = Vector2D(0.0f, 0.0f);

float Joystick::xMax = 3000.0f;
float Joystick::yMax = 3000.0f;

float Joystick::minX = 2000.0f;
float Joystick::minY = 2000.0f;

float Joystick::previousReadX = 0.0f;
float Joystick::previousReadY = 0.0f;
long Joystick::previousMillis = 0;
long Joystick::IntervalMillis = 0;
long Joystick::Interval2Millis = 0;
long Joystick::Interval3Millis = 0;

KalmanFilter<10> Joystick::FilterX;
KalmanFilter<10> Joystick::FilterY;