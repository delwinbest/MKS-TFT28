#include "includes.h"
#include "eeprom.h"
#include "eeprom_config.h"


EEPROM eeprom;
extern LCD lcd;
extern URTouch myTouch;


void EEPROMConfig::loadConfig() {
  lcd.lcd_console_log("Load EEPROM Config..");
  eeprom.init();
  // Validate Config else request restore to default
  if (eeprom.readEEPROM(eeprom_address, CONFIG_START + sizeof(settings) - 2) == settings.config_version[2] &&
      eeprom.readEEPROM(eeprom_address, CONFIG_START + sizeof(settings) - 3) == settings.config_version[1] &&
      eeprom.readEEPROM(eeprom_address, CONFIG_START + sizeof(settings) - 4) == settings.config_version[0])
  { // reads settings from EEPROM
    for (unsigned int t=0; t<sizeof(settings); t++)
      *((char*)&settings + t) = eeprom.readEEPROM(eeprom_address, CONFIG_START + t);
  } else {
    // settings aren't valid! will overwrite with default settings
    lcd.lcd_console_log("config_version mismatch: " + 
        String(eeprom.readEEPROM(eeprom_address, CONFIG_START + sizeof(settings) - 2), HEX) + 
        String(eeprom.readEEPROM(eeprom_address, CONFIG_START + sizeof(settings) - 3), HEX) +
        String(eeprom.readEEPROM(eeprom_address, CONFIG_START + sizeof(settings) - 4), HEX) );
    lcd.lcd_console_log("Touch screen to restore default");
    while(!myTouch.dataAvailable()){};
    saveConfig();
  }
  lcd.lcd_console_log("Config Ver: " + String(settings.config_version));
}

void EEPROMConfig::saveConfig() {
  for (unsigned int t=0; t<sizeof(settings); t++)
  { // writes to EEPROM
    eeprom.writeEEPROM(eeprom_address, CONFIG_START + t, *((char*)&settings + t));
    // and verifies the data
    if (eeprom.readEEPROM(eeprom_address, CONFIG_START + t) != *((char*)&settings + t))
    {
      // error writing to EEPROM
    }
  }
}
