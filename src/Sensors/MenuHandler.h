#pragma once

#include "EEPROMHandler.h"
#include <IntervalTimer.h>
#include "Joystick.h"

//NOTE: layer count is currently only restricted to two (main menu with options, then options within main menu options) for simplicity.
class MenuHandler{
private:
    static const uint8_t menuCount = 9; //including any options inside of submenus
    static const uint8_t SubMenuCount = 8; //number of options in a submenu
    static IntervalTimer menuChangeTimer;
    static long previousMillisHold;
    static long previousMillisHold2;
    static uint16_t holdingTime;
    static uint16_t holdingTime2;
    static uint8_t currentMenu;
    static uint8_t currentValue[menuCount];
    static uint8_t currentSubValue[SubMenuCount];
    static uint8_t maxValue[menuCount];
    static bool SubMenu[menuCount];
    static uint8_t LayerValue[menuCount];
    static uint8_t Layer; //what layer
    static uint8_t button1Pin;
    static bool holdingState;
    static bool holdingState2;
    static bool previousState;
    static bool previousState2;

    static bool radial;
    static bool twobutton;
    static uint8_t button2Pin;

    static Joystick joystick;

 //Regular - one button
    static void UpdateState(){
        long currentTime = millis();
        bool pinState = digitalRead(button1Pin);
        
        long timeOn = 0;
        
        if(pinState && !previousState){//pin not pressed, not triggered -> reset time
            previousMillisHold = currentTime;
        }
        else if (pinState && previousState){//pin not pressed, was triggered -> measure time
            timeOn = currentTime - previousMillisHold;
            previousState = false;
        }
        else if (!pinState){//pin is pressed,
            previousState = true;
        }
        
        if(timeOn > holdingTime && pinState){
            previousMillisHold = currentTime;

            EEPROMObj.WriteEEPROM(currentMenu, currentValue[currentMenu]);

            currentMenu += 1;
            if (currentMenu >= menuCount) currentMenu = 0;
        } else if(timeOn > 50 && pinState){
            previousMillisHold = currentTime;

            currentValue[currentMenu] += 1;
            if (currentValue[currentMenu] >= maxValue[currentMenu]) currentValue[currentMenu] = 0;
        }
    }

//Regular - two buttons
    static void UpdateState1(){
        long currentTime = millis();
        bool pinState = digitalRead(button1Pin);
        bool pinState2 = digitalRead(button2Pin);
        
        long timeOn = 0;
        long timeOn2 = 0;
        
        if(pinState && !previousState){//pin not pressed, not triggered -> reset time
            previousMillisHold = currentTime;
        }
        else if (pinState && previousState){//pin not pressed, was triggered -> measure time
            timeOn = currentTime - previousMillisHold;
            previousState = false;
        }
        else if (!pinState){//pin is pressed,
            previousState = true;
        }

        if(pinState2 && !previousState2){//pin2 not pressed, not triggered -> reset time
            previousMillisHold2 = currentTime;
        }
        else if (pinState2 && previousState2){//pin2 not pressed, was triggered -> measure time
            timeOn2 = currentTime - previousMillisHold2;
            previousState2 = false;
        }
        else if (!pinState2){//pin2 is pressed,
            previousState2 = true;
        }
        
        //button 1
        if(timeOn > holdingTime && pinState){
            previousMillisHold = currentTime;

            EEPROMObj.WriteEEPROM(currentMenu, currentValue[currentMenu]);

            currentMenu += 1;
            if (currentMenu >= menuCount) currentMenu = 0;
        } else if(timeOn > 50 && pinState){
            previousMillisHold = currentTime;

            currentValue[currentMenu] += 1;
            if (currentValue[currentMenu] >= maxValue[currentMenu]) currentValue[currentMenu] = 0;
        }

        //button 2
        if(timeOn2 > holdingTime2 && pinState2){
            previousMillisHold2 = currentTime;

            EEPROMObj.WriteEEPROM(currentMenu, currentValue[currentMenu]);

            currentMenu += 1;
            if (currentMenu <= 0) currentMenu = menuCount;
        } else if(timeOn2 > 50 && pinState2){
            previousMillisHold2 = currentTime;

            currentValue[currentMenu] += 1;
            if (currentValue[currentMenu] >= maxValue[currentMenu]) currentValue[currentMenu] = 0;
        }
    }

 //Radial - two buttons, one joystick
 /** To do
  * 2 button control and layer selections
 */
    static void UpdateStateRadial(){
        long currentTime = millis();
        bool pinState1 = digitalRead(button1Pin);
        bool pinState2 = digitalRead(button2Pin);

        joystick.Calculate();
        
        long timeOn = 0;
        long timeOn2 = 0;
        
        if(pinState1 && !previousState){//pin not pressed, not triggered -> reset time
            previousMillisHold = currentTime;
        }
        else if (pinState1 && previousState){//pin not pressed, was triggered -> measure time
            timeOn = currentTime - previousMillisHold;

            previousState = false;
        }
        else if (!pinState1){//pin is pressed,
            previousState = true;
        }
        
        if(timeOn > 50 && pinState1){
            previousMillisHold = currentTime;

            EEPROMObj.WriteEEPROM(currentMenu, currentValue[currentMenu]);

            currentMenu += 1;
            if (currentMenu >= menuCount) currentMenu = 0;
        } else if(pinState1){ 
            previousMillisHold = currentTime;
            if((joystick.posPolar.X >= 50.0f) && (joystick.posPolar.Y >= (currentValue[currentMenu] * 360.0f / maxValue[currentMenu]))){
                currentValue[currentMenu] += 1;
            }
            if(currentValue[currentMenu] >= maxValue[currentMenu]) currentValue[currentMenu] = 0;
        }

        //if the current menu has a submenu, then navigate inside its submenu
        if(SubMenu[currentMenu] == true){
            if((joystick.posPolar.X >= 50.0f) && (joystick.posPolar.Y >= (currentSubValue[currentMenu] * 360.0f / SubMenuCount))){
                currentSubValue[currentMenu] += 1;
            }
            if(currentSubValue[currentMenu] >= SubMenuCount) currentSubValue[currentMenu] = 0;
        }

        //exit submenu if inside one, if on main menu then go back a page
        if(pinState2 && !previousState2){//pin not pressed, not triggered -> reset time
            previousMillisHold2 = currentTime;
        }
        else if (pinState2 && previousState2){//pin not pressed, was triggered -> measure time
            timeOn2 = currentTime - previousMillisHold2;

            previousState2 = false;
        }
        else if(!pinState2){//pin is pressed,
            previousState2 = true;
            if(Layer <= 0){
                Layer = 0;
                currentMenu--;
            } 
            else Layer--;
        }
    }

public:
    static void Begin(){
        if(radial) menuChangeTimer.begin(UpdateStateRadial, 1000);
        else if(!radial){
            if(twobutton) menuChangeTimer.begin(UpdateState1, 1000);
            else if(!twobutton) menuChangeTimer.begin(UpdateState, 1000);
        } 
    }

    static bool Initialize(uint8_t pin, uint16_t holdingTime){//if true, eeprom needs set
        MenuHandler::twobutton = false;
        MenuHandler::holdingState = true;
        MenuHandler::previousState = false;

        pinMode(pin, INPUT_PULLUP);

        MenuHandler::button1Pin = pin;
        MenuHandler::holdingTime = holdingTime;

        for (uint8_t i = 0; i < menuCount; i++){
            currentValue[i] = EEPROMObj.ReadEEPROM(i);
        }

        return EEPROMObj.ReadEEPROM(menuCount + 1) != 255;
    }

    static bool Initialize(uint8_t button1pin, uint8_t button2pin, uint16_t holdingTime){//if true, eeprom needs set
        MenuHandler::twobutton = true;
        MenuHandler::holdingState = true;
        MenuHandler::previousState = false;

        pinMode(button1pin, INPUT_PULLUP);
        pinMode(button2pin, INPUT_PULLUP);

        MenuHandler::button1Pin = button1pin;
        MenuHandler::button2Pin = button2pin;
        MenuHandler::holdingTime = holdingTime;

        for (uint8_t i = 0; i < menuCount; i++){
            currentValue[i] = EEPROMObj.ReadEEPROM(i);
        }

        return EEPROMObj.ReadEEPROM(menuCount + 1) != 255;
    }

    static bool Initialize(uint8_t sensitivity, uint8_t X, uint8_t Y, uint8_t button1Pin, uint8_t button2Pin, uint16_t holdingTime){//if true, eeprom needs set
        MenuHandler::radial = true;
        MenuHandler::holdingState = true;
        MenuHandler::previousState = false;

        pinMode(button1Pin, INPUT_PULLUP);
        pinMode(button2Pin, INPUT_PULLUP);

        joystick.SetPins(X, Y);
        joystick.Initialize(sensitivity);

        MenuHandler::button1Pin = button1Pin;
        MenuHandler::holdingTime = holdingTime;

        for (uint8_t i = 0; i < menuCount; i++){
            currentValue[i] = EEPROMObj.ReadEEPROM(i);
        }

        return EEPROMObj.ReadEEPROM(menuCount + 1) != 255;
    }

    static void SetDefaultValue(uint16_t menu, uint8_t value){
        if(menu >= menuCount) return;

        currentValue[menu] = value;

        EEPROMObj.WriteEEPROM(menu, value);
    }

    static void SetInitialized(){
        EEPROMObj.WriteEEPROM(menuCount + 1, 0);
    }

    static void SetMenuMax(uint8_t menu, uint8_t maxValue){
        if(menu >= menuCount) return;

        MenuHandler::maxValue[menu] = maxValue;
    }

    //Establish if the layer has a submenu
    static void SetSubMenu(uint8_t menu, bool value){
        if(menu >= menuCount) return;

        MenuHandler::SubMenu[menu] = value;
    }

    //Set the layer of the current menu
    static void SetLayer(uint8_t menu, uint8_t layer){
        if(menu >= menuCount) return;

        MenuHandler::LayerValue[menu] = layer;
    }
    
    static void CalculateJoystick(){
        joystick.Calculate();
    }

    static uint8_t GetMenuValue(uint8_t menu){
        return currentValue[menu];
    }
    
    static uint8_t GetCurrentMenu(){
        return currentMenu;
    }
    
    static bool GetButton1State(){
        return holdingState;
    }

    static bool GetButton2State(){
        return holdingState2;
    }

    static Vector2D GetJoystickPosPolar(){
        return joystick.posPolar;
    }

    static Vector2D GetJoystickPosRect(){
        return joystick.posRectangular;
    }
};

const uint8_t MenuHandler::menuCount;
const uint8_t MenuHandler::SubMenuCount;
IntervalTimer MenuHandler::menuChangeTimer;
long MenuHandler::previousMillisHold;
uint16_t MenuHandler::holdingTime;
long MenuHandler::previousMillisHold2;
uint16_t MenuHandler::holdingTime2;
uint8_t MenuHandler::currentMenu;
uint8_t MenuHandler::currentValue[];
uint8_t MenuHandler::maxValue[menuCount];
bool MenuHandler::SubMenu[menuCount];
uint8_t MenuHandler::currentSubValue[SubMenuCount];
uint8_t MenuHandler::LayerValue[menuCount];
uint8_t MenuHandler::Layer = 0;

uint8_t MenuHandler::button1Pin;
bool MenuHandler::radial = false;
bool MenuHandler::twobutton = false;
uint8_t MenuHandler::button2Pin;

bool MenuHandler::holdingState = true;
bool MenuHandler::holdingState2 = true;
bool MenuHandler::previousState = false;
bool MenuHandler::previousState2 = false;

Joystick MenuHandler::joystick;