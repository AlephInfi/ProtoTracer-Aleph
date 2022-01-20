#pragma once

#include "Arduino.h"
#include "KeyFrame.h"
#include "..\Math\Mathematics.h"

class KeyFrameTrack{
public:
    enum InterpolationMethod{
        Linear,
        Cosine,
        Step
    };

private:
    const int maxParameters;
    const int maxKeyFrames;
    InterpolationMethod interpMethod;
    float** parameters;
    KeyFrame** keyFrames;
    float min = 0.0f;
    float max = 0.0f;
    float startFrameTime = 100000.0f;//initialize to out of bounds
    float stopFrameTime = -100000.0f;//initialize to out of bounds
    int currentFrames = 0;
    int currentParameters = 0;
    long startTime = 0;
    bool isActive = true;
    float parameterValue = 0.0f;
    float currentTime = 0.0f;
    float timeOffset = 0.0f;

    //shift array from position
    void ShiftKeyFrameArray(int position){
        for(int i = position; i < currentFrames; i++){
            keyFrames[i + 1] = keyFrames[i];
        }
    }

public:
    KeyFrameTrack(int maxParameters, float min, float max, int maxKeyFrames, InterpolationMethod interpMethod) : maxParameters(maxParameters), maxKeyFrames(maxKeyFrames){
        this->min = min;
        this->max = max;
        this->startTime = millis();
        this->interpMethod = interpMethod;

        keyFrames = new KeyFrame*[maxKeyFrames];
        parameters = new float*[maxParameters];
    }

    ~KeyFrameTrack(){
        for (int i = 0; i < currentFrames; i++){
            delete keyFrames[i];
        }

        delete[] keyFrames;
    }

    float GetCurrentTime(){
        currentTime = fmod(millis() / 1000.0f + timeOffset, stopFrameTime - startFrameTime) + startFrameTime;//normalize time and add offset

        return currentTime;
    }

    void SetCurrentTime(float setTime){
        GetCurrentTime();

        //Test case: current time = 1.32s, set time = 1.09s, 1.59s
        timeOffset = setTime - currentTime;//1.59 - 1.32 = 0.27, 1.09 - 1.32 = -0.23
    }

    void Pause(){
        isActive = false;
    }

    void Play(){
        isActive = true;
    }

    void AddParameter(float* parameter){
        if(currentParameters < maxParameters){
            parameters[currentParameters] = parameter;
            currentParameters++;
        }
    }

    void AddKeyFrame(float time, float value){
        if (currentFrames < maxKeyFrames){
            value = Mathematics::Constrain(value, min, max);

            if(currentFrames == 0){
                keyFrames[0] = new KeyFrame(time, value);
            }
            else if (time > this->stopFrameTime){
                keyFrames[currentFrames] = new KeyFrame(time, value);
            }
            else{
                for(int i = 0; i < currentFrames; i++){
                    if(time < keyFrames[i]->Time){
                        ShiftKeyFrameArray(i);
                        keyFrames[i] = new KeyFrame(time, value);
                        break;
                    }
                }
            }
            
            currentFrames++;

            this->startFrameTime = time < this->startFrameTime ? time : this->startFrameTime;//set new min time if lesser than current
            this->stopFrameTime = time > this->stopFrameTime ? time : this->stopFrameTime;//Set new max time if greater than current
        }
    }

    float GetParameterValue(){
        return parameterValue;
    }

    void Reset(){
        for(int i = 0; i < currentParameters; i++){
            *(this->parameters[i]) = min;
        }
    }

    void Update(){
        GetCurrentTime();

        byte previousFrame = 0, nextFrame = 0;

        //find current time, find keyframe before and after
        if(currentFrames > 0 && isActive){
            for (int i = currentFrames - 1; i >= 0; i--){
                if (currentTime >= keyFrames[i]->Time){
                    previousFrame = i;
                    nextFrame = i + 1;

                    break;
                }
            }

            float ratio = Mathematics::Map(currentTime, keyFrames[previousFrame]->Time, keyFrames[nextFrame]->Time, 0.0f, 1.0f);
            float parameter = 0.0f;

            switch(interpMethod){
                case Cosine:
                    parameter = Mathematics::CosineInterpolation(keyFrames[previousFrame]->Value, keyFrames[nextFrame]->Value, ratio);
                    break;
                case Step:
                    parameter = keyFrames[previousFrame]->Value;
                    break;
                default://Linear
                    parameter = Mathematics::Map(ratio, 0.0f, 1.0f, keyFrames[previousFrame]->Value, keyFrames[nextFrame]->Value);
                    break;

            }

            parameterValue = parameter;

            if (currentParameters > 0){//Update if not parameters are linked
                for(int i = 0; i < currentParameters; i++){
                    *(this->parameters[i]) = parameter;
                }
            }
        }
    }

};
