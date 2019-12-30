#ifndef __lcd_H
#define __lcd_H

/* Helper Functions for lcd */
/* These should be refactored out over time into their respective libaries */
#define WHITE                 0xFFFF
#define BLACK                 0x0000    
#define BLUE                  0x001F  
#define BRED                  0XF81F
#define GRED                  0XFFE0
#define GBLUE                 0X07FF
#define RED                   0xF800
#define MAGENTA               0xF81F
#define GREEN                 0x07E0
#define CYAN                  0x7FFF
#define YELLOW                0xFFE0
#define BROWN                 0XBC40 //
#define BRRED                 0XFC07 //
#define GRAY                  0X8430 //

class LCD 
{
    public:
        int consoleLine = 1;
        void init();
        String get_lcd_registers(int regs, int reads);
        void start_pwm_backlight();
        void print_regs_serial(int regs,int reads);
        void lcdprint_lcd_registers();
        void serialprint_lcd_registers();
        void lcdprint_string(String string, int x, int y, int deg);
        void lcd_console_log(String string);
        void drawBitmap(int x, int y, int sx, int sy, unsigned short* data, int scale);
};

#endif 