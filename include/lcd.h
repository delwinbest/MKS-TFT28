#ifndef __lcd_H
#define __lcd_H

/* Helper Functions used in the app that do not have a home */
/* These should be refactored out over time into their respective libaries */


String get_lcd_registers(int regs, int reads);
void start_lcd();
void start_pwm_backlight();
void print_regs_serial(int regs,int reads);
void lcdprint_lcd_registers();
void serialprint_lcd_registers();

#endif /*__ helperfunctions_H */