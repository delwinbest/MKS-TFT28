#include "includes.h"
#include<SPIMemory.h>

LCD lcd;
EEPROM eeprom;
URTouch  myTouch(PIN_SPI1_SCK , TOUCH_CS, PIN_SPI1_MOSI,PIN_SPI1_MISO, TOUCH_DI);
EEPROMConfig eeprom_config;
SDCard sdcard;

SPIFlash flash(FLASH_CS);

int data_address=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  //TX=PA9,RX=PA10
  Serial.println("Booting");
  BUZZER_Init();
  // Setup the LCD
  lcd.init();
  lcd.lcd_console_log("Booting...");
  //lcd.lcd_console_log("LCD Register Read Test...");
  // serialprint_lcd_registers();
  //lcd.lcdprint_lcd_registers();
  //Touch
  lcd.lcd_console_log("URTouch Init...");
  myTouch.InitTouch(1);
  myTouch.setPrecision(PREC_MEDIUM);
  eeprom.init();
  eeprom_config.loadConfig();
  sdcard.init();
  if(sdcard.root.name() != NULL){
    sdcard.printDirectory(sdcard.root);
  }
  lcd.lcd_console_log("SPIFlash Begin...");
  flash.begin(MB(8));
  uint32_t JEDEC = flash.getJEDECID();
  long long _uniqueID = flash.getUniqueID();
  if (JEDEC) {
    lcd.lcd_console_log("JEDECID ID: 0x" + String(JEDEC, HEX));
    lcd.lcd_console_log("Unique ID: 0x" + String(uint32_t(_uniqueID >> 32), HEX) + String(uint32_t(_uniqueID), HEX));
  } else {
    lcd.lcd_console_log("SPIFlash ERR");
  }
  

  lcd.lcd_console_log("End Setup");
  lcd.consoleLine = 1;
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  
  if(myTouch.dataAvailable()){
    myTouch.read();
    lcd.lcd_console_log("X " + String(myTouch.getX()) + " Y " + String(myTouch.getX()));
  }

}