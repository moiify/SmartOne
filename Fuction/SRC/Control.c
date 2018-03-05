#include "Control.h"
#include "string.h"
#include "usart.h"

	u8 t; 
	u8 len;
static	u8 Avoidence=1;
//	u8 BeepFlag=1;
  u8 CamRiceAngle=90;
	u8 CamAroundAngle=90;

void Init(void)
{
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	LED_Init();			     //LED端口初始化
	BEEP_Init();
  PWM_Init();	 //不分频。PWM频率=72000000/900=80Khz
	uart_init(115200);	 //串口初始化为115200
	UltrasonicWave_Configuration();
	CarDir(110);
	CamRiceSet(CamRiceAngle);
	CamAroundSet(CamAroundAngle);
  
}





void Front(void)    //调速前进
{  
	 
	 TIM_SetCompare3(TIM3,800);
	 TIM_SetCompare4(TIM3,0);
}
void Back(void)     //调速后退
{  
	 TIM_SetCompare3(TIM3,0);
   TIM_SetCompare4(TIM3,800);
}		
void Stop(void)     //停止
{  
	 
 	  TIM_SetCompare3(TIM3,0);
	  TIM_SetCompare4(TIM3,0);
}
void CarDir(u16 Duo)   //摄像云台向左
{
	 TIM_SetCompare1(TIM1,Duo);  
}
//void Cam_Right(u16 Duo)  //摄像云台向右
//{
//	 TIM_SetCompare1(TIM1,Duo);
//}
void CamRiceSet(u16 Duo)     //摄像云台向右
{
	 TIM_SetCompare1(TIM3,Duo);
}
void CamAroundSet(u16 Duo)
{
	 TIM_SetCompare2(TIM3,Duo);
	
}
//void Cam_Down(u16 Duo)   //摄像云台向右
//{
//	 TIM_SetCompare2(TIM1,Duo);
//}
//void Cam_Mid (u16 Duo)    //摄像云台向右
//{
//	 TIM_SetCompare1(TIM1,Duo);
//	 TIM_SetCompare2(TIM1,Duo);
//}



void Control(void)
{
	if(USART_RX_STA&0x8000)
	{

		len=USART_RX_STA&0x3fff;
		for(t=0;t<len;t++)
		{
			USART1->DR=USART_RX_BUF[t];
			while((USART1->SR&0X40)==0);
		}
		USART_RX_STA=0;
	}

	if(!(strcmp((char*)USART_RX_BUF,"MD_stop"))) //strcmp  C语言关键字 比较
	{ 
		//if(flag==1)
		//Stop();
		//else
		Stop();
		CarDir(110);
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF));  //  memset，strlen C语言关键字  清空                       
	} 

	else if(!(strcmp((char*)USART_RX_BUF,"MD_down"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
		
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"MD_up"))) 
	{ 
	
		Front();
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"MD_left"))) 
	{ 
		CarDir(70);
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"MD_right"))) 
	{ 
		CarDir(135); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"MD_ULeft"))) 
	{ 
		CarDir(70);
		Front();
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"MD_URight"))) 
	{ 
		CarDir(135);
		Front(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	}
  else if(!(strcmp((char*)USART_RX_BUF,"MD_BLeft"))) 
	{ 
	  CarDir(70);
  	Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"MD_BRight"))) 
	{ 
		CarDir(135); 
		Back();
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"DJ_up"))) 
	{ 
		CamRiceAngle+=10;
		CamRiceSet(CamRiceAngle);
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"DJ_down"))) 
	{ 
		CamRiceAngle-=10;
		CamRiceSet(CamRiceAngle);
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"DJ_left"))) 
	{ 
		CamAroundAngle+=10;
		CamAroundSet(CamAroundAngle);
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	}
  else if(!(strcmp((char*)USART_RX_BUF,"DJ_right"))) 
	{ 
		CamAroundAngle-=10;
		CamAroundSet(CamAroundAngle);
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"DJ_middle"))) 
	{ 
		CamRiceAngle=90;
		CamAroundAngle=90;
		CamAroundSet(CamAroundAngle);
		CamRiceSet(CamRiceAngle);
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"stopbuzz"))) 
	{ 
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);	
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"beep"))) 
	{ 
		
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"avoidance"))) 
	{ 
		Avoidence++;
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	
}


void Auto(void)
{
	  
//    Average_Distance();
//	  if(Averge_distance>15)
//		{
//		  flag=1;
//		  LED0=1;
//		}
//		else 
//		{ 
//			flag=0;
//			LED0=0;
//	  }
Control();
if ( Avoidence%2==1)	  
{
			 LED0=0;
	     LED1=1;
	     
}
else if(Avoidence%2==0)
{   
	     LED0=1;
	     Average_Distance();
	     if(Averge_distance<15)
			 {	
				  LED1=1;
				  Back();
			 }
			 else if(Averge_distance>15)
			 {	
				  LED1=0;
				  Stop();
			 }
}
	 
	
	
	
}
