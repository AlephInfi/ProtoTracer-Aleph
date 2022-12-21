#pragma once

#include "AnimationTrack.h"

template<size_t parameters>
class BlinkTrack : public AnimationTrack<parameters, 10>{
private:
    void AddKeyFrames(){
        this->track.AddKeyFrame(0.0f, 0.0f);
        this->track.AddKeyFrame(2.85f, 0.0f);
        this->track.AddKeyFrame(3.0f, 1.0f);
        this->track.AddKeyFrame(3.15f, 0.0f);
        this->track.AddKeyFrame(9.85f, 0.0f);
        this->track.AddKeyFrame(10.0f, 1.0f);
        this->track.AddKeyFrame(10.15f, 0.0f);
        this->track.AddKeyFrame(10.85f, 0.0f);
        this->track.AddKeyFrame(11.0f, 1.0f);
        this->track.AddKeyFrame(11.15f, 0.0f);
        this->track.AddKeyFrame(15.0f, 0.0f);
    }

public:
    BlinkTrack(){
        AddKeyFrames();
    }

};
    