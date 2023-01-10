#pragma once

#include "AnimatedMaterial.h"
#include "..\..\Signals\FunctionGenerator.h"
#include "..\..\Materials\GradientMaterial.h"
#include "..\..\Materials\SimplexNoise.h"

class Noise : public AnimatedMaterial{
private:
    FunctionGenerator fGenMatGradient = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 6.0f);
    RGBColor noiseSpectrum[3] = {RGBColor(69, 255, 118), RGBColor(31, 35, 255), RGBColor(31, 240, 255)};
    GradientMaterial<3> gNoiseMat = GradientMaterial<3>(noiseSpectrum, 2.0f, false);
    SimplexNoise<3> sNoise = SimplexNoise<3>(3, &gNoiseMat);
    float simplexNoiseDepth = 0.0f;

public:
    Noise(){}

    void Update(float ratio){
        float sweep = fGenMatGradient.Update();
        float sShift = sweep * 0.004f + 0.005f;

        simplexNoiseDepth += 0.001f;

        gNoiseMat.SetGradientPeriod(0.5f + sweep * 12.0f);
        //gNoiseMat.HueShift(ratio * 360 * 2);
        sNoise.SetScale(Vector3D(sShift, sShift, sShift));
        sNoise.SetZPosition(simplexNoiseDepth);
    }

    Material* GetMaterial(){
        return &sNoise;
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        return sNoise.GetRGB(position, normal, uvw);
    }
};



