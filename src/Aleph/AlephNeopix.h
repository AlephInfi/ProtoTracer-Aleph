#pragma once

#include <Adafruit_NeoPixel.h>

#define PIN 19
#define ledCt 72

Adafruit_NeoPixel ring = Adafruit_NeoPixel(ledCt, PIN, NEO_GRB + NEO_KHZ800);

void initNeopixRing(uint8_t brightness){
    ring.begin();
    ring.setBrightness(brightness); //adjust brightness here
    ring.show();
}

