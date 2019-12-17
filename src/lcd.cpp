#include "includes.h"

UTFT myGLCD(HX8353C,LCD_RS,LCD_WR,LCD_CS,LCD_RD,LANDSCAPE);


void LCD::start_lcd(){
  myGLCD.Init(PORTRAIT);
  myGLCD.clrScr();
  myGLCD.setBackColor(0,0,0);
  myGLCD.setFont(SmallFont);
  myGLCD.fillScr(BLACK);
  start_pwm_backlight();
  delay(500);
}

void LCD::start_pwm_backlight()
{
  TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(LCD_LED), PinMap_PWM);
  uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(LCD_LED), PinMap_PWM));
  // Instantiate HardwareTimer object. Thanks to 'new' instantiation, HardwareTimer is not destructed when setup() function is finished.
  HardwareTimer *MyTim = new HardwareTimer(Instance);

  // Configure and start PWM
  MyTim->setPWM(channel, LCD_LED, 160, 50, NULL, NULL); // No callback required, we can simplify the function call
  //MyTim->setPWM(channel, pin, 5, 1); // 5 Hertz, 10% dutycycle
}

String LCD::get_lcd_registers(int reg_address, int size_of_reg)
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

void LCD::lcdprint_string(String string, int x, int y, int deg) {
  myGLCD.printStr(string,x,y,deg);
}

void LCD::lcd_console_log(String string){
  myGLCD.setFont(SmallFont);
  if(consoleLine == 1) { myGLCD.clrScr(); }
  lcdprint_string(string, 1, consoleLine, 0);
  if( consoleLine > 230) {
    consoleLine = 1;
  } else {
    consoleLine = consoleLine+10;
  }
}


void LCD::lcdprint_lcd_registers()
{
  lcd_console_log("lcd man/mdl:" + get_lcd_registers(0x04,2));
  lcd_console_log("Reg 0x09:" + get_lcd_registers(0x09,2));
  lcd_console_log("Reg 0x0A:" + get_lcd_registers(0x0A,2));
  lcd_console_log("Reg 0x0B:" + get_lcd_registers(0x0B,2));
  lcd_console_log("Reg 0x0C:" + get_lcd_registers(0x0C,2));
  lcd_console_log("Reg 0x0D:" + get_lcd_registers(0x0D,2));
  lcd_console_log("Reg 0x0E:" + get_lcd_registers(0x0E,2));
  lcd_console_log("Reg 0x0F:" + get_lcd_registers(0x0F,1));
}

void LCD::print_regs_serial(int regs,int reads)
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

void LCD::serialprint_lcd_registers()
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