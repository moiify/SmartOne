#include "Ultrasonic.h"
#include "delay.h"





u16 UltrasonicWave_Distance;
vu32 Averge_distance;







void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
  	       
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;					 //PC8接TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //设为推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOC, &GPIO_InitStructure);	                 //初始化外设GPIO 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				     //PC9接ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //设为输入
  GPIO_Init(GPIOC,&GPIO_InitStructure);						 //初始化GPIOC
}

/*
 * 函数名：UltrasonicWave_CalculateTime
 * 描述  ：计算距离
 * 输入  ：无
 * 输出  ：无	
 */
void UltrasonicWave_CalculateTime(void)
{
   UltrasonicWave_Distance=TIM_GetCounter(TIM4)*5*34/2000;
}

/*
 * 函数名：UltrasonicWave_StartMeasure
 * 描述  ：开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
 * 输入  ：无
 * 输出  ：无	
 */
void UltrasonicWave_StartMeasure(void)
{
  GPIO_SetBits(GPIOC,GPIO_Pin_8); 		  //送>10US的高电平
  delay_us(20);		                      //延时20US
  GPIO_ResetBits(GPIOC,GPIO_Pin_8);
  
  while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9));	             //等待高电平
  TIM_Cmd(TIM4, ENABLE);                                             //开启时钟
  while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9));	                 //等待低电平
  TIM_Cmd(TIM4, DISABLE);			                                 //定时器2失能
  UltrasonicWave_CalculateTime();									 //计算距离
  TIM_SetCounter(TIM4,0);

//  printf("\r\ndistance:%d%d cm\r\n",UltrasonicWave_Distance/256,UltrasonicWave_Distance%256);	
}
void Average_Distance(void)
{
    UltrasonicWave_StartMeasure();
	  Averge_distance=UltrasonicWave_Distance/256*100+UltrasonicWave_Distance%256;

}
