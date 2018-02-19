#ifndef __ULT_H
#define __ULT_H	 
#include "sys.h"
void UltrasonicWave_Configuration(void);               //对超声波模块初始化
void UltrasonicWave_StartMeasure(void);                //开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
void Average_Distance(void);
extern vu32 Averge_distance;	
#endif
