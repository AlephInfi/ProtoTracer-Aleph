#pragma once

#include "..\Material.h"
#include "..\GradientMaterial.h"
#include "..\..\Controls\BouncePhysics.h"

class EQ : public Material {
private:
    BouncePhysics* bPhy[128];
    Vector2D size;
    Vector2D offset;
    float angle = 0.0f;
    float hueAngle = 0.0f;
    uint8_t colors;
    float* data;
    float bounceData[128];
    uint8_t bins = 128;
    bool mirrorY = false;
    bool flipY = false;
    bool bounce = false;
    bool UseYWall = false;
    
    RGBColor LowSpectrum[2] = {RGBColor(255, 0, 0), RGBColor(255, 100, 0)};
    GradientMaterial<2> LM = GradientMaterial<2>(LowSpectrum, 1.0f, false);

    RGBColor MidSpectrum[3] = {RGBColor(200, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 100)};
    GradientMaterial<3> MM = GradientMaterial<3>(MidSpectrum, 1.0f, false);

    RGBColor HighSpectrum[2] = {RGBColor(0, 50, 255), RGBColor(60, 0, 255)};
    GradientMaterial<2> HM = GradientMaterial<2>(HighSpectrum, 1.0f, false);

    Material* materialLows;
    Material* materialMids;
    Material* materialHighs;

public:
    EQ(Vector2D size, Vector2D offset, bool bounce = false, bool flipY = false, bool mirrorY = false){
        this->size = size.Divide(2.0f);
        this->offset = offset;
        this->mirrorY = mirrorY;
        this->flipY = flipY;
        this->bounce = bounce;

        this->materialLows = &LM;
        this->materialMids = &MM;
        this->materialHighs = &HM;

        if (bounce){
            for (uint8_t i = 0; i < 128; i++){
                bPhy[i] = new BouncePhysics(27.0f, 15.0f);
            }
        }
    }

    ~EQ(){
        for (uint8_t i = 0; i < 128; i++){
            delete bPhy[i];
        }

    }

    void SetMirrorYState(bool state){
        mirrorY = state;
    }

    void SetFlipYState(bool state){
        flipY = state;
    }

    void SetMaterial(Material* material){
        this->materialLows = materialLows;
    }

    float* GetFourierData(){
        if(bounce){
            return bounceData;
        }
        else{
            return data;
        }
    }

    void SetSize(Vector2D size){
        this->size = size.Divide(2.0f);
    }

    void SetPosition(Vector2D offset){
        this->offset = offset;
    }

    void SetRotation(float angle){
        this->angle = angle;
    }

    void SetHueAngle(float hueAngle){
        this->hueAngle = hueAngle;
    }

    void SetYWallUsage(bool YWall){
        this->UseYWall = YWall;
    }

    void Update(float* readData){
        data = readData;
        
        for (uint8_t i = 0; i < 128; i++){
            if(bounce){
                bounceData[i] = bPhy[i]->Calculate(data[i], 0.1f);
            }
            else{
                bounceData[i] = data[i];
            }
        }
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override {
        if(UseYWall){
            Vector2D rPos = Mathematics::IsClose(angle, 0.0f, 0.1f) ? Vector2D(position.X, position.Y) - offset : Vector2D(position.X, position.Y).Rotate(angle, offset) - offset;

            if (-size.Y > rPos.Y && size.Y < rPos.Y) return RGBColor();
            if (-size.X > rPos.X && size.X < rPos.X) return RGBColor();
            
            uint8_t y = uint8_t(Mathematics::Map(rPos.Y, -size.Y, size.Y, float(bins), 0.0f));

            if(bins > y && 0 > y) return RGBColor();

            float yDistance = size.Y / float(bins) * y - size.Y;
            float yDistance2 = size.Y / float(bins) * (y + 1) - size.Y;
            float ratio = Mathematics::Map(rPos.Y, yDistance, yDistance2, 0.0f, 1.0f);//ratio between two bins
            float height = bounce ? Mathematics::CosineInterpolation(bounceData[y], bounceData[y + 1], ratio) : Mathematics::CosineInterpolation(data[y], data[y + 1], ratio);//0->1.0f of max height of color
            float xColor;

            height = height * 3.0f;

            if(mirrorY){
                xColor = Mathematics::Map(fabsf(rPos.X), size.X, 0.0f, 1.0f, 0.0f);
            }
            else{
                xColor = Mathematics::Map(rPos.X, -size.X, size.X, 1.0f, 0.0f);
            }
            
            if(flipY) xColor = 1.0f - xColor;

            if (xColor <= height){
                if((y <= size.Y) && (y >= 2 * (size.Y) / 3)){
                    return materialHighs->GetRGB(Vector3D(1.0f - height - xColor, 0, 0), Vector3D(), Vector3D());
                }
                else if((y <= 2 * (size.Y) / 3) && (y >= (size.Y) / 4)){
                    return materialMids->GetRGB(Vector3D(1.0f - height - xColor, 0, 0), Vector3D(), Vector3D());
                }
                else{
                    return materialLows->GetRGB(Vector3D(1.0f - height - xColor, 0, 0), Vector3D(), Vector3D());
                }
            }
            else{
                return RGBColor(0, 0, 0);
            }
        }
        else{
            Vector2D rPos = Mathematics::IsClose(angle, 0.0f, 0.1f) ? Vector2D(position.X, position.Y) - offset : Vector2D(position.X, position.Y).Rotate(angle, offset) - offset;

            if (-size.X > rPos.X && size.X < rPos.X) return RGBColor();
            if (-size.Y > rPos.Y && size.Y < rPos.Y) return RGBColor();
            
            uint8_t x = uint8_t(Mathematics::Map(rPos.X, -size.X, size.X, float(bins), 0.0f));

            if(bins > x && 0 > x) return RGBColor();

            float xDistance = size.X / float(bins) * x - size.X;
            float xDistance2 = size.X / float(bins) * (x + 1) - size.X;
            float ratio = Mathematics::Map(rPos.X, xDistance, xDistance2, 0.0f, 1.0f);//ratio between two bins
            float height = bounce ? Mathematics::CosineInterpolation(bounceData[x], bounceData[x + 1], ratio) : Mathematics::CosineInterpolation(data[x], data[x + 1], ratio);//0->1.0f of max height of color
            float yColor;

            height = height * 3.0f;

            if(mirrorY){
                yColor = Mathematics::Map(fabsf(rPos.Y), size.Y, 0.0f, 1.0f, 0.0f);
            }
            else{
                yColor = Mathematics::Map(rPos.Y, -size.Y, size.Y, 1.0f, 0.0f);
            }
            
            if(flipY) yColor = 1.0f - yColor;

            if (yColor <= height){
                if(x <= size.X && x >= 2 * (size.X) / 3){
                    return materialLows->GetRGB(Vector3D(1.0f - height - yColor, 0, 0), Vector3D(), Vector3D()).HueShift(180);
                }
                else if(x <= 2 * (size.X) / 3 && x >= (size.X) / 4){
                    return materialLows->GetRGB(Vector3D(1.0f - height - yColor, 0, 0), Vector3D(), Vector3D()).HueShift(120);
                }
                else{
                    return materialLows->GetRGB(Vector3D(1.0f - height - yColor, 0, 0), Vector3D(), Vector3D()).HueShift(60);
                }
            }
            else{
                return RGBColor(0, 0, 0);
            }
        }
    }
};
