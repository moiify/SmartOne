#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED0 PBout(6)    //����
#define LED1 PAout(8)     //����
#define LED2 PDout(2)	    //������
#define LED3 PBout(7)     //׷��
void LED_Init(void);//��ʼ��
void BEEP_Init(void);

#endif
