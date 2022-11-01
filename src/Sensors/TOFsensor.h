#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

class BoopSensor{
    private:
        static Adafruit_VL53L0X boopsensor;
        static VL53L0X_RangingMeasurementData_t measure;
        static uint16_t boopRange;

    public:
        static bool Initialize(uint16_t r){
            if(boopsensor.begin()){
                BoopSensor::boopRange = r;
                return true;
            }
            else return false;
        };

        bool isBooped(){
            boopsensor.rangingTest(&measure, false);
            if (measure.RangeStatus != 4){
                uint16_t d = measure.RangeMilliMeter;
                if(d <= BoopSensor::boopRange){
                    return true;
                }
                else return false;
            }
        }

        uint16_t GetDist(){
            boopsensor.rangingTest(&measure, false);
            return measure.RangeMilliMeter;
        }
};

Adafruit_VL53L0X boopsensor = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure;
uint16_t boopRange;