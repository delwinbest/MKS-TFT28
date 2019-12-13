#ifndef __helperfunctions_H
#define __helperfunctions_H

/* Helper Functions used in the app that do not have a home */
/* These should be refactored out over time into their respective libaries */


String get_regs(int regs, int reads);
void start_lcd();
void print_regs_lcd();
void start_pwm_backlight();
void print_regs(int regs,int reads);
void do_regs();


#endif /*__ helperfunctions_H */