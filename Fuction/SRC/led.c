#include "led.h"
#include "delay.h"


//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化

void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //LED0-->PB.6 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	 GPIO_SetBits(GPIOB,GPIO_Pin_6);						 //PB.5 输出高

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //LED0-->PB.6 端口配置
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	 LED3=1;
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //LED1-->PE.5 端口配置, 推挽输出
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	 GPIO_SetBits(GPIOA,GPIO_Pin_8); 						 //PE.6 输出高 
	
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PE.5 端口配置, 推挽输出
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	 GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PE.6 输出高 
	 
	 
	 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	    		 //LED1-->PE.5 端口配置, 推挽输出
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz

}	 
	 
	 
	 


void BEEP_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
		
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PB.5 端口配置
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	 // GPIO_ResetBits(GPIOB,GPIO_Pin_8);						 //低电平关闭蜂鸣器

}
