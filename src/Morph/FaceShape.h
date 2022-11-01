#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class FaceShape{
public:
    enum Morphs {
        Eyesblink,
        Mouthopen,
        sadeyes,
        sadmouth,
        angery,
        wideeyes
    };

private:
    Vector3D basisVertices[119] = {Vector3D(-1.4931f,2.0037f,0.0000f),Vector3D(-2.8025f,1.4644f,0.0000f),Vector3D(-2.2939f,2.8730f,0.0000f),Vector3D(-2.8775f,3.2779f,0.0000f),Vector3D(-3.9919f,3.8126f,0.0000f),Vector3D(-3.6967f,3.7136f,0.0000f),Vector3D(-5.0059f,2.1275f,0.0000f),Vector3D(-1.6948f,1.8114f,0.0000f),Vector3D(-1.5769f,1.8862f,0.0000f),Vector3D(-1.0592f,-1.0957f,-0.0000f),Vector3D(9.9915f,-2.7936f,-0.0000f),Vector3D(-2.2977f,0.2326f,-0.0000f),Vector3D(9.9957f,-2.1532f,-0.0000f),Vector3D(-1.8562f,0.0863f,-0.0000f),Vector3D(-1.7398f,-0.4316f,-0.0000f),Vector3D(-1.4301f,-0.7943f,-0.0000f),Vector3D(-1.1276f,-0.5974f,-0.0000f),Vector3D(-1.2600f,-0.9552f,-0.0000f),Vector3D(1.8483f,-1.5164f,-0.0000f),Vector3D(-0.8003f,-1.1506f,-0.0000f),Vector3D(0.1470f,-1.2419f,-0.0000f),Vector3D(0.9912f,-1.3430f,-0.0000f),Vector3D(1.4006f,-1.3977f,-0.0000f),Vector3D(-0.7361f,-0.7941f,-0.0000f),Vector3D(0.2121f,-0.8479f,-0.0000f),Vector3D(0.9588f,-0.8961f,-0.0000f),Vector3D(1.7837f,-0.9649f,-0.0000f),Vector3D(4.7276f,-2.9349f,-0.0000f),Vector3D(7.1565f,-1.1977f,-0.0000f),Vector3D(2.2011f,-1.7088f,-0.0000f),Vector3D(2.8674f,-2.2480f,-0.0000f),Vector3D(3.2773f,-2.6496f,-0.0000f),Vector3D(3.8102f,-3.0762f,-0.0000f),Vector3D(4.1831f,-3.3066f,-0.0000f),Vector3D(4.5464f,-3.4963f,-0.0000f),Vector3D(2.1985f,-1.0663f,-0.0000f),Vector3D(2.6664f,-1.4511f,-0.0000f),Vector3D(3.3647f,-2.0439f,-0.0000f),Vector3D(4.0802f,-2.5703f,-0.0000f),Vector3D(4.3954f,-2.7739f,-0.0000f),Vector3D(6.3140f,-1.7497f,-0.0000f),Vector3D(6.5819f,-1.5355f,-0.0000f),Vector3D(6.8436f,-1.3474f,-0.0000f),Vector3D(5.6329f,-2.3048f,-0.0000f),Vector3D(5.2242f,-2.6462f,-0.0000f),Vector3D(6.0406f,-2.6747f,-0.0000f),Vector3D(4.9299f,-3.5445f,-0.0000f),Vector3D(5.5648f,-3.0924f,-0.0000f),Vector3D(6.4591f,-2.3352f,-0.0000f),Vector3D(6.9839f,-1.9889f,-0.0000f),Vector3D(7.6540f,-1.9882f,-0.0000f),Vector3D(8.7503f,-2.3526f,-0.0000f),Vector3D(7.6949f,-1.3073f,-0.0000f),Vector3D(8.0999f,-1.4491f,-0.0000f),Vector3D(9.0435f,-1.8182f,-0.0000f),Vector3D(-4.1424f,4.6902f,0.0000f),Vector3D(-2.2728f,3.6328f,0.0000f),Vector3D(-3.6350f,4.9543f,0.0000f),Vector3D(-2.4039f,4.3053f,0.0000f),Vector3D(-3.1508f,4.3550f,0.0000f),Vector3D(-4.0218f,4.8507f,0.0000f),Vector3D(-3.0337f,4.8322f,0.0000f),Vector3D(-2.1875f,3.8430f,0.0000f),Vector3D(-2.7420f,4.0986f,0.0000f),Vector3D(-4.0956f,4.6397f,0.0000f),Vector3D(-3.7652f,4.6074f,0.0000f),Vector3D(-3.9428f,4.6466f,0.0000f),Vector3D(-3.4686f,4.5060f,0.0000f),Vector3D(-4.1243f,4.6508f,0.0000f),Vector3D(-4.1371f,4.7314f,0.0000f),Vector3D(-4.0901f,4.7981f,0.0000f),Vector3D(-3.8320f,4.9344f,0.0000f),Vector3D(-3.3415f,4.9323f,0.0000f),Vector3D(-2.7046f,4.6291f,0.0000f),Vector3D(-2.2460f,4.0493f,0.0000f),Vector3D(-2.1787f,3.7432f,0.0000f),Vector3D(-2.1991f,3.6791f,0.0000f),Vector3D(-2.3175f,3.6651f,0.0000f),Vector3D(-2.5049f,3.8961f,0.0000f),Vector3D(8.7072f,2.3338f,0.0000f),Vector3D(9.5578f,2.4301f,0.0000f),Vector3D(9.5800f,1.9059f,0.0000f),Vector3D(9.7920f,1.5528f,0.0000f),Vector3D(9.6953f,1.6902f,0.0000f),Vector3D(9.9046f,1.5702f,0.0000f),Vector3D(9.8077f,2.1218f,0.0000f),Vector3D(9.8784f,1.8961f,0.0000f),Vector3D(9.9211f,1.7069f,0.0000f),Vector3D(9.6832f,2.3382f,0.0000f),Vector3D(9.4431f,2.4608f,0.0000f),Vector3D(9.3044f,2.4688f,0.0000f),Vector3D(9.1389f,2.4629f,0.0000f),Vector3D(8.9748f,2.4452f,0.0000f),Vector3D(8.8460f,2.4240f,0.0000f),Vector3D(8.7887f,2.2550f,0.0000f),Vector3D(8.9600f,2.2468f,0.0000f),Vector3D(9.1270f,2.2353f,0.0000f),Vector3D(9.2697f,2.2148f,0.0000f),Vector3D(9.4567f,2.1376f,0.0000f),Vector3D(-5.5969f,4.0106f,0.0000f),Vector3D(-3.4185f,3.5805f,0.0000f),Vector3D(-5.2272f,2.5510f,0.0000f),Vector3D(-4.5993f,3.9681f,0.0000f),Vector3D(-5.5377f,3.5257f,0.0000f),Vector3D(-4.7676f,1.7807f,0.0000f),Vector3D(-1.9987f,1.6276f,0.0000f),Vector3D(-1.8552f,2.4810f,0.0000f),Vector3D(-5.2621f,4.0511f,0.0000f),Vector3D(-4.2956f,3.9031f,0.0000f),Vector3D(-4.9264f,4.0224f,0.0000f),Vector3D(-5.4785f,4.0628f,0.0000f),Vector3D(-5.5907f,3.7575f,0.0000f),Vector3D(-5.4208f,3.0767f,0.0000f),Vector3D(-4.3192f,1.4561f,0.0000f),Vector3D(-4.5123f,1.5437f,0.0000f),Vector3D(-3.5985f,1.4382f,0.0000f),Vector3D(-2.2771f,1.5460f,0.0000f),Vector3D(-1.5889f,2.1657f,0.0000f),Vector3D(-2.0695f,2.6894f,0.0000f)};
    IndexGroup basisIndexes[111] = {IndexGroup(57,65,67),IndexGroup(98,89,97),IndexGroup(12,54,51),IndexGroup(102,109,112),IndexGroup(69,55,64),IndexGroup(55,68,64),IndexGroup(64,66,70),IndexGroup(69,64,70),IndexGroup(60,70,66),IndexGroup(57,71,65),IndexGroup(71,60,66),IndexGroup(65,71,66),IndexGroup(61,72,67),IndexGroup(72,57,67),IndexGroup(58,73,63),IndexGroup(73,61,59),IndexGroup(63,73,59),IndexGroup(62,74,78),IndexGroup(74,58,78),IndexGroup(76,75,77),IndexGroup(75,62,77),IndexGroup(77,56,76),IndexGroup(78,77,62),IndexGroup(63,78,58),IndexGroup(59,61,67),IndexGroup(98,81,85),IndexGroup(81,83,86),IndexGroup(83,82,87),IndexGroup(82,84,87),IndexGroup(87,86,83),IndexGroup(86,85,81),IndexGroup(85,88,98),IndexGroup(88,80,98),IndexGroup(80,89,98),IndexGroup(89,90,97),IndexGroup(90,91,97),IndexGroup(97,91,96),IndexGroup(91,92,96),IndexGroup(92,93,95),IndexGroup(93,79,94),IndexGroup(93,94,95),IndexGroup(92,95,96),IndexGroup(17,9,16),IndexGroup(9,19,23),IndexGroup(9,23,16),IndexGroup(19,20,23),IndexGroup(14,15,16),IndexGroup(15,17,16),IndexGroup(13,11,14),IndexGroup(16,13,14),IndexGroup(25,24,20),IndexGroup(24,23,20),IndexGroup(20,21,25),IndexGroup(26,25,22),IndexGroup(36,35,29),IndexGroup(35,26,18),IndexGroup(29,35,18),IndexGroup(37,36,30),IndexGroup(25,21,22),IndexGroup(38,37,31),IndexGroup(36,29,30),IndexGroup(26,22,18),IndexGroup(30,31,37),IndexGroup(31,32,38),IndexGroup(39,38,32),IndexGroup(32,33,39),IndexGroup(33,34,27),IndexGroup(34,46,27),IndexGroup(46,47,27),IndexGroup(47,45,43),IndexGroup(44,47,43),IndexGroup(47,44,27),IndexGroup(45,48,43),IndexGroup(27,39,33),IndexGroup(40,43,48),IndexGroup(41,40,49),IndexGroup(42,41,49),IndexGroup(40,48,49),IndexGroup(52,28,50),IndexGroup(28,42,49),IndexGroup(50,28,49),IndexGroup(54,53,51),IndexGroup(53,52,50),IndexGroup(51,53,50),IndexGroup(10,12,51),IndexGroup(104,114,113),IndexGroup(113,115,5),IndexGroup(115,1,2),IndexGroup(3,115,2),IndexGroup(1,116,118),IndexGroup(116,105,106),IndexGroup(118,116,106),IndexGroup(105,7,117),IndexGroup(7,8,117),IndexGroup(8,0,117),IndexGroup(117,106,105),IndexGroup(118,2,1),IndexGroup(3,100,115),IndexGroup(100,5,115),IndexGroup(4,108,101),IndexGroup(108,102,101),IndexGroup(101,102,112),IndexGroup(5,4,6),IndexGroup(113,5,6),IndexGroup(6,104,113),IndexGroup(101,6,4),IndexGroup(111,103,107),IndexGroup(103,112,109),IndexGroup(111,107,110),IndexGroup(110,99,111),IndexGroup(109,107,103)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 119, 111);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 6;
    int EyesblinkIndexes[28] = {0,1,2,3,4,5,6,7,8,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,116,117,118};
    int MouthopenIndexes[46] = {9,10,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,118};
    int sadeyesIndexes[38] = {3,4,5,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,99,100,102,103,107,108,109,110,111,112,118};
    int sadmouthIndexes[47] = {9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,118};
    int angeryIndexes[50] = {0,1,2,3,4,5,6,7,8,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,99,100,102,103,104,106,107,108,109,110,111,112,113,114,115,117,118};
    int wideeyesIndexes[51] = {1,2,3,4,5,6,7,8,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118};

    Vector3D EyesblinkVectors[28] = {Vector3D(-1.3078f,-0.5367f,0.0000f),Vector3D(-0.3698f,-0.0188f,0.0000f),Vector3D(-0.5027f,-1.4057f,0.0000f),Vector3D(-0.0017f,-1.7222f,0.0000f),Vector3D(0.6938f,-2.2576f,0.0000f),Vector3D(0.4949f,-2.1613f,0.0000f),Vector3D(0.4132f,-0.5112f,0.0000f),Vector3D(-1.1075f,-0.3450f,0.0000f),Vector3D(-1.2226f,-0.4175f,0.0000f),Vector3D(1.1988f,-2.3742f,0.0000f),Vector3D(0.3120f,-2.0271f,0.0000f),Vector3D(0.6347f,-0.9329f,0.0000f),Vector3D(1.0363f,-2.4091f,0.0000f),Vector3D(0.9457f,-1.9084f,0.0000f),Vector3D(0.1732f,-0.1653f,0.0000f),Vector3D(-0.8008f,-0.1619f,0.0000f),Vector3D(-0.9414f,-1.0138f,0.0000f),Vector3D(1.2141f,-2.4645f,0.0000f),Vector3D(0.8659f,-2.3467f,0.0000f),Vector3D(1.1680f,-2.4542f,0.0000f),Vector3D(1.2456f,-2.4599f,0.0000f),Vector3D(1.1053f,-2.0828f,0.0000f),Vector3D(0.8264f,-1.4568f,0.0000f),Vector3D(0.0342f,0.0120f,0.0000f),Vector3D(0.0034f,0.0034f,0.0000f),Vector3D(-0.5197f,-0.0809f,0.0000f),Vector3D(-1.2055f,-0.6986f,0.0000f),Vector3D(-0.7250f,-1.2222f,0.0000f)};
    Vector3D MouthopenVectors[46] = {Vector3D(0.1676f,-0.2351f,-0.0001f),Vector3D(0.0078f,-1.8432f,0.0000f),Vector3D(0.0118f,0.2255f,0.0000f),Vector3D(-0.0329f,-0.0258f,0.0000f),Vector3D(0.0405f,-0.0216f,0.0000f),Vector3D(0.0633f,-0.0594f,-0.0011f),Vector3D(-0.0186f,-0.0102f,0.0000f),Vector3D(0.1224f,-0.1451f,-0.0006f),Vector3D(0.1048f,-0.6734f,0.0000f),Vector3D(0.1745f,-0.3333f,0.0000f),Vector3D(0.2036f,-0.4227f,0.0003f),Vector3D(0.1671f,-0.5149f,0.0002f),Vector3D(0.1240f,-0.6164f,0.0000f),Vector3D(-0.0145f,-0.0019f,0.0000f),Vector3D(-0.0136f,0.0182f,0.0000f),Vector3D(-0.0127f,0.0340f,0.0000f),Vector3D(-0.0115f,0.0515f,0.0000f),Vector3D(0.0296f,0.1142f,0.0000f),Vector3D(-0.0078f,0.1652f,0.0000f),Vector3D(0.0769f,-0.7175f,0.0000f),Vector3D(0.0014f,-0.7993f,0.0000f),Vector3D(-0.0541f,-0.8490f,0.0000f),Vector3D(-0.1139f,-0.9145f,0.0000f),Vector3D(-0.1469f,-0.9609f,0.0000f),Vector3D(-0.1745f,-1.0064f,0.0000f),Vector3D(-0.0094f,0.0603f,0.0000f),Vector3D(-0.0014f,0.0703f,0.0000f),Vector3D(0.0110f,0.0852f,0.0000f),Vector3D(0.0220f,0.1004f,0.0000f),Vector3D(0.0262f,0.1072f,0.0000f),Vector3D(0.0041f,0.1475f,0.0000f),Vector3D(-0.0005f,0.1532f,0.0000f),Vector3D(-0.0045f,0.1587f,0.0000f),Vector3D(0.0160f,0.1332f,0.0000f),Vector3D(0.0233f,0.1247f,0.0000f),Vector3D(-0.0807f,-1.2069f,0.0000f),Vector3D(-0.1840f,-1.0557f,0.0000f),Vector3D(-0.1308f,-1.1418f,0.0000f),Vector3D(-0.0402f,-1.2640f,0.0000f),Vector3D(0.0003f,-1.3350f,0.0000f),Vector3D(-0.0053f,-1.4218f,0.0000f),Vector3D(-0.0618f,-1.5608f,0.0000f),Vector3D(-0.0056f,0.1767f,0.0000f),Vector3D(-0.0026f,0.1853f,0.0000f),Vector3D(0.0050f,0.2053f,0.0000f),Vector3D(0.0034f,0.0004f,0.0000f)};
    Vector3D sadeyesVectors[38] = {Vector3D(0.0083f,-0.0282f,0.0000f),Vector3D(1.0045f,-0.6959f,0.0000f),Vector3D(0.7585f,-0.5600f,0.0000f),Vector3D(-0.4645f,-1.1417f,0.0000f),Vector3D(-0.1714f,0.6244f,0.0000f),Vector3D(-0.8396f,-0.8493f,0.0000f),Vector3D(-0.6028f,0.3431f,0.0000f),Vector3D(-0.4264f,-0.1911f,0.0000f),Vector3D(-0.6275f,-1.1060f,0.0000f),Vector3D(-0.9552f,-0.3522f,0.0000f),Vector3D(-0.3420f,0.6245f,0.0000f),Vector3D(-0.3634f,0.1661f,0.0000f),Vector3D(-0.4425f,-1.0888f,0.0000f),Vector3D(-0.5323f,-0.8278f,0.0000f),Vector3D(-0.5005f,-0.9757f,0.0000f),Vector3D(-0.5581f,-0.5684f,0.0000f),Vector3D(-0.4409f,-1.1144f,0.0000f),Vector3D(-0.4975f,-1.1519f,0.0000f),Vector3D(-0.5642f,-1.1394f,0.0000f),Vector3D(-0.7565f,-0.9913f,0.0000f),Vector3D(-0.9245f,-0.6196f,0.0000f),Vector3D(-0.7434f,0.0422f,0.0000f),Vector3D(-0.4691f,0.5254f,0.0000f),Vector3D(-0.2749f,0.6588f,0.0000f),Vector3D(-0.2245f,0.6627f,0.0000f),Vector3D(-0.1813f,0.5842f,0.0000f),Vector3D(-0.2893f,0.3884f,0.0000f),Vector3D(1.0849f,-1.2657f,0.0000f),Vector3D(0.5245f,-0.3785f,0.0000f),Vector3D(1.3129f,-1.0065f,0.0000f),Vector3D(0.2955f,-0.7229f,0.0000f),Vector3D(1.4885f,-1.2362f,0.0000f),Vector3D(1.1754f,-0.8661f,0.0000f),Vector3D(1.4236f,-1.1320f,0.0000f),Vector3D(1.3725f,-1.2869f,0.0000f),Vector3D(0.6967f,-1.0190f,0.0000f),Vector3D(0.0434f,-0.2113f,0.0000f),Vector3D(0.0034f,0.0004f,0.0000f)};
    Vector3D sadmouthVectors[47] = {Vector3D(2.1257f,-1.1028f,0.0000f),Vector3D(0.0073f,-0.0080f,0.0000f),Vector3D(2.4278f,-3.0998f,0.0000f),Vector3D(-0.0037f,-0.0089f,0.0000f),Vector3D(2.0978f,-2.7291f,0.0000f),Vector3D(2.1153f,-2.2381f,0.0000f),Vector3D(2.0081f,-1.7191f,0.0000f),Vector3D(2.1525f,-1.2571f,0.0000f),Vector3D(2.0912f,-1.3985f,0.0000f),Vector3D(0.0878f,-0.4715f,0.0000f),Vector3D(2.0805f,-0.9080f,0.0000f),Vector3D(1.2491f,-0.7548f,0.0000f),Vector3D(0.5771f,-0.5984f,0.0000f),Vector3D(0.3427f,-0.5300f,0.0000f),Vector3D(2.1952f,-0.7990f,0.0000f),Vector3D(1.4145f,-0.6808f,0.0000f),Vector3D(0.8598f,-0.6015f,0.0000f),Vector3D(0.1021f,-0.5254f,0.0000f),Vector3D(0.0260f,-0.3322f,0.0000f),Vector3D(-0.0857f,-0.1858f,0.0000f),Vector3D(0.0567f,-0.4840f,0.0000f),Vector3D(-0.0128f,-0.4482f,0.0000f),Vector3D(0.0112f,-0.4221f,0.0000f),Vector3D(0.0365f,-0.3885f,0.0000f),Vector3D(0.0500f,-0.3650f,0.0000f),Vector3D(0.0610f,-0.3423f,0.0000f),Vector3D(-0.0844f,-0.4917f,0.0000f),Vector3D(-0.0615f,-0.4621f,0.0000f),Vector3D(-0.0263f,-0.4179f,0.0000f),Vector3D(0.0048f,-0.3728f,0.0000f),Vector3D(0.0167f,-0.3530f,0.0000f),Vector3D(-0.0501f,-0.2366f,0.0000f),Vector3D(-0.0638f,-0.2205f,0.0000f),Vector3D(-0.0759f,-0.2048f,0.0000f),Vector3D(-0.0146f,-0.2776f,0.0000f),Vector3D(0.0073f,-0.3021f,0.0000f),Vector3D(0.0075f,-0.2517f,0.0000f),Vector3D(0.0632f,-0.3186f,0.0000f),Vector3D(0.0341f,-0.2803f,0.0000f),Vector3D(-0.0143f,-0.2266f,0.0000f),Vector3D(-0.0366f,-0.1949f,0.0000f),Vector3D(-0.0379f,-0.1536f,0.0000f),Vector3D(-0.0175f,-0.0853f,0.0000f),Vector3D(-0.0800f,-0.1524f,0.0000f),Vector3D(-0.0720f,-0.1271f,0.0000f),Vector3D(-0.0510f,-0.0682f,0.0000f),Vector3D(0.0034f,0.0004f,0.0000f)};
    Vector3D angeryVectors[50] = {Vector3D(0.0427f,-0.0056f,0.0000f),Vector3D(0.1576f,0.0427f,0.0000f),Vector3D(-0.2039f,-0.1678f,0.0000f),Vector3D(-0.0719f,-0.3459f,0.0000f),Vector3D(-0.0963f,-0.4237f,0.0000f),Vector3D(-0.0883f,-0.4477f,0.0000f),Vector3D(-0.0271f,0.0950f,0.0000f),Vector3D(0.0000f,-0.0591f,0.0000f),Vector3D(0.0788f,0.0000f,0.0000f),Vector3D(0.2050f,-0.5048f,0.0000f),Vector3D(0.0455f,-0.7470f,0.0000f),Vector3D(0.2360f,-0.5755f,0.0000f),Vector3D(0.1373f,-0.7355f,0.0000f),Vector3D(0.1508f,-0.6353f,0.0000f),Vector3D(0.2256f,-0.5225f,0.0000f),Vector3D(0.2141f,-0.6554f,0.0000f),Vector3D(0.0731f,-0.7604f,0.0000f),Vector3D(0.1126f,-0.6880f,0.0000f),Vector3D(0.1978f,-0.5106f,0.0000f),Vector3D(0.1904f,-0.5548f,0.0000f),Vector3D(0.1973f,-0.5313f,0.0000f),Vector3D(0.1741f,-0.5939f,0.0000f),Vector3D(0.1996f,-0.5069f,0.0000f),Vector3D(0.2105f,-0.5059f,0.0000f),Vector3D(0.2191f,-0.5128f,0.0000f),Vector3D(0.2351f,-0.5488f,0.0000f),Vector3D(0.2303f,-0.6149f,0.0000f),Vector3D(0.1837f,-0.6979f,0.0000f),Vector3D(0.1014f,-0.7544f,0.0000f),Vector3D(0.0596f,-0.7607f,0.0000f),Vector3D(0.0511f,-0.7573f,0.0000f),Vector3D(0.0503f,-0.7413f,0.0000f),Vector3D(0.0831f,-0.7181f,0.0000f),Vector3D(-0.0331f,-0.3983f,0.0000f),Vector3D(0.0181f,-0.4445f,0.0000f),Vector3D(-0.0460f,-0.4160f,0.0000f),Vector3D(0.0000f,-0.2759f,0.0000f),Vector3D(-0.0010f,0.1145f,0.0000f),Vector3D(-0.1235f,-0.0527f,0.0000f),Vector3D(-0.0369f,-0.3619f,0.0000f),Vector3D(-0.0523f,-0.4407f,0.0000f),Vector3D(-0.0404f,-0.3893f,0.0000f),Vector3D(-0.0379f,-0.3491f,0.0000f),Vector3D(-0.0512f,-0.2984f,0.0000f),Vector3D(0.0000f,-0.0788f,0.0000f),Vector3D(0.1577f,0.0661f,0.0000f),Vector3D(0.0166f,0.1349f,0.0000f),Vector3D(0.1573f,0.0550f,0.0000f),Vector3D(-0.0564f,0.0193f,0.0000f),Vector3D(-0.1636f,-0.1082f,0.0000f)};
    Vector3D wideeyesVectors[51] = {Vector3D(0.1566f,-0.0727f,0.0000f),Vector3D(0.0389f,0.4273f,0.0000f),Vector3D(0.1199f,0.3731f,0.0000f),Vector3D(0.1109f,0.2181f,0.0000f),Vector3D(0.1225f,0.2639f,0.0000f),Vector3D(-0.1851f,-0.0123f,0.0000f),Vector3D(-0.0465f,-0.0064f,0.0000f),Vector3D(-0.0520f,0.0017f,0.0000f),Vector3D(-0.4157f,-0.1211f,-0.0029f),Vector3D(-0.2086f,0.3876f,-0.0015f),Vector3D(-0.4992f,-0.0010f,-0.0035f),Vector3D(-0.3749f,0.3324f,-0.0026f),Vector3D(-0.3631f,0.1414f,-0.0025f),Vector3D(-0.4603f,-0.0957f,-0.0032f),Vector3D(-0.4879f,0.1555f,-0.0034f),Vector3D(-0.2647f,0.4024f,-0.0019f),Vector3D(-0.3114f,0.2534f,-0.0022f),Vector3D(-0.4044f,-0.1076f,-0.0028f),Vector3D(-0.4070f,-0.0227f,-0.0028f),Vector3D(-0.4111f,-0.0690f,-0.0029f),Vector3D(-0.3910f,0.0558f,-0.0027f),Vector3D(-0.4063f,-0.1152f,-0.0028f),Vector3D(-0.4263f,-0.1211f,-0.0030f),Vector3D(-0.4448f,-0.1113f,-0.0031f),Vector3D(-0.4878f,-0.0503f,-0.0034f),Vector3D(-0.5032f,0.0741f,-0.0035f),Vector3D(-0.4472f,0.2455f,-0.0031f),Vector3D(-0.3151f,0.3808f,-0.0022f),Vector3D(-0.2397f,0.4079f,-0.0017f),Vector3D(-0.2228f,0.4048f,-0.0016f),Vector3D(-0.2154f,0.3752f,-0.0015f),Vector3D(-0.2678f,0.3202f,-0.0019f),Vector3D(0.1394f,0.3075f,0.0000f),Vector3D(-0.1452f,0.0062f,0.0000f),Vector3D(0.1200f,0.1518f,0.0000f),Vector3D(-0.0542f,0.0307f,0.0000f),Vector3D(-0.2180f,-0.0328f,0.0000f),Vector3D(-0.0328f,-0.0273f,0.0000f),Vector3D(0.0261f,0.3397f,0.0000f),Vector3D(0.1149f,0.0807f,0.0000f),Vector3D(0.1252f,0.1845f,0.0000f),Vector3D(0.1161f,0.1166f,0.0000f),Vector3D(0.1149f,0.0576f,0.0000f),Vector3D(-0.0327f,0.0346f,0.0000f),Vector3D(-0.0960f,0.0218f,0.0000f),Vector3D(0.0197f,-0.1379f,0.0000f),Vector3D(-0.0788f,-0.1576f,0.0000f),Vector3D(0.1580f,-0.1007f,0.0000f),Vector3D(-0.0264f,-0.0467f,0.0000f),Vector3D(-0.0305f,0.2995f,0.0000f),Vector3D(0.0084f,0.4315f,0.0000f)};

    Morph morphs[6] = {
        Morph(28, EyesblinkIndexes, EyesblinkVectors),
        Morph(46, MouthopenIndexes, MouthopenVectors),
        Morph(38, sadeyesIndexes, sadeyesVectors),
        Morph(47, sadmouthIndexes, sadmouthVectors),
        Morph(50, angeryIndexes, angeryVectors),
        Morph(51, wideeyesIndexes, wideeyesVectors)
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
