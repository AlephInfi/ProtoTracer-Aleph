#pragma once

#include <EEPROM.h>
#include <strings.h>
#include <Arduino.h>

class EEPROMHandler{
    public:
    EEPROMHandler(){
        for(int n = 0; n < indexes; n++){
            Defined[n] = false;
        }
    }

    enum IndexName{};

    static const uint8_t indexes = 30; //30 max indexes by default
    static bool Defined[indexes]; //true = value already defined

    //WRITE TO EEPROM AT AN UNDEFINED INDEX
    static bool WriteEEPROM(uint16_t index, uint8_t value){
        if(EEPROM.read(index) == 255){//If defined index is unused, write at the defined address
            EEPROM.write(index, value);
            Defined[index] = true;
            return true;
        }  

        else if(EEPROM.read(index) != 255){
            for(int i = index; (i < (index + 50)); i++){ /*arbritrary value added to index, assumes index is somewhat close to existing max*/
                if(EEPROM.read(i) == 255){
                    EEPROM.write(i, value); //If EEPROM reads a non-used address, then write at that address
                    Defined[index] = true;
                    return true;
                }
                else{
                    if(Defined[index] == true) Defined[index] = false;
                }
            }
        }
        return false;
    }

    //Read settings from EEPROM
    static uint8_t ReadEEPROM(uint16_t index){
        return EEPROM.read(index);
    }
};

const uint8_t EEPROMHandler::indexes;
bool EEPROMHandler::Defined[indexes];

static EEPROMHandler EEPROMObj __attribute__ ((unused)) = EEPROMHandler();