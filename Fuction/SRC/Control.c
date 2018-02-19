#include "Control.h"
#include "string.h"
#include "usart.h"

	u8 t; 
	u8 len;
	u8 flag;


void Init(void)
{
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	LED_Init();			     //LED端口初始化
  PWM_Init();	 //不分频。PWM频率=72000000/900=80Khz
	uart_init(115200);	 //串口初始化为115200
	UltrasonicWave_Configuration();
}





void Front(void)    //调速前进
{  
	 GPIO_SetBits(GPIOB,GPIO_Pin_5);
	 GPIO_ResetBits(GPIOE,GPIO_Pin_5);
}
void Back(void)     //调速后退
{  
	 GPIO_ResetBits(GPIOB,GPIO_Pin_5);
   GPIO_SetBits(GPIOE,GPIO_Pin_5);
}		
void Stop(void)     //后退
{  
	 GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	 GPIO_ResetBits(GPIOE,GPIO_Pin_5);
}
void Cam_Left(u16 Duo)   //摄像云台向左
{
	 TIM_SetCompare1(TIM1,Duo);  
}
void Cam_Right(u16 Duo)  //摄像云台向右
{
	 TIM_SetCompare1(TIM1,Duo);
}
void Cam_Up(u16 Duo)     //摄像云台向右
{
	 TIM_SetCompare2(TIM1,Duo);
}
void Cam_Down(u16 Duo)   //摄像云台向右
{
	 TIM_SetCompare2(TIM1,Duo);
}
void Cam_Mid (u16 Duo)    //摄像云台向右
{
	 TIM_SetCompare1(TIM1,Duo);
	 TIM_SetCompare2(TIM1,Duo);
}



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

	if(!(strcmp((char*)USART_RX_BUF,"前进"))) //strcmp  C语言关键字 比较
	{ 
		if(flag==1)
		Stop();
		else
		Front();
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF));  //  memset，strlen C语言关键字  清空                       
	} 

	else if(!(strcmp((char*)USART_RX_BUF,"beep"))) 
	{ 
		LED0=0;
		//Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"beep_stop"))) 
	{ 
		LED0=1;
		//Stop(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"左转"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"右转"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"左前转"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"右前转"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	}
  else if(!(strcmp((char*)USART_RX_BUF,"左后转"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"右后转"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"相机左转"))) 
	{ 
		Cam_Left(37); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"相机右转"))) 
	{ 
		Cam_Right(135);
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"相机归中"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	}
  else if(!(strcmp((char*)USART_RX_BUF,"寻迹"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"调速1"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"调速2"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"调速3"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"追踪"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	}  	
}


void Auto(void)
{
	  
//    Average_Distance();
//	  if(Averge_distance>30)
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
	
	
	
}
