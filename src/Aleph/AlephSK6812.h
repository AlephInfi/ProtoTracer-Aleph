#pragma once

#include <NeoPixelBus.h>

/** Aleph needed LED strips:
 *  1 - side circles, horns
 *  2 - on-body strips
 *  3 - wings (?)
 */

class AlephNeopixel{
    private:
    static const uint16_t ledCt = 70;
    static const uint8_t pin = 22;

    #define colorSaturation 128

    static NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod> ring;

    public:
    AlephNeopixel(){};

    void Initialize(){
        ring.Begin();
        ring.Show();
    }

    uint8_t GetLEDCt(){
        return ledCt;
    } 

    void SetColor(uint16_t n, uint8_t R, uint8_t G, uint8_t B, uint8_t W){\
        ring.SetPixelColor(n, RgbwColor(R, G, B, W));
    }

    void Display(){
        ring.Show();
    }
};

NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod> AlephNeopixel::ring(AlephNeopixel::ledCt, AlephNeopixel::pin);
AlephNeopixel AlephNeopix;