#include "buzzer.h"
#include <Arduino.h>
#define BUZZER_Pin PA2

TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(BUZZER_Pin), PinMap_PWM);
uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(BUZZER_Pin), PinMap_PWM));
HardwareTimer *tim2 = new HardwareTimer(Instance);

void TIM_Callback(HardwareTimer*){

}

void BUZZER_Init(void)
{   
    Serial1.print("Init Buzzer...");
    // No need to configure pin, it will be done by HardwareTimer configuration
   // pinMode(BUZZER_Pin, OUTPUT);

    // Automatically retrieve TIM instance and channel associated to pin
    // This is used to be compatible with all STM32 series automatically.


    tim2->setMode(channel, TIMER_OUTPUT_COMPARE_TOGGLE, BUZZER_Pin);
    tim2->setPrescaleFactor(0);
    tim2->setOverflow(5000, HERTZ_FORMAT); // 10000 microseconds = 10 milliseconds


    tim2->attachInterrupt(TIM_Callback);
    tim2->attachInterrupt(channel, TIM_Callback);
    //pause does not turn off output if output is high, 
    //tim2->pause();
    Serial1.print("DONE");
    //tim2->setPWM(channel, SPEAKER, 0, 0, NULL, NULL);
}

void BUZZER_ShortBeep()
{
	Serial1.print("beep");
    tim2->resume();
	delay(500);
    //MyTim_two->setPWM(channel_two, SPEAKER, 0, 0, NULL, NULL);
    tim2->setPWM(channel, SPEAKER, 0, 0, NULL, NULL);
	//tim2->pause();  
}

