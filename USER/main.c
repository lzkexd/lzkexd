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
 ALIENTEK ս��STM32F103������ʵ��15
 RTCʵʱʱ��ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
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
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	 
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	 	
	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	
	RTC_Init();	  			//RTC��ʼ��
	 
	 KEY_Init();
	 
	 	 
	 	PCA_MG9XX_Init(60,90);//��ʼ���������
// 	TIM3_PWM_Init(19999,71);	 //72��Ƶ��PWMƵ��=72000000/72/20000=50hz
//	TIM2_PWM_Init(19999,71);
	 
//	  	TIM4_PWM_Init(19999,71);	 //����Ƶ��PWMƵ��=72000000/900=80Khz
	 
	 
//	LCD_ShowString(60,110,200,16,16,"2015/1/14");		
	 
	 
//	//��ʾʱ��

//	LCD_ShowString(60,130,200,16,16,"    -  -  ");	 
		OLED_ShowString(8,2,"    -  -  ",8,1);//�� �� λ�� ��С	 
//	LCD_ShowString(60,162,200,16,16,"  :  :  ");		  
		OLED_ShowString(8,20,"  :  :  ",8,1);
		

		OLED_ShowChinese(8,30,0,16,1);//��
		OLED_ShowChinese(24,30,1,16,1);//ǰ
		OLED_ShowChinese(42,30,2,16,1);//ҩ
		OLED_ShowChinese(58,30,3,16,1);//��
		OLED_ShowString(74,30,":",16,1);
//		
//		OLED_ShowChinese(8,46,4,16,1);//��
//		OLED_ShowChinese(24,46,5,16,1);//ǰ
//		OLED_ShowChinese(42,46,6,16,1);//ҩ
//		OLED_ShowChinese(58,46,7,16,1);//��
//		OLED_ShowString(74,46,":",16,1);
//		

	delay_ms(1000);
	delay_ms(1000);
	
	 
	while(1)
	{			
		
//void PCA_MG9XX(u8 num,u8 start_angle,u8 end_angle,u8 mode,u8 speed)		
//				PCA_MG9XX(1,0,180,1,10); //ͨ��1 ��0��ת��180��
		
		OLED_Refresh();
		
		key=KEY_Scan(0);	//�õ���ֵ
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
								PCA_MG9XX(1,0,105,1,10); //ͨ��1 ��0��ת��180��
							  delay_ms(300);
							 	PCA_MG9XX(1,180,0,1,10); //ͨ��1 ��0��ת��180��

						}
						else if(flag_jiaodu==0)
						{							
//							led0pwmval=500;
								PCA_MG9XX(1,0,105,1,10); //ͨ��1 ��0��ת��180��
							  delay_ms(300);
								PCA_MG9XX(1,180,0,1,10); //ͨ��1 ��0��ת��180��

						}
					}
					
					else if(flag_mdc==1)
					{
						if(flag_jiaodu==1)						
						{
//							led0pwmval1=2500;
							PCA_MG9XX(5,80,20,1,3);//��
							delay_ms(25);
						  PCA_MG9XX(5,0,80,1,3);//��ס
							delay_ms(100);
							PCA_MG9XX(3,180,0,1,10);//��
							delay_ms(500);
							PCA_MG9XX(3,0,90,1,10);//��ס
							
						}
						else if(flag_jiaodu==0)	
						{
//							led0pwmval1=500;
							PCA_MG9XX(5,80,20,1,3);//��
							delay_ms(25);
						  PCA_MG9XX(5,0,80,1,3);//��ס
							delay_ms(100);
							PCA_MG9XX(3,180,0,1,10);//��
							delay_ms(500);
							PCA_MG9XX(3,0,90,1,10);//��ס
							
						}
					}
					
					else if(flag_mdc==2)
					{
						if(flag_jiaodu==1)						
						{
//							led0pwmval1=2500;
//							PCA_MG9XX(5,0,80,1,10);//��ס
							NEW78(7,0,140);
							delay_ms(1500);
							NEW78(7,0,80);	
						}
						else if(flag_jiaodu==0)	
						{
//							led0pwmval1=500;
//							PCA_MG9XX(5,80,20,1,10);//��
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
							PCA_MG9XX(1,0,105,1,10); //ͨ��1 ��0��ת��180��
							  delay_ms(300);
							 	PCA_MG9XX(1,180,0,1,10); //ͨ��1 ��0��ת��180��
							  delay_ms(300);
								PCA_MG9XX(5,80,20,1,3);//��
							delay_ms(25);
						  PCA_MG9XX(5,0,80,1,3);//��ס
							delay_ms(100);
							PCA_MG9XX(3,180,0,1,10);//��
							delay_ms(500);
							PCA_MG9XX(3,0,90,1,10);//��ס
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

