#include "Ultrasonic.h"
#include "delay.h"





u16 UltrasonicWave_Distance;
vu32 Averge_distance;







void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
  	       
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;					 //PC8��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOC, &GPIO_InitStructure);	                 //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				     //PC9��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //��Ϊ����
  GPIO_Init(GPIOC,&GPIO_InitStructure);						 //��ʼ��GPIOC
}

/*
 * ��������UltrasonicWave_CalculateTime
 * ����  ���������
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_CalculateTime(void)
{
   UltrasonicWave_Distance=TIM_GetCounter(TIM4)*5*34/2000;
}

/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_StartMeasure(void)
{
  GPIO_SetBits(GPIOC,GPIO_Pin_8); 		  //��>10US�ĸߵ�ƽ
  delay_us(20);		                      //��ʱ20US
  GPIO_ResetBits(GPIOC,GPIO_Pin_8);
  
  while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9));	             //�ȴ��ߵ�ƽ
  TIM_Cmd(TIM4, ENABLE);                                             //����ʱ��
  while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9));	                 //�ȴ��͵�ƽ
  TIM_Cmd(TIM4, DISABLE);			                                 //��ʱ��2ʧ��
  UltrasonicWave_CalculateTime();									 //�������
  TIM_SetCounter(TIM4,0);

//  printf("\r\ndistance:%d%d cm\r\n",UltrasonicWave_Distance/256,UltrasonicWave_Distance%256);	
}
void Average_Distance(void)
{
    UltrasonicWave_StartMeasure();
	  Averge_distance=UltrasonicWave_Distance/256*100+UltrasonicWave_Distance%256;

}
