#ifndef _BSP_I2C_GPIO_H
#define _BSP_I2C_GPIO_H


#include <inttypes.h>


#define SHT30_I2C_WR	0		/* д����bit */
#define SHT30_I2C_RD	1		/* ������bit */


/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */
#define SHT30_GPIO_PORT_I2C	GPIOB			/* GPIO�˿� */
#define SHT30_I2C_SCL_PIN		GPIO_Pin_10			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define SHT30_I2C_SDA_PIN		GPIO_Pin_11			/* ���ӵ�SDA�����ߵ�GPIO */
#define SHT30_RCC						RCC_APB2Periph_GPIOB	/* ʱ�� */


/* �����дSCL��SDA�ĺ꣬�����Ӵ���Ŀ���ֲ�ԺͿ��Ķ��� */
#if 1	/* �������룺 1 ѡ��GPIO�Ŀ⺯��ʵ��IO��д */
	#define SHT30_I2C_SCL_1()  GPIO_SetBits(SHT30_GPIO_PORT_I2C, SHT30_I2C_SCL_PIN)		/* SCL = 1 */
	#define SHT30_I2C_SCL_0()  GPIO_ResetBits(SHT30_GPIO_PORT_I2C, SHT30_I2C_SCL_PIN)		/* SCL = 0 */
	
	#define SHT30_I2C_SDA_1()  GPIO_SetBits(SHT30_GPIO_PORT_I2C, SHT30_I2C_SDA_PIN)		/* SDA = 1 */
	#define SHT30_I2C_SDA_0()  GPIO_ResetBits(SHT30_GPIO_PORT_I2C, SHT30_I2C_SDA_PIN)		/* SDA = 0 */
	
	#define SHT30_I2C_SDA_READ()  GPIO_ReadInputDataBit(SHT30_GPIO_PORT_I2C, SHT30_I2C_SDA_PIN)	/* ��SDA����״̬ */
#else	/* �����֧ѡ��ֱ�ӼĴ�������ʵ��IO��д */
    /*��ע�⣺����д������IAR��߼����Ż�ʱ���ᱻ�����������Ż� */
	#define SHT30_I2C_SCL_1()  SHT30_GPIO_PORT_I2C->BSRR = SHT30_I2C_SCL_PIN				/* SCL = 1 */
	#define SHT30_I2C_SCL_0()  SHT30_GPIO_PORT_I2C->BRR = SHT30_I2C_SCL_PIN				/* SCL = 0 */
	
	#define SHT30_I2C_SDA_1()  SHT30_GPIO_PORT_I2C->BSRR = SHT30_I2C_SDA_PIN				/* SDA = 1 */
	#define SHT30_I2C_SDA_0()  SHT30_GPIO_PORT_I2C->BRR = SHT30_I2C_SDA_PIN				/* SDA = 0 */
	
	#define SHT30_I2C_SDA_READ()  ((SHT30_GPIO_PORT_I2C->IDR & SHT30_I2C_SDA_PIN) != 0)	/* ��SDA����״̬ */
#endif


void i2c_Start(void); //CPU����I2C���������ź�
void i2c_Stop(void);  // CPU����I2C����ֹͣ�ź�
void i2c_SendByte(uint8_t _ucByte);//CPU��I2C�����豸����8bit����
uint8_t i2c_ReadByte(void);// CPU��I2C�����豸��ȡ8bit����
uint8_t i2c_WaitAck(void);//CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
void i2c_Ack(void);//CPU����һ��ACK�ź�
void i2c_NAck(void);//CPU����һ��NACK�ź�
uint8_t i2c_CheckDevice(uint8_t _Address);//���I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����жϸ��豸�Ƿ����


#endif

