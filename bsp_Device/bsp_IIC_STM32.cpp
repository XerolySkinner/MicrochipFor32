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
  * @file		 bsp_IIC_STM32.cpp
  * @brief		 实现针对STM32的软件IIC类
  * @mainpage	 主要信息
  * @author 	 Yuankang Liang(XerolySkinner)
  * @email		 zabbcccbbaz@163.com
  * @version	 V1.0.0
  * @date		 2022-11-07 00:56
  */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "bsp_IIC_STM32.h"
#include "gpio.h"
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
//////////////////////////////////////////////////////////////////////////////////////////////////////

