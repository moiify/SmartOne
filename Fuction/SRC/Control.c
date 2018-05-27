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
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	LED_Init();			     //LED端口初始化
	BEEP_Init();
  PWM_Init();	 
	//uart1_init(115200);
	uart2_init(115200);	 //串口初始化为115200
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


void Front(void)    //调速前进    定时器3  3 4 通道 。 前进后退
{  
	 
	 TIM_SetCompare3(TIM3,Speed);
	 TIM_SetCompare4(TIM3,0);
}
void Back(void)     //调速后退
{  
	 TIM_SetCompare3(TIM3,0);
   TIM_SetCompare4(TIM3,Speed);
}		
void Stop(void)     //停止
{  
	 
 	  TIM_SetCompare3(TIM3,0);
	  TIM_SetCompare4(TIM3,0);
}
void CarDir(u16 Duo)   //小车方向  定时器1  4通道
{
	 TIM_SetCompare4(TIM1,Duo);  
}
//void Cam_Right(u16 Duo)  //摄像云台向右
//{
//	 TIM_SetCompare1(TIM1,Duo);
//}
void CamRiceSet(u16 Duo)     //摄像云台上下 定时器3 1通道
{
	 TIM_SetCompare1(TIM3,Duo);
}
void CamAroundSet(u16 Duo)
{
	 TIM_SetCompare2(TIM3,Duo);  //摄像头云台左右  定时器3 2通道
	
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

	if(!(strcmp((char*)USART1_RX_BUF,"MD_stop"))) //strcmp  C语言关键字 比较              //停止
	{ 
		Stop();
		CarDir(110);        
		memset(USART1_RX_BUF,0,strlen((char*)USART1_RX_BUF));  //  memset，strlen C语言关键字  清空                       
	} 

	else if(!(strcmp((char*)USART1_RX_BUF,"MD_down")))                                    //后退
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
  case 0:                  //垂直与线了 左转  000  OK 
		CarDir(85);
		CarDir(85);
		Front();
	break;                    
  case 1:                   // 001  黑线在左侧 左转   OK
		CarDir(82);
		CarDir(82);
		Front();
  break;
	case 2:                  //010  不存在 停止  OK
		CarDir(110);
		CarDir(110);
		Stop();
	break;
	case 3:                  // 011  黑线在右侧 左转
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
		CarDir(110);        //  101黑线在下面  直行   OK 
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
		Back();               //111  没直线 停止     OK
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
//  case 0:                  //垂直与线了 左转  000  OK 
//	 error+=-8;
//	break;                    
//  case 1:                   // 001  黑线在左侧 左转   OK
//	error+=-5;
//  break;
//	case 2:                  //010  不存在 停止  OK
//	error+=0;
//	break;
//	case 3:                  // 011  黑线在右侧 左转
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
//	error+=0;            //111  没直线 停止     OK
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
					printf("正好 停止");	
          }//在停止区域内
				 else
				if((dataX<165)&&(dataY<195))
          {//右上角
          CarDir(130);
      		Front();    
          printf("右转向前");						
           }
         else
         if((dataX>165)&&(dataY<195))
          {//左上角
          CarDir(85);
      		Front();
					printf("左转向前");							
           }
				else
        if((dataX<165)&&(dataY>195))
        {//右下角
         CarDir(85);
      		Back();  
					printf("左后转");	
        }
        else
        if((dataX>165)&&(dataY>195))
        {//左下角
         CarDir(130);
      		Back();  
					printf("右后转");	
        }
        
    
				
      }
      else
      {
				memset(USART2_RX_BUF,0,strlen((char*)USART2_RX_BUF)); 
      }
if(USART2_RX_BUF[0] == 'f'&&USART2_RX_BUF[0] == 'a') //strcmp  C语言关键字 比较              //停止
	{ 
		printf("fail");      
		memset(USART2_RX_BUF,0,strlen((char*)USART2_RX_BUF));  //  memset，strlen C语言关键字  清空                       
	}
}

       }

	
	

