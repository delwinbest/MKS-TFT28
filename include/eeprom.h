#ifndef __eeprom_H
#define __eeprom_H

#define     eeprom_address 0x50    //Address of 24LC256 eeprom chip
#include "stdint.h"

class EEPROM 
{
    public:    
        void init();
        uint8_t readEEPROM(int deviceaddress, unsigned int eeaddress );
        void writeEEPROM(int deviceaddress, unsigned int eeaddress, uint8_t data );
};


#endif