#pragma once

#include "EEPROMHandler.h"
#include <IntervalTimer.h>
#include "Joystick.h"

// NOTE: layer count is currently only restricted to two (main menu with options, then options within main menu options) for simplicity.
class MenuHandler
{
private:

    // radial for Aleph
    static const uint8_t menuCount = 9; //change to 9 for ProtogenHUB75Animation / non-submenu, 4 for submenu
    static const uint8_t SubMenuCount = 8;

    // default variables w/ radial mixed in
    static IntervalTimer menuChangeTimer;
    static long previousMillisHold;
    static long previousMillisHold2;
    static uint8_t currentMenu;
    static uint8_t currentSubMenu;
    static uint8_t currentValue[menuCount];
    static uint8_t SubValue[SubMenuCount];
    static uint8_t currentSubValue[menuCount][SubMenuCount];
    static uint8_t maxValue[menuCount];
    static uint8_t maxSubValue[menuCount][SubMenuCount];
    static bool SubMenu[menuCount];
    static uint8_t LayerValue[menuCount];
    static uint8_t Layer; // what layer
    static uint8_t button1Pin;
    static bool holdingState;
    static bool holdingState2;
    static bool previousState;
    static bool previousState2;
    static bool previousJoystickState;

    static bool enable; // For radial, if true then menu is toggled on; see UpdateStateRadial()

    static uint8_t button2Pin;

    static long currentTime;
    static bool pinState;
    static bool pinState2;
    static long timeOn2;
    static long timeOn;
    static uint32_t updated;
    static uint32_t previousMillis;
    
    //radial submenu value
    static uint8_t CurrentSubMenuValue;
    static uint8_t MenuState;

public:
    static bool radial;
    static bool twobutton;

    static uint16_t holdingTime;

    static Joystick joystick;
    static bool button2RadialState;
    static uint16_t button2TimeOn;

private:
    static void UpdateButtonState()
    {
        currentTime = millis();
        pinState = digitalRead(button1Pin);
        timeOn = 0;

        if (pinState && !previousState)
        { // pin not pressed, not triggered -> reset time
            previousMillisHold = currentTime;
        }
        else if (pinState && previousState)
        { // pin not pressed, was triggered -> measure time
            timeOn = currentTime - previousMillisHold;
            previousState = false;
        }
        else if (!pinState)
        { // pin is pressed,
            previousState = true;
        }

        currentTime = millis();
        pinState2 = digitalRead(button2Pin);
        timeOn2 = 0;

        if (pinState2 && !previousState2)
        { // pin2 not pressed, not triggered -> reset time
            previousMillisHold2 = currentTime;
        }
        else if (pinState2 && previousState2)
        { // pin2 not pressed, was triggered -> measure time
            timeOn2 = currentTime - previousMillisHold2;
            previousState2 = false;
        }
        else if (!pinState2)
        { // pin2 is pressed
            previousState2 = true;
        }

        currentTime = millis();
    }

    // Regular - one button
    static void UpdateState()
    {
        UpdateButtonState();

        if (timeOn > holdingTime && pinState)
        {
            previousMillisHold = currentTime;
            MenuState = 0;

            EEPROMObj.WriteEEPROM(currentMenu, currentValue[currentMenu]);

            currentMenu += 1;
            if (currentMenu >= menuCount)
                currentMenu = 0;
        }
        else if (timeOn > 50 && pinState)
        {
            MenuState = 1;
            previousMillisHold = currentTime;

            currentValue[currentMenu] += 1;
            if (currentValue[currentMenu] >= maxValue[currentMenu])
                currentValue[currentMenu] = 0;
        }
    }

    // Regular - two buttons
    static void UpdateState1()
    {
        UpdateButtonState();

        // button 1 handles menu switch on and off, and through menus
        if (timeOn > holdingTime && pinState)
        {
            if (enable)
                enable = false;
            else if (!enable)
                enable = true;
        }
        else if (timeOn > 50 && pinState && enable)
        {
            previousMillisHold = currentTime;

            currentMenu += 1;
            if (currentMenu >= menuCount)
                currentMenu = 0;
        }

        if(enable){
            // button 2 handles Submenu increase (slow press; similar to increase Menu Value above), menu value switch (fast press)
            if (timeOn2 > holdingTime && pinState2){ // next value, submenu and menu are seperate because submenus are within menu values
                previousMillisHold2 = currentTime;

                currentSubMenu += 1;
                if (currentSubMenu >= SubMenuCount)
                    currentSubMenu = 1;
            }
            else if (timeOn2 > 50 && pinState2){ // increase value of submenu and/or menu selection (fast press)
                previousMillisHold2 = currentTime;

                if(!SubMenu[currentMenu]){
                    EEPROMObj.WriteEEPROM(currentMenu, currentValue[currentMenu]);

                    currentValue[currentMenu] += 1;
                    if (currentValue[currentMenu] >= maxValue[currentMenu])
                        currentValue[currentMenu] = 0;
                }
                else if(SubMenu[currentMenu]){
                    EEPROMObj.WriteEEPROM((menuCount + 1 + (SubMenuCount * currentMenu) + currentSubMenu), currentSubValue[currentMenu][currentSubMenu]);

                    currentSubValue[currentMenu][currentSubMenu] += 1;
                    if (currentSubValue[currentMenu][currentSubMenu] >= maxSubValue[currentMenu][currentSubMenu])
                        currentSubValue[currentMenu][currentSubMenu] = 0;
                }
            }
        }
    }

    // Radial - one button, one joystick, extra button used for specific handlers
    static void UpdateStateRadial()
    {
        UpdateButtonState();

        // button 1 handles menu toggle - long press = enable/disable, quick press = switch through menus // confirm value
        if ((timeOn > holdingTime) && pinState){
            previousMillisHold = currentTime;
            MenuState = 1;

            if (enable)
                enable = false;
            else if (!enable)
                enable = true;
        }

        else if ((timeOn > 50) && (pinState) && (enable)){
            previousMillisHold = currentTime;
            MenuState = 2;

            EEPROMObj.WriteEEPROM(currentMenu, currentValue[currentMenu]); // submenu selection

            currentMenu += 1;
            if (currentMenu >= menuCount)
                currentMenu = 0;
        }

        if (enable)
        {
            joystick.Calculate();

            //If button 2 pressed when magnitude greater than half & not inside a submenu, navigate to inside of the selected submenu. Submenu values not set yet
            if ((joystick.posPolar.X > 0.8f) && (previousJoystickState == false) && (SubMenu[currentMenu] == true) && (!pinState2)){
                MenuState = 3;
                previousJoystickState = true;
                CurrentSubMenuValue = round(joystick.posPolar.Y / 360.0f * maxValue[currentMenu]);
            }
            
            // If magnitude is greater than half, the submenu has been navigated into
            if ((joystick.posPolar.X > 0.8f) && (previousJoystickState == true) && (SubMenu[currentMenu] == true) && (!pinState2)){ 
                MenuState = 4;

                // Divide circle into sections based on how many values are available; 8 = 8 sections, etc
                // Selects any option instead of incrementing by 1
                EEPROMObj.WriteEEPROM((menuCount + 1 + (SubMenuCount * currentMenu) + currentSubMenu), currentSubValue[currentMenu][currentSubMenu]);

                CurrentSubMenuValue = round(joystick.posPolar.Y / 360.0f * maxSubValue[currentMenu][CurrentSubMenuValue]);
                currentSubValue[currentMenu][currentSubMenu] = CurrentSubMenuValue;

                if (currentSubValue[currentMenu][CurrentSubMenuValue] >= maxSubValue[currentMenu][CurrentSubMenuValue])
                    currentSubValue[currentMenu][CurrentSubMenuValue] = 0;
            }

            // For menu without submenu, just increment values up and down;
            // allows better control over e.g. many menu values like 10, which is unwieldy
            if((joystick.posPolar.X > 0.8f) && (SubMenu[currentMenu] == false)){
                MenuState = 5;

                if ((joystick.posPolar.Y >= 180) && (!pinState2)){
                    EEPROMObj.WriteEEPROM(currentMenu, currentValue[currentMenu]);

                    currentValue[currentMenu] += 1;
                    if (currentValue[currentMenu] >= maxValue[currentMenu])
                        currentValue[currentMenu] = 0;
                }
                if ((joystick.posPolar.Y < 180) && (!pinState2)){
                    EEPROMObj.WriteEEPROM(currentMenu, currentValue[currentMenu]);

                    currentValue[currentMenu] -= 1;
                    if (currentValue[currentMenu] <= 0)
                        currentValue[currentMenu] = maxValue[currentMenu];
                }
            }

            UpdateButtonState();

            if(joystick.posPolar.X < 0.8) previousJoystickState = false; 

            button2TimeOn = timeOn2;

            updated = millis();

            if((updated - previousMillis) >= 300){
                Serial.println("\n\n\n");
                Serial.print("\nButton 1 state: ");
                Serial.print(pinState);

                Serial.print(" | Button 2 state: ");
                Serial.println(pinState2);

                Serial.print("\nCurrent Menu: ");
                Serial.print(currentMenu);
                Serial.print(" Current Menu value: ");
                Serial.println(currentValue[currentMenu]);
                
                Serial.print("Current Submenu: ");
                Serial.print(currentSubMenu);
                Serial.print(" Current Submenu value: ");
                Serial.println(currentSubValue[currentMenu][currentSubMenu]);

                Serial.print("\nJoystick magnitude: ");
                Serial.print(joystick.posPolar.X);
                Serial.print(" | Joystick angle: ");
                Serial.println(joystick.posPolar.Y);

                Serial.print("Joystick raw X: ");
                Serial.print(analogRead(joystick.getPinX()));
                Serial.print(" | Joystick raw Y: ");
                Serial.println(analogRead(joystick.getPinY()));

                Serial.print("Joystick filtered X: ");
                Serial.print(joystick.posRectangular.X);
                Serial.print(" | Joystick filtered Y: ");
                Serial.println(joystick.posRectangular.Y);

                Serial.print("Max Joystick X: ");
                Serial.print(joystick.GetXMax());
                Serial.print(" | Max Joystick Y: ");
                Serial.print(joystick.GetYMax());
                Serial.print(" || Min Joystick X: ");
                Serial.print(joystick.GetXMin());
                Serial.print(" | Min Joystick Y: ");
                Serial.println(joystick.GetYMin());

                Serial.print("\nMenu State: ");
                Serial.println(MenuState);

                switch(MenuState){
                    case 1: 
                        Serial.println("Toggled menu on/off"); 
                        break;
                    case 2: 
                        Serial.println("Menu is on, switching through menus (layer 1)");
                        break;
                    case 3: 
                        Serial.println("Joystick has been moved enough once, selecting a submenu"); 
                        break;
                    case 4: 
                        Serial.println("Joystick has been moved enough twice, selecting submenu value");
                        break;
                    case 5: 
                        Serial.println("There are no submenus available, incrementing one-parameter menu value");
                        break;
                    case 0: 
                        Serial.println("No Menu State - Error!");
                        break;
                }
                MenuState = 255;
                previousMillis = updated;
            }
        }
    }

public:
    static void Begin()
    {
        if (radial)
            menuChangeTimer.begin(UpdateStateRadial, 1000);
        else if (!radial)
        {
            if (twobutton)
                menuChangeTimer.begin(UpdateState1, 1000);
            else if (!twobutton)
                menuChangeTimer.begin(UpdateState, 1000);
        }
    }

    static bool Initialize(uint8_t pin, uint16_t holdingTime)
    { // if true, eeprom needs set
        MenuHandler::twobutton = false;
        MenuHandler::holdingState = true;
        MenuHandler::previousState = false;

        pinMode(pin, INPUT_PULLUP);

        MenuHandler::button1Pin = pin;
        MenuHandler::holdingTime = holdingTime;

        for (uint8_t i = 0; i < menuCount; i++)
        {
            currentValue[i] = EEPROMObj.ReadEEPROM(i);
        }

        return EEPROMObj.ReadEEPROM(menuCount + 1) != 255;
    }

    static bool Initialize(uint8_t button1pin, uint8_t button2pin, uint16_t holdingTime)
    { // if true, eeprom needs set
        MenuHandler::twobutton = true;
        MenuHandler::holdingState = true;
        MenuHandler::previousState = false;

        pinMode(button1pin, INPUT_PULLUP);
        pinMode(button2pin, INPUT_PULLUP);

        MenuHandler::button1Pin = button1pin;
        MenuHandler::button2Pin = button2pin;
        MenuHandler::holdingTime = holdingTime;

        for (uint8_t i = 0; i < menuCount; i++)
        {
            currentValue[i] = EEPROMObj.ReadEEPROM(i); // set menu

            for (uint8_t ii = 0; ii < SubMenuCount; ii++)
            { // set sub menu within menu
                currentSubValue[currentMenu][currentSubMenu] = EEPROMObj.ReadEEPROM(menuCount + 1 + (i * SubMenuCount) + ii);
            }
        }

        return EEPROMObj.ReadEEPROM(menuCount + (SubMenuCount * menuCount) + 1) != 255; // 9 menus, 8 submenus in all 9, add one to check
    }

    static bool Initialize(uint8_t sensitivity, uint8_t X, uint8_t Y, uint8_t button1Pin, uint8_t button2Pin, uint16_t holdingTime)
    { // if true, eeprom needs set
        MenuHandler::radial = true;
        MenuHandler::holdingState = true;
        MenuHandler::previousState = false;

        pinMode(button1Pin, INPUT_PULLUP);
        pinMode(button2Pin, INPUT_PULLUP);

        joystick.Initialize(X, Y, sensitivity);

        MenuHandler::button1Pin = button1Pin;
        MenuHandler::button2Pin = button2Pin;
        MenuHandler::holdingTime = holdingTime;

        for (uint8_t i = 0; i < menuCount; i++)
        {
            currentValue[i] = EEPROMObj.ReadEEPROM(i); // set menu

            for (uint8_t ii = 0; ii < SubMenuCount; ii++)
            { // set sub menu within menu
                currentSubValue[currentMenu][currentSubMenu] = EEPROMObj.ReadEEPROM(menuCount + 1 + (i * SubMenuCount) + ii);
            }
        }

        return EEPROMObj.ReadEEPROM(menuCount + (SubMenuCount * menuCount) + 1) != 255;
    }

    static void SetDefaultValue(uint16_t menu, uint8_t value)
    {
        if (menu >= menuCount)
            return;

        currentValue[menu] = value;

        EEPROMObj.WriteEEPROM(menu, value);
    }

    static void SetInitialized()
    {
        EEPROMObj.WriteEEPROM(menuCount + 1, 0);
    }

    static void SetMenuMax(uint8_t menu, uint8_t maxValue)
    {
        if (menu >= menuCount)
            return;

        MenuHandler::maxValue[menu] = maxValue;
    }

    static void SetSubMenuMax(uint8_t menu, uint8_t submenu, uint8_t maxValue)
    {
        if (menu >= menuCount)
            return;

        MenuHandler::maxSubValue[menu][submenu] = maxValue;
    }

    // Establish if the layer has a submenu
    static void SetSubMenu(uint8_t menu, bool value)
    {
        if (menu >= menuCount)
            return;

        MenuHandler::SubMenu[menu] = value;
    }

    // Set the layer of the current menu
    static void SetLayer(uint8_t menu, uint8_t layer)
    {
        if (menu >= menuCount)
            return;

        MenuHandler::LayerValue[menu] = layer;
    }

    static void CalculateJoystick()
    {
        joystick.Calculate();
    }

    static uint8_t GetMenuValue(uint8_t menu)
    {
        return currentValue[menu];
    }

    static uint8_t GetSubMenuValue(uint8_t menu, uint8_t submenu)
    {
        return currentSubValue[menu][submenu];
    }

    static uint8_t GetCurrentMenu()
    {
        return currentMenu;
    }

    static uint8_t GetCurrentSubMenu()
    {
        return currentSubMenu;
    }

    static bool GetButton1State()
    {
        return holdingState;
    }

    static bool GetButton2State()
    {
        return holdingState2;
    }

    static Vector2D GetJoystickPosPolar()
    {
        return joystick.posPolar;
    }

    static Vector2D GetJoystickPosRect()
    {
        return joystick.posRectangular;
    }
};

long MenuHandler::currentTime;
bool MenuHandler::pinState;
bool MenuHandler::pinState2;

long MenuHandler::timeOn = 0;
long MenuHandler::timeOn2 = 0;

const uint8_t MenuHandler::menuCount;
const uint8_t MenuHandler::SubMenuCount;
IntervalTimer MenuHandler::menuChangeTimer;
long MenuHandler::previousMillisHold;
uint16_t MenuHandler::holdingTime;
long MenuHandler::previousMillisHold2;
uint8_t MenuHandler::currentMenu;
uint8_t MenuHandler::currentSubMenu;
uint8_t MenuHandler::currentValue[];
uint8_t MenuHandler::maxValue[menuCount];
uint8_t MenuHandler::maxSubValue[menuCount][SubMenuCount];
bool MenuHandler::SubMenu[menuCount];
uint8_t MenuHandler::currentSubValue[menuCount][SubMenuCount];
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
bool MenuHandler::previousJoystickState = false;

uint8_t MenuHandler::CurrentSubMenuValue;

bool MenuHandler::enable = true;

Joystick MenuHandler::joystick;
bool MenuHandler::button2RadialState = false;
uint16_t MenuHandler::button2TimeOn = 0;
uint8_t MenuHandler::MenuState = 255;
uint32_t MenuHandler::updated = 0;
uint32_t MenuHandler::previousMillis = 0;