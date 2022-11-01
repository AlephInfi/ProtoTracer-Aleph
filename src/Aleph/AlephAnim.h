#pragma once

#include "Animation\Animation.h"
#include "Animation\KeyFrameTrack.h"
#include "Animation\EasyEaseAnimator.h"
#include "FaceShapeNew.h"
#include "PupilObj.h"
#include "Render\Scene.h"
#include "..\Materials\GradientMaterial.h"
#include "..\Materials\SimplexNoise.h"
#include "..\Math\FunctionGenerator.h"
#include "..\Materials\NormalMaterial.h"

#include "..\Materials\CombineMaterial.h"

//#include "..\Sensors\TOFsensor"
#include "..\Sensors\EarSteppers.h"
#include "..\Sensors\MicrophoneSimple.h"

class AlephAnim : public Animation {

    private:

    float colorMix;

    FaceShape Aleph;
    PupilObj Pupil;
    EasyEaseAnimator eEA = EasyEaseAnimator(20, EasyEaseAnimator::Overshoot, 1.0f, 0.5f);

    RGBColor noiseSpectrum[4] = {RGBColor(0, 255, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
    GradientMaterial gNoiseMat = GradientMaterial(4, noiseSpectrum, 2.0f, false);
    SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);
    
    RGBColor gradientSpectrum[2] = {RGBColor(130, 255, 130), RGBColor(130, 200, 255)};
    GradientMaterial gradientMat = GradientMaterial(2, gradientSpectrum, 350.0f, false);

    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial blackMaterial = SimpleMaterial(RGBColor(0, 0, 0));
    
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    
    //default face material with gradient + simplex noise
    Material* noiseMaterials[2] = {&gradientMat, &sNoise};
    CombineMaterial noiseMaterial = CombineMaterial(CombineMaterial::Lighten, 2, noiseMaterials);

    //for combining angry face with default material
    Material* faceMaterials[2] = {&redMaterial, &noiseMaterial};
    CombineMaterial faceMaterial = CombineMaterial(CombineMaterial::Replace, 2, faceMaterials);

    Material* PupilMaterials[2] = {&blackMaterial, &faceMaterial};
    CombineMaterial PupilMaterial = CombineMaterial(CombineMaterial::Replace, 2, PupilMaterials);

    KeyFrameTrack eBlk = KeyFrameTrack(10, 0.0f, 1.0f, 14, KeyFrameTrack::Cosine);
    KeyFrameTrack mOpen = KeyFrameTrack(10, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    /*KeyFrameTrack mClos = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack eSad = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack mSad = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack eSurpr = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack eMad = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack eSqnt = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack eCute = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack mNeut = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    */

    KeyFrameTrack pupilH = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack pupilV = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack pupilD = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack pupilS = KeyFrameTrack(10, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);

    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);

    SimpleMaterial sMat = SimpleMaterial(RGBColor(0, 0, 0));
    GradientMaterial gMat = GradientMaterial(6, gradientSpectrum, 150.0f, true);

    MicrophoneSimple mic = MicrophoneSimple(22);
    bool talk = true;

    sStepper Ears;

    void LinkEasyEase(){
        eEA.AddParameter(Aleph.GetMorphWeightReference(FaceShape::eSad), FaceShape::eSad, 10, 0.0f);
        eEA.AddParameter(Aleph.GetMorphWeightReference(FaceShape::mSad), FaceShape::mSad, 10, 0.0f);
        eEA.AddParameter(Aleph.GetMorphWeightReference(FaceShape::eSurpr), FaceShape::eSurpr, 10, 0.0f);
        eEA.AddParameter(Aleph.GetMorphWeightReference(FaceShape::eMad), FaceShape::eMad, 10, 0.0f);
        eEA.AddParameter(Aleph.GetMorphWeightReference(FaceShape::eSqnt), FaceShape::eSqnt, 10, 0.0f);
        eEA.AddParameter(Aleph.GetMorphWeightReference(FaceShape::eCute), FaceShape::eCute, 10, 0.0f);
        eEA.AddParameter(Aleph.GetMorphWeightReference(FaceShape::mNeut), FaceShape::mNeut, 10, 0.0f);

        eEA.AddParameter(Pupil.GetMorphWeightReference(PupilObj::horiz), PupilObj::horiz, 15, 0.0f);
        eEA.AddParameter(Pupil.GetMorphWeightReference(PupilObj::vert), PupilObj::vert, 15, 0.0f);
        eEA.AddParameter(Pupil.GetMorphWeightReference(PupilObj::dilation), PupilObj::dilation, 5, 0.0f);
        eEA.AddParameter(Pupil.GetMorphWeightReference(PupilObj::size), PupilObj::size, 5, 0.0f);

        eEA.AddParameter(&colorMix, 99, 10, 0.0f);
    }

    void LinkParam(){
        eBlk.AddParameter(Aleph.GetMorphWeightReference(FaceShape::eBlk));
        mOpen.AddParameter(Aleph.GetMorphWeightReference(FaceShape::mOpen));
        /*
        eSad.AddParameter(Aleph.GetMorphWeightReference(FaceShape::eSad));
        mSad.AddParameter(Aleph.GetMorphWeightReference(FaceShape::mSad));
        eSurpr.AddParameter(Aleph.GetMorphWeightReference(FaceShape::eSurpr));
        eMad.AddParameter(Aleph.GetMorphWeightReference(FaceShape::eMad));
        */

        pupilD.AddParameter(Pupil.GetMorphWeightReference(PupilObj::dilation));
        pupilH.AddParameter(Pupil.GetMorphWeightReference(PupilObj::horiz));
        pupilS.AddParameter(Pupil.GetMorphWeightReference(PupilObj::size));
        pupilV.AddParameter(Pupil.GetMorphWeightReference(PupilObj::vert));
    }

    void eBlkKFrames(){
        eBlk.AddKeyFrame(0.0f, 0.0f);
        eBlk.AddKeyFrame(2.75f, 0.0f);
        eBlk.AddKeyFrame(3.0f, 1.0f);
        eBlk.AddKeyFrame(3.25f, 0.0f);
        eBlk.AddKeyFrame(8.5f, 0.0f);
        eBlk.AddKeyFrame(8.75f, 1.0f);
        eBlk.AddKeyFrame(9.0f, 0.0f);
        eBlk.AddKeyFrame(15.25f, 0.0f);
        eBlk.AddKeyFrame(15.5f, 1.0f);
        eBlk.AddKeyFrame(15.75f, 0.0f);
        eBlk.AddKeyFrame(16.5f, 0.0f);
        eBlk.AddKeyFrame(16.75f, 1.0f);
        eBlk.AddKeyFrame(17.0f, 0.0f);
    }

    void eBlkSqntKFrames(){
        eBlk.AddKeyFrame(0.0f, 0.0f);
        eBlk.AddKeyFrame(2.75f, 0.0f);
        eBlk.AddKeyFrame(3.0f, 1.0f);
        eBlk.AddKeyFrame(3.25f, 0.0f);
        eBlk.AddKeyFrame(8.5f, 0.0f);
        eBlk.AddKeyFrame(8.75f, 1.0f);
        eBlk.AddKeyFrame(9.0f, 0.0f);
        eBlk.AddKeyFrame(15.25f, 0.0f);
        eBlk.AddKeyFrame(15.5f, 1.0f);
        eBlk.AddKeyFrame(15.75f, 0.0f);
        eBlk.AddKeyFrame(16.5f, 0.0f);
        eBlk.AddKeyFrame(16.75f, 1.0f);
        eBlk.AddKeyFrame(17.0f, 0.0f);
    }

    void mOpenKFrames(){
        mOpen.AddKeyFrame(0.0f, 0.0f);
        mOpen.AddKeyFrame(1.5f, 1.0f);
        mOpen.AddKeyFrame(4.0f, 0.0f);
    }

    void mOpenSmolKFrames(){
        mOpen.AddKeyFrame(0.0f, 0.0f);
        mOpen.AddKeyFrame(1.5f, 0.2f);
        mOpen.AddKeyFrame(4.0f, 0.0f);
    }

/*
    void mCloseKFrames(float t){
        mClos.AddKeyFrame(0.0f, 1.0f);
        mClos.AddKeyFrame((t/2), 0.5f);
        mClos.AddKeyFrame(t, 0.0f);
    }

    void eSadKFrames(){
        eSad.AddKeyFrame(0.0f, 0.0f);
        eSad.AddKeyFrame(0.1f, 0.1f);
        eSad.AddKeyFrame(0.2f, 0.2f);
        eSad.AddKeyFrame(0.3f, 0.3f);
        eSad.AddKeyFrame(0.4f, 0.4f);
        eSad.AddKeyFrame(0.5f, 0.5f);
        eSad.AddKeyFrame(0.6f, 0.6f);
        eSad.AddKeyFrame(0.7f, 0.7f);
        eSad.AddKeyFrame(0.8f, 0.8f);
        eSad.AddKeyFrame(0.9f, 0.9f);
        eSad.AddKeyFrame(1.0f, 1.0f);
    }

    void mSadKFrames(){
        mSad.AddKeyFrame(0.0f, 0.0f);
        mSad.AddKeyFrame(0.166667f, 0.0f);
        mSad.AddKeyFrame(0.333333f, 0.0f);
        mSad.AddKeyFrame(0.5f, 0.0f);
        mSad.AddKeyFrame(0.666666f, 0.0f);
        mSad.AddKeyFrame(0.833333f, 0.0f);
        mSad.AddKeyFrame(1.0f, 1.0f);
    }

    void eSurprKFrames(){
        eSurpr.AddKeyFrame(0.0f, 0.0f);
        eSurpr.AddKeyFrame(0.15f, 0.2);
        eSurpr.AddKeyFrame(0.3f, 0.4f);
        eSurpr.AddKeyFrame(0.45f, 0.6f);
        eSurpr.AddKeyFrame(0.6f, 0.8f);
        eSurpr.AddKeyFrame(0.75f, 1.0f);
    }

    void eMadKFrames(){
        eMad.AddKeyFrame(0.0f, 0.0f);
        eMad.AddKeyFrame(0.15f, 0.2);
        eMad.AddKeyFrame(0.3f, 0.4f);
        eMad.AddKeyFrame(0.45f, 0.6f);
        eMad.AddKeyFrame(0.6f, 0.8f);
        eMad.AddKeyFrame(0.75f, 1.0f);
    }
*/

    void pupilHKFrames(){
        pupilH.AddKeyFrame(0.0f, 0.7f);
        pupilH.AddKeyFrame(4.0f, 0.85f);
        pupilH.AddKeyFrame(8.0f, 0.7f);
    }

    void pupilVKFrames(){
        pupilV.AddKeyFrame(0.0f, 0.0f);
        pupilV.AddKeyFrame(2.0f, 0.2f);
        pupilV.AddKeyFrame(5.0f, 0.0f);
    }

    void pupilSKFrames(){
        pupilS.AddKeyFrame(0.0f, 0.0f);
        pupilS.AddKeyFrame(2.0f, 1.0f);
        pupilS.AddKeyFrame(4.0f, 0.0f);
    }

    void pupilDKFrames(){
        pupilS.AddKeyFrame(0.0f, 0.0f);
        pupilS.AddKeyFrame(2.0f, 1.0f);
        pupilS.AddKeyFrame(4.0f, 0.0f);
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(FaceShape::eSad, EasyEaseAnimator::Cosine);
        eEA.SetInterpolationMethod(FaceShape::mSad, EasyEaseAnimator::Cosine);
        eEA.SetInterpolationMethod(99, EasyEaseAnimator::Cosine);
    }

    public:

    AlephAnim() : Animation(2){
        scene->AddObject(Aleph.GetObject());
        scene->AddObject(Pupil.GetObject());

        LinkEasyEase();
        LinkParam();

        eBlkKFrames();
        mOpenKFrames();
        /*
        eSadKFrames();
        mSadKFrames();
        eSurprKFrames();
        eMadKFrames();
        */

        pupilHKFrames();
        pupilVKFrames();

        ChangeInterpolationMethods();

        Aleph.GetObject()->SetMaterial(&faceMaterial);
        Pupil.GetObject()->SetMaterial(&PupilMaterial);
        noiseMaterial.SetFirstLayerOpacity(0.4f); 
    }

    void UpdateKeyFrameTracks(){
        eBlk.Update();
        mOpen.Update();

        pupilH.Update();
        pupilV.Update();
    }

    void Default(){
        Ears.emotion(sStepper::Modes::happy, 100);

        Aleph.Reset();
        Pupil.Reset();

        eBlk.Play();
        mOpen.Play();

        pupilH.Play();
        pupilV.Play();

        eEA.AddParameterFrame(99, 0.0f);

        talk = true;
    }

    //emotions will go here

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    // Retrieve object of count ct in an animation. Only for animations using more than one object.
    Object3D* GetObject(int ct){
        if(ct == 1) return Aleph.GetObject();
        if(ct == 2) return Pupil.GetObject();
    }

    void Update(float ratio) override { 
        float micIn = mic.Update();

        Default();

        UpdateKeyFrameTracks();

        if(talk) Aleph.SetMorphWeight(FaceShape::mOpen, micIn);

        //Example of Face with slight movement, scaling, and rotation
        eEA.Update();
        Aleph.Update();
        Pupil.Update();

        float x = 0.5f * sinf(ratio * 3.14159f / 180.0f * 360.0f * 2.0f);
        float y = 0.5f * cosf(ratio * 3.14159f / 180.0f * 360.0f * 3.0f);
        
        float linSweep = ratio > 0.5f ? 1.0f - ratio : ratio;
        float sShift = linSweep * 0.002f + 0.005f;

        gNoiseMat.SetGradientPeriod(0.5f + linSweep * 6.0f);
        gNoiseMat.HueShift(ratio * 360 * 2);
        sNoise.SetScale(Vector3D(sShift, sShift, sShift));
        sNoise.SetZPosition(x * 4.0f);
        
        faceMaterial.SetFirstLayerOpacity(colorMix);
        PupilMaterial.SetFirstLayerOpacity(1.0f);

        //Serial.println(colorMix);

        float defXr = 0.0f;
        float defYr = 180.0f;
        float defZr = 195.0f;

        float defXp = 120.0f;
        float defYp = 45.0f;
        float defZp = 600.0f;

        float defXs = 5.4f;
        float defYs = 3.8f;
        float defZs = 0.4f;
        
        Aleph.GetObject()->GetTransform()->SetRotation(Vector3D(defXr, defYr, defZr));
        Pupil.GetObject()->GetTransform()->SetRotation(Vector3D(defXr, defYr, defZr));

        Aleph.GetObject()->GetTransform()->SetPosition(Vector3D(x + defXp, y + defYp, defZp));
        Pupil.GetObject()->GetTransform()->SetPosition(Vector3D(x + defXp, y + defYp, defZp + 10.0f));
        
        Aleph.GetObject()->GetTransform()->SetScale(Vector3D(defXs, defYs, defZs));
        Pupil.GetObject()->GetTransform()->SetScale(Vector3D(defXs, defYs, defZs));

        Aleph.GetObject()->UpdateTransform();
        Pupil.GetObject()->UpdateTransform();

        /*
        //Objects visibility can be enabled and disabled at any point before rasterizing to change its visibility
        Aleph.GetObject()->Enable();//

        //Objects can be moved to a coordinate or translated by a vector
        Aleph.GetObject()->GetTransform()->SetPosition(Vector3D(35.0f, 20.0f, 600.0f));

        //Objects can be rotated with by any rotation object (quaternion is preferred) and about any coordinate or center
        Aleph.GetObject()->GetTransform()->SetRotation(Vector3D(sinf(ratio * 3.14159f / 180.0f * 1440.0f) * 1.0f, sinf(ratio * 3.14159f / 180.0f * 720.0f) * 1.0f, 1));

        //Objects can be scaled by origin, center, and at a point
        float s = 1.0f + sin(ratio * 3.14159f / 180.0f * 2160.0f) * 0.03f;
        Aleph.GetObject()->GetTransform()->SetScale(Vector3D(s, s, s));
        */

    }
};