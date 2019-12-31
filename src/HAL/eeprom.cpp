#include "eeprom.h"
#include <Wire.h>
#include <Arduino.h>


void EEPROM::init()
{
    pinMode(PIN_WIRE_SCL, OUTPUT_OPEN_DRAIN);
    pinMode(PIN_WIRE_SDA, OUTPUT_OPEN_DRAIN);
    digitalWrite(PIN_WIRE_SCL, HIGH);
    digitalWrite(PIN_WIRE_SDA, HIGH);
    Wire.begin();  

}


uint8_t EEPROM::readEEPROM(int deviceaddress, unsigned int eeaddress) 
{
    uint8_t rdata = 0xFF;
    Wire.beginTransmission(deviceaddress);
    Wire.write(eeaddress);
    Wire.endTransmission(true);
    
    Wire.requestFrom(deviceaddress,1);
    
    if (Wire.available()) rdata = Wire.read();
    
    return rdata;
}

void EEPROM::writeEEPROM(int deviceaddress, unsigned int eeaddress, uint8_t data ) 
{
    Wire.beginTransmission(deviceaddress);
    Wire.write(eeaddress);
    Wire.write(data);
    Wire.endTransmission(true);
    
    delay(5);
}