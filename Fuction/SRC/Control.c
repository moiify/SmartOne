#include "Control.h"
#include "string.h"
#include "USART.h"
#include "stdlib.h"
#include "stdio.h"
#define P 0.6
#define D 0.1
int Speed=600;

	u8 t; 
	u8 len;
static	u8 Avoidence=1;
//	u8 BeepFlag=1;
  u8 CamRiceAngle=90;
	u8 CamAroundAngle=86;
	unsigned int dataX,dataY,dataT;
	unsigned char a[3]={0,0,0};
	unsigned int value=0;
	unsigned int TrackFlag=0;
 extern unsigned int WaitTime;
void Init(void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 	LED_Init();			     //LED�˿ڳ�ʼ��
	BEEP_Init();
  PWM_Init();	 
	//uart1_init(115200);
	uart2_init(115200);	 //���ڳ�ʼ��Ϊ115200
	UltrasonicWave_Configuration();
	CarDir(110);
	CamRiceSet(CamRiceAngle);
	CamAroundSet(CamAroundAngle);
  
}

int fputc(int ch, FILE *f)
{
  
   USART_SendData(USART1, (u8) ch);

  
   while(!(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET))
   {
   }

   return ch;
}


void Front(void)    //����ǰ��    ��ʱ��3  3 4 ͨ�� �� ǰ������
{  
	 
	 TIM_SetCompare3(TIM3,Speed);
	 TIM_SetCompare4(TIM3,0);
}
void Back(void)     //���ٺ���
{  
	 TIM_SetCompare3(TIM3,0);
   TIM_SetCompare4(TIM3,Speed);
}		
void Stop(void)     //ֹͣ
{  
	 
 	  TIM_SetCompare3(TIM3,0);
	  TIM_SetCompare4(TIM3,0);
}
void CarDir(u16 Duo)   //С������  ��ʱ��1  4ͨ��
{
	 TIM_SetCompare4(TIM1,Duo);  
}
//void Cam_Right(u16 Duo)  //������̨����
//{
//	 TIM_SetCompare1(TIM1,Duo);
//}
void CamRiceSet(u16 Duo)     //������̨���� ��ʱ��3 1ͨ��
{
	 TIM_SetCompare1(TIM3,Duo);
}
void CamAroundSet(u16 Duo)
{
	 TIM_SetCompare2(TIM3,Duo);  //����ͷ��̨����  ��ʱ��3 2ͨ��
	
}
//void Cam_Down(u16 Duo)   //������̨����
//{
//	 TIM_SetCompare2(TIM1,Duo);
//}
//void Cam_Mid (u16 Duo)    //������̨����
//{
//	 TIM_SetCompare1(TIM1,Duo);
//	 TIM_SetCompare2(TIM1,Duo);
//}



void Control(void)
{
	if(USART1_RX_STA&0x8000)
	{
    Speed=630;
		len=USART1_RX_STA&0x3fff;
		for(t=0;t<len;t++)
		{
			USART1->DR=USART1_RX_BUF[t];
			while((USART1->SR&0X40)==0);
		}
		USART1_RX_STA=0;
	}

	if(!(strcmp((char*)USART1_RX_BUF,"MD_stop"))) //strcmp  C���Թؼ��� �Ƚ�              //ֹͣ
	{ 
		Stop();
		CarDir(110);        
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF));  //  memset��strlen C���Թؼ���  ���                       
	} 

	else if(!(strcmp((char*)USART1_RX_BUF,"MD_down")))                                    //����
	{ 
		Back(); 
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
		
	} 
	else if(!(strcmp((char*)USART1_RX_BUF,"MD_up"))) 
	{ 
	  //printf("upup");
		Front();
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART1_RX_BUF,"MD_left"))) 
	{ 
		CarDir(70);
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART1_RX_BUF,"MD_right"))) 
	{ 
		CarDir(135); 
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART1_RX_BUF,"MD_ULeft"))) 
	{ 
		CarDir(70);
		Front();
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART1_RX_BUF,"MD_URight"))) 
	{ 
		CarDir(135);
		Front(); 
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	}
  else if(!(strcmp((char*)USART1_RX_BUF,"MD_BLeft"))) 
	{ 
	  CarDir(70);
  	Back(); 
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART1_RX_BUF,"MD_BRight"))) 
	{ 
		CarDir(135); 
		Back();
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART1_RX_BUF,"DJ_up"))) 
	{ 
		CamRiceAngle+=5;
		CamRiceSet(CamRiceAngle);
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART1_RX_BUF,"DJ_down"))) 
	{ 
		CamRiceAngle-=5;
		CamRiceSet(CamRiceAngle);
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART1_RX_BUF,"DJ_left"))) 
	{ 
		CamAroundAngle+=5;
		CamAroundSet(CamAroundAngle);
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	}
  else if(!(strcmp((char*)USART1_RX_BUF,"DJ_right"))) 
	{ 
		CamAroundAngle-=5;
		CamAroundSet(CamAroundAngle);
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART1_RX_BUF,"DJ_middle"))) 
	{ 
		CamRiceAngle=90;
		CamAroundAngle=86;
		CamAroundSet(CamAroundAngle);
		CamRiceSet(CamRiceAngle);
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART1_RX_BUF,"stopbuzz"))) 
	{ 
		LED2=1;
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);	
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
  else if(!(strcmp((char*)USART1_RX_BUF,"beep"))) 
	{ 
		LED2=0;
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
	  else if(!(strcmp((char*)USART1_RX_BUF,"track"))) 
	{ 
	 TrackFlag=1;
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	}   else if(!(strcmp((char*)USART1_RX_BUF,"stop"))) 
	{ 
		TrackFlag=0;
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
	else if(!(strcmp((char*)USART1_RX_BUF,"avoidance"))) 
	{ 
		Avoidence++;
		LED3=~LED3;
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF)); 
	} 
	
}


void Auto(void)
{
	  
static int flag=0;
if(WaitTime){
Average_Distance();
	     if(Averge_distance<10)
			 {	
				  LED1=0;
				  Back();
				  flag=1;
			 }
			 else if(Averge_distance>10)
			 {	
				  
				  LED1=1;
				 if(flag)
				 {
					flag=0;
				  Stop();
				 }
				 Speed=550;
				 Control();
			 }
}


if(TrackFlag){   
Speed=450;
a[2]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1);
a[1]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2);
a[0]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3);
value = a[0]+a[1]*2+a[2]*4; 
switch (value ){
  case 0:                  //��ֱ������ ��ת  000  OK 
		CarDir(85);
		CarDir(85);
		Front();
	break;                    
  case 1:                   // 001  ��������� ��ת   OK
		CarDir(82);
		CarDir(82);
		Front();
  break;
	case 2:                  //010  ������ ֹͣ  OK
		CarDir(110);
		CarDir(110);
		Stop();
	break;
	case 3:                  // 011  �������Ҳ� ��ת
		CarDir(85);
		CarDir(85);
		Front();
	break;
	case 4:
		CarDir(135);  
		CarDir(135);	
		Front(); 
	break;
	case 5:
		CarDir(110);        //  101����������  ֱ��   OK 
		Front(); 
	break;
	case 6:
		CarDir(130);
		CarDir(130);	//110
		Front(); 
	break;
	case 7:
		Speed=400;
		CarDir(110);
		Back();               //111  ûֱ�� ֹͣ     OK
	break;
	default:
		break;
}	
 
}	
//if(TrackFlag){ 
//static int error,lasterror;
//	int Pwmout;
//Speed=380;
//a[2]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1);
//a[1]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2);
//a[0]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3);
//value = a[0]+a[1]*2+a[2]*4; 
//lasterror=error;
//switch (value ){
//  case 0:                  //��ֱ������ ��ת  000  OK 
//	 error+=-8;
//	break;                    
//  case 1:                   // 001  ��������� ��ת   OK
//	error+=-5;
//  break;
//	case 2:                  //010  ������ ֹͣ  OK
//	error+=0;
//	break;
//	case 3:                  // 011  �������Ҳ� ��ת
//	error+=-5;
//	break;
//	case 4:
//	error+=8;
//	break;
//	case 5:
//	error+=0;
//	break;
//	case 6:
//	error+=5;
//	break;
//	case 7:
//	error+=0;            //111  ûֱ�� ֹͣ     OK
//	break;
//	default:
//		break;
//}	
//Pwmout=P*error+D*(error-lasterror);
//CarDir(110+Pwmout);
//Front();

//}

if(Avoidence%2==0){
	if(USART2_RX_STA&0x8000)
	{

		len=USART2_RX_STA&0x3fff;
		for(t=0;t<len;t++)
		{
			USART2->DR=USART2_RX_BUF[t];
			while((USART2->SR&0X40)==0);
		}
		USART2_RX_STA=0;
	}


      if (USART2_RX_BUF[0] == 'o'&&USART2_RX_BUF[1] == 'k')
      {
        strtok((char *)USART2_RX_BUF, ",");
        dataX = atol(strtok(NULL, ","));
        dataY = atol(strtok(NULL, ","));
        dataT = atol(strtok(NULL, ";"));
				printf("dataX=%d\n dataY=%d\n dataT=%d\n", dataX,dataY,dataT);
				memset(USART2_RX_BUF,0,strlen((char*)USART2_RX_BUF)); 
				
				if((dataX>150)&&(dataX<190)&&(dataY>170)&&(dataY<230))

         {
					CarDir(110);
          Stop(); 
					printf("���� ֹͣ");	
          }//��ֹͣ������
				 else
				if((dataX<165)&&(dataY<195))
          {//���Ͻ�
          CarDir(130);
      		Front();    
          printf("��ת��ǰ");						
           }
         else
         if((dataX>165)&&(dataY<195))
          {//���Ͻ�
          CarDir(85);
      		Front();
					printf("��ת��ǰ");							
           }
				else
        if((dataX<165)&&(dataY>195))
        {//���½�
         CarDir(85);
      		Back();  
					printf("���ת");	
        }
        else
        if((dataX>165)&&(dataY>195))
        {//���½�
         CarDir(130);
      		Back();  
					printf("�Һ�ת");	
        }
        
    
				
      }
      else
      {
				memset(USART2_RX_BUF,0,strlen((char*)USART2_RX_BUF)); 
      }
if(USART2_RX_BUF[0] == 'f'&&USART2_RX_BUF[0] == 'a') //strcmp  C���Թؼ��� �Ƚ�              //ֹͣ
	{ 
		printf("fail");      
		memset(USART2_RX_BUF,0,strlen((char*)USART2_RX_BUF));  //  memset��strlen C���Թؼ���  ���                       
	}
}

       }

	
	

