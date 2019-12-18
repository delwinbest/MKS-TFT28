#ifndef __lcd_H
#define __lcd_H

/* Helper Functions for lcd */
/* These should be refactored out over time into their respective libaries */

class LCD 
{
    public:
    int consoleLine = 1;

    void start_lcd();
    String get_lcd_registers(int regs, int reads);

    void start_pwm_backlight();
    void print_regs_serial(int regs,int reads);
    void lcdprint_lcd_registers();
    void serialprint_lcd_registers();
    void lcdprint_string(String string, int x, int y, int deg);
    void lcd_console_log(String string);
    void drawBitmap(int x, int y, int sx, int sy, unsigned short* data, int scale);
};

#endif /*__ helperfunctions_H */