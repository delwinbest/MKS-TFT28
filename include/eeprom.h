#ifndef __eeprom_H
#define __eeprom_H

#define     eeprom_address 0x50    //Address of 24LC256 eeprom chip

class EEPROM 
{
    public:    
        void init();
        byte readEEPROM(int deviceaddress, unsigned int eeaddress );
        void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data );
};


#endif