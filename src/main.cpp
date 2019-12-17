#include "includes.h"

//#include <STM32SD.h>

LCD lcd;
URTouch  myTouch(PIN_SPI1_SCK , TOUCH_CS, PIN_SPI1_MOSI,PIN_SPI1_MISO, TOUCH_DI);

//Sd2Card card;
//SdFatFs fatFs;

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
  myTouch.InitTouch(1);
  myTouch.setPrecision(PREC_MEDIUM);
  delay(500);
  // BUZZER_ShortBeep();
  lcd.consoleLine = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  if(myTouch.dataAvailable()){
    myTouch.read();
    lcd.lcd_console_log("X " + String(myTouch.getX()) + " Y " + String(myTouch.getX()));
  }

}