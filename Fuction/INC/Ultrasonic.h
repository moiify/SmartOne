#ifndef __ULT_H
#define __ULT_H	 
#include "sys.h"
void UltrasonicWave_Configuration(void);               //�Գ�����ģ���ʼ��
void UltrasonicWave_StartMeasure(void);                //��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
void Average_Distance(void);
extern vu32 Averge_distance;	
#endif
