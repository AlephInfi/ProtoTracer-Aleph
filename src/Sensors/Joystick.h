#pragma once

#include <Arduino.h>
#include "Math\Mathematics.h"
#include "Math\Vector2D.h"
#include "Filter\RunningAverageFilter.h"

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

    static RunningAverageFilter<25> FilterX;
    static RunningAverageFilter<25> FilterY;

    static RunningAverageFilter<25> FilterXout;
    static RunningAverageFilter<25> FilterYout;

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
    
        previousReadX = readX;
        previousReadY = readY;

        if(readX > xMax) xMax = readX;
        if(readY > yMax) yMax = readY;

        if(readX < minX) minX = readX;
        if(readY < minY) minY = readY;

        readX = Mathematics::Constrain(Mathematics::Map(readX, minX, xMax, -1.0f, 1.0f), -1.0f, 1.0f);
        readY = Mathematics::Constrain(Mathematics::Map(readY, minY, yMax, -1.0f, 1.0f), -1.0f, 1.0f);

        FilterXout.Filter(readX);
        FilterYout.Filter(readY);

        posPolar.X = Mathematics::Constrain((powf(readX, 2) + powf(readY, 2)), 0.0f, 1.0f);
        posPolar.Y = atan( readY / readX ) * 180.0f / PI;
        if(readX < 0.0f || (readY < 0.0f && readX < 0.0f)) posPolar.Y += 180.0f;
        else if(readY < 0.0f) posPolar.Y += 360.0f;

        posRectangular.X = readX;
        posRectangular.Y = readY;
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

    static uint16_t GetUnfilteredX(){
        return analogRead(X);
    }
    static uint16_t GetUnfilteredY(){
        return analogRead(Y);
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

RunningAverageFilter<25> Joystick::FilterX;
RunningAverageFilter<25> Joystick::FilterY;
RunningAverageFilter<25> Joystick::FilterXout;
RunningAverageFilter<25> Joystick::FilterYout;