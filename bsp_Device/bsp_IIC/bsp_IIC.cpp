/*----------------------------------------------------------------------------------------------------
 #
 #	Copyright (c) 2022 Yuankang Liang(XerolySkinner)
 #
 #	本软件按原样提供,无任何明示或暗示
 #	在任何情况下,作者都不承担任何损害赔偿责任
 #
 #	使用的许可声明:
 #	1.	不得歪曲本软件的来源,你不能声称你编写了原始软件.
 #	2.	免费授予以任何目的,前提是版权声明出现在所有副本中.
 #		并且版权声明和许可声明同时出现.
 #	3.	你有使用,复制,修改,分发,和销售本软件的许可.
 #	4.	如果你在产品中使用,产品文档中的声明是赞赏的但不是必须的.
 #	5.	本通知不得从任何来源删除或更改.
 #
 #	Yuankang Liang(XerolySkinner)
 #		E-mail:zabbcccbbaz@163.com
 #		QQ:2715099320
 #		Mobile Phone:13005636215
 #
 #	All rights reserved.
 */
 
/**
 * @file		bsp_IIC.cpp
 * @brief		本类实现软件IIC功能
 *				依此类派生出其他软件IIC功能
 * @mainpage	主要信息
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 00:56
 *
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "bsp_IIC.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	底层程序
//	
/**
 * @brief			发送IIC开始信号
 */
void bsp_IIC::IIC_Start(void) {
	IIC_SDA(IIC_SET);
	IIC_SDA(IIC_SET);
	IIC_SCK(IIC_SET);
	IIC_Delay();
	IIC_SDA(IIC_RESET);
	IIC_Delay();
	IIC_SCK(IIC_RESET);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送IIC停止信号
 */
void bsp_IIC::IIC_Stop(void) {
	IIC_SDA(IIC_RESET);
	IIC_SCK(IIC_SET);
	IIC_Delay();
	IIC_SDA(IIC_SET);
	IIC_Delay();}
//----------------------------------------------------------------------------------------------------
//发送应答或非应答信号
/**
 * @brief			发送IIC应答信号
 * @param	ackbit	0为应答,1位非应答
 */
void bsp_IIC::IIC_SendAck(u8 ackbit) {
	IIC_SCK(IIC_RESET);
	IIC_SDA(ackbit);
	IIC_Delay();
	IIC_SCK(IIC_SET);
	IIC_Delay();
	IIC_SCK(IIC_RESET);
	IIC_SDA(IIC_SET);
	IIC_Delay();}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			等待应答信号
 * @return			返回是否有回应
 */
u8 bsp_IIC::IIC_WaitAck(void) {
	u8 ackbit;
	IIC_SCK(IIC_SET);
	IIC_Delay();
	ackbit = IIC_SDA(IIC_READ);
	IIC_SCK(IIC_RESET);
	IIC_Delay();
	return ackbit;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送IIC一个字节信号
 * @param	byt		发送的字节
 */
void bsp_IIC::IIC_SendByte(u8 byt) {
	u8 i;
	for (i = 0; i < 8; i++) {
		IIC_SCK(IIC_RESET);
		IIC_Delay();
		IIC_SDA((byt & 0x80) != 0);
		IIC_Delay();
		IIC_SCK(IIC_SET);
		byt <<= 1;
		IIC_Delay();}
	IIC_SCK(IIC_RESET);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			接收IIC一个字节信号
 * @return			接收到的一个字节信号
 */
u8 bsp_IIC::IIC_RecByte(void) {
	u8 i=0, da=0;
	for (i = 0; i < 8; i++) {
		IIC_SCK(IIC_SET);
		IIC_Delay();
		da <<= 1;
		if (IIC_SDA(IIC_READ))da |= 1;
		IIC_SCK(IIC_RESET);
		IIC_Delay();}
	return da;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	封装程序
//	
/**
 * @brief			使用总线发送一个字节数据
 * 
 * @param	id		发送的器件地址,如0x68(MPU6050)
 * @param	addr	需要改写的寄存器地址
 * @param	dat 	改写的数据
 * @return			无返回值
 */ 
void bsp_IIC::IIC_WriteOneByte(u8 id, u8 addr, u8 dat) {
	IIC_Start();
	IIC_SendByte(id << 1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	IIC_SendByte(dat);
	IIC_WaitAck();
	IIC_Stop();}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			使用总线接收一个字节数据
 * 
 * @param	id		接收的器件地址,如0x68(MPU6050)
 * @param	addr	需要获取数据的寄存器地址
 * @return			返回该寄存器内的数据
 */
u8 bsp_IIC::IIC_ReadOneByte(u8 id, u8 addr) {
	u8 temp = 0;
	IIC_Start();
	IIC_SendByte(id << 1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_SendAck(0);
	IIC_Start();
	IIC_SendByte((id << 1) | 0x01);
	IIC_SendAck(0);
	temp = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();
	return temp;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			使用总线发送定长数据
 * 
 * @param	id		发送的器件地址,如0x68(MPU6050)
 * @param	addr	需要改写的寄存器地址起始
 * @param	dat 	改写的数据指针
 * @param	len		数据数目
 * @return			无返回值
 */
void bsp_IIC::IIC_Write(u8 id,u8 addr,u8* dat,u32 len){
	IIC_Start();
	IIC_SendByte(id<<1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	for(int i=0;i<len;i++){
		IIC_SendByte(dat[i]);
		IIC_WaitAck();}
	IIC_Stop();
	return;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			使用总线接收定长数据
 * 
 * @param	id		接收的器件地址,如0x68(MPU6050)
 * @param	addr	需要接收的寄存器地址起始
 * @param	dat 	改写的数据指针
 * @param	len		数据数目
 * @return			无返回值
 */
void bsp_IIC::IIC_Read(u8 id,u8 addr,u8* dat,u32 len){
	IIC_Start();
	IIC_SendByte(id<<1);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_SendAck(0);
	IIC_Start();
	IIC_SendByte((id<<1)|0x01);
	IIC_SendAck(0);
	for(int i=0;i<len;i++){
		dat[i]=IIC_RecByte();
		IIC_SendAck(i==(len-1));}
	IIC_Stop();
	return;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	bsp适配
#ifdef _STM32_HAL_
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
//	
/**
 * @brief					构造STM32的IIC软件发生器
 * 
 * @param	*GPIOx_SCK		SCK的端口
 * @param	GPIO_Pin_SCK	SCK的管口号
 * @param	*GPIOx_SDA		SDA的端口
 * @param	GPIO_Pin_SDA	SDA的管口号
 */
bsp_IIC_STM32::bsp_IIC_STM32(GPIO_TypeDef *GPIOx_SCK,uint16_t GPIO_Pin_SCK,GPIO_TypeDef *GPIOx_SDA,uint16_t GPIO_Pin_SDA){
	bsp_IIC_STM32::GPIOx_SCK=GPIOx_SCK;
	bsp_IIC_STM32::GPIO_Pin_SCK=GPIO_Pin_SCK;
	bsp_IIC_STM32::GPIOx_SDA=GPIOx_SDA;
	bsp_IIC_STM32::GPIO_Pin_SDA=GPIO_Pin_SDA;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	适配程序
//	
/**
 * @brief			时序中的延时
 *					在此处短暂延时
 */ 
void bsp_IIC_STM32::IIC_Delay(void) {
	u8 i = 0;
	while (++i);}
/**
 * @brief			控制SCK管脚口
 * 
 * @param	var 	此处有三个状态,IIC_SET置位管脚,IIC_RESET复位管脚
 * @return			当var为IIC_READ时返回管脚状态
 */ 
u8 bsp_IIC_STM32::IIC_SCK(u8 var) {
	if (var == IIC_RESET) {
		HAL_GPIO_WritePin(GPIOx_SCK, GPIO_Pin_SCK, GPIO_PIN_RESET);
		return 2;}
	else if (var == IIC_SET) {
		HAL_GPIO_WritePin(GPIOx_SCK, GPIO_Pin_SCK, GPIO_PIN_SET);
		return 2;}
	else {
		return HAL_GPIO_ReadPin(GPIOx_SCK, GPIO_Pin_SCK);
	}}
/**
 * @brief			控制SDA管脚口
 * @param	var 	此处有三个状态,IIC_SET置位管脚,IIC_RESET复位管脚
 * @return			当var为IIC_READ时返回管脚状态
 */ 
u8 bsp_IIC_STM32::IIC_SDA(u8 var) {
	if (var == IIC_RESET) {
		HAL_GPIO_WritePin(GPIOx_SDA, GPIO_Pin_SDA, GPIO_PIN_RESET);
		return 2;}
	else if (var == IIC_SET) {
		HAL_GPIO_WritePin(GPIOx_SDA, GPIO_Pin_SDA, GPIO_PIN_SET);
		return 2;}
	else {
		return HAL_GPIO_ReadPin(GPIOx_SDA, GPIO_Pin_SDA);
		}}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////

