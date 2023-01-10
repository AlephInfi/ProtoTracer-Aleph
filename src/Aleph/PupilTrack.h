#pragma once

#include "Math\Vector3D.h"
#include <Arduino.h>
#include "Sensors\Joystick.h"
#include "Sensors\MenuHandler.h"

class PupilTrack{
    private:
    static Vector3D basis;
    static uint8_t sensitivity;
    float horiz, vert, dil;
    uint16_t stickX, stickY;
    bool debug;
    elapsedMillis time;

    static Joystick joystick;

    public:
    Vector3D position;

    //joystick from radial menu, one button, basis x, y, z, sensitivity in percent 0-100
    void Initialize(uint8_t sensitivity, Vector3D basis = Vector3D(0.0f, 0.0f, 0.0f), bool debug = false){
        this->sensitivity = sensitivity;
        this->basis = basis;
        if(debug) this->debug = true;
    }

    //use non-menu joystick
    void Initialize(uint8_t sensitivity, uint8_t x, uint8_t y, Vector3D basis = Vector3D(0.0f, 0.0f, 0.0f), bool debug = false){
        this->joystick.Initialize(x, y, sensitivity);
        this->sensitivity = sensitivity;
        this->basis = basis;
        if(debug) this->debug = true;
    }

    void SampleData(){
        MenuHandler::CalculateJoystick();

        horiz = 0.5f + (MenuHandler::GetJoystickPosRect().X * 0.5f);
        vert = 0.5f + (MenuHandler::GetJoystickPosRect().Y * 0.5f);

        if(MenuHandler::GetButton2State()){
            dil = MenuHandler::GetJoystickPosPolar().Y;
            time = 0;
        }

        if(debug){
            Serial.print("Joystick: X pos = ");
            Serial.print(horiz);
            Serial.print(" | Y pos = ");
            Serial.print(vert);
            Serial.print(" | Dilation = ");
            Serial.print(dil);
            Serial.print(" | Time since last press (ms): ");
            if(time > 15000) Serial.println("over 15s!");
            else Serial.println(time);
        }
    }

    void Update(){
        position = Vector3D(basis.X + horiz, basis.Y + vert, basis.Z + dil);
    }
};

Vector3D PupilTrack::basis = Vector3D(0.0f, 0.0f, 0.0f);
uint8_t PupilTrack::sensitivity = 100;

Joystick PupilTrack::joystick;