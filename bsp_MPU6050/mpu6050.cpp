/**
 * @file		mpu6050
 * @brief		实现mpu6050功能
 * @mainpage	主要信息
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version 	V1.0.0
 * @date		2022-11-08 01:09
 */
 
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "bsp_IIC.h"
#include "mpu6050.h"
#define delay_ms(var) HAL_Delay(var)
bsp_IIC_STM32 mpu6050IIC(IIC_SCL_GPIO_Port,IIC_SCL_Pin,IIC_SDA_GPIO_Port,IIC_SDA_Pin);
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	函数区
/**
 * @brief			初始化MPU6050
 * @return			0,成功
 */ 
u8 MPU_Init(void){
	u8 res;
	//MPU_IIC_Init();//初始化IIC总线
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//复位MPU6050
	delay_ms(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//唤醒MPU6050 
	MPU_Set_Gyro_Fsr(3);					//陀螺仪传感器,±2000dps
	MPU_Set_Accel_Fsr(0);					//加速度传感器,±2g
	MPU_Set_Rate(50);						//设置采样率50Hz
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//关闭所有中断
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C主模式关闭
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//关闭FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
	res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
	if(res==MPU_ADDR)//器件ID正确
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//设置CLKSEL,PLL X轴为参考
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//加速度与陀螺仪都工作
		MPU_Set_Rate(50);						//设置采样率为50Hz
 	}else return 1;
	return 0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			设置MPU6050陀螺仪传感器满量程范围
 * @param	fsr 	0,±250dps
 * 					1,±500dps
 * 					2,±1000dps
 *					3,±2000dps
 * @return			0,设置成功
 */
u8 MPU_Set_Gyro_Fsr(u8 fsr){
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			设置MPU6050加速度传感器满量程范围
 * @param	fsr 	0,±2g
 *					1,±4g
 *					2,±8g
 *					3,±16g
 * @return			0,设置成功
 */
u8 MPU_Set_Accel_Fsr(u8 fsr){
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			设置MPU6050的数字低通滤波器
 * @param	lpf 	数字低通滤波频率(Hz)
 * @return			0,设置成功
 */
u8 MPU_Set_LPF(u16 lpf){
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU_CFG_REG,data);//设置数字低通滤波器  
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			设置MPU6050的采样率(假定Fs=1KHz)
 * @param	rate 	4~1000(Hz)
 * @return			0,设置成功
 */
u8 MPU_Set_Rate(u16 rate){
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
 	return MPU_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			得到温度值
 * @return			温度值(扩大了100倍)
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
 * @brief			得到陀螺仪值(原始值)
 * @param	gx	 	陀螺仪x轴的原始读数(带符号)
 * @param	gy	 	陀螺仪y轴的原始读数(带符号)
 * @param	gx	 	陀螺仪z轴的原始读数(带符号)
 * @return			0,设置成功
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
 * @brief			得到加速度值(原始值)
 * @param	ax	 	陀螺仪a轴的原始读数(带符号)
 * @param	ay	 	陀螺仪a轴的原始读数(带符号)
 * @param	ax	 	陀螺仪a轴的原始读数(带符号)
 * @return			0,设置成功
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
//	适配区
/**
 * @brief			IIC连续写
 * @param	addr	器件地址
 * @param	reg		寄存器地址
 * @param	len		写入长度
 * @param	*buf	数据区
 * @return			0,设置成功
 */
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf){
	mpu6050IIC.IIC_Write(addr,reg,(u8*)buf,len);
	return 0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			IIC连续读
 * @param	addr	器件地址
 * @param	reg		寄存器地址
 * @param	len		读取长度
 * @param	*buf	读取数据区
 * @return			0,设置成功
 */
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf){
	mpu6050IIC.IIC_Read(addr,reg,(u8*)buf,len);
	return 0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			IIC写一个字节 
 * @param	reg		寄存器地址
 * @param	data	数据
 * @return			0,设置成功
 */
u8 MPU_Write_Byte(u8 reg,u8 data){
	mpu6050IIC.IIC_WriteOneByte(MPU_ADDR,reg,data);
	return 0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			IIC读一个字节
 * @param	reg		寄存器地址
 * @return			0,设置成功
 */
u8 MPU_Read_Byte(u8 reg){
	return mpu6050IIC.IIC_ReadOneByte(MPU_ADDR,reg);}
//////////////////////////////////////////////////////////////////////////////////////////////////////

