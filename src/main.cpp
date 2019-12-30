#include "includes.h"

LCD lcd;
URTouch  myTouch(PIN_SPI1_SCK , TOUCH_CS, PIN_SPI1_MOSI,PIN_SPI1_MISO, TOUCH_DI);
EEPROMConfig eeprom_config;
SDCard sdcard;

//SPIFlash flash(FLASH_CS);

int data_address=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  //TX=PA9,RX=PA10
  Serial.println("Booting");
  BUZZER_Init();
  // Setup the LCD
  lcd.init();
  lcd.lcd_console_log("Booting...");
  lcd.lcd_console_log("URTouch Init...");
  myTouch.InitTouch(1);
  myTouch.setPrecision(PREC_MEDIUM);
  eeprom_config.loadConfig();
  lcd.lcd_console_log("SD Test Init...");
  // if(SD_Init() == 0){
  //   lcd.lcd_console_log("SD Init returned 0");
  // } else {
  //   lcd.lcd_console_log("SD Init failed");
  // }
  uint32_t sectorcount;
  sectorcount = SD_Get_Sector_Count();
  if (sectorcount) {
    lcd.lcd_console_log("Sector Count: " + String(uint32_t(sectorcount), DEC));
  } else {
    lcd.lcd_console_log("SD ERR");
  }

  sdcard.init();
  if(sdcard.root.name() != NULL){
    sdcard.printDirectory(sdcard.root);
  }
  lcd.lcd_console_log("SPIFlash Begin...");
  W25Qxx_Init();

  // uint32_t _uniqueID = W25Qxx_ReadID();
  // if (_uniqueID) {
  //   lcd.lcd_console_log("Unique ID: 0x" + String(uint32_t(_uniqueID), HEX));
  // } else {
  //   lcd.lcd_console_log("SPIFlash ERR");
  // }
  

  // lcd.lcd_console_log("End Setup");
  // lcd.consoleLine = 1;
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  
  // if(myTouch.dataAvailable()){
  //   myTouch.read();
  //   lcd.lcd_console_log("X " + String(myTouch.getX()) + " Y " + String(myTouch.getX()));
  // }

}