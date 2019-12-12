#include <Arduino.h>
#include <UTFT.h>
#include "buzzer.h"

#define WIDTH 319
#define LED LED_BUILTIN

extern uint8_t SmallFont[];


//UTFT lcdthingyname(byte model, int RS, int WR, int CS, int RST, int SER)
UTFT myGLCD(HX8353C,LCD_RS,LCD_WR,LCD_CS,LCD_RD,LANDSCAPE);
extern uint8_t SmallFont[];
extern uint8_t BigFont[];

#define X_RES 320
#define Y_RES 240
#define pin LCD_LED
#define dlay  8
#define freq 60
#define gamma_start 45


void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);  //TX=PA9,RX=PA10
  Serial1.println("Booting");
  BUZZER_Init();
  // Setup the LCD
  digitalWrite(LCD_BACKLIGHT_PIN,HIGH);
  myGLCD.Init(PORTRAIT);
  myGLCD.setFont(SmallFont);

  myGLCD.setBackColor(RED);
  BUZZER_ShortBeep();
  
}

void loop() {



}
