#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED0 PBout(6)    //´®¿Ú
#define LED1 PAout(8)     //±ÜÕÏ
#define LED2 PDout(2)	    //·äÃùÆ÷
#define LED3 PBout(7)     //×·×Ù
void LED_Init(void);//³õÊ¼»¯
void BEEP_Init(void);

#endif
