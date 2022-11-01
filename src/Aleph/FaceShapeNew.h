#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "..\Morph\Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class FaceShape{
public:
    enum Morphs {
        eBlk,
        eSqnt,
        eSad,
        eSurpr,
        eMad,
        eCute,
        eHeart,
        mSad,
        mNeut,
        mOpen,
        mSmol,
        blush
    };

private:
    Vector3D basisVertices[57] = {Vector3D(-6.1953f,-2.1783f,776.9922f),Vector3D(0.5170f,-0.9460f,775.8984f),Vector3D(-3.0520f,5.6439f,776.9922f),Vector3D(1.5514f,8.9660f,776.8359f),Vector3D(-5.5964f,0.9037f,776.8359f),Vector3D(-3.3462f,-2.3820f,777.0703f),Vector3D(1.9374f,4.8610f,776.4453f),Vector3D(0.4863f,9.1631f,776.9141f),Vector3D(-6.3401f,-1.3655f,776.6797f),Vector3D(-0.8137f,-1.7783f,775.7422f),Vector3D(1.7927f,7.6910f,776.7578f),Vector3D(-1.1031f,7.9861f,777.2266f),Vector3D(-4.4692f,3.2894f,777.1484f),Vector3D(-5.2763f,-2.4200f,778.0078f),Vector3D(1.4867f,1.6186f,776.1328f),Vector3D(1.1323f,9.4305f,776.9141f),Vector3D(-0.3086f,9.8423f,-49117.0801f),Vector3D(-5.2417f,5.9359f,-49117.2363f),Vector3D(-3.6648f,9.3889f,-49117.2363f),Vector3D(-3.0977f,8.5197f,-49116.5332f),Vector3D(-4.7193f,7.9263f,-49117.0801f),Vector3D(-1.9292f,10.0314f,-49116.2207f),Vector3D(-19.4562f,-2.9308f,-49144.1113f),Vector3D(-20.4906f,-5.7835f,-49145.2832f),Vector3D(-20.8595f,-4.2433f,-49146.5332f),Vector3D(-3.3732f,-5.6675f,-49108.7988f),Vector3D(-20.5224f,-3.2519f,-49146.2207f),Vector3D(-20.9398f,-5.3495f,-49146.2988f),Vector3D(-20.1885f,-4.1106f,-49145.2832f),Vector3D(-19.2486f,-3.3720f,-49143.5645f),Vector3D(-20.8331f,-6.1554f,-49145.8301f),Vector3D(-11.8686f,-12.1940f,-49124.9707f),Vector3D(-20.8672f,-12.3435f,-49143.4863f),Vector3D(-17.8863f,-15.8318f,-49136.6895f),Vector3D(-3.9702f,-4.8242f,-49110.4395f),Vector3D(-20.6003f,-13.8232f,-49142.4707f),Vector3D(-11.5200f,-13.9508f,-49123.7207f),Vector3D(-5.6694f,-8.1132f,-49112.8613f),Vector3D(-18.0423f,-14.0904f,-49137.5488f),Vector3D(-3.3749f,-3.9772f,-49109.3457f),Vector3D(-5.3339f,-9.5325f,-49111.8457f),Vector3D(-9.1127f,-7.8875f,-49120.2051f),Vector3D(-15.3928f,-12.6336f,-49131.6113f),Vector3D(-15.5252f,-11.0991f,-49132.3145f),Vector3D(-8.8334f,-9.3833f,-49119.1895f),Vector3D(1.9126f,-6.5765f,-49131.9238f),Vector3D(2.3841f,-5.9982f,-49134.6582f),Vector3D(1.8755f,-6.4958f,-49131.6113f),Vector3D(2.3470f,-5.9174f,-49134.3457f),Vector3D(0.0652f,-7.0974f,-49135.5176f),Vector3D(0.5367f,-6.5190f,-49138.2520f),Vector3D(0.0280f,-7.0166f,-49135.2051f),Vector3D(0.4995f,-6.4383f,-49137.9395f),Vector3D(-1.6112f,-7.5700f,-49138.7988f),Vector3D(-1.1397f,-6.9916f,-49141.5332f),Vector3D(-1.6484f,-7.4892f,-49138.4863f),Vector3D(-1.1769f,-6.9109f,-49141.2207f)};
    IndexGroup basisIndexes[43] = {IndexGroup(16,19,21),IndexGroup(21,20,18),IndexGroup(20,21,19),IndexGroup(19,17,20),IndexGroup(22,28,26),IndexGroup(26,27,24),IndexGroup(26,28,27),IndexGroup(23,27,28),IndexGroup(22,29,28),IndexGroup(23,30,27),IndexGroup(41,44,36),IndexGroup(33,35,32),IndexGroup(33,32,38),IndexGroup(42,33,43),IndexGroup(33,38,43),IndexGroup(37,34,40),IndexGroup(34,39,25),IndexGroup(40,34,25),IndexGroup(37,40,44),IndexGroup(42,43,31),IndexGroup(41,37,44),IndexGroup(36,42,31),IndexGroup(31,41,36),IndexGroup(8,0,13),IndexGroup(10,3,6),IndexGroup(3,15,6),IndexGroup(6,15,14),IndexGroup(15,7,14),IndexGroup(14,7,1),IndexGroup(7,11,1),IndexGroup(1,11,9),IndexGroup(11,2,9),IndexGroup(9,2,5),IndexGroup(2,12,5),IndexGroup(5,12,13),IndexGroup(12,4,13),IndexGroup(4,8,13),IndexGroup(46,47,45),IndexGroup(50,51,49),IndexGroup(54,55,53),IndexGroup(46,48,47),IndexGroup(50,52,51),IndexGroup(54,56,55)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 57, 43);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 12;
    int eBlkIndexes[43] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,25,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56};
    int eSqntIndexes[41] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,25,34,37,39,40,41,44,45,46,47,48,49,50,51,52,53,54,55,56};
    int eSadIndexes[49] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,25,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56};
    int eSurprIndexes[49] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,25,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56};
    int eMadIndexes[49] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,25,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56};
    int eCuteIndexes[49] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,25,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56};
    int eHeartIndexes[22] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
    int mSadIndexes[43] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,25,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56};
    int mNeutIndexes[43] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,25,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56};
    int mOpenIndexes[43] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,25,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56};
    int mSmolIndexes[43] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,25,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56};
    int blushIndexes[28] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,45,46,47,48,49,50,51,52,53,54,55,56};

    Vector3D eBlkVectors[43] = {Vector3D(0.7635f,0.6594f,1.3672f),Vector3D(-1.2793f,0.7998f,-2.8516f),Vector3D(-0.2475f,-5.4440f,1.7578f),Vector3D(-2.3530f,-7.7421f,-1.9922f),Vector3D(0.7720f,-1.2547f,2.4609f),Vector3D(-0.5481f,1.0006f,-1.3672f),Vector3D(-1.9222f,-3.5105f,-2.6172f),Vector3D(-2.2602f,-8.3794f,-1.4453f),Vector3D(0.8949f,0.5277f,1.7578f),Vector3D(-1.3522f,1.0176f,-3.0859f),Vector3D(-2.1987f,-6.2729f,-2.2266f),Vector3D(-1.4523f,-7.4862f,-0.0391f),Vector3D(0.2813f,-3.4053f,2.2266f),Vector3D(0.5002f,0.6683f,0.8203f),Vector3D(-1.1169f,-0.6860f,-1.9141f),Vector3D(-2.3284f,-8.3615f,-1.6016f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(0.0022f,-0.0207f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.3750f)};
    Vector3D eSqntVectors[41] = {Vector3D(-0.3906f,-0.3948f,-0.9766f),Vector3D(-1.9213f,-0.5712f,-3.7109f),Vector3D(-0.8586f,-4.3282f,-0.3516f),Vector3D(-1.9929f,-5.4769f,-1.9922f),Vector3D(-0.1045f,-1.6423f,0.3516f),Vector3D(-0.6691f,-0.4432f,-1.2891f),Vector3D(-2.2450f,-3.0260f,-3.3984f),Vector3D(-1.8557f,-5.8647f,-1.6016f),Vector3D(0.0378f,-0.2679f,-0.1172f),Vector3D(-1.5234f,-0.5913f,-2.8516f),Vector3D(-2.0910f,-4.6401f,-2.4609f),Vector3D(-1.4501f,-5.5097f,-0.9766f),Vector3D(-0.3693f,-2.9047f,0.3516f),Vector3D(-0.4318f,-0.5801f,-0.9766f),Vector3D(-2.2242f,-1.5878f,-3.8672f),Vector3D(-1.8183f,-5.8204f,-1.5234f),Vector3D(-2.9358f,-5.1016f,-3.6719f),Vector3D(-1.4975f,-6.5625f,-1.2500f),Vector3D(-2.2152f,-6.0739f,-2.4219f),Vector3D(-2.2195f,-5.9740f,-2.4219f),Vector3D(-1.9128f,-6.7739f,-1.7969f),Vector3D(-2.6186f,-5.4359f,-3.2031f),Vector3D(0.0000f,0.0000f,-0.0049f),Vector3D(0.0000f,0.0000f,-0.0049f),Vector3D(0.0000f,0.0000f,-0.0049f),Vector3D(0.0000f,0.0000f,-0.0049f),Vector3D(0.0000f,0.0000f,-0.0049f),Vector3D(0.0000f,0.0000f,-0.0049f),Vector3D(0.0000f,0.0000f,-0.0049f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.3750f)};
    Vector3D eSadVectors[49] = {Vector3D(0.2566f,0.7043f,0.2734f),Vector3D(-0.4508f,0.4960f,-1.2891f),Vector3D(-0.4979f,-0.6805f,-0.8203f),Vector3D(-1.2405f,-5.9498f,-0.6641f),Vector3D(-0.7567f,-0.0430f,-1.2891f),Vector3D(-0.1247f,1.7715f,-0.8984f),Vector3D(-0.7836f,-2.8044f,-0.9766f),Vector3D(-2.4100f,-5.3906f,-3.0078f),Vector3D(-0.3225f,-0.5461f,-0.3516f),Vector3D(-0.6458f,1.3815f,-1.9141f),Vector3D(-0.6786f,-4.7037f,0.1172f),Vector3D(-1.6356f,-3.6170f,-2.0703f),Vector3D(-0.8797f,-0.2844f,-1.5234f),Vector3D(0.1432f,1.3194f,-0.1953f),Vector3D(-0.6900f,-1.0013f,-1.2891f),Vector3D(-1.8780f,-6.1468f,-1.7578f),Vector3D(2.1156f,-5.6103f,4.3750f),Vector3D(1.5364f,1.2625f,4.4531f),Vector3D(2.7165f,-1.4635f,6.2500f),Vector3D(2.1880f,-1.9372f,5.2344f),Vector3D(2.3094f,0.1563f,5.8594f),Vector3D(2.5899f,-3.7059f,5.7031f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-0.0041f,0.0388f,-0.0146f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.3750f)};
    Vector3D eSurprVectors[49] = {Vector3D(-0.7714f,-0.8119f,-1.5234f),Vector3D(-0.0668f,-0.4790f,-0.1172f),Vector3D(-0.4936f,0.5032f,-1.2891f),Vector3D(-0.1375f,-0.6428f,-0.1953f),Vector3D(-0.6914f,0.4857f,-1.6016f),Vector3D(-0.7509f,-1.2279f,-1.2891f),Vector3D(-0.1080f,-0.9220f,-0.0391f),Vector3D(-0.5711f,-0.4295f,-1.2109f),Vector3D(-0.7316f,-0.5226f,-1.5234f),Vector3D(-0.0667f,-1.0350f,0.0391f),Vector3D(-0.0647f,-1.0536f,0.1172f),Vector3D(-0.2733f,0.0859f,-0.7422f),Vector3D(-0.7955f,0.5811f,-1.8359f),Vector3D(-1.3554f,-0.8423f,-2.6953f),Vector3D(-0.0608f,-0.8129f,0.0391f),Vector3D(-0.2044f,-0.5657f,-0.4297f),Vector3D(0.7524f,-0.5280f,0.4688f),Vector3D(-0.3405f,0.2812f,-0.1562f),Vector3D(0.2361f,0.3309f,0.4688f),Vector3D(0.2258f,0.0535f,0.3906f),Vector3D(-0.0622f,0.4161f,0.3125f),Vector3D(0.5451f,-0.0561f,0.7031f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.3750f)};
    Vector3D eMadVectors[49] = {Vector3D(-0.1965f,-1.2937f,1.6016f),Vector3D(-1.2549f,0.1066f,-4.3359f),Vector3D(-1.2362f,-3.7541f,-0.3516f),Vector3D(-1.5608f,-1.3690f,-4.0234f),Vector3D(-0.8944f,-3.0444f,1.0547f),Vector3D(-0.7501f,-0.3872f,-1.0547f),Vector3D(-2.0857f,-0.5602f,-5.6641f),Vector3D(-1.8090f,-2.9471f,-3.3203f),Vector3D(-0.6258f,-1.9561f,1.1328f),Vector3D(-1.2881f,0.0693f,-3.7891f),Vector3D(-1.7183f,-1.1990f,-4.4922f),Vector3D(-1.5319f,-3.5241f,-1.7578f),Vector3D(-1.0928f,-3.6675f,0.5078f),Vector3D(-0.1031f,-0.7914f,1.2891f),Vector3D(-1.9750f,-0.2649f,-5.7422f),Vector3D(-1.6166f,-2.2557f,-3.4766f),Vector3D(-3.5872f,-3.3274f,-4.3750f),Vector3D(-1.2678f,-6.4784f,-1.0938f),Vector3D(-2.6861f,-5.9716f,-3.5156f),Vector3D(-2.5479f,-5.3101f,-3.1250f),Vector3D(-1.9976f,-6.5027f,-2.3438f),Vector3D(-3.2774f,-4.6968f,-4.2969f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.3750f)};
    Vector3D eCuteVectors[49] = {Vector3D(0.4938f,1.4474f,3.2422f),Vector3D(1.1889f,0.0867f,-0.2734f),Vector3D(-1.8571f,-2.1884f,-1.4453f),Vector3D(-1.9212f,-4.3478f,-4.1797f),Vector3D(-0.8427f,-0.9897f,1.6016f),Vector3D(1.4968f,2.7512f,2.6953f),Vector3D(-0.8994f,-2.6296f,-3.7891f),Vector3D(-2.8260f,-4.0328f,-5.2734f),Vector3D(-0.1275f,0.0920f,2.6953f),Vector3D(1.3190f,1.5963f,0.2734f),Vector3D(-1.3694f,-4.1483f,-3.4766f),Vector3D(-2.5319f,-3.2992f,-3.7109f),Vector3D(-1.2922f,-1.3393f,0.3516f),Vector3D(0.9185f,2.4386f,3.5547f),Vector3D(0.0086f,-0.7435f,-2.7734f),Vector3D(-2.4880f,-4.3328f,-5.0391f),Vector3D(2.2848f,-4.4719f,4.3750f),Vector3D(1.6961f,2.0304f,4.3750f),Vector3D(2.8300f,-0.5338f,6.0938f),Vector3D(2.3321f,-0.9908f,5.1562f),Vector3D(2.4349f,0.9944f,5.7031f),Vector3D(2.7232f,-2.6603f,5.6250f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(0.0041f,-0.0388f,0.0098f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.3750f)};
    Vector3D eHeartVectors[22] = {Vector3D(1.0588f,3.5095f,0.8739f),Vector3D(-0.2230f,0.4764f,-0.6536f),Vector3D(0.1325f,1.1722f,-0.1292f),Vector3D(-0.7229f,-1.4027f,-0.8544f),Vector3D(0.3256f,5.0827f,-1.1853f),Vector3D(0.7886f,0.0708f,1.5634f),Vector3D(-0.3917f,-1.6465f,-0.1819f),Vector3D(-1.9506f,-1.9066f,-3.3083f),Vector3D(0.5969f,5.0835f,-0.6475f),Vector3D(-0.2758f,-1.8217f,0.0354f),Vector3D(-0.1044f,-2.1769f,0.6223f),Vector3D(-0.9809f,-1.8629f,-1.3257f),Vector3D(0.3532f,3.6543f,-0.5854f),Vector3D(1.3163f,1.7596f,2.0523f),Vector3D(-0.4419f,-0.0958f,-0.8732f),Vector3D(-1.5288f,-1.4363f,-2.5900f),Vector3D(1.5520f,-1.4623f,2.6562f),Vector3D(1.0126f,2.9905f,2.1094f),Vector3D(1.8472f,1.2838f,3.5156f),Vector3D(1.5132f,0.9414f,2.8125f),Vector3D(1.5434f,2.3163f,3.0469f),Vector3D(1.8172f,-0.1888f,3.2812f)};
    Vector3D mSadVectors[43] = {Vector3D(-0.0126f,-0.1218f,-0.1321f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(-0.0283f,-0.1854f,0.1055f),Vector3D(-0.0373f,-0.0633f,-0.1068f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0257f,-0.0487f,0.0166f),Vector3D(0.0333f,-0.0833f,0.0406f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(-0.0002f,-0.0448f,0.1401f),Vector3D(-0.0206f,-0.0458f,-0.1452f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(-0.4524f,-6.0319f,0.8594f),Vector3D(-1.0790f,3.8868f,-3.8281f),Vector3D(-0.0411f,-0.8000f,0.0781f),Vector3D(-0.1206f,3.0130f,-1.3281f),Vector3D(0.2472f,-5.9650f,2.1875f),Vector3D(0.1189f,-0.6451f,0.0000f),Vector3D(-1.2629f,3.8097f,-4.1406f),Vector3D(-0.5897f,-0.9601f,-1.0156f),Vector3D(0.0075f,3.0236f,-1.0938f),Vector3D(0.2151f,-7.8869f,1.9531f),Vector3D(-0.8051f,-1.0636f,-1.4062f),Vector3D(-0.4015f,-3.1868f,0.0000f),Vector3D(0.3672f,-0.6626f,1.1719f),Vector3D(0.3878f,-0.5382f,1.1719f),Vector3D(-0.5455f,-3.2447f,-0.3125f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.3750f)};
    Vector3D mNeutVectors[43] = {Vector3D(-0.0052f,0.0401f,-0.1476f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(-0.0914f,-0.2830f,-0.0256f),Vector3D(-0.0652f,-0.0312f,-0.1755f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(-0.0022f,-0.0166f,-0.0520f),Vector3D(0.0251f,-0.0057f,-0.0043f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(-0.1066f,-0.1946f,-0.0241f),Vector3D(0.0507f,-0.0257f,-0.0063f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(-1.5051f,-5.3348f,-1.8750f),Vector3D(-0.9238f,-0.7053f,-2.0312f),Vector3D(0.2671f,-0.9837f,0.7031f),Vector3D(-0.0964f,0.5565f,-0.7031f),Vector3D(-1.3914f,-5.0341f,-1.7188f),Vector3D(0.5307f,-1.4724f,1.0938f),Vector3D(-1.1144f,-0.6011f,-2.3438f),Vector3D(-2.0591f,-3.2620f,-2.7344f),Vector3D(-0.0712f,0.3185f,-0.5469f),Vector3D(-1.2430f,-5.4475f,-1.4844f),Vector3D(-2.1992f,-3.3448f,-3.0469f),Vector3D(-1.3601f,-3.6503f,-1.7969f),Vector3D(-0.2041f,-1.6181f,-0.1562f),Vector3D(-0.2041f,-1.6181f,-0.1562f),Vector3D(-1.4650f,-3.6981f,-2.0312f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.3750f)};
    Vector3D mOpenVectors[43] = {Vector3D(-0.0052f,0.0401f,-0.1476f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0380f,0.1130f,0.0967f),Vector3D(-0.0931f,0.0009f,-0.2441f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0019f,-0.0554f,-0.0297f),Vector3D(0.0013f,-0.0124f,-0.0134f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(-0.0829f,-0.1879f,0.0314f),Vector3D(0.0744f,-0.0190f,0.0399f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(-0.1819f,-0.7557f,0.0000f),Vector3D(0.0110f,-0.1073f,0.0000f),Vector3D(0.0107f,-0.0439f,0.0781f),Vector3D(0.3655f,-2.8959f,1.7969f),Vector3D(0.0304f,-0.1629f,0.0000f),Vector3D(0.4753f,-3.3790f,2.2656f),Vector3D(0.6740f,-2.6125f,2.2656f),Vector3D(0.0218f,-0.1510f,0.0781f),Vector3D(0.0061f,-0.0638f,0.0781f),Vector3D(0.0818f,-0.6434f,0.3125f),Vector3D(-0.0616f,-1.6131f,0.7031f),Vector3D(0.0224f,-0.1267f,0.0781f),Vector3D(0.6425f,-4.0641f,2.7344f),Vector3D(0.0140f,-0.0815f,0.0000f),Vector3D(0.2333f,-2.1735f,1.4062f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.3750f)};
    Vector3D mSmolVectors[43] = {Vector3D(-0.0290f,0.0334f,-0.1939f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0535f,0.1972f,0.0983f),Vector3D(-0.0455f,0.0143f,-0.1516f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0134f,0.0677f,-0.0506f),Vector3D(0.0013f,-0.0124f,-0.0134f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0351f,0.0850f,0.1654f),Vector3D(0.0269f,-0.0324f,-0.0526f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(-12.2826f,-7.8066f,-22.2656f),Vector3D(-6.0789f,-0.9382f,-13.2812f),Vector3D(0.8342f,-1.1449f,1.2500f),Vector3D(-1.4050f,1.1965f,-4.5312f),Vector3D(-12.0093f,-7.6088f,-21.7969f),Vector3D(0.7311f,-0.7010f,1.0156f),Vector3D(-6.3191f,-0.4872f,-13.6719f),Vector3D(-10.8263f,-4.5897f,-21.0156f),Vector3D(-1.3290f,0.7534f,-4.4531f),Vector3D(-11.9331f,-8.1267f,-22.1094f),Vector3D(-11.0067f,-4.3873f,-21.4062f),Vector3D(-8.0983f,-5.0388f,-15.3906f),Vector3D(-3.2074f,-1.9333f,-6.1719f),Vector3D(-3.1352f,-2.1770f,-6.1719f),Vector3D(-8.3141f,-4.8818f,-15.7031f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.4531f),Vector3D(-1.9695f,3.2052f,-472320.6250f),Vector3D(-2.2946f,3.1135f,-472320.6250f),Vector3D(-1.9695f,3.2052f,472359.3750f),Vector3D(-2.2946f,3.1135f,472359.3750f)};
    Vector3D blushVectors[28] = {Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.0000f,0.0000f,-0.0391f),Vector3D(0.5315f,-1.4516f,1.3281f),Vector3D(0.5399f,-1.3718f,1.7969f),Vector3D(-0.3343f,0.0893f,-1.0156f),Vector3D(-0.3258f,0.1692f,-0.5469f),Vector3D(0.7461f,-1.3641f,2.1094f),Vector3D(0.7774f,-1.3295f,1.8750f),Vector3D(-0.1520f,0.4119f,-0.3906f),Vector3D(-0.1206f,0.4465f,-0.4688f),Vector3D(0.5622f,-1.4944f,2.1094f),Vector3D(0.6037f,-1.4160f,1.1719f),Vector3D(-0.5224f,0.6520f,-0.7812f),Vector3D(-0.4809f,0.7305f,-1.7188f)};

    Morph morphs[12] = {
        Morph(43, eBlkIndexes, eBlkVectors),
        Morph(41, eSqntIndexes, eSqntVectors),
        Morph(49, eSadIndexes, eSadVectors),
        Morph(49, eSurprIndexes, eSurprVectors),
        Morph(49, eMadIndexes, eMadVectors),
        Morph(49, eCuteIndexes, eCuteVectors),
        Morph(22, eHeartIndexes, eHeartVectors),
        Morph(43, mSadIndexes, mSadVectors),
        Morph(43, mNeutIndexes, mNeutVectors),
        Morph(43, mOpenIndexes, mOpenVectors),
        Morph(43, mSmolIndexes, mSmolVectors),
        Morph(28, blushIndexes, blushVectors)
    };

public:
    FaceShape(){}

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
