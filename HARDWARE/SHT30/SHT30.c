#include "SHT30.h"   
#include "bsp_i2c_gpio.h"

u8 Buff[6]={0};


float Temperature ;
float Humidity ;

void Sht30_Init(void)
{	
	// �ڷ���I2C�豸ǰ�����ȵ��� i2c_CheckDevice() ���I2C�豸�Ƿ��������ú���������GPIO
while (i2c_CheckDevice(0x88+0));  //�����豸��ַ+д�ź� 
}


/**
  * @brief  SHT30д����
  * @param  msb
            lsb
  * @retval None
  */
void Sht30_WriteCmd(uint8_t msb,uint8_t lsb)
	{
		i2c_Start();//��ʼ�ź�
        i2c_SendByte(0x88+0); //�����豸��ַ+д�ź�
		while (i2c_WaitAck());//CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
		i2c_SendByte(msb); //���������λ
		while (i2c_WaitAck());//CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
		i2c_SendByte(lsb); //���������λ
		while (i2c_WaitAck());//CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
		i2c_Stop();  // CPU����I2C����ֹͣ�ź�

	 }
	
	 
 
/**
  * @brief  SHT30������
  * @param  None
  * @retval None
  */
void Sht30_ReadData(void)
	{   	
		Sht30_WriteCmd(0x21,0x26);	//���ݲɼ�Ƶ��1 m/s
		i2c_Start();//��ʼ�ź�
		i2c_SendByte(0x88+1); //�����豸��ַ+���ź�
		i2c_Ack();//CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
		Buff[0]=i2c_ReadByte();//��ȡ�¶ȸ߰�λ���ҷ���һ��ack
		i2c_Ack();
		Buff[1]=i2c_ReadByte(); //�Ͱ�λ
		i2c_Ack();
		Buff[2]=i2c_ReadByte(); //У��λ����ACK8λ
		i2c_Ack();
		Buff[3] = i2c_ReadByte();  //ʪ�ȷ���ACK��8λ
		i2c_Ack();
		Buff[4] = i2c_ReadByte();  //ʪ�ȵͰ�λ
        i2c_Ack();
        Buff[5] = i2c_ReadByte();  //У��λ֮����nack����������ֲ�
		i2c_NAck();
        i2c_Stop();  // CPU����I2C����ֹͣ�ź�	
	}	
	
/**
  * @brief  ��ȡ�����ݽ��й�ʽת��
  * @param  None
  * @retval None
  */
void Convert_sht30(void)
{
    Temperature = (float)175*((Buff[0]<<8)+Buff[1])/65535-45;    //����һλ�൱�ڳ�2������8λ*2^8��
    Humidity = (float)100*((Buff[3]<<8)+Buff[4])/65535;

    Buff[0] = 0;
    Buff[1] = 0;
    Buff[2] = 0;
    Buff[3] = 0;
    Buff[4] = 0;
    Buff[5] = 0;
}

