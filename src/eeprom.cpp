#include "includes.h"
#include <Wire.h>



void EEPROM::init()
{
    pinMode(PIN_WIRE_SCL, OUTPUT_OPEN_DRAIN);
    pinMode(PIN_WIRE_SDA, OUTPUT_OPEN_DRAIN);
    digitalWrite(PIN_WIRE_SCL, HIGH);
    digitalWrite(PIN_WIRE_SDA, HIGH);
    Wire.begin();  

}


byte EEPROM::readEEPROM(int deviceaddress, unsigned int eeaddress) 
{
    byte rdata = 0xFF;
    Wire.beginTransmission(deviceaddress);
    Wire.write(eeaddress);
    Wire.endTransmission(true);
    
    Wire.requestFrom(deviceaddress,1);
    
    if (Wire.available()) rdata = Wire.read();
    
    return rdata;
}

void EEPROM::writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) 
{
    Wire.beginTransmission(deviceaddress);
    Wire.write(eeaddress);
    Wire.write(data);
    Wire.endTransmission(true);
    
    delay(5);
}