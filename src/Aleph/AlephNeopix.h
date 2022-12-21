#pragma once

#include <Adafruit_NeoPixel.h>

#define PIN 19 // May need to change
#define ledCt 72 // May also need to change default  - 11/3/22

/** Aleph needed LED strips:
 *  1 - side circles, horns
 *  2 - on-body strips
 *  3 - wings (?)
 */

class addedLEDs{
    private:

    static Adafruit_NeoPixel ring;
    static bool status; // Debugging purposes

    public:

    enum modes{
        
    };

    static bool Initialize(uint8_t numleds, uint8_t brightness){ // Initialize with number of leds and brightness
        ring.updateLength(numleds);
        ring.setBrightness(brightness);

        ring.begin();
        status = true;
    }

    void setBrightness(uint8_t brightness){
        ring.setBrightness(brightness);
    }

    uint8_t GetBrightness(){
        return ring.getBrightness();
    }

    uint8_t GetLEDCt(){
        return ring.numPixels();
    }

    void syncToFace(){
        
    }
};

Adafruit_NeoPixel addedLEDs::ring = Adafruit_NeoPixel(ledCt, PIN, NEO_GRB + NEO_KHZ800);

