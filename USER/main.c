#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
#include "usart.h"	
#include "usmart.h"	 
#include "rtc.h" 
#include "timer.h"
#include "stm32_pca9685.h"

/************************************************
 ALIENTEK 战舰STM32F103开发板实验15
 RTC实时时钟实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

 int main(void)
 {	 
// 	 u16 led0pwmval  =0;
//	 u16 led0pwmval1 =0;
	 
	 u16 flag_mdc=0;
	 u16 flag_jiaodu=0;
	 u16 flag_mdc1=0;

	 
	 vu8 key=0;	
	 
	u8 t=0;	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	 
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	 	
	usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART	
	RTC_Init();	  			//RTC初始化
	 
	 KEY_Init();
	 
	 	 
	 	PCA_MG9XX_Init(60,90);//初始化舵机驱动
// 	TIM3_PWM_Init(19999,71);	 //72分频。PWM频率=72000000/72/20000=50hz
//	TIM2_PWM_Init(19999,71);
	 
//	  	TIM4_PWM_Init(19999,71);	 //不分频。PWM频率=72000000/900=80Khz
	 
	 
//	LCD_ShowString(60,110,200,16,16,"2015/1/14");		
	 
	 
//	//显示时间

//	LCD_ShowString(60,130,200,16,16,"    -  -  ");	 
		OLED_ShowString(8,2,"    -  -  ",8,1);//列 行 位置 大小	 
//	LCD_ShowString(60,162,200,16,16,"  :  :  ");		  
		OLED_ShowString(8,20,"  :  :  ",8,1);
		

		OLED_ShowChinese(8,30,0,16,1);//当
		OLED_ShowChinese(24,30,1,16,1);//前
		OLED_ShowChinese(42,30,2,16,1);//药
		OLED_ShowChinese(58,30,3,16,1);//仓
		OLED_ShowString(74,30,":",16,1);
//		
//		OLED_ShowChinese(8,46,4,16,1);//当
//		OLED_ShowChinese(24,46,5,16,1);//前
//		OLED_ShowChinese(42,46,6,16,1);//药
//		OLED_ShowChinese(58,46,7,16,1);//仓
//		OLED_ShowString(74,46,":",16,1);
//		

	delay_ms(1000);
	delay_ms(1000);
	
	 
	while(1)
	{			
		
//void PCA_MG9XX(u8 num,u8 start_angle,u8 end_angle,u8 mode,u8 speed)		
//				PCA_MG9XX(1,0,180,1,10); //通道1 从0度转到180度
		
		OLED_Refresh();
		
		key=KEY_Scan(0);	//得到键值
	   	if(key)
		{						   
			switch(key)
			{				 

				case KEY0_PRES:	 
				{
					flag_mdc++;
					if(flag_mdc==6)flag_mdc=0;
				
			  };
					break;
				case KEY1_PRES:	
				{
					flag_jiaodu++;
						if(flag_jiaodu==2)flag_jiaodu=0;
					if(flag_mdc==0)
					{
						if(flag_jiaodu==1)					
						{
//							led0pwmval=2500;
								PCA_MG9XX(1,0,105,1,10); //通道1 从0度转到180度
							  delay_ms(300);
							 	PCA_MG9XX(1,180,0,1,10); //通道1 从0度转到180度

						}
						else if(flag_jiaodu==0)
						{							
//							led0pwmval=500;
								PCA_MG9XX(1,0,105,1,10); //通道1 从0度转到180度
							  delay_ms(300);
								PCA_MG9XX(1,180,0,1,10); //通道1 从0度转到180度

						}
					}
					
					else if(flag_mdc==1)
					{
						if(flag_jiaodu==1)						
						{
//							led0pwmval1=2500;
							PCA_MG9XX(5,80,20,1,3);//打开
							delay_ms(25);
						  PCA_MG9XX(5,0,80,1,3);//堵住
							delay_ms(100);
							PCA_MG9XX(3,180,0,1,10);//打开
							delay_ms(500);
							PCA_MG9XX(3,0,90,1,10);//堵住
							
						}
						else if(flag_jiaodu==0)	
						{
//							led0pwmval1=500;
							PCA_MG9XX(5,80,20,1,3);//打开
							delay_ms(25);
						  PCA_MG9XX(5,0,80,1,3);//堵住
							delay_ms(100);
							PCA_MG9XX(3,180,0,1,10);//打开
							delay_ms(500);
							PCA_MG9XX(3,0,90,1,10);//堵住
							
						}
					}
					
					else if(flag_mdc==2)
					{
						if(flag_jiaodu==1)						
						{
//							led0pwmval1=2500;
//							PCA_MG9XX(5,0,80,1,10);//堵住
							NEW78(7,0,140);
							delay_ms(1500);
							NEW78(7,0,80);	
						}
						else if(flag_jiaodu==0)	
						{
//							led0pwmval1=500;
//							PCA_MG9XX(5,80,20,1,10);//打开
							NEW78(7,0,140);
							delay_ms(1500);
							NEW78(7,0,80);
							
						}
					}
					
					else if(flag_mdc==3)
					{
						if(flag_jiaodu==1)						
						{
//							led0pwmval1=2500;
							NEW78(9,0,140);
							delay_ms(1500);
							NEW78(9,0,80);
						}
						else if(flag_jiaodu==0)	
						{
//							led0pwmval1=500;
							NEW78(9,0,140);
							delay_ms(1500);
							NEW78(9,0,80);
						}
					}
					
					else if(flag_mdc==4)
					{
						if(flag_jiaodu==1)						
						{
//							led0pwmval1=2500;
							PCA_MG9XX(1,0,105,1,10); //通道1 从0度转到180度
							  delay_ms(300);
							 	PCA_MG9XX(1,180,0,1,10); //通道1 从0度转到180度
							  delay_ms(300);
								PCA_MG9XX(5,80,20,1,3);//打开
							delay_ms(25);
						  PCA_MG9XX(5,0,80,1,3);//堵住
							delay_ms(100);
							PCA_MG9XX(3,180,0,1,10);//打开
							delay_ms(500);
							PCA_MG9XX(3,0,90,1,10);//堵住
							  delay_ms(300);
								NEW78(7,0,140);
							delay_ms(1500);
							NEW78(7,0,80);	
							 delay_ms(300);
								NEW78(9,0,140);
							delay_ms(1500);
							NEW78(9,0,80);
							

						}
						else if(flag_jiaodu==0)	
						{
//							led0pwmval1=500;
							PCA_MG9XX(10,180,0,1,10);
						}
					}
					
					else if(flag_mdc==5)
					{
						if(flag_jiaodu==1)						
						{
//							led0pwmval1=2500;
							PCA_MG9XX(11,0,180,1,10);
						}
						else if(flag_jiaodu==0)	
						{
//							led0pwmval1=500;
							PCA_MG9XX(11,180,0,1,10);
						}
					}
			
				};			
					break;

			}
		}else delay_ms(10); 
		
//		TIM_SetCompare2(TIM2,led0pwmval1);	
//		TIM_SetCompare2(TIM3,led0pwmval);		   
			 

		if(t!=calendar.sec)
		{
			t=calendar.sec;
//			LCD_ShowNum(60,130,calendar.w_year,4,16);		
				OLED_ShowNum(8,2,calendar.w_year,4,8,1);
//			LCD_ShowNum(100,130,calendar.w_month,2,16);		
				OLED_ShowNum(40,2,calendar.w_month,2,8,1);			
//			LCD_ShowNum(124,130,calendar.w_date,2,16);	 
				OLED_ShowNum(57,2,calendar.w_date,2,8,1);
			switch(calendar.week)
			{
				case 0:
//					LCD_ShowString(60,148,200,16,16,"Sunday   ");
						OLED_ShowString(74,2,"Sunday",8,1);
					break;
				case 1:
//					LCD_ShowString(60,148,200,16,16,"Monday   ");
						OLED_ShowString(74,2,"Monday",8,1);
					break;
				case 2:
//					LCD_ShowString(60,148,200,16,16,"Tuesday  ");
						OLED_ShowString(74,2,"Tuesday",8,1);
					break;
				case 3:
//					LCD_ShowString(60,148,200,16,16,"Wednesday");
						OLED_ShowString(74,2,"Wednesday",8,1);
					break;
				case 4:
//					LCD_ShowString(60,148,200,16,16,"Thursday ");
						OLED_ShowString(74,2,"Thursday",8,1);
					break;
				case 5:
//					LCD_ShowString(60,148,200,16,16,"Friday   ");
						OLED_ShowString(74,2,"Friday",8,1);
					break;
				case 6:
//					LCD_ShowString(60,148,200,16,16,"Saturday ");
						OLED_ShowString(74,2,"Saturday",8,1);
					break;  
			}
//			LCD_ShowNum(60,162,calendar.hour,2,16);									  
//			LCD_ShowNum(84,162,calendar.min,2,16);									  
//			LCD_ShowNum(108,162,calendar.sec,2,16);
				OLED_ShowNum(8,20,calendar.hour,2,8,1);
				OLED_ShowNum(26,20,calendar.min,2,8,1);
				OLED_ShowNum(44,20,calendar.sec,2,8,1);
			LED0=!LED0;
		}	
//		delay_ms(10);
			flag_mdc1=flag_mdc+1;
		OLED_ShowNum(80,30,flag_mdc1,1,16,1);
			OLED_ShowNum(90,30,flag_jiaodu,1,8,1);
		

	
	}
 }

