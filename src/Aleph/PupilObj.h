#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "..\Morph\Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class PupilObj{
public:
    enum Morphs {
        horiz,
        vert,
        size,
        dilation
    };

private:
    Vector3D basisVertices[8] = {Vector3D(3.1269f,-2.6099f,-0011.6074f),Vector3D(1.8760f,-3.0349f,-0003.2278f),Vector3D(1.9775f,2.5619f,-0007.6031f),Vector3D(2.5599f,-3.2594f,-0005.2502f),Vector3D(1.2439f,-0.6078f,-0005.7458f),Vector3D(3.2382f,0.0967f,-0007.1078f),Vector3D(2.6225f,2.2372f,-0007.6031f),Vector3D(1.3980f,1.9413f,-0007.3969f)};
    IndexGroup basisIndexes[6] = {IndexGroup(3,4,5),IndexGroup(0,3,5),IndexGroup(3,1,4),IndexGroup(4,7,5),IndexGroup(7,2,6),IndexGroup(5,7,6)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 8, 6);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 4;
    int horizIndexes[8] = {0,1,2,3,4,5,6,7};
    int vertIndexes[8] = {0,1,2,3,4,5,6,7};
    int sizeIndexes[8] = {0,1,2,3,4,5,6,7};
    int dilationIndexes[8] = {0,1,2,3,4,5,6,7};

    Vector3D horizVectors[8] = {Vector3D(-7.5175f,-2.1193f,0.5964f),Vector3D(-7.5175f,-2.1193f,0.5977f),Vector3D(-7.5175f,-2.1193f,0.5970f),Vector3D(-7.5175f,-2.1193f,0.5964f),Vector3D(-7.5175f,-2.1193f,0.5964f),Vector3D(-7.5175f,-2.1193f,0.5964f),Vector3D(-7.5175f,-2.1193f,0.5970f),Vector3D(-7.5175f,-2.1193f,0.5970f)};
    Vector3D vertVectors[8] = {Vector3D(-0.9742f,9.2107f,0.0461f),Vector3D(-0.9742f,9.2107f,0.0474f),Vector3D(-0.9742f,9.2107f,0.0468f),Vector3D(-0.9742f,9.2107f,0.0461f),Vector3D(-0.9742f,9.2107f,0.0461f),Vector3D(-0.9742f,9.2107f,0.0461f),Vector3D(-0.9742f,9.2107f,0.0468f),Vector3D(-0.9742f,9.2107f,0.0468f)};
    Vector3D sizeVectors[8] = {Vector3D(0.0547f,0.2308f,0.8713f),Vector3D(0.2472f,0.2961f,0.1226f),Vector3D(0.2315f,-0.5650f,0.4579f),Vector3D(0.1419f,0.3307f,0.8479f),Vector3D(0.3444f,-0.0773f,0.7698f),Vector3D(0.0376f,-0.1857f,0.5354f),Vector3D(0.1323f,-0.5150f,0.4579f),Vector3D(0.3207f,-0.4695f,0.5360f)};
    Vector3D dilationVectors[8] = {Vector3D(-0.3316f,0.0932f,0.5823f),Vector3D(0.2968f,0.3067f,0.8022f),Vector3D(0.0000f,0.0000f,0.9657f),Vector3D(0.0000f,0.0000f,0.9651f),Vector3D(0.5227f,0.1576f,0.5901f),Vector3D(-0.5159f,-0.2093f,0.8870f),Vector3D(-0.2646f,-0.3560f,0.8876f),Vector3D(0.3161f,-0.2157f,0.0048f)};

    Morph morphs[4] = {
        Morph(8, horizIndexes, horizVectors),
        Morph(8, vertIndexes, vertVectors),
        Morph(8, sizeIndexes, sizeVectors),
        Morph(8, dilationIndexes, dilationVectors)
    };

public:
    PupilObj(){}

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
