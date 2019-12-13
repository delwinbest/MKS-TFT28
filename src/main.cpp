
#include <Arduino.h>
#include <UTFT.h>
#include <memorysaver.h>
#include <URTouch.h>
#include "buzzer.h"

#define WIDTH 319
#define LED LED_BUILTIN

extern uint8_t SmallFont[];


UTFT myGLCD(HX8558,LCD_RS,LCD_WR,LCD_CS,NOT_IN_USE,0);
URTouch  myTouch(PIN_SPI1_SCK , TOUCH_CS, PIN_SPI1_MOSI,PIN_SPI1_MISO, TOUCH_DI);

void start_pwm_backlight()
{
   TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(LCD_LED), PinMap_PWM);
  uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(LCD_LED), PinMap_PWM));


  // Instantiate HardwareTimer object. Thanks to 'new' instantiation, HardwareTimer is not destructed when setup() function is finished.
  HardwareTimer *MyTim = new HardwareTimer(Instance);

  // Configure and start PWM
  MyTim->setPWM(channel, LCD_LED, 160, 50, NULL, NULL); // No callback required, we can simplify the function call
  //MyTim->setPWM(channel, pin, 5, 1); // 5 Hertz, 10% dutycycle
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  //TX=PA9,RX=PA10
  Serial.println("Booting");
  BUZZER_Init();
  randomSeed(analogRead(0));
  // Setup the LCD
  myGLCD.InitLCD(PORTRAIT);
  myGLCD.clrScr();
  myGLCD.setColor(VGA_LIME);
  myGLCD.setFont(SmallFont);
  myGLCD.setBackColor(0,0,0);
  myGLCD.fillScr(VGA_BLACK);
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  start_pwm_backlight();
  // BUZZER_ShortBeep();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(SPEAKER, HIGH);   // turn the SPEAKER on (HIGH is the voltage level)
  // delay(1000);                       // wait for a second
  // digitalWrite(SPEAKER, LOW);    // turn the SPEAKER off by making the voltage LOW
  // delay(1000); 

  int buf[WIDTH-2];
  int x, x2;
  int y, y2;
  int r;

// Clear the screen and draw the frame
  myGLCD.clrScr();

  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, WIDTH-1, 13);
  myGLCD.setColor(64, 64, 64);
  myGLCD.fillRect(0, 226, WIDTH-1, 239);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("* STM32 Color TFT Display Library *", CENTER, 1);
  myGLCD.setBackColor(64, 64, 64);
  myGLCD.setColor(255,255,0);
  myGLCD.print("<darkspr1te>", CENTER, 227);

  myGLCD.setColor(0, 0, 255);
  myGLCD.drawRect(0, 14, WIDTH-1, 225);

// Draw crosshairs
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(199, 15, 199, 224);
  myGLCD.drawLine(1, 119, WIDTH-2, 119);
  for (int i=9; i<390; i+=10)
    myGLCD.drawLine(i, 117, i, 121);
  for (int i=19; i<220; i+=10)
    myGLCD.drawLine(157, i, 161, i);

// Draw sin-, cos- and tan-lines  
  myGLCD.setColor(0,255,255);
  myGLCD.print("Sin", 5, 15);
  for (int i=1; i<WIDTH-2; i++)
  {
    myGLCD.drawPixel(i,119+(sin(((i*1.13)*3.14)/180)*95));
  }
  
  myGLCD.setColor(255,0,0);
  myGLCD.print("Cos", 5, 27);
  for (int i=1; i<WIDTH-2; i++)
  {
    myGLCD.drawPixel(i,119+(cos(((i*1.13)*3.14)/180)*95));
  }

  myGLCD.setColor(255,255,0);
  myGLCD.print("Tan", 5, 39);
  for (int i=1; i<WIDTH-2; i++)
  {
    myGLCD.drawPixel(i,119+(tan(((i*1.13)*3.14)/180)));
  }

  delay(2000);

  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,WIDTH-2,224);
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(199, 15, 199, 224);
  myGLCD.drawLine(1, 119, WIDTH-2, 119);

// Draw a moving sinewave
  x=1;
  for (int i=1; i<((WIDTH-2)*20); i++) 
  {
    x++;
    if (x==(WIDTH-1))
      x=1;
    if (i>(WIDTH-1))
    {
      if ((x==(WIDTH/2-1))||(buf[x-1]==119))
        myGLCD.setColor(0,0,255);
      else
        myGLCD.setColor(0,0,0);
      myGLCD.drawPixel(x,buf[x-1]);
    }
    myGLCD.setColor(0,255,255);
    y=119+(sin(((i*1.1)*3.14)/180)*(90-(i / 100)));
    myGLCD.drawPixel(x,y);
    buf[x-1]=y;
  }

  delay(2000);
  // BUZZER_ShortBeep();
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,15,WIDTH-2,224);

  Serial.println("loop");
}