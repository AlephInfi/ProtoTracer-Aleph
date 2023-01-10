#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "..\Morph\Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class AlephL2{
public:
    enum Morphs {
        PupilVertical,
        PupilHorizontal,
        PupilDilate,
        PupilOff
    };

private:
    Vector3D basisVertices[8] = {Vector3D(-0.4182f,-0.2549f,0.0855f),Vector3D(-0.2465f,-0.2549f,0.0855f),Vector3D(-0.4182f,0.1261f,0.0855f),Vector3D(-0.2465f,0.1261f,0.0855f),Vector3D(-0.4518f,-0.0644f,0.0855f),Vector3D(-0.3324f,-0.3162f,0.0855f),Vector3D(-0.2129f,-0.0644f,0.0855f),Vector3D(-0.3324f,0.1874f,0.0855f)};
    IndexGroup basisIndexes[6] = {IndexGroup(1,5,0),IndexGroup(0,4,6),IndexGroup(4,2,3),IndexGroup(2,7,3),IndexGroup(3,6,4),IndexGroup(6,1,0)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 8, 6);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 4;
    int PupilVerticalIndexes[8] = {0,1,2,3,4,5,6,7};
    int PupilHorizontalIndexes[8] = {0,1,2,3,4,5,6,7};
    int PupilDilateIndexes[8] = {0,1,2,3,4,5,6,7};
    int PupilOffIndexes[8] = {0,1,2,3,4,5,6,7};

    Vector3D PupilVerticalVectors[8] = {Vector3D(0.0000f,0.8773f,0.0000f),Vector3D(0.0000f,0.8773f,0.0000f),Vector3D(0.0000f,0.8773f,0.0000f),Vector3D(0.0000f,0.8773f,0.0000f),Vector3D(0.0000f,0.8773f,0.0000f),Vector3D(0.0000f,0.8773f,0.0000f),Vector3D(0.0000f,0.8773f,0.0000f),Vector3D(0.0000f,0.8773f,0.0000f)};
    Vector3D PupilHorizontalVectors[8] = {Vector3D(0.8109f,0.0000f,0.0000f),Vector3D(0.8109f,0.0000f,0.0000f),Vector3D(0.8109f,0.0000f,0.0000f),Vector3D(0.8109f,0.0000f,0.0000f),Vector3D(0.8109f,0.0000f,0.0000f),Vector3D(0.8109f,0.0000f,0.0000f),Vector3D(0.8109f,0.0000f,0.0000f),Vector3D(0.8109f,0.0000f,0.0000f)};
    Vector3D PupilDilateVectors[8] = {Vector3D(0.0535f,0.0757f,0.0000f),Vector3D(-0.0535f,0.0757f,0.0000f),Vector3D(0.0535f,-0.0757f,0.0000f),Vector3D(-0.0535f,-0.0757f,0.0000f),Vector3D(0.0744f,0.0000f,0.0000f),Vector3D(0.0000f,0.0512f,0.0000f),Vector3D(-0.0744f,0.0000f,0.0000f),Vector3D(0.0000f,-0.0512f,0.0000f)};
    Vector3D PupilOffVectors[8] = {Vector3D(0.0625f,1.7931f,0.0000f),Vector3D(-0.1087f,1.7931f,0.0000f),Vector3D(0.0625f,1.4131f,0.0000f),Vector3D(-0.1087f,1.4131f,0.0000f),Vector3D(0.0960f,1.6031f,0.0000f),Vector3D(-0.0231f,1.8542f,0.0000f),Vector3D(-0.1422f,1.6031f,0.0000f),Vector3D(-0.0231f,1.3519f,0.0000f)};

    Morph morphs[4] = {
        Morph(8, PupilVerticalIndexes, PupilVerticalVectors),
        Morph(8, PupilHorizontalIndexes, PupilHorizontalVectors),
        Morph(8, PupilDilateIndexes, PupilDilateVectors),
        Morph(8, PupilOffIndexes, PupilOffVectors)
    };

public:
    AlephL2(){}

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
