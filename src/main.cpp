#include "includes.h"

//#include <STM32SD.h>

LCD lcd;
EEPROM eeprom;
URTouch  myTouch(PIN_SPI1_SCK , TOUCH_CS, PIN_SPI1_MOSI,PIN_SPI1_MISO, TOUCH_DI);
EEPROMConfig eeprom_config;

//Sd2Card card;
//SdFatFs fatFs;
int data_address=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  //TX=PA9,RX=PA10
  Serial.println("Booting");
  BUZZER_Init();
  // Setup the LCD
  lcd.start_lcd();
  lcd.lcd_console_log("Booting...");
  lcd.lcd_console_log("LCD Register Read Test...");
  // serialprint_lcd_registers();
  lcd.lcdprint_lcd_registers();
  //Touch
  lcd.lcd_console_log("URTouch Init...");
  myTouch.InitTouch(1);
  myTouch.setPrecision(PREC_MEDIUM);
  lcd.lcd_console_log("Load EEPROM Config..");
  eeprom.init();
  eeprom_config.loadConfig();
  lcd.lcd_console_log("Config Ver: " + String(eeprom_config.settings.config_version));
  lcd.lcd_console_log("a: " + String(eeprom_config.settings.a));
  lcd.lcd_console_log("b: " + String(eeprom_config.settings.b));
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