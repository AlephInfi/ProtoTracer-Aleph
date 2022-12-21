#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph\Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class AlephBase{
public:
    enum Morphs {
        Blink,
        eSad,
        eMad,
        eScared,
        eBoop,
        eDoubt,
        eBlush,
        eHeart,
        m_EE,
        m_AE,
        m_UH,
        m_AR,
        m_ER,
        m_AH,
        m_OO,
        m_IH,
        m_DD,
        m_CH,
        m_SS,
        m_FF,
        m_Open,
        mSad,
        Blush
    };

private:
    Vector3D basisVertices[47] = {Vector3D(0.5052f,-0.5444f,-0.0145f),Vector3D(2.4236f,-0.7069f,-0.0145f),Vector3D(1.4999f,-0.8451f,-0.0145f),Vector3D(1.5038f,-0.6933f,-0.0145f),Vector3D(0.4683f,-0.6694f,-0.0145f),Vector3D(2.0010f,-0.5937f,-0.0145f),Vector3D(1.0589f,-0.3658f,-0.0145f),Vector3D(2.4460f,-0.6206f,-0.0145f),Vector3D(0.1506f,-0.2889f,-0.0145f),Vector3D(1.0462f,-0.5070f,-0.0145f),Vector3D(2.0062f,-0.4624f,-0.0145f),Vector3D(-0.1539f,-0.0885f,-0.0145f),Vector3D(0.7602f,-0.0267f,-0.0145f),Vector3D(-0.3989f,0.7486f,-0.0145f),Vector3D(0.3436f,0.5539f,-0.0145f),Vector3D(-0.4000f,0.3219f,-0.0145f),Vector3D(0.4024f,-0.1343f,-0.0145f),Vector3D(0.6928f,0.1866f,-0.0145f),Vector3D(0.0987f,0.6956f,-0.0145f),Vector3D(-0.2844f,0.0874f,-0.0145f),Vector3D(0.6516f,-0.0847f,-0.0145f),Vector3D(0.5446f,0.3780f,-0.0145f),Vector3D(-0.1793f,0.7669f,-0.0145f),Vector3D(-0.4337f,0.5737f,-0.0145f),Vector3D(0.1157f,-0.1353f,-0.0145f),Vector3D(0.2625f,0.7313f,-0.0145f),Vector3D(0.5523f,0.4848f,-0.0145f),Vector3D(-0.0827f,0.8260f,-0.0145f),Vector3D(0.3053f,0.8199f,-0.0145f),Vector3D(-2.2118f,-0.0872f,-0.0145f),Vector3D(-2.2112f,-0.0872f,-0.0145f),Vector3D(-2.2127f,-0.0891f,-0.0145f),Vector3D(-2.2121f,-0.0891f,-0.0145f),Vector3D(-2.2134f,-0.0872f,-0.0145f),Vector3D(-2.2127f,-0.0872f,-0.0145f),Vector3D(-2.2142f,-0.0892f,-0.0145f),Vector3D(-2.2136f,-0.0892f,-0.0145f),Vector3D(-2.2149f,-0.0872f,-0.0145f),Vector3D(-2.2142f,-0.0872f,-0.0145f),Vector3D(-2.2158f,-0.0892f,-0.0145f),Vector3D(-2.2151f,-0.0892f,-0.0145f),Vector3D(2.1495f,0.2299f,-0.0145f),Vector3D(2.2894f,0.0683f,-0.0145f),Vector3D(2.1727f,0.2785f,-0.0145f),Vector3D(2.3155f,0.2480f,-0.0145f),Vector3D(2.2554f,0.1936f,-0.0145f),Vector3D(2.3366f,0.1084f,-0.0145f)};
    IndexGroup basisIndexes[33] = {IndexGroup(9,6,3),IndexGroup(4,8,0),IndexGroup(10,7,5),IndexGroup(7,1,5),IndexGroup(3,10,5),IndexGroup(9,4,0),IndexGroup(3,5,2),IndexGroup(9,0,6),IndexGroup(3,2,9),IndexGroup(23,15,16),IndexGroup(25,28,27),IndexGroup(29,32,30),IndexGroup(33,36,35),IndexGroup(37,40,39),IndexGroup(45,46,44),IndexGroup(43,41,45),IndexGroup(45,42,46),IndexGroup(44,43,45),IndexGroup(25,26,28),IndexGroup(16,15,24),IndexGroup(15,19,24),IndexGroup(19,11,24),IndexGroup(16,20,23),IndexGroup(20,13,23),IndexGroup(13,20,12),IndexGroup(13,12,22),IndexGroup(12,17,22),IndexGroup(22,17,18),IndexGroup(17,21,18),IndexGroup(21,14,18),IndexGroup(29,31,32),IndexGroup(33,34,36),IndexGroup(37,38,40)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 47, 33);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 23;
    int BlinkIndexes[14] = {11,12,13,14,15,16,17,18,19,20,21,22,23,24};
    int eSadIndexes[18] = {11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
    int eMadIndexes[18] = {11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
    int eScaredIndexes[18] = {11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
    int eBoopIndexes[18] = {11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
    int eDoubtIndexes[18] = {11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
    int eBlushIndexes[18] = {11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
    int eHeartIndexes[18] = {11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
    int m_EEIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int m_AEIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int m_UHIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int m_ARIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int m_ERIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int m_AHIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int m_OOIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int m_IHIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int m_DDIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int m_CHIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int m_SSIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int m_FFIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int m_OpenIndexes[5] = {1,2,4,5,9};
    int mSadIndexes[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int BlushIndexes[12] = {29,30,31,32,33,34,35,36,37,38,39,40};

    Vector3D BlinkVectors[14] = {Vector3D(0.0306f,0.0550f,0.0000f),Vector3D(-0.0764f,0.0428f,0.0000f),Vector3D(0.4433f,-0.7066f,0.0000f),Vector3D(0.1406f,-0.5031f,0.0000f),Vector3D(0.2232f,-0.2697f,0.0000f),Vector3D(-0.0245f,0.0764f,0.0000f),Vector3D(0.0061f,-0.1101f,0.0000f),Vector3D(0.2538f,-0.6546f,0.0000f),Vector3D(0.0459f,-0.0612f,0.0000f),Vector3D(-0.0703f,0.0519f,0.0000f),Vector3D(0.0642f,-0.3118f,0.0000f),Vector3D(0.3699f,-0.7331f,0.0000f),Vector3D(0.3577f,-0.5197f,0.0000f),Vector3D(0.0031f,0.0764f,0.0000f)};
    Vector3D eSadVectors[18] = {Vector3D(-0.0153f,0.0520f,0.0000f),Vector3D(-0.1468f,0.0917f,0.0000f),Vector3D(0.2450f,-0.4220f,0.0000f),Vector3D(0.1753f,-0.0663f,0.0000f),Vector3D(0.0428f,-0.1682f,0.0000f),Vector3D(-0.0642f,0.1437f,0.0000f),Vector3D(-0.0622f,0.0479f,0.0000f),Vector3D(0.2219f,-0.2377f,0.0000f),Vector3D(0.0153f,-0.0520f,0.0000f),Vector3D(-0.0948f,0.0581f,0.0000f),Vector3D(0.0504f,0.0189f,0.0000f),Vector3D(0.2820f,-0.3746f,0.0000f),Vector3D(0.0566f,-0.3190f,0.0000f),Vector3D(0.0031f,0.1376f,0.0000f),Vector3D(-0.4075f,-0.1928f,0.0000f),Vector3D(-0.3974f,0.1176f,0.0000f),Vector3D(-0.3536f,-0.4434f,0.0000f),Vector3D(-0.5169f,-0.2151f,0.0000f)};
    Vector3D eMadVectors[18] = {Vector3D(0.1293f,0.0623f,0.0000f),Vector3D(-0.0039f,0.0530f,0.0000f),Vector3D(0.0433f,-0.0210f,0.0000f),Vector3D(-0.0631f,-0.0873f,0.0000f),Vector3D(0.1541f,-0.0303f,0.0000f),Vector3D(0.0619f,0.0924f,0.0000f),Vector3D(-0.0624f,-0.0183f,0.0000f),Vector3D(-0.0496f,-0.0789f,0.0000f),Vector3D(0.1775f,-0.0300f,0.0000f),Vector3D(-0.0000f,0.0802f,0.0000f),Vector3D(-0.0624f,-0.0693f,0.0000f),Vector3D(0.0272f,-0.0839f,0.0000f),Vector3D(0.1141f,-0.0829f,0.0000f),Vector3D(0.0626f,0.0756f,0.0000f),Vector3D(0.1863f,-0.1249f,0.0000f),Vector3D(0.0742f,-0.1882f,0.0000f),Vector3D(0.2737f,-0.0501f,0.0000f),Vector3D(0.2219f,-0.1559f,0.0000f)};
    Vector3D eScaredVectors[18] = {Vector3D(0.0000f,-0.0287f,0.0000f),Vector3D(0.0000f,-0.0238f,0.0000f),Vector3D(0.0000f,0.0095f,0.0000f),Vector3D(0.0000f,-0.0061f,0.0000f),Vector3D(0.0000f,0.0040f,0.0000f),Vector3D(-0.0858f,0.1025f,0.0000f),Vector3D(0.0000f,-0.0068f,0.0000f),Vector3D(0.0000f,0.0052f,0.0000f),Vector3D(0.0000f,-0.0147f,0.0000f),Vector3D(-0.0858f,0.0615f,0.0000f),Vector3D(0.0000f,0.0085f,0.0000f),Vector3D(0.0000f,0.0109f,0.0000f),Vector3D(0.0000f,-0.0045f,0.0000f),Vector3D(-0.0653f,0.0738f,0.0000f),Vector3D(-0.0227f,0.0081f,0.0000f),Vector3D(0.0063f,0.1052f,0.0000f),Vector3D(-0.0323f,-0.0240f,0.0000f),Vector3D(-0.0491f,0.0411f,0.0000f)};
    Vector3D eBoopVectors[18] = {Vector3D(-0.0389f,0.0095f,0.0000f),Vector3D(-0.0070f,0.0895f,0.0000f),Vector3D(0.2830f,-0.0921f,0.0000f),Vector3D(0.0109f,-0.1107f,0.0000f),Vector3D(0.6872f,-0.2580f,0.0000f),Vector3D(0.0004f,0.1220f,0.0000f),Vector3D(0.0514f,-0.0500f,0.0000f),Vector3D(0.0325f,-0.1053f,0.0000f),Vector3D(0.0889f,-0.1069f,0.0000f),Vector3D(0.0653f,0.1383f,0.0000f),Vector3D(0.0260f,-0.1011f,0.0000f),Vector3D(0.1067f,-0.0515f,0.0000f),Vector3D(1.0040f,-0.4362f,0.0000f),Vector3D(0.0030f,0.0830f,0.0000f),Vector3D(0.0324f,-0.0973f,0.0000f),Vector3D(0.0245f,-0.1107f,0.0000f),Vector3D(0.0361f,-0.0851f,0.0000f),Vector3D(0.0377f,-0.0990f,0.0000f)};
    Vector3D eDoubtVectors[18] = {Vector3D(-0.0326f,0.1376f,0.0000f),Vector3D(-0.0347f,0.0277f,0.0000f),Vector3D(0.0505f,-0.0910f,0.0000f),Vector3D(0.0251f,-0.1061f,0.0000f),Vector3D(0.0092f,0.0381f,0.0000f),Vector3D(-0.0420f,0.0959f,0.0000f),Vector3D(-0.0135f,-0.0300f,0.0000f),Vector3D(0.0409f,-0.1245f,0.0000f),Vector3D(-0.0145f,0.0974f,0.0000f),Vector3D(-0.0394f,0.0561f,0.0000f),Vector3D(0.0063f,-0.0730f,0.0000f),Vector3D(0.0503f,-0.1184f,0.0000f),Vector3D(0.0339f,-0.0346f,0.0000f),Vector3D(-0.0395f,0.1248f,0.0000f),Vector3D(-0.0005f,-0.0557f,0.0000f),Vector3D(-0.0176f,-0.0830f,0.0000f),Vector3D(0.0077f,-0.0305f,0.0000f),Vector3D(0.0104f,-0.0595f,0.0000f)};
    Vector3D eBlushVectors[18] = {Vector3D(0.0659f,0.3294f,0.0000f),Vector3D(-0.0075f,0.0937f,0.0000f),Vector3D(0.3442f,-0.2454f,0.0000f),Vector3D(0.1276f,-0.1467f,0.0000f),Vector3D(0.0530f,0.0549f,0.0000f),Vector3D(-0.0827f,0.3400f,0.0000f),Vector3D(0.0505f,-0.0039f,0.0000f),Vector3D(0.2277f,-0.2242f,0.0000f),Vector3D(0.0118f,0.1663f,0.0000f),Vector3D(-0.0914f,0.2442f,0.0000f),Vector3D(0.0604f,-0.0730f,0.0000f),Vector3D(0.3162f,-0.2592f,0.0000f),Vector3D(0.2220f,-0.1227f,0.0000f),Vector3D(-0.0642f,0.3775f,0.0000f),Vector3D(-0.1274f,-0.0662f,0.0000f),Vector3D(-0.0875f,0.0523f,0.0000f),Vector3D(-0.1358f,-0.1690f,0.0000f),Vector3D(-0.1722f,-0.0621f,0.0000f)};
    Vector3D eHeartVectors[18] = {Vector3D(0.0651f,0.0569f,0.0000f),Vector3D(-0.0965f,0.1622f,0.0000f),Vector3D(0.2674f,-0.0617f,0.0000f),Vector3D(0.0843f,0.0135f,0.0000f),Vector3D(0.1108f,0.0919f,0.0000f),Vector3D(-0.1455f,0.0170f,0.0000f),Vector3D(-0.0086f,0.1349f,0.0000f),Vector3D(0.1285f,-0.1146f,0.0000f),Vector3D(0.0757f,0.0914f,0.0000f),Vector3D(-0.1691f,0.0756f,0.0000f),Vector3D(0.0399f,0.0866f,0.0000f),Vector3D(0.2190f,-0.0789f,0.0000f),Vector3D(0.1887f,0.0226f,0.0000f),Vector3D(-0.0776f,-0.0658f,0.0000f),Vector3D(-0.0938f,0.0922f,0.0000f),Vector3D(-0.0513f,0.2367f,0.0000f),Vector3D(-0.0991f,-0.0319f,0.0000f),Vector3D(-0.1479f,0.0951f,0.0000f)};
    Vector3D m_EEVectors[11] = {Vector3D(0.1648f,-0.0248f,0.0000f),Vector3D(0.0198f,-0.2425f,0.0000f),Vector3D(0.0659f,-0.1446f,0.0000f),Vector3D(0.1092f,0.0030f,0.0000f),Vector3D(0.1484f,-0.0370f,0.0000f),Vector3D(0.0575f,-0.1987f,0.0000f),Vector3D(0.1275f,-0.0095f,0.0000f),Vector3D(0.0515f,0.0291f,0.0000f),Vector3D(0.1983f,-0.0239f,0.0000f),Vector3D(0.1268f,-0.0987f,0.0000f),Vector3D(0.0737f,0.0169f,0.0000f)};
    Vector3D m_AEVectors[11] = {Vector3D(0.4384f,0.0037f,0.0000f),Vector3D(0.0128f,-0.2743f,0.0000f),Vector3D(0.1836f,-0.1294f,0.0000f),Vector3D(0.2214f,0.1070f,0.0000f),Vector3D(0.4145f,-0.0558f,0.0000f),Vector3D(0.1005f,-0.2496f,0.0000f),Vector3D(0.3054f,-0.0293f,0.0000f),Vector3D(0.0262f,0.0259f,0.0000f),Vector3D(0.4955f,0.0000f,0.0000f),Vector3D(0.2751f,-0.1409f,0.0000f),Vector3D(0.1130f,0.0486f,0.0000f)};
    Vector3D m_UHVectors[11] = {Vector3D(0.3414f,0.0019f,0.0000f),Vector3D(0.0025f,-0.1941f,0.0000f),Vector3D(0.1571f,-0.1501f,0.0000f),Vector3D(0.1694f,0.0153f,0.0000f),Vector3D(0.3487f,-0.1015f,0.0000f),Vector3D(0.0834f,-0.1742f,0.0000f),Vector3D(0.2418f,0.0093f,0.0000f),Vector3D(0.0036f,0.0280f,0.0000f),Vector3D(0.4031f,0.0000f,0.0000f),Vector3D(0.2564f,-0.1292f,0.0000f),Vector3D(0.0778f,0.0220f,0.0000f)};
    Vector3D m_ARVectors[11] = {Vector3D(0.4413f,0.0000f,0.0000f),Vector3D(0.0068f,0.0000f,0.0000f),Vector3D(0.2160f,-0.0611f,0.0000f),Vector3D(0.2151f,0.0611f,0.0000f),Vector3D(0.4496f,0.0000f,0.0000f),Vector3D(0.1025f,-0.0856f,0.0000f),Vector3D(0.3159f,0.0000f,0.0000f),Vector3D(0.0017f,0.0000f,0.0000f),Vector3D(0.5216f,0.0000f,0.0000f),Vector3D(0.3187f,-0.1070f,0.0000f),Vector3D(0.1013f,0.0000f,0.0000f)};
    Vector3D m_ERVectors[11] = {Vector3D(0.4637f,-0.0027f,0.0000f),Vector3D(0.0269f,-0.0118f,0.0000f),Vector3D(0.2372f,-0.0005f,0.0000f),Vector3D(0.2364f,0.0320f,0.0000f),Vector3D(0.4721f,-0.0149f,0.0000f),Vector3D(0.1232f,-0.0211f,0.0000f),Vector3D(0.3376f,0.0052f,0.0000f),Vector3D(0.0219f,0.0036f,0.0000f),Vector3D(0.5444f,-0.0236f,0.0000f),Vector3D(0.3405f,-0.0282f,0.0000f),Vector3D(0.1220f,0.0131f,0.0000f)};
    Vector3D m_AHVectors[11] = {Vector3D(0.2001f,0.0000f,0.0000f),Vector3D(0.0067f,-0.3134f,0.0000f),Vector3D(0.0816f,-0.1923f,0.0000f),Vector3D(0.1071f,0.0000f,0.0000f),Vector3D(0.2123f,-0.0605f,0.0000f),Vector3D(0.0662f,-0.2598f,0.0000f),Vector3D(0.1485f,0.0000f,0.0000f),Vector3D(0.0194f,0.0000f,0.0000f),Vector3D(0.2331f,0.0000f,0.0000f),Vector3D(0.1763f,-0.1370f,0.0000f),Vector3D(0.0603f,0.0000f,0.0000f)};
    Vector3D m_OOVectors[11] = {Vector3D(0.9965f,0.0336f,0.0000f),Vector3D(0.0058f,-0.1804f,0.0000f),Vector3D(0.4284f,-0.0978f,0.0000f),Vector3D(0.4266f,0.0734f,0.0000f),Vector3D(0.9858f,0.0122f,0.0000f),Vector3D(0.1991f,-0.2568f,0.0000f),Vector3D(0.6263f,-0.1478f,0.0000f),Vector3D(-0.0044f,0.0000f,0.0000f),Vector3D(1.1342f,0.0000f,0.0000f),Vector3D(0.6328f,-0.2262f,0.0000f),Vector3D(0.2005f,-0.0907f,0.0000f)};
    Vector3D m_IHVectors[11] = {Vector3D(0.1385f,0.0000f,0.0000f),Vector3D(-0.0030f,-0.1897f,0.0000f),Vector3D(0.0537f,-0.1065f,0.0000f),Vector3D(0.0685f,0.0000f,0.0000f),Vector3D(0.1445f,-0.0150f,0.0000f),Vector3D(0.0376f,-0.1524f,0.0000f),Vector3D(0.0997f,0.0000f,0.0000f),Vector3D(0.0024f,0.0000f,0.0000f),Vector3D(0.1633f,0.0000f,0.0000f),Vector3D(0.1153f,-0.0673f,0.0000f),Vector3D(0.0333f,0.0000f,0.0000f)};
    Vector3D m_DDVectors[11] = {Vector3D(0.1140f,0.0000f,0.0000f),Vector3D(0.0093f,-0.1090f,0.0000f),Vector3D(0.0489f,-0.0331f,0.0000f),Vector3D(0.0628f,0.0000f,0.0000f),Vector3D(0.1188f,0.0506f,0.0000f),Vector3D(0.0411f,-0.0748f,0.0000f),Vector3D(0.0856f,0.0000f,0.0000f),Vector3D(0.0144f,0.0000f,0.0000f),Vector3D(0.1322f,0.0000f,0.0000f),Vector3D(0.0998f,0.0029f,0.0000f),Vector3D(0.0370f,0.0000f,0.0000f)};
    Vector3D m_CHVectors[11] = {Vector3D(0.0994f,0.0000f,0.0000f),Vector3D(-0.0262f,-0.1620f,0.0000f),Vector3D(0.0246f,-0.0943f,0.0000f),Vector3D(0.0368f,0.0000f,0.0000f),Vector3D(0.1039f,-0.0196f,0.0000f),Vector3D(0.0091f,-0.1315f,0.0000f),Vector3D(0.0647f,0.0000f,0.0000f),Vector3D(-0.0224f,0.0000f,0.0000f),Vector3D(0.1217f,0.0000f,0.0000f),Vector3D(0.0773f,-0.0622f,0.0000f),Vector3D(0.0052f,0.0000f,0.0000f)};
    Vector3D m_SSVectors[11] = {Vector3D(0.1875f,-0.0109f,0.0000f),Vector3D(-0.0674f,-0.0939f,0.0000f),Vector3D(0.0486f,-0.0229f,0.0000f),Vector3D(0.0564f,0.0254f,0.0000f),Vector3D(0.1934f,0.0328f,0.0000f),Vector3D(-0.0062f,-0.1822f,0.0000f),Vector3D(0.1148f,-0.0545f,0.0000f),Vector3D(-0.0672f,0.0077f,0.0000f),Vector3D(0.2340f,-0.0732f,0.0000f),Vector3D(0.1243f,-0.1037f,0.0000f),Vector3D(-0.0095f,-0.0309f,0.0000f)};
    Vector3D m_FFVectors[11] = {Vector3D(0.4740f,-0.0067f,0.0000f),Vector3D(-0.0813f,-0.0146f,0.0000f),Vector3D(0.1779f,-0.0990f,0.0000f),Vector3D(0.1873f,0.0286f,0.0000f),Vector3D(0.4864f,0.0006f,0.0000f),Vector3D(0.0475f,-0.1536f,0.0000f),Vector3D(0.3150f,-0.0490f,0.0000f),Vector3D(-0.0833f,0.0114f,0.0000f),Vector3D(0.5758f,-0.0673f,0.0000f),Vector3D(0.3287f,-0.1104f,0.0000f),Vector3D(0.0430f,-0.0261f,0.0000f)};
    Vector3D m_OpenVectors[5] = {Vector3D(-0.0320f,-0.3964f,0.0000f),Vector3D(-0.0398f,-0.1909f,0.0000f),Vector3D(0.0236f,0.0307f,0.0000f),Vector3D(0.0030f,-0.3067f,0.0000f),Vector3D(0.0452f,-0.0998f,0.0000f)};
    Vector3D mSadVectors[11] = {Vector3D(-0.0342f,-0.0833f,0.0000f),Vector3D(0.0224f,-0.0073f,0.0000f),Vector3D(-0.1302f,0.0599f,0.0000f),Vector3D(-0.1245f,0.0596f,0.0000f),Vector3D(0.0243f,-0.0418f,0.0000f),Vector3D(-0.1146f,0.1027f,0.0000f),Vector3D(-0.2384f,-0.1263f,0.0000f),Vector3D(-0.0266f,0.0193f,0.0000f),Vector3D(0.1064f,-0.4555f,0.0000f),Vector3D(-0.2204f,-0.1268f,0.0000f),Vector3D(-0.1097f,0.1024f,0.0000f)};
    Vector3D BlushVectors[12] = {Vector3D(2.1930f,-0.1404f,0.2000f),Vector3D(2.2718f,-0.1321f,0.2000f),Vector3D(2.1119f,-0.3929f,0.2000f),Vector3D(2.1907f,-0.3845f,0.2000f),Vector3D(2.0036f,-0.1654f,0.2000f),Vector3D(2.0824f,-0.1571f,0.2000f),Vector3D(1.9224f,-0.4179f,0.2000f),Vector3D(2.0012f,-0.4095f,0.2000f),Vector3D(1.8183f,-0.1899f,0.2000f),Vector3D(1.8971f,-0.1816f,0.2000f),Vector3D(1.7371f,-0.4424f,0.2000f),Vector3D(1.8159f,-0.4340f,0.2000f)};

    Morph morphs[23] = {
        Morph(14, BlinkIndexes, BlinkVectors),
        Morph(18, eSadIndexes, eSadVectors),
        Morph(18, eMadIndexes, eMadVectors),
        Morph(18, eScaredIndexes, eScaredVectors),
        Morph(18, eBoopIndexes, eBoopVectors),
        Morph(18, eDoubtIndexes, eDoubtVectors),
        Morph(18, eBlushIndexes, eBlushVectors),
        Morph(18, eHeartIndexes, eHeartVectors),
        Morph(11, m_EEIndexes, m_EEVectors),
        Morph(11, m_AEIndexes, m_AEVectors),
        Morph(11, m_UHIndexes, m_UHVectors),
        Morph(11, m_ARIndexes, m_ARVectors),
        Morph(11, m_ERIndexes, m_ERVectors),
        Morph(11, m_AHIndexes, m_AHVectors),
        Morph(11, m_OOIndexes, m_OOVectors),
        Morph(11, m_IHIndexes, m_IHVectors),
        Morph(11, m_DDIndexes, m_DDVectors),
        Morph(11, m_CHIndexes, m_CHVectors),
        Morph(11, m_SSIndexes, m_SSVectors),
        Morph(11, m_FFIndexes, m_FFVectors),
        Morph(5, m_OpenIndexes, m_OpenVectors),
        Morph(11, mSadIndexes, mSadVectors),
        Morph(12, BlushIndexes, BlushVectors)
    };

public:
    AlephBase(){}

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
