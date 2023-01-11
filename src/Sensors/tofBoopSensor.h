#include <Arduino.h>
//#include <Adafruit_SPIDevice.h>
#include <Adafruit_VL53L0X.h>
#include "..\Signals\TimeStep.h"
#include "..\Filter\MinFilter.h"

class BoopSensor{
private:
    static Adafruit_VL53L0X tof;
    static uint16_t proximity;
    static uint16_t threshold;
    static uint16_t minimum;
    static long previousMillis;
    static long previousMillis2;
    static bool didBegin;

public:
    static bool Initialize(uint16_t threshold) {//timeout in milliseconds and threshold is maximum distance before not being detected (in millimeters)
        BoopSensor::threshold = threshold;

        Wire.begin();

        Wire.setSCL(19);
        Wire.setSDA(18);

        didBegin = (tof.begin()) && (tof.startRangeContinuous(100));

        return didBegin;
    }

    static bool isBooped(){
        if(millis() - previousMillis > 100){
            previousMillis = millis();
            if (didBegin){
                proximity = tof.readRange();
            }
            else proximity = 0;
        }

        if(millis() - previousMillis2 > 2000){
            previousMillis2 = millis();
            minimum = 60;
        } 

        if(proximity < minimum) minimum = proximity;

        return (proximity < minimum + threshold);
    }
};

Adafruit_VL53L0X BoopSensor::tof = Adafruit_VL53L0X();
uint16_t BoopSensor::proximity;
uint16_t BoopSensor::threshold;
uint16_t BoopSensor::minimum = 60;
long BoopSensor::previousMillis = 0;
long BoopSensor::previousMillis2 = 0;
bool BoopSensor::didBegin = false;