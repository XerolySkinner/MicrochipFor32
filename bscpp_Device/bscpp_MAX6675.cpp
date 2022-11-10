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
  * @file		bscpp_MAX6675.cpp
  * @brief		实现了MAX6675的驱动
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-11 02:01
  */
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
//	
#include "bscpp_MAX6675.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
//	
/**
 * @brief				构造一个MAX6675对象
 * @param	*hspi 		设置的hspi,举例输入:&hspi1
 * @param	*GPIOx_CS 	设置的选通端口,举例输入:GPIOA
 * @param	GPIO_Pin_CS 设置的选通针脚,举例输入:GPIO_PIN_0
 * @return				无返回
 */ 
bscpp_MAX6675::bscpp_MAX6675(
	SPI_HandleTypeDef *hspi,
	GPIO_TypeDef* GPIOx_CS, uint16_t GPIO_Pin_CS
	) {
	bscpp_MAX6675::hspi=hspi;
	bscpp_MAX6675::GPIOx_CS = GPIOx_CS;
	bscpp_MAX6675::GPIO_Pin_CS = GPIO_Pin_CS;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	内含函数
//	
/**
 * @brief				访问目前温度
 * @return				返回浮点类型温度
 */ 
float bscpp_MAX6675::ReadTemperature(void) {
	u16 tmps = 0;
	u8 txdata[2] = { 0xFF,0xFF };
	HAL_GPIO_WritePin(GPIOx_CS, GPIO_Pin_CS, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, txdata, (u8*)(&tmps), 1, 1000);
	HAL_GPIO_WritePin(GPIOx_CS, GPIO_Pin_CS, GPIO_PIN_SET);
	return (tmps >> 3) * 1024.0 / 4096;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
