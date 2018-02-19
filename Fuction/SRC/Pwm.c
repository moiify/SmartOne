#include "Pwm.h"
#include "timer.h"

void PWM_Init(void)
{
	 TIM3_PWM_Init(1439,999);
	 TIM1_PWM_Init(1439,999);
	 TIM4_Configuration();
}
