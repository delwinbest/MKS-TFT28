#include <Arduino.h>
#include "buzzer.h"
#include "lcd.h"
#include "helperfunctions.h"
#include "UTFT.h"
#include "URTouch.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  //TX=PA9,RX=PA10
  Serial.println("Booting");
  BUZZER_Init();
  // Setup the LCD
  start_lcd();
  // BUZZER_ShortBeep();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  serialprint_lcd_registers();
  lcdprint_lcd_registers();

  Serial.println("loop");
}