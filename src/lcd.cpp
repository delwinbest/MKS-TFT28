#include <Arduino.h>
#include "lcd.h"
#include "UTFT.h"
#include "URTouch.h"

extern UTFT myGLCD(HX8353C,LCD_RS,LCD_WR,LCD_CS,LCD_RD,LANDSCAPE);
extern URTouch  myTouch(PIN_SPI1_SCK , TOUCH_CS, PIN_SPI1_MOSI,PIN_SPI1_MISO, TOUCH_DI);

void start_lcd(){
  myGLCD.Init(PORTRAIT);
  myGLCD.clrScr();
  myGLCD.setBackColor(0,0,0);
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  start_pwm_backlight();
}

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

String  get_lcd_registers(int reg_address, int size_of_reg)
{
  String return_string;
  int data;
  myGLCD.h_write_COM(reg_address);
  data = myGLCD.h_read_DATA();//first two bytes dummy
  return_string = return_string+String((data&0xff),HEX);
  for (int xr=0;xr<size_of_reg;xr++)
  {
    data = myGLCD.h_read_DATA();
    return_string = return_string+String(data,HEX); 
  }
  return return_string;
}


void lcdprint_lcd_registers()
{
 String thisstring;
  myGLCD.setFont(SmallFont);

  
  myGLCD.fillScr(BLACK);
  myGLCD.printStr("lcd man/mdl:", 1, 1,0);myGLCD.printStr(get_lcd_registers(0x04,2),95, 1,0);

  myGLCD.printStr("Reg 0x09",1,15,0);
  myGLCD.printStr("Reg 0x0A",1,25,0);
  myGLCD.printStr("Reg 0x0B",1,35,0);
  myGLCD.printStr("Reg 0x0C",1,45,0);
  myGLCD.printStr("Reg 0x0D",1,55,0);
  myGLCD.printStr("Reg 0x0E",1,65,0);
  myGLCD.printStr("Reg 0x0F",1,75,0);


  myGLCD.printStr(get_lcd_registers(0x09,2),75, 15,0);
  myGLCD.printStr(get_lcd_registers(0x0A,2),75, 25,0);
  myGLCD.printStr(get_lcd_registers(0x0B,2),75, 35,0);
  myGLCD.printStr(get_lcd_registers(0x0C,2),75, 45,0);
  myGLCD.printStr(get_lcd_registers(0x0D,2),75, 55,0);
  myGLCD.printStr(get_lcd_registers(0x0E,2),75, 65,0);
  myGLCD.printStr(get_lcd_registers(0x0F,1),75, 75,0);
}

void print_regs_serial(int regs,int reads)
{
  myGLCD.h_write_COM(regs);
  Serial.print("Reg: 0x");
  Serial.print(regs,HEX);
  Serial.print(" ");
  for (int xr=0;xr<reads;xr++)
  {
  int data = myGLCD.h_read_DATA();
  Serial.print(data,HEX);
  if (xr==(reads-1)){}
  else
    Serial.print(",");
  }
  Serial.println();
}

void serialprint_lcd_registers()
{
   //Automated read lcd id
  Serial.print("LCD ID:");
  Serial.println(myGLCD.readID(),HEX);
  Serial.println("Reading registers:-");
  Serial.println();
  //Manual way 
  print_regs_serial(0x04,4);//print lcd ID
  print_regs_serial(0x09,4);//Read Display Status 4 words(reads)
  //print_regs(0x09,4);//Read Display Status 4 words(reads)
  Serial.print("Register 0x4 {ID} as a string :0x");
  Serial.println(get_lcd_registers(0x04,2));
  print_regs_serial(0x0a,1);//Read Display power mode
  print_regs_serial(0x0b,1);//Read Display  MADCTL
  print_regs_serial(0x0c,1);//Read Display Pixel format
  print_regs_serial(0x0d,1);//Read Display Image Mode
  print_regs_serial(0x0e,1);//Read Display Signal Mode 
  print_regs_serial(0x0f,1);//Read Display Self Diag result 
  print_regs_serial(0xd0,4);//Read Display Self Diag result 
}