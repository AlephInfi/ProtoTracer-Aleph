#pragma once

#include <Arduino.h>
#include "..\Controls\DampedSpring.h"
#include "..\Sensors\MenuHandler.h"
#include "..\Materials\Animated\RainbowNoise.h"
#include "..\Materials\Menu\TextEngine.h"

//built for Aleph's protogen model
class Menu{
public:
    enum MenuState{
        //4 Menus
        EarMotors,
        Faces,
        SettingsP1,
        SettingsP2,

        //Faces, then settings page 1, then settings page 2
        Sad,
        Happy,
        Mad,
        Scared,
        Doubt,
        Blush,

        Bright,
        AccentBright,
        Microphone,
        MicLevel,
        BoopSensor,
        SpectrumMirror,
        FaceSize,
        Color,

        PupilToggle
    };

private:
    static RainbowNoise material;
    static DampedSpring dampedSpringX;
    static DampedSpring dampedSpringShow;

    static FunctionGenerator fGenMatXMenu;
    static FunctionGenerator fGenMatYMenu;
    static FunctionGenerator fGenMatRMenu;

    static Vector2D size;
    static Vector2D position;
    static Vector2D positionOffset;
    static Vector2D rotationOffset;
    static float rotation;
    static float showMenuRatio;

    static const uint8_t menuCount = 14;
    static const uint8_t menuLength = 12;
    static TextEngine<2, menuLength * menuCount> textEngine;
    static uint8_t faceCount;
    static float wiggleRatio;
    
    static String line1;
    static String line2;

    static void SetMaxEntries(){
        MenuHandler::SetMenuMax(EarMotors, 2); //no submenus
        MenuHandler::SetMenuMax(Faces, faceCount);
        MenuHandler::SetMenuMax(SettingsP1, 8);
        MenuHandler::SetMenuMax(SettingsP2, 1);
        

        //Frames in each face
        MenuHandler::SetSubMenuMax(Faces, Sad, 10);
        MenuHandler::SetSubMenuMax(Faces, Happy, 10);
        MenuHandler::SetSubMenuMax(Faces, Mad, 10);
        MenuHandler::SetSubMenuMax(Faces, Scared, 10);
        MenuHandler::SetSubMenuMax(Faces, Doubt, 10);
        MenuHandler::SetSubMenuMax(Faces, Blush, 10);

        //Range of values for each setting
        MenuHandler::SetSubMenuMax(SettingsP1, Bright, 10);
        MenuHandler::SetSubMenuMax(SettingsP1, AccentBright, 10);
        MenuHandler::SetSubMenuMax(SettingsP1, Microphone, 2);
        MenuHandler::SetSubMenuMax(SettingsP1, MicLevel, 10);
        MenuHandler::SetSubMenuMax(SettingsP1, BoopSensor, 2);
        MenuHandler::SetSubMenuMax(SettingsP1, SpectrumMirror, 2);
        MenuHandler::SetSubMenuMax(SettingsP1, FaceSize, 4);
        MenuHandler::SetSubMenuMax(SettingsP1, Color, 11);

        MenuHandler::SetSubMenuMax(SettingsP2, PupilToggle, 2);
    }

    static void SetDefaultEntries(){
        MenuHandler::SetDefaultValue(Faces, 0);
        MenuHandler::SetDefaultValue(Bright, 3);
        MenuHandler::SetDefaultValue(AccentBright, 5);
        MenuHandler::SetDefaultValue(Microphone, 1);
        MenuHandler::SetDefaultValue(MicLevel, 5);
        MenuHandler::SetDefaultValue(BoopSensor, 1);
        MenuHandler::SetDefaultValue(SpectrumMirror, 0);
        MenuHandler::SetDefaultValue(FaceSize, 0);
        MenuHandler::SetDefaultValue(Color, 0);
        MenuHandler::SetDefaultValue(PupilToggle, 0);
        MenuHandler::SetDefaultValue(EarMotors, 0);

        MenuHandler::SetInitialized();
    }

    static void SetSubMenu(){
        MenuHandler::SetSubMenu(EarMotors, false);
        MenuHandler::SetSubMenu(Faces, true);
        MenuHandler::SetSubMenu(SettingsP1, true);
        MenuHandler::SetSubMenu(SettingsP2, true);
    }

public:
    static void Initialize(uint8_t faceCount, uint8_t sensitivity, uint8_t button1Pin, uint8_t button2Pin, uint8_t joystickXPin, uint8_t joystickYPin, uint16_t holdingTime, Vector2D size = Vector2D(240, 50)){
        Menu::faceCount = faceCount;

        dampedSpringX.SetConstants(1.0f, 0.5f);
        dampedSpringShow.SetConstants(1.0f, 0.5f);

        SetSize(size);

        textEngine.SetMaterial(&material);
        textEngine.SetPositionOffset(position);
        textEngine.SetBlinkTime(200);

        if (!MenuHandler::Initialize(sensitivity, joystickXPin, joystickYPin, button1Pin, button2Pin, holdingTime)){
            SetDefaultEntries();
        }

        SetMaxEntries();
        SetSubMenu();

        MenuHandler::Begin();
    }

    static void Initialize(uint8_t faceCount, uint8_t button1Pin, uint8_t button2Pin, uint16_t holdingTime, Vector2D size = Vector2D(240, 50)){
        Menu::faceCount = faceCount;

        dampedSpringX.SetConstants(1.0f, 0.5f);
        dampedSpringShow.SetConstants(1.0f, 0.5f);

        SetSize(size);

        textEngine.SetMaterial(&material);
        textEngine.SetPositionOffset(position);
        textEngine.SetBlinkTime(200);

        if (!MenuHandler::Initialize(button1Pin, button2Pin, holdingTime)){
            SetDefaultEntries();
        }

        SetMaxEntries();
        SetSubMenu();

        MenuHandler::Begin();
    }

    static Material* GetMaterial(){
        return &textEngine;
    }

    static void Update(){
        float target = (1.0f - float(MenuHandler::GetCurrentMenu() + 1) / float(menuCount)) * size.X + 25.0f;
        float xPosition = dampedSpringX.Calculate(target, 0.25f);
        float menuTarget = MenuHandler::GetCurrentMenu() != 0 ? 0.0f : 100.0f;

        showMenuRatio = dampedSpringShow.Calculate(menuTarget, 0.25f);
        material.Update(float(millis() % 15000) / 15000.0f);

        Menu::GenerateText();
        Menu::SetPosition(Vector2D(-xPosition + fGenMatXMenu.Update() * wiggleRatio, fGenMatYMenu.Update() * wiggleRatio + 40.0f + showMenuRatio));
        Menu::SetRotationOffset(Vector2D(200.0f / 2, 100.0f / 2));
        Menu::SetRotation(fGenMatRMenu.Update());
    }

    static void SetWiggleRatio(float wiggleRatio){
        Menu::wiggleRatio = wiggleRatio;
    }

    static void SetSize(Vector2D size){
        size.X = size.X * menuCount;

        Menu::size = size;

        textEngine.SetSize(size);
    }

    static void SetPosition(Vector2D position){
        Menu::position = position + positionOffset;
        textEngine.SetPositionOffset(Menu::position);
    }

    static void SetPositionOffset(Vector2D positionOffset){
        Menu::positionOffset = positionOffset;
    }

    static void SetRotationOffset(Vector2D rotationOffset){
        Menu::rotationOffset = rotationOffset;
        textEngine.SetRotationOffset(rotationOffset);
    }
    
    static void SetRotation(float rotation){
        Menu::rotation = rotation;
        textEngine.SetRotationAngle(rotation);
    }

    static char IntToBlink(char value){
        switch(value){
            case '0': return '[';
            case '1': return '\\';
            case '2': return ']';
            case '3': return '^';
            case '4': return '_';
            case '5': return '`';
            case '6': return '{';
            case '7': return '|';
            case '8': return '}';
            case '9': return '~';
            default: return ' ';
        }
    }

    static String GenerateLine(uint8_t options, uint8_t selection){
        String text;
        uint8_t spacing = options >= 5 ? 3 : (menuLength - options) / 2;

        for(uint8_t i = 0; i < spacing; i++){//pad spacing
            text += " ";
        }

        for(uint8_t i = 0; i < 5; i++){
            if(selection < 5 && i < options){
                char value = '0' + i;

                if(i == selection){
                    text += IntToBlink(value);
                }
                else{
                    text += value;
                }
            }
            else if (selection >= 5 && i + 5 < options){
                char value = '5' + i;

                if(i + 5 == selection){
                    text += IntToBlink(value);
                }
                else{
                    text += value;
                }
            }
        }
        
        while(text.length() < 12){
            text += " ";
        }

        return text;
    }


    static void GenerateText(){
        textEngine.SetText(0, line1, false);

        line2 = "            ";

        line2 += GenerateLine(10, MenuHandler::GetMenuValue(Bright));
        line2 += GenerateLine(10, MenuHandler::GetMenuValue(AccentBright));
        line2 += UseMicrophone() ? "   on OFF   " : "   ON off   ";
        line2 += GenerateLine(10, GetMicLevel());
        line2 += UseBoopSensor() ? "   on OFF   " : "   ON off   ";
        line2 += MirrorSpectrumAnalyzer() ? "   on OFF   " : "   ON off   ";
        line2 += GenerateLine(4, GetFaceSize());
        line2 += GenerateLine(10, GetFaceColor());
        line2 += GenerateLine(2, GetPupilStatus());
        line2 += GenerateLine(2, GetEarStatus());

        textEngine.SetText(1, line2, false);
    }

    static uint8_t GetFaceState(){
        return MenuHandler::GetMenuValue(Faces);
    }

    static uint8_t GetBrightness(){
        return (MenuHandler::GetSubMenuValue(SettingsP1, Bright) + 1) * 25;
    }

    static uint8_t GetAccentBrightness(){
        return (MenuHandler::GetSubMenuValue(SettingsP1, AccentBright) + 1) * 25;
    }

    static uint8_t UseMicrophone(){
        return MenuHandler::GetSubMenuValue(SettingsP1, Microphone);
    }

    static uint8_t GetMicLevel(){
        return MenuHandler::GetSubMenuValue(SettingsP1, MicLevel);
    }

    static uint8_t UseBoopSensor(){
        return MenuHandler::GetSubMenuValue(SettingsP1, BoopSensor);
    }

    static uint8_t MirrorSpectrumAnalyzer(){
        return MenuHandler::GetSubMenuValue(SettingsP1, SpectrumMirror);
    }

    static uint8_t GetFaceSize(){
        return MenuHandler::GetSubMenuValue(SettingsP1, FaceSize);
    }

    static uint8_t GetFaceColor(){
        return MenuHandler::GetSubMenuValue(SettingsP1, Color);
    }

    static uint8_t GetPupilStatus(){
        return MenuHandler::GetSubMenuValue(SettingsP2, PupilToggle);
    }

    static uint8_t GetEarStatus(){
        return MenuHandler::GetMenuValue(EarMotors);
    }

    static float ShowMenu(){
        return showMenuRatio / 100.0f;
    }
};

RainbowNoise Menu::material;
DampedSpring Menu::dampedSpringX;
DampedSpring Menu::dampedSpringShow;

FunctionGenerator Menu::fGenMatXMenu = FunctionGenerator(FunctionGenerator::Sine, -4.0f, 4.0f, 1.12f);
FunctionGenerator Menu::fGenMatYMenu = FunctionGenerator(FunctionGenerator::Sine, -4.0f, 4.0f, 1.73f);
FunctionGenerator Menu::fGenMatRMenu = FunctionGenerator(FunctionGenerator::Sine, -4.0f, 4.0f, 0.76f);

Vector2D Menu::size;
Vector2D Menu::position;
Vector2D Menu::positionOffset;
Vector2D Menu::rotationOffset;
float Menu::rotation;
float Menu::showMenuRatio;

const uint8_t Menu::menuCount;
const uint8_t Menu::menuLength;
TextEngine<2, 12 * Menu::menuCount> Menu::textEngine;
uint8_t Menu::faceCount;
float Menu::wiggleRatio = 1.0f;

//                    111111111111222222222222333333333333444444444444555555555555666666666666777777777777888888888888999999999999
String Menu::line1 = "               BRIGHT     SIDEBRT       MIC        LEVEL        BOOP        SPEC        SIZE       COLOR    ";
String Menu::line2 = " a b c d e f   12^45       12^45       ON off     123456|8     on OFF      ON off      12^45      123456|8  ";