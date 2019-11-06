#include "buzzer.h"
#include <Arduino.h>

HardwareTimer *tim2 = new HardwareTimer(TIM2);

void BUZZER_Init(void)
{   
    
    tim2->setMode(TIM_CHANNEL_3, TIMER_OUTPUT_COMPARE_TOGGLE, SPEAKER);
    tim2->setOverflow(100000, MICROSEC_FORMAT); // 10000 microseconds = 10 milliseconds



    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // initialize digital pin SPEAKER as an output.
    pinMode(SPEAKER, OUTPUT);
    tim2->pause();

}

void BUZZER_ShortBeep()
{
	tim2->resume();
	delay(40);
	tim2->pause();
}