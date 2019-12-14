#include <Arduino.h>
#include "buzzer.h"
#include "lcd.h"
#include "helperfunctions.h"
#include "UTFT.h"
#include "URTouch.h"

int consoleLine = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  //TX=PA9,RX=PA10
  Serial.println("Booting");
  BUZZER_Init();
  // Setup the LCD
  start_lcd();
  lcd_console_log("Booting...", consoleLine);
  lcd_console_log("LCD Register Read Test...", consoleLine);
  // serialprint_lcd_registers();
  lcdprint_lcd_registers(consoleLine);
  delay(1000);
  // BUZZER_ShortBeep();
  consoleLine = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  lcd_console_log("Line #" + String(consoleLine), consoleLine);

  Serial.println("loop");
}