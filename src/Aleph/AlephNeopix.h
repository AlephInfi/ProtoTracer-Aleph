#pragma once

#include <Adafruit_NeoPixel.h>

/** Aleph needed LED strips:
 *  1 - side circles, horns
 *  2 - on-body strips
 *  3 - wings (?)
 */

class AlephNeopixel{
    private:
    Adafruit_NeoPixel ring;
    const uint16_t ledCt = 70;
    const uint8_t pin = 22;

    public:
    AlephNeopixel(){};

    void Initialize(uint8_t brightness){ // Initialize with number of leds (set) and brightness
        ring = Adafruit_NeoPixel(ledCt, pin, NEO_GRB + NEO_KHZ800); 
        ring.setPin(pin);
        ring.setBrightness(brightness);
        ring.begin();
    }

    void setBrightness(uint8_t brightness){
        ring.setBrightness(brightness);
    }

    uint8_t GetBrightness(){
        return ring.getBrightness();
    }

    uint8_t GetLEDCt(){
        return ledCt;
    } 

    void SetColor(uint16_t n, uint8_t R, uint8_t G, uint8_t B){
        ring.setPixelColor(n, R, G, B);
    }

    void Display(){
        ring.show();
    }
};

AlephNeopixel AlephNeopix;