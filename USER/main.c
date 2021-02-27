#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "oled.h"
#include "SHT30.h"
#include "wifi.h"
#include "key.h"
#include "mcu_api.h"
#include "rtc.h"

extern float Temperature;
extern float Humidity;
extern u16 tcnt;


 int main(void)
 {	
	 unsigned char flag = 2;   
	 u8 buff[10];
	 unsigned char i = 0;
	 u8 j;
 
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
	OLED_Init();       //OLED��ʼ��
	Sht30_Init();				//��ʪ�ȴ�������ʼ��
	wifi_protocol_init();		//wifi��ʼ��
	KEY_Init();		    			 //������ʼ��			
	OLED_Clear();           //����
	 for(j = 0;j < 6;j++)    //��ʾ  ����ʪ�ȴ�������
	 {
		 OLED_ShowCHinese(15+16*j,0,j);
	 }
	while(RTC_Init())		//RTC��ʼ��   ��ʱ��ÿ5���Ӵ���һ���ϴ��ƶ�
	{
		OLED_ShowString(0,2,"RTC ERROR!   ",16);	   //��ʼ��ʧ��
		delay_ms(800);
		OLED_ShowString(0,2,"RTC Trying...",16);	    //��������
	}
	while(1)
	{
		wifi_uart_service();     //��������
		if(tcnt >= 297)          //ÿ5���Ӷ�ȡһ�����ݸ���һ����Ļ��ÿ�ζ�ȡ������3sʱ�䣬�Լ���������
		{
			Sht30_ReadData();     //��ȡSHT30����
			Convert_sht30();      //ת��Ϊ�¶ȡ�ʪ��
			sprintf(buff,"%.2f",Temperature);
			OLED_ShowCHinese(0,2,0);
			OLED_ShowCHinese(16,2,2);
			OLED_ShowChar(32,2,':',16);
			OLED_ShowString(48,2,buff,16);
			sprintf(buff,"%.2f",Humidity);
			OLED_ShowCHinese(0,4,1);
			OLED_ShowCHinese(16,4,2);
			OLED_ShowChar(32,4,':',16);
			OLED_ShowString(48,4,buff,16);
		}
		i = KEY_Scan(1);    //ɨ�谴��
		switch(i)     //�ж�ѡ���ģʽ
		{
			case 1:mcu_set_wifi_mode(SMART_CONFIG);flag = 0;break;    //SMART����
			case 2:mcu_set_wifi_mode(AP_CONFIG);flag = 1;break;       //AP����
			default:break;
		}
		switch(flag)   //��ͬ����ģʽָʾ�Ʋ�ͬ���
		{
			case 0:delay_ms(20);LED = !LED;break;
			case 1:delay_ms(200);LED = !LED;break;
			default:break;
		}
		switch(mcu_get_wifi_work_state())    //�ж�WiFi���
		{
			case SMART_CONFIG_STATE:flag = 0;OLED_ShowString(0,6,"SMART MODE     ",8);break;
			case AP_STATE:flag = 1;OLED_ShowString(0,6,"AP MODE        ",8);break;
			case WIFI_NOT_CONNECTED:LED = 1;flag = 2;OLED_ShowString(0,6,"CONNECTING     ",8);break;
			case WIFI_CONNECTED:LED = 0;flag = 2;OLED_ShowString(0,6,"CONNECTED      ",8);break;
			case WIFI_CONN_CLOUD:LED = 1;flag = 2;OLED_ShowString(0,6,"CONNECTED CLOUD",8);break;
			default:break;
		}
	}	 
}


