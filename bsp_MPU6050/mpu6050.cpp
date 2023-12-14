/**
 * @file		mpu6050
 * @brief		ʵ��mpu6050����
 * @mainpage	��Ҫ��Ϣ
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version 	V1.0.0
 * @date		2022-11-08 01:09
 */
 
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "bsp_IIC.h"
#include "mpu6050.h"
#define delay_ms(var) HAL_Delay(var)
bsp_IIC_STM32 mpu6050IIC(IIC_SCL_GPIO_Port,IIC_SCL_Pin,IIC_SDA_GPIO_Port,IIC_SDA_Pin);
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	������
/**
 * @brief			��ʼ��MPU6050
 * @return			0,�ɹ�
 */ 
u8 MPU_Init(void){
	u8 res;
	//MPU_IIC_Init();//��ʼ��IIC����
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//��λMPU6050
	delay_ms(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//����MPU6050 
	MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps
	MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
	MPU_Set_Rate(50);						//���ò�����50Hz
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//�ر������ж�
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
	res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
	if(res==MPU_ADDR)//����ID��ȷ
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
		MPU_Set_Rate(50);						//���ò�����Ϊ50Hz
 	}else return 1;
	return 0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����MPU6050�����Ǵ����������̷�Χ
 * @param	fsr 	0,��250dps
 * 					1,��500dps
 * 					2,��1000dps
 *					3,��2000dps
 * @return			0,���óɹ�
 */
u8 MPU_Set_Gyro_Fsr(u8 fsr){
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����MPU6050���ٶȴ����������̷�Χ
 * @param	fsr 	0,��2g
 *					1,��4g
 *					2,��8g
 *					3,��16g
 * @return			0,���óɹ�
 */
u8 MPU_Set_Accel_Fsr(u8 fsr){
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����MPU6050�����ֵ�ͨ�˲���
 * @param	lpf 	���ֵ�ͨ�˲�Ƶ��(Hz)
 * @return			0,���óɹ�
 */
u8 MPU_Set_LPF(u16 lpf){
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
 * @param	rate 	4~1000(Hz)
 * @return			0,���óɹ�
 */
u8 MPU_Set_Rate(u16 rate){
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	return MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			�õ��¶�ֵ
 * @return			�¶�ֵ(������100��)
 */
short MPU_Get_Temperature(void){
    u8 buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			�õ�������ֵ(ԭʼֵ)
 * @param	gx	 	������x���ԭʼ����(������)
 * @param	gy	 	������y���ԭʼ����(������)
 * @param	gx	 	������z���ԭʼ����(������)
 * @return			0,���óɹ�
 */
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz){
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0){
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];}
    return res;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			�õ����ٶ�ֵ(ԭʼֵ)
 * @param	ax	 	������a���ԭʼ����(������)
 * @param	ay	 	������a���ԭʼ����(������)
 * @param	ax	 	������a���ԭʼ����(������)
 * @return			0,���óɹ�
 */
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az){
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0){
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];}
    return res;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	������
/**
 * @brief			IIC����д
 * @param	addr	������ַ
 * @param	reg		�Ĵ�����ַ
 * @param	len		д�볤��
 * @param	*buf	������
 * @return			0,���óɹ�
 */
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf){
	mpu6050IIC.IIC_Write(addr,reg,(u8*)buf,len);
	return 0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			IIC������
 * @param	addr	������ַ
 * @param	reg		�Ĵ�����ַ
 * @param	len		��ȡ����
 * @param	*buf	��ȡ������
 * @return			0,���óɹ�
 */
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf){
	mpu6050IIC.IIC_Read(addr,reg,(u8*)buf,len);
	return 0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			IICдһ���ֽ� 
 * @param	reg		�Ĵ�����ַ
 * @param	data	����
 * @return			0,���óɹ�
 */
u8 MPU_Write_Byte(u8 reg,u8 data){
	mpu6050IIC.IIC_WriteOneByte(MPU_ADDR,reg,data);
	return 0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			IIC��һ���ֽ�
 * @param	reg		�Ĵ�����ַ
 * @return			0,���óɹ�
 */
u8 MPU_Read_Byte(u8 reg){
	return mpu6050IIC.IIC_ReadOneByte(MPU_ADDR,reg);}
//////////////////////////////////////////////////////////////////////////////////////////////////////

