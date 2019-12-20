#ifndef __eeprom_config_H
#define __eeprom_config_H

// ID of the settings block
#define CONFIG_VERSION "005"

// EEPROM CONFIG START ADDRESS
#define CONFIG_START 0

class EEPROMConfig 
{
    public:    
        // Config Structure AND Default Values
        // Add new configuration variables here, and bump config version to overwrite
        // Access these variables from the extern eeprom_config object using eeprom_config.settings.$var
        struct ConfigStoreStruct {
            // The variables of your settings
            int a, b;
            char c;
            long d;
            float e[6];
            // Require version ID for version control and config completeness validation
            char config_version[4]; // Should be last variable of struct
        };

        // Deafult Config Values
        ConfigStoreStruct settings = {
            // The default values
            110, 1994,
            'c',
            10000,
            {4.5, 5.5, 7, 8.5, 10, 12},
            CONFIG_VERSION
        };
        void loadConfig();
        void saveConfig();
};

#endif