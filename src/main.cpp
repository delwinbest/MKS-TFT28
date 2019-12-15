#include <Arduino.h>
#include "buzzer.h"
#include "lcd.h"
#include "helperfunctions.h"
#include "UTFT.h"
#include "URTouch.h"
#include <SPI.h>


LCD lcd;


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
  //Start SD Card

  delay(1000);
  // BUZZER_ShortBeep();
  lcd.consoleLine = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  lcd.lcd_console_log("Line #" + String(lcd.consoleLine));

  Serial.println("loop");
}