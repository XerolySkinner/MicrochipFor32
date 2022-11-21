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
  * @file		bsp_MAX6675.h
  * @brief		实现了MAX6675的驱动
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-11 02:01
  */

#ifdef __cplusplus
#pragma once
#include "varint.h"
#include "spi.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
/**
 * @brief 		MAX6675的一个对象类
 * @note		硬件SPI需要设置如下
 *				Date Size:16 Bits
 *				MSB First
 *				分频速度合适即可
 *				需要准备一个CS管脚以控制选通
 */
class bsp_MAX6675{
	public:
		bsp_MAX6675(
			SPI_HandleTypeDef* hspi,
			GPIO_TypeDef* GPIOx_CS, uint16_t GPIO_Pin_CS);
	public:
		float ReadTemperature(void);
	 protected:
		SPI_HandleTypeDef* hspi;
		GPIO_TypeDef* GPIOx_CS;
		uint16_t GPIO_Pin_CS;
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
