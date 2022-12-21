#include <Arduino.h>
//#include <Adafruit_SPIDevice.h>
#include <Adafruit_VL53L0X.h>
#include "..\Filter\MinFilter.h"
#include "..\Signals\TimeStep.h"

class BoopSensor{
private:
    static Adafruit_VL53L0X tof;
    static VL53L0X_RangingMeasurementData_t measure;
    static uint16_t proximity;
    static uint16_t threshold;
    static MinFilter<10> minF;
    static TimeStep timeStep;
    static float minimum;
    static bool didBegin;

public:
    static bool Initialize(uint8_t threshold) {//timeout in milliseconds and threshold is minimum for detection (0 is far away, 255 is touching)
        BoopSensor::threshold = threshold;

        Wire.begin();

        Wire.setSCL(19);
        Wire.setSDA(18);

        didBegin = tof.begin();

        return didBegin;
    }

    static bool isBooped(){
        GetValue();
        
        if(timeStep.IsReady()){
            minimum = minF.Filter(proximity);
        }

        return proximity > minimum + threshold;
    }

    static uint8_t GetValue(){
        tof.rangingTest(&measure, false);
        if (didBegin && measure.RangeStatus != 4){
            proximity = measure.RangeMilliMeter;
        }

        return proximity;
    }
};

Adafruit_VL53L0X BoopSensor::tof;
VL53L0X_RangingMeasurementData_t BoopSensor::measure;
uint16_t BoopSensor::proximity;
uint16_t BoopSensor::threshold;

MinFilter<10> BoopSensor::minF = MinFilter<10>(false);
TimeStep BoopSensor::timeStep = TimeStep(5);
float BoopSensor::minimum = 0.0f;
bool BoopSensor::didBegin = false;