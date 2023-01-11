#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "..\Morph\Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class AlephDJLogo{
public:
    enum Morphs {
        ShapeAnimation,
        Dissapate,
        Explode
    };

private:
    Vector3D basisVertices[56] = {Vector3D(0.6626f,0.3637f,0.0000f),Vector3D(9.0019f,-12.6651f,0.0000f),Vector3D(-3.8176f,12.2120f,0.0000f),Vector3D(2.5950f,2.7915f,0.0000f),Vector3D(-1.7967f,3.8768f,0.0000f),Vector3D(3.9587f,-4.2071f,0.0000f),Vector3D(6.6473f,-3.3292f,0.0000f),Vector3D(-0.0546f,5.1245f,0.0000f),Vector3D(-8.7742f,-15.7050f,0.0000f),Vector3D(9.4125f,-37.9154f,0.0000f),Vector3D(-22.1968f,10.6048f,0.0000f),Vector3D(-5.1517f,-11.3088f,0.0000f),Vector3D(-17.7111f,-4.4877f,0.0000f),Vector3D(0.0848f,-23.7006f,0.0000f),Vector3D(3.8847f,-21.8319f,0.0000f),Vector3D(-14.6340f,-2.0369f,0.0000f),Vector3D(-9.2342f,-20.1815f,0.0000f),Vector3D(-8.5909f,-17.7371f,0.0000f),Vector3D(-13.7064f,-22.1583f,0.0000f),Vector3D(-11.8510f,-18.3587f,0.0000f),Vector3D(-8.9793f,-22.0204f,0.0000f),Vector3D(-8.6345f,-24.5244f,0.0000f),Vector3D(-7.4076f,-19.8309f,0.0000f),Vector3D(-4.5189f,-22.1141f,0.0000f),Vector3D(-12.2663f,-26.9670f,0.0000f),Vector3D(-9.8157f,-27.5865f,0.0000f),Vector3D(-13.0173f,-24.6537f,0.0000f),Vector3D(-10.5066f,-22.8673f,0.0000f),Vector3D(-13.5528f,-29.2101f,0.0000f),Vector3D(-13.5218f,-31.5406f,0.0000f),Vector3D(-10.5298f,-28.7851f,0.0000f),Vector3D(-12.0094f,-30.7122f,0.0000f),Vector3D(-17.9923f,-29.8993f,0.0000f),Vector3D(-14.3390f,-40.4463f,0.0000f),Vector3D(-20.1165f,-18.6669f,0.0000f),Vector3D(-16.1686f,-28.6603f,0.0000f),Vector3D(-20.0918f,-24.7607f,0.0000f),Vector3D(-16.0328f,-33.8727f,0.0000f),Vector3D(-14.0234f,-33.8450f,0.0000f),Vector3D(-18.6823f,-24.1851f,0.0000f),Vector3D(-15.3025f,-22.9800f,0.0000f),Vector3D(-17.0529f,-23.3566f,0.0000f),Vector3D(-14.5497f,-27.8889f,0.0000f),Vector3D(-16.3212f,-24.8819f,0.0000f),Vector3D(-1.9629f,1.0899f,0.0000f),Vector3D(-4.2246f,-0.8571f,0.0000f),Vector3D(0.8959f,-2.5196f,0.0000f),Vector3D(-4.0338f,-3.2582f,0.0000f),Vector3D(2.0846f,-5.8431f,0.0000f),Vector3D(2.4304f,-3.7081f,0.0000f),Vector3D(0.2498f,-7.2403f,0.0000f),Vector3D(-1.5411f,-4.6480f,0.0000f),Vector3D(-4.9868f,-5.1400f,0.0000f),Vector3D(-7.7991f,-6.2858f,0.0000f),Vector3D(-1.9709f,-6.3186f,0.0000f),Vector3D(-3.7699f,-10.3600f,0.0000f)};
    IndexGroup basisIndexes[34] = {IndexGroup(5,0,3),IndexGroup(0,4,3),IndexGroup(4,2,7),IndexGroup(7,3,4),IndexGroup(3,6,5),IndexGroup(6,1,5),IndexGroup(13,8,11),IndexGroup(16,19,18),IndexGroup(8,12,11),IndexGroup(12,10,15),IndexGroup(15,11,12),IndexGroup(11,14,13),IndexGroup(14,9,13),IndexGroup(16,17,19),IndexGroup(20,23,22),IndexGroup(20,21,23),IndexGroup(24,27,26),IndexGroup(24,25,27),IndexGroup(28,31,30),IndexGroup(28,29,31),IndexGroup(37,32,35),IndexGroup(32,36,35),IndexGroup(36,34,39),IndexGroup(39,35,36),IndexGroup(35,38,37),IndexGroup(38,33,37),IndexGroup(40,43,42),IndexGroup(40,41,43),IndexGroup(44,47,46),IndexGroup(44,45,47),IndexGroup(52,55,54),IndexGroup(52,53,55),IndexGroup(51,48,49),IndexGroup(51,50,48)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 56, 34);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 3;
    int ShapeAnimationIndexes[32] = {16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55};
    int DissapateIndexes[56] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55};
    int ExplodeIndexes[56] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55};

    Vector3D ShapeAnimationVectors[32] = {Vector3D(-1.1134f,0.5355f,0.0000f),Vector3D(-2.0927f,0.3017f,0.0000f),Vector3D(-0.1429f,-0.0103f,0.0000f),Vector3D(-1.7902f,-0.2901f,0.0000f),Vector3D(-1.0300f,0.8359f,0.0000f),Vector3D(-0.0223f,2.3684f,0.0000f),Vector3D(0.4155f,1.0977f,0.0000f),Vector3D(-0.7648f,1.4419f,0.0000f),Vector3D(1.9514f,-1.2771f,0.0000f),Vector3D(1.9847f,2.5273f,0.0000f),Vector3D(0.4732f,-2.1962f,0.0000f),Vector3D(-1.1676f,-0.6655f,0.0000f),Vector3D(-0.1192f,-2.3653f,0.0000f),Vector3D(1.8549f,-1.1675f,0.0000f),Vector3D(-2.8025f,-0.3442f,0.0000f),Vector3D(0.8490f,0.4103f,0.0000f),Vector3D(0.3034f,0.9184f,0.0000f),Vector3D(0.3134f,0.8747f,0.0000f),Vector3D(0.4262f,0.9389f,0.0000f),Vector3D(-0.3861f,-0.1315f,0.0000f),Vector3D(-1.6489f,-3.1726f,0.0000f),Vector3D(0.2292f,-3.0107f,0.0000f),Vector3D(-1.6387f,-0.1371f,0.0000f),Vector3D(2.2009f,-2.0166f,0.0000f),Vector3D(0.0268f,-1.5451f,0.0000f),Vector3D(1.0771f,-1.6696f,0.0000f),Vector3D(-0.3424f,-0.7688f,0.0000f),Vector3D(2.2221f,-0.3068f,0.0000f),Vector3D(1.6346f,-2.0827f,0.0000f),Vector3D(3.0762f,-3.7148f,0.0000f),Vector3D(-0.2665f,-2.2526f,0.0000f),Vector3D(2.0326f,-2.7754f,0.0000f)};
    Vector3D DissapateVectors[56] = {Vector3D(64.3024f,3.2854f,0.0000f),Vector3D(64.3024f,3.2854f,0.0000f),Vector3D(64.3024f,3.2854f,0.0000f),Vector3D(64.3024f,3.2854f,0.0000f),Vector3D(64.3024f,3.2854f,0.0000f),Vector3D(64.3024f,3.2854f,0.0000f),Vector3D(64.3024f,3.2854f,0.0000f),Vector3D(64.3024f,3.2854f,0.0000f),Vector3D(2.7771f,-0.5204f,0.0000f),Vector3D(13.2157f,23.8470f,0.0000f),Vector3D(-13.0507f,-22.7334f,0.0000f),Vector3D(-2.3685f,0.5724f,0.0000f),Vector3D(-2.6007f,-12.6238f,0.0000f),Vector3D(5.5492f,10.1454f,0.0000f),Vector3D(2.3982f,12.4612f,0.0000f),Vector3D(-5.9203f,-11.1482f,0.0000f),Vector3D(-62.4314f,-3.1898f,0.0000f),Vector3D(-62.4314f,-3.1898f,0.0000f),Vector3D(-62.4314f,-3.1898f,0.0000f),Vector3D(-62.4314f,-3.1898f,0.0000f),Vector3D(-31.8065f,-1.6251f,0.0000f),Vector3D(-31.8065f,-1.6251f,0.0000f),Vector3D(-31.8065f,-1.6251f,0.0000f),Vector3D(-31.8065f,-1.6251f,0.0000f),Vector3D(-40.7675f,-2.0829f,0.0000f),Vector3D(-40.7675f,-2.0829f,0.0000f),Vector3D(-40.7675f,-2.0829f,0.0000f),Vector3D(-40.7675f,-2.0829f,0.0000f),Vector3D(-44.0171f,-2.2490f,0.0000f),Vector3D(-44.0171f,-2.2490f,0.0000f),Vector3D(-44.0171f,-2.2490f,0.0000f),Vector3D(-44.0171f,-2.2490f,0.0000f),Vector3D(-59.3787f,-3.0339f,0.0000f),Vector3D(-59.3787f,-3.0339f,0.0000f),Vector3D(-59.3787f,-3.0339f,0.0000f),Vector3D(-59.3787f,-3.0339f,0.0000f),Vector3D(-59.3787f,-3.0339f,0.0000f),Vector3D(-59.3787f,-3.0339f,0.0000f),Vector3D(-59.3787f,-3.0339f,0.0000f),Vector3D(-59.3787f,-3.0339f,0.0000f),Vector3D(-49.8269f,-2.5458f,0.0000f),Vector3D(-49.8269f,-2.5458f,0.0000f),Vector3D(-49.8269f,-2.5458f,0.0000f),Vector3D(-49.8269f,-2.5458f,0.0000f),Vector3D(61.3482f,3.1345f,0.0000f),Vector3D(61.3482f,3.1345f,0.0000f),Vector3D(61.3482f,3.1345f,0.0000f),Vector3D(61.3482f,3.1345f,0.0000f),Vector3D(48.1529f,2.4603f,0.0000f),Vector3D(48.1529f,2.4603f,0.0000f),Vector3D(48.1529f,2.4603f,0.0000f),Vector3D(48.1529f,2.4603f,0.0000f),Vector3D(42.3430f,2.1634f,0.0000f),Vector3D(42.3430f,2.1634f,0.0000f),Vector3D(42.3430f,2.1634f,0.0000f),Vector3D(42.3430f,2.1634f,0.0000f)};
    Vector3D ExplodeVectors[56] = {Vector3D(58.6563f,18.5691f,0.0047f),Vector3D(66.8082f,47.3801f,0.0047f),Vector3D(47.2563f,-3.1380f,0.0047f),Vector3D(52.6587f,18.2481f,0.0047f),Vector3D(56.7289f,10.4952f,0.0047f),Vector3D(61.0402f,29.2130f,0.0047f),Vector3D(56.3154f,31.9781f,0.0047f),Vector3D(52.6845f,11.4148f,0.0047f),Vector3D(-0.0379f,-0.0459f,0.0253f),Vector3D(0.3056f,-0.4873f,0.0673f),Vector3D(-0.2867f,0.4729f,-0.0681f),Vector3D(0.0347f,0.0378f,-0.0218f),Vector3D(-0.2065f,0.1769f,0.0027f),Vector3D(0.1308f,-0.2060f,0.0280f),Vector3D(0.2056f,-0.1715f,-0.0042f),Vector3D(-0.1455f,0.2231f,-0.0292f),Vector3D(-38.3048f,-19.1243f,-0.0370f),Vector3D(-37.2432f,-19.7026f,-0.0370f),Vector3D(-38.7113f,-16.8215f,-0.0370f),Vector3D(-37.1590f,-18.1176f,-0.0370f),Vector3D(-14.7898f,-22.7507f,-0.0583f),Vector3D(-13.7614f,-22.3689f,-0.0583f),Vector3D(-15.8653f,-22.2911f,-0.0583f),Vector3D(-15.1701f,-20.8523f,-0.0583f),Vector3D(-3.3490f,-31.0080f,-0.0614f),Vector3D(-3.3954f,-29.6082f,-0.0614f),Vector3D(-4.4653f,-31.7630f,-0.0614f),Vector3D(-5.8019f,-30.7006f,-0.0614f),Vector3D(-25.9426f,-28.3720f,-0.0370f),Vector3D(-28.1910f,-26.7592f,-0.0370f),Vector3D(-27.6669f,-31.5597f,-0.0370f),Vector3D(-28.4654f,-28.7880f,-0.0370f),Vector3D(-29.1245f,-18.2286f,-0.0031f),Vector3D(-44.4404f,-11.7700f,-0.0031f),Vector3D(-14.5725f,-27.0628f,-0.0031f),Vector3D(-29.5689f,-21.4817f,-0.0031f),Vector3D(-21.3442f,-21.0214f,-0.0031f),Vector3D(-35.4754f,-16.4412f,-0.0031f),Vector3D(-37.4458f,-18.6935f,-0.0031f),Vector3D(-22.1105f,-23.1554f,-0.0031f),Vector3D(-40.7982f,-37.8174f,-0.0173f),Vector3D(-40.6598f,-36.6615f,-0.0173f),Vector3D(-43.9757f,-37.2426f,-0.0173f),Vector3D(-41.7523f,-36.7889f,-0.0173f),Vector3D(13.8472f,28.1880f,0.0371f),Vector3D(15.4491f,33.0454f,0.0371f),Vector3D(6.4600f,30.9639f,0.0371f),Vector3D(13.0479f,36.4034f,0.0371f),Vector3D(39.1201f,-1.9963f,-0.0087f),Vector3D(37.0383f,-2.8414f,-0.0087f),Vector3D(41.3505f,-2.8712f,-0.0087f),Vector3D(40.0156f,-5.8598f,-0.0087f),Vector3D(31.6066f,21.1850f,0.0654f),Vector3D(33.5568f,25.2425f,0.0654f),Vector3D(27.1197f,19.4790f,0.0654f),Vector3D(25.0750f,25.7101f,0.0654f)};

    Morph morphs[3] = {
        Morph(32, ShapeAnimationIndexes, ShapeAnimationVectors),
        Morph(56, DissapateIndexes, DissapateVectors),
        Morph(56, ExplodeIndexes, ExplodeVectors)
    };

public:
    AlephDJLogo(){}

    Object3D* GetObject(){
        return &basisObj;
    }

    void SetMorphWeight(Morphs morph, float weight){
        morphs[morph].Weight = weight;
    }

    float* GetMorphWeightReference(Morphs morph){
        return &morphs[morph].Weight;
    }

    void Reset(){
        for(int i = 0; i < morphCount; i++){
            morphs[i].Weight = 0.0f;
        }
    }

    void Update(){
        basisObj.ResetVertices();

        for(int i = 0; i < morphCount; i++){
            if(morphs[i].Weight > 0.0f){
                morphs[i].MorphObject3D(basisObj.GetTriangleGroup());
            }
        }

    }
};
