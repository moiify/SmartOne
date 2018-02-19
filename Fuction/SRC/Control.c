#include "Control.h"
#include "string.h"
#include "usart.h"

	u8 t; 
	u8 len;
	u8 flag;


void Init(void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 	LED_Init();			     //LED�˿ڳ�ʼ��
  PWM_Init();	 //����Ƶ��PWMƵ��=72000000/900=80Khz
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	UltrasonicWave_Configuration();
}





void Front(void)    //����ǰ��
{  
	 GPIO_SetBits(GPIOB,GPIO_Pin_5);
	 GPIO_ResetBits(GPIOE,GPIO_Pin_5);
}
void Back(void)     //���ٺ���
{  
	 GPIO_ResetBits(GPIOB,GPIO_Pin_5);
   GPIO_SetBits(GPIOE,GPIO_Pin_5);
}		
void Stop(void)     //����
{  
	 GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	 GPIO_ResetBits(GPIOE,GPIO_Pin_5);
}
void Cam_Left(u16 Duo)   //������̨����
{
	 TIM_SetCompare1(TIM1,Duo);  
}
void Cam_Right(u16 Duo)  //������̨����
{
	 TIM_SetCompare1(TIM1,Duo);
}
void Cam_Up(u16 Duo)     //������̨����
{
	 TIM_SetCompare2(TIM1,Duo);
}
void Cam_Down(u16 Duo)   //������̨����
{
	 TIM_SetCompare2(TIM1,Duo);
}
void Cam_Mid (u16 Duo)    //������̨����
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

	if(!(strcmp((char*)USART_RX_BUF,"ǰ��"))) //strcmp  C���Թؼ��� �Ƚ�
	{ 
		if(flag==1)
		Stop();
		else
		Front();
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF));  //  memset��strlen C���Թؼ���  ���                       
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
	else if(!(strcmp((char*)USART_RX_BUF,"��ת"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"��ת"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"��ǰת"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART_RX_BUF,"��ǰת"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	}
  else if(!(strcmp((char*)USART_RX_BUF,"���ת"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"�Һ�ת"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"�����ת"))) 
	{ 
		Cam_Left(37); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"�����ת"))) 
	{ 
		Cam_Right(135);
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"�������"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	}
  else if(!(strcmp((char*)USART_RX_BUF,"Ѱ��"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"����1"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"����2"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"����3"))) 
	{ 
		Back(); 
		memset(USART_RX_BUF,0,strlen((char*)USART_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART_RX_BUF,"׷��"))) 
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
