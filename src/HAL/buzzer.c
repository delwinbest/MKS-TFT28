#include "buzzer.h"
#include <Arduino.h>

void BUZZER_Init(void)
{   
    pinMode(SPEAKER, OUTPUT);
    digitalWrite(SPEAKER,LOW);
}

void BUZZER_ShortBeep()
{
  digitalWrite(SPEAKER,HIGH);
	delay(500);
	digitalWrite(SPEAKER,LOW);
}