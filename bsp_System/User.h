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
 * @file		User.h
 * @brief		用户设置信息
 * @mainpage	主要信息
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 13:29
 */

#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////
//<<< Use Configuration Wizard in Context Menu >>>
//<c1>开发人员调试模式
//<i>用户需要取消设置,该选项仅供开发人员使用
#define 	__DEBUG__							///<调试模式开关
//</c>

//<c>使用STM32_HAL库
#define		_STM32_HAL_
//</c>
// <s>版本号
#define 	BPS_CONFIG_VERSION "1.0.0"
//<h>演示
// <o>复选框
//  <0=> 选择A
//  <1=> 选择B
#define		EQ_CheckBox		0

// <o>数字框
//  <0-16777215>
#define		EQ_NumBox 		0

// <o.0..3>位选
//  <0=>空
//  <1=>1号
//  <2=>2号
//  <3=>3号
#define 	EQ_BITERABI 		0x000

// <q.0> 复选框0
// <q.1> 复选框1
#define 	EQ_BITERABIS 		0x00

//</h>

//<<< end of configuration section >>>
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef		__DEBUG__
#define		text(format, ...)	com.print(format, ##__VA_ARGS__)
#else
#define		text(format, ...)
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////
