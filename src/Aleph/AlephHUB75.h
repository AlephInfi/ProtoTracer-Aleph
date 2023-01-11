#pragma once

#include "Animation\Animation.h"
#include "Animation\KeyFrameTrack.h"
#include "Animation\EasyEaseAnimator.h"
#include "..\Objects\Background.h"
#include "..\Objects\LEDStripBackground.h"
#include "AlephBase.h"
#include "AlephL2.h"
#include "AlephDJLogo.h"
#include "..\Render\Scene.h"
#include "..\Signals\FunctionGenerator.h"
#include "..\Menu\Menu.h"
#include "..\Sensors\tofBoopSensor.h"
#include "PupilTrack.h"
#include "Sensors\EarSteppers.h"

#include "..\Materials\Animated\RainbowNoise.h"
#include "..\Materials\Animated\NoiseTemplate.h"
#include "..\Materials\Animated\LogoNoise.h"
#include "..\Materials\Animated\RainbowSpiral.h"
#include "..\Materials\Animated\SpectrumAnalyzer.h"
#include "..\Materials\Animated\EQGradient.h"
#include "..\Materials\Animated\AudioReactiveGradient.h"
#include "..\Materials\Animated\Oscilloscope.h"

#include "..\Materials\materialAnimator.h"

#include "Animation\AnimationTracks\BlinkTrack.h"

#include "..\Signals\FFTVoiceDetection.h"

#include "..\Sensors\MicrophoneFourier_MAX9814.h"

class AlephHUB75 : public Animation<4> {
private:

    const uint8_t numParamsL1 = 23 + 1; //23 parameters plus enum value 0, + 1 because other enums start at 0
    const uint8_t numParamsL2 = 23 + 1 + 4 + 1; //4 parameters plus enum value 0, + 1 because other enums start at 0

    AlephBase L1;
    AlephL2 L2;
    AlephDJLogo Logo;
    Background background;
    LEDStripBackground ledStripBackground;
    EasyEaseAnimator<35> eEA = EasyEaseAnimator<35>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    PupilTrack pupil;
    sStepper ears; // for Aleph
    
    //Materials
    RainbowNoise rainbowNoise;
    Noise AlephNoise;
    LogoNoise logoNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial orangeMaterial = SimpleMaterial(RGBColor(255, 165, 0));
    SimpleMaterial whiteMaterial = SimpleMaterial(RGBColor(255, 255, 255));
    SimpleMaterial greenMaterial = SimpleMaterial(RGBColor(0, 255, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    SimpleMaterial yellowMaterial = SimpleMaterial(RGBColor(255, 255, 0));
    SimpleMaterial purpleMaterial = SimpleMaterial(RGBColor(255, 0, 255));
    SimpleMaterial pinkMaterial = SimpleMaterial(RGBColor(252, 121, 224));
    SimpleMaterial blackMaterial = SimpleMaterial(RGBColor(0, 0, 0));
    
    RGBColor DJgrad[7] = {RGBColor(255, 0, 0), RGBColor(255, 100, 0), RGBColor(60, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 100), RGBColor(0, 50, 255), RGBColor(50, 0, 255)};
    GradientMaterial<7> DJMat = GradientMaterial<7>(DJgrad, 1.0f, false);

    MaterialAnimator<13> L1materialAnimator;
    MaterialAnimator<5> backgroundMaterial;
    
    EQ sA = EQ(Vector2D(200, 100), Vector2D(85, 50), true, false, false); 
    //SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(200, 100), Vector2D(85, 50), true, false, false); 
    AudioReactiveGradient aRG = AudioReactiveGradient(Vector2D(160, 160), Vector2D(0, 0), true, true); 
    Oscilloscope oSC = Oscilloscope(Vector2D(200, 50), Vector2D(0, 0));

    //Animation controllers
    BlinkTrack<1> blink;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 5.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 6.7f);
    FunctionGenerator fGenMatHue = FunctionGenerator(FunctionGenerator::Triangle, 0.0f, 360.0f, 17.3f);

    FunctionGenerator fGenMatXMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 1.1f);
    FunctionGenerator fGenMatYMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 2.7f);
    FunctionGenerator fGenMatRMenu = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 1.7f);

    BoopSensor boop;

    FFTVoiceDetection<128> voiceDetection;

    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    uint8_t offsetFaceIndSA = 50;
    uint8_t offsetFaceIndARG = 51;
    uint8_t offsetFaceIndOSC = 52;

    void LinkEasyEase(){
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::eMad), AlephBase::eMad, 15, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::eSad), AlephBase::eSad, 30, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::eScared), AlephBase::eScared, 10, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::eDoubt), AlephBase::eDoubt, 25, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::mSad), AlephBase::mSad, 45, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::eBlush), AlephBase::eBlush, 45, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::eBoop), AlephBase::eBoop, 10, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::eScared), AlephBase::eScared, 45, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::Blush), AlephBase::Blush, 3, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::eHeart), AlephBase::eHeart, 30, 0.0f, 1.0f);

        eEA.AddParameter(L2.GetMorphWeightReference(AlephL2::PupilVertical), AlephL2::PupilVertical + numParamsL1, 30, 0.5f, 1.0f);
        eEA.AddParameter(L2.GetMorphWeightReference(AlephL2::PupilHorizontal), AlephL2::PupilHorizontal + numParamsL1, 30, 0.5f, 1.0f);
        eEA.AddParameter(L2.GetMorphWeightReference(AlephL2::PupilDilate), AlephL2::PupilDilate + numParamsL1, 30, 0.0f, 1.0f);
        eEA.AddParameter(L2.GetMorphWeightReference(AlephL2::PupilOff), AlephL2::PupilOff + numParamsL1, 2, 0.0f, 1.0f);

        eEA.AddParameter(Logo.GetMorphWeightReference(AlephDJLogo::ShapeAnimation), AlephDJLogo::ShapeAnimation + numParamsL2, 30, 0.0f, 1.0f);
        eEA.AddParameter(Logo.GetMorphWeightReference(AlephDJLogo::Dissapate), AlephDJLogo::Dissapate + numParamsL2, 30, 0.0f, 1.0f);
        eEA.AddParameter(Logo.GetMorphWeightReference(AlephDJLogo::Explode), AlephDJLogo::Explode + numParamsL2, 30, 0.0f, 1.0f);

        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::m_EE), AlephBase::m_EE, 2, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::m_IH), AlephBase::m_IH, 2, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::m_DD), AlephBase::m_DD, 2, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::m_ER), AlephBase::m_ER, 2, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::m_CH), AlephBase::m_CH, 2, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::m_AH), AlephBase::m_AH, 2, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::m_OO), AlephBase::m_OO, 2, 0.0f, 1.0f);
        eEA.AddParameter(L1.GetMorphWeightReference(AlephBase::m_SS), AlephBase::m_SS, 2, 0.0f, 1.0f);

        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(L1.GetMorphWeightReference(AlephBase::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(AlephBase::Blush, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AlephBase::eSad, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(AlephBase::eBlush, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(AlephBase::eDoubt, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(AlephBase::eHeart, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(AlephBase::eMad, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(AlephBase::eScared, EasyEaseInterpolation::Cosine);

        eEA.SetInterpolationMethod(AlephDJLogo::ShapeAnimation, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(AlephDJLogo::Dissapate, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(AlephDJLogo::Explode, EasyEaseInterpolation::Cosine);

        eEA.SetInterpolationMethod(AlephBase::mSad, EasyEaseInterpolation::Cosine);
        
        eEA.SetInterpolationMethod(AlephBase::m_EE, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AlephBase::m_IH, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AlephBase::m_DD, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AlephBase::m_ER, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AlephBase::m_CH, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AlephBase::m_AH, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AlephBase::m_OO, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(AlephBase::m_SS, EasyEaseInterpolation::Linear);
    }

    void SetMaterialLayers(){
        L1materialAnimator.SetBaseMaterial(Material::Replace, &AlephNoise);
        L1materialAnimator.AddMaterial(Material::Replace, &orangeMaterial, 40, 0.0f, 1.0f);//layer 1
        L1materialAnimator.AddMaterial(Material::Replace, &whiteMaterial, 40, 0.0f, 1.0f);//layer 2
        L1materialAnimator.AddMaterial(Material::Replace, &greenMaterial, 40, 0.0f, 1.0f);//layer 3
        L1materialAnimator.AddMaterial(Material::Replace, &yellowMaterial, 40, 0.0f, 1.0f);//layer 4
        L1materialAnimator.AddMaterial(Material::Replace, &purpleMaterial, 40, 0.0f, 1.0f);//layer 5
        L1materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 6
        L1materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 7
        L1materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 8
        L1materialAnimator.AddMaterial(Material::Lighten, &rainbowNoise, 40, 0.35f, 1.0f);//layer 9
        L1materialAnimator.AddMaterial(Material::Replace, &AlephNoise, 40, 0.0f, 1.0f);//layer 10
        L1materialAnimator.AddMaterial(Material::Replace, &logoNoise, 40, 0.0f, 1.0f);//layer 11
        L1materialAnimator.AddMaterial(Material::Replace, &pinkMaterial, 40, 0.0f, 1.0f);//layer 1

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){
        ears.emotion(sStepper::happy, 700);
        eEA.AddParameterFrame(AlephL2::PupilOff + numParamsL1, 0.0f);
    }

    void Angry(){
        ears.emotion(sStepper::mad, 400);
        eEA.AddParameterFrame(AlephBase::eMad, 1.0f);
        eEA.AddParameterFrame(AlephBase::mSad, 1.0f);
        eEA.AddParameterFrame(AlephL2::PupilOff + numParamsL1, 0.0f);
        L1materialAnimator.AddMaterialFrame(redMaterial, 0.9f);
    }

    void Sad(){
        ears.emotion(sStepper::sad, 700);
        eEA.AddParameterFrame(AlephBase::eSad, 1.0f);
        eEA.AddParameterFrame(AlephBase::mSad, 1.0f);
        eEA.AddParameterFrame(AlephL2::PupilOff + numParamsL1, 0.0f);
        L1materialAnimator.AddMaterialFrame(blueMaterial, 0.9f);
    }

    void Boop(){
        ears.emotion(sStepper::happy, 700);
        eEA.AddParameterFrame(AlephBase::eBoop, 1.0f);
        eEA.AddParameterFrame(AlephBase::Blush, 1.0f);
        eEA.AddParameterFrame(AlephL2::PupilOff + numParamsL1, 1.0f);
        L1materialAnimator.AddMaterialFrame(pinkMaterial, 0.9f);
    }
    
    void Doubt(){
        ears.emotion(sStepper::sad, 1000);
        eEA.AddParameterFrame(AlephBase::eDoubt, 1.0f);
        eEA.AddParameterFrame(AlephBase::mSad, 0.7f);
        eEA.AddParameterFrame(AlephL2::PupilOff + numParamsL1, 0.0f);
    }
    
    void Frown(){
        ears.emotion(sStepper::sad, 1000);
        eEA.AddParameterFrame(AlephBase::mSad, 1.0f);
        eEA.AddParameterFrame(AlephL2::PupilOff + numParamsL1, 0.0f);
    }

    void Cute(){
        ears.emotion(sStepper::happy, 500);
        eEA.AddParameterFrame(AlephBase::eBlush, 1.0f);
        eEA.AddParameterFrame(AlephL2::PupilOff + numParamsL1, 1.0f);
        L1materialAnimator.AddMaterialFrame(pinkMaterial, 0.9f);
    }

    void HeartEyes(){
        ears.emotion(sStepper::happy, 500);
        eEA.AddParameterFrame(AlephBase::eHeart, 1.0f);
        eEA.AddParameterFrame(AlephL2::PupilOff + numParamsL1, 1.0f);
        L1materialAnimator.AddMaterialFrame(pinkMaterial, 0.9f);
    }

    void SpectrumAnalyzerFace(float ratio){
        eEA.AddParameterFrame(offsetFaceIndSA, 1.0f);

        eEA.AddParameterFrame(AlephDJLogo::ShapeAnimation + numParamsL2, ratio);
        backgroundMaterial.AddMaterialFrame(sA, offsetFaceSA);
    }

    void AudioReactiveGradientFace(){
        eEA.AddParameterFrame(offsetFaceIndARG, 1.0f);

        backgroundMaterial.AddMaterialFrame(aRG, offsetFaceARG);
    }

    void OscilloscopeFace(){
        eEA.AddParameterFrame(offsetFaceIndOSC, 1.0f);

        backgroundMaterial.AddMaterialFrame(oSC, offsetFaceOSC);
    }

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            eEA.AddParameterFrame(AlephBase::m_SS, MicrophoneFourier::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourier::GetCurrentMagnitude() > 0.075f){
                voiceDetection.Update(MicrophoneFourier::GetFourierFiltered(), MicrophoneFourier::GetSampleRate());
        
                eEA.AddParameterFrame(AlephBase::m_EE, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(AlephBase::m_IH, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(AlephBase::m_DD, voiceDetection.GetViseme(voiceDetection.UH));
                eEA.AddParameterFrame(AlephBase::m_ER, voiceDetection.GetViseme(voiceDetection.AR));
                eEA.AddParameterFrame(AlephBase::m_CH, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(AlephBase::m_AH, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(AlephBase::m_OO, voiceDetection.GetViseme(voiceDetection.OO));
            }
        }
    }

    void SetMaterialColor(){
        switch(Menu::GetFaceColor()){
            case 1: L1materialAnimator.AddMaterialFrame(redMaterial, 0.8f); break;
            case 2: L1materialAnimator.AddMaterialFrame(orangeMaterial, 0.8f); break;
            case 3: L1materialAnimator.AddMaterialFrame(whiteMaterial, 0.8f); break;
            case 4: L1materialAnimator.AddMaterialFrame(greenMaterial, 0.8f); break;
            case 5: L1materialAnimator.AddMaterialFrame(blueMaterial, 0.8f); break;
            case 6: L1materialAnimator.AddMaterialFrame(yellowMaterial, 0.8f); break;
            case 7: L1materialAnimator.AddMaterialFrame(purpleMaterial, 0.8f); break;
            case 8: L1materialAnimator.AddMaterialFrame(rainbowNoise, 0.8f); break;
            case 9: L1materialAnimator.AddMaterialFrame(AlephNoise, 0.8f); break;
            default: break;
        }
    }

public:
    AlephHUB75() {
        scene.AddObject(L1.GetObject());
        scene.AddObject(L2.GetObject());
        scene.AddObject(Logo.GetObject());
        scene.AddObject(background.GetObject());
        scene.AddObject(ledStripBackground.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        L1.GetObject()->SetMaterial(&L1materialAnimator);
        L2.GetObject()->SetMaterial(&blackMaterial);
        Logo.GetObject()->SetMaterial(&logoNoise);
        background.GetObject()->SetMaterial(&backgroundMaterial);
        ledStripBackground.GetObject()->SetMaterial(&L1materialAnimator);

        //ears.Initialize(24, 25, 28, 29);
        boop.Initialize(10);
        pupil.Initialize(80, 27, 26); //uses pins from menu if called without defining joystick pins (26, 27)

        MicrophoneFourier::Initialize(15, 8000, 50.0f, 120.0f); //8KHz sample rate, 50dB min, 120dB max default
    }

    //Initialize dependent objects: menu, joystick calibration, ear calibration
    void Initialize(){
        //Menu::Initialize(6, 80, 30, 31, 26, 27, 500); //Radial
        Menu::Initialize(10, 30, 31, 500);//7 is number of faces

        //ears.CalibrateRotation();
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    /**
     * Layers:
     * 1: Base, including blush
     * 2: Pupil
     */
    Object3D* GetObject(uint8_t layer){
        if(layer == 1) return L1.GetObject();
        else if(layer == 2) return L2.GetObject();
    }

    void Update(float ratio) override {
        L1.Reset();
        L2.Reset();
        Logo.Reset();

        float xOffset = fGenMatXMove.Update();
        float yOffset = fGenMatYMove.Update();
 
        Menu::Update();
 
        SetMaterialColor();

        bool isBooped = Menu::UseBoopSensor() ? boop.isBooped() : 0;

        Serial.print(isBooped);

        uint8_t mode = Menu::GetFaceState();//change by button press
 
        MicrophoneFourier::Update();
        sA.SetHueAngle(ratio * 360.0f * 4.0f);
        sA.SetMirrorYState(Menu::MirrorSpectrumAnalyzer());
        sA.SetFlipYState(!Menu::MirrorSpectrumAnalyzer());
 
        aRG.SetRadius((xOffset + 2.0f) * 2.0f + 25.0f);
        aRG.SetSize(Vector2D((xOffset + 2.0f) * 10.0f + 50.0f, (xOffset + 2.0f) * 10.0f + 50.0f));
        aRG.SetHueAngle(ratio * 360.0f * 8.0f);
        aRG.SetRotation(ratio * 360.0f * 2.0f);
        aRG.SetPosition(Vector2D(80.0f + xOffset * 4.0f, 48.0f + yOffset * 4.0f));

        oSC.SetSize(Vector2D(200.0f, 100.0f));
        oSC.SetHueAngle(ratio * 360.0f * 8.0f);
        oSC.SetPosition(Vector2D(100.0f, 50.0f));
        
        voiceDetection.SetThreshold(map(Menu::GetMicLevel(), 0, 10, 1000, 50));

        UpdateFFTVisemes();
        
        pupil.SampleData();

        if (isBooped && mode != 6){
            Boop();
        }
        else{
            if (mode == 0){
                //Serial.print("0"); 
                Default();
            }
            else if (mode == 1){
                //Serial.print("1"); 
                Angry();
            } 
            else if (mode == 2){
                //Serial.print("2"); 
                Doubt();
            } 
            else if (mode == 3){
                //Serial.print("3"); 
                Frown();
            }   
            else if (mode == 4){
                //Serial.print("4"); 
                Sad();
            } 
            else if (mode == 5){
                //Serial.print("5"); 
                Cute();
            } 
            else if (mode == 6){
                //Serial.print("6"); 
                HeartEyes();
            } 
            else if (mode == 7){ 
                //Serial.print("7"); 
                aRG.Update(MicrophoneFourier::GetFourierFiltered());
                AudioReactiveGradientFace();
            }
            else if (mode == 8){
                //Serial.print("8"); 
                oSC.Update(MicrophoneFourier::GetSamples());
                OscilloscopeFace();
            } 
            else {
                //Serial.print("spectrum");
                sA.Update(MicrophoneFourier::GetFourierFiltered());
                SpectrumAnalyzerFace(acosf(ratio));
            }
        }

        pupil.Update();
        UpdateKeyFrameTracks();

        //L1.SetMorphWeight(NukudeFace::BiggerNose, 1.0f);
        //L1.SetMorphWeight(NukudeFace::MoveEye, 1.0f);

        eEA.AddParameterFrame(AlephL2::PupilHorizontal + numParamsL1, pupil.position.X);
        eEA.AddParameterFrame(AlephL2::PupilVertical + numParamsL1, -pupil.position.Y);

        eEA.Update();
        L1.Update();
        L2.Update();
        Logo.Update();

        float menuRatio = Menu::ShowMenu();

        rainbowNoise.Update(ratio);
        AlephNoise.Update(ratio);
        logoNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        L1materialAnimator.Update();
        backgroundMaterial.Update();
        
        L1.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 0.0f));
        L2.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 0.0f));

        uint8_t faceSize = Menu::GetFaceSize();
        float scale = menuRatio * 0.6f + 0.4f;
        float xShift = (1.0f - menuRatio) * 60.0f;
        float yShift = (1.0f - menuRatio) * 20.0f + offsetFaceSA * -100.0f + offsetFaceARG * -100.0f + offsetFaceOSC * -100.0f;
        float adjustFacePos = float(4 - faceSize) * 5.0f;
        float adjustFaceX = float(faceSize) * 0.05f;
        
        L1.GetObject()->GetTransform()->SetPosition(Vector3D(105.0f + xOffset - xShift + adjustFacePos, 51.5f + yOffset + yShift, 0.0f));
        L1.GetObject()->GetTransform()->SetScale(Vector3D(-45.0f + adjustFaceX, 45.0f, 1.0f).Multiply(scale));
        L2.GetObject()->GetTransform()->SetPosition(Vector3D(105.0f + xOffset - xShift + adjustFacePos, 51.5f + yOffset + yShift, -10.0f));
        L2.GetObject()->GetTransform()->SetScale(Vector3D(-45.0f + adjustFaceX, 45.0f, 1.0f).Multiply(scale));
        Logo.GetObject()->GetTransform()->SetPosition(Vector3D(55.0f + xOffset - xShift + adjustFacePos, 171.5f + yOffset + yShift, -10.0f));
        Logo.GetObject()->GetTransform()->SetScale(Vector3D(-2.0f + adjustFaceX, 2.0f, 1.0f).Multiply(scale));

        L1.GetObject()->UpdateTransform();
        L2.GetObject()->UpdateTransform();
        Logo.GetObject()->UpdateTransform();
    }
};