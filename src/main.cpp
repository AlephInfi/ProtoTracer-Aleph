#include "Controllers\SmartMatrixHUB75.h"


const uint8_t maxBrightness = 20;

#include "Aleph\AlephAnim.h"
#include "Aleph\AlephNeopix.h"

Animation* animation = new AlephAnim();
Controller* controller = new SmartMatrixHUB75(maxBrightness);

sStepper motors;

void setup() {
    Serial.begin(115200);
    Serial.println("\nStarting...");
    //initNeopixRing(30);
    //controller->Initialize();
}

void loop(){
    motors.setSpeeds(60);
}

/*
void loop() {
    float ratio = (float)(millis() % 5000) / 5000.0f;
    animation->UpdateTime(ratio);

    controller->Render(animation->GetScene());

    controller->Display();
    Serial.print("Rendered in ");
    Serial.print(controller->GetRenderTime(), 4);
    Serial.println("s");
}
*/