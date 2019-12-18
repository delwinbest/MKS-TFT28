#include "includes.h"

//#include <STM32SD.h>

LCD lcd;
EEPROM eeprom;
URTouch  myTouch(PIN_SPI1_SCK , TOUCH_CS, PIN_SPI1_MOSI,PIN_SPI1_MISO, TOUCH_DI);

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
  lcd.lcd_console_log("EEPROM Init...");
  eeprom.init();
  lcd.lcd_console_log("EEPROM Read  : 0x" + String(data_address,HEX) + " " + String(eeprom.readEEPROM(eeprom_address, 0), HEX) + " " + String(eeprom.readEEPROM(eeprom_address, 1), HEX) + " " + String(eeprom.readEEPROM(eeprom_address, 2), HEX) + " " + String(eeprom.readEEPROM(eeprom_address, 3), HEX));
  // BUZZER_ShortBeep();
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