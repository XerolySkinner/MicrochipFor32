/*----------------------------------------------------------------------------------------------------
 #
 #	Copyright (c) 2022 Yuankang Liang(XerolySkinner)
 #
 #	本软件按原样提供,无任何明示或暗示
 #	在任何情况下,作者都不承担任何损害赔偿责任
 #
 #	使用的许可声明:
 #	1.	不得歪曲本软件的来源,您不能声称你编写了原始软件.
 #	2.	版权声明出现在所有副本中,并且版权声明和许可声明同时出现.
 #	3.	请确保您有使用,复制,修改,分发,和销售本软件的许可.
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
 * @file		MainSystem.cpp
 * @brief		实现了一个C++库针对单片机开发
 * @mainpage	主要信息
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 18:50
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "vartable.h"
//----------------------------------------------------------------------------------------------------
bsp_PrintArt_STM32 com(&huart1);
bsp_IDLEUART RS485_Arm(&huart2,&htim5);
bsp_IDLEUART RS485_Ear(&huart3,&htim6);
bsp_IDLEUART RS485_Eye(&huart4,&htim7);
_mb_master wire_Arm;
_mb_master wire_Ear;
_mb_master wire_Eye;
//----------------------------------------------------------------------------------------------------
u8 transmit_RS485_Arm(u8* buff,u32 len){
	HAL_UART_Transmit_DMA(RS485_Arm.huart,buff,len);
	return 0;}

u8 transmit_RS485_Ear(u8* buff,u32 len){
	HAL_UART_Transmit_DMA(RS485_Ear.huart,buff,len);
	return 0;}

u8 transmit_RS485_Eye(u8* buff,u32 len){
	HAL_UART_Transmit_DMA(RS485_Eye.huart,buff,len);
	return 0;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	程序
//	
/**
 * @brief			初始化步骤的首部
 * @note			在MX生成的main中,进入循环前放置本函数
 *
 */
void MainInit(void){
	/// @todo		在此处填写初始化程序
	rt_kprintf("MainThread\r\n");
	RS485_Arm.init();
	RS485_Eye.init();
	RS485_Ear.init();
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	
	wire_Arm=mb_Master_create_F(transmit_RS485_Arm);
	wire_Ear=mb_Master_create_F(transmit_RS485_Ear);
	wire_Eye=mb_Master_create_F(transmit_RS485_Eye);
	
	Val_Init();
	bsp_rtThread_Init();
	while(1)osDelay(1000);
	return;}
//////////////////////////////////////////////////////////////////////////////////////////////////////

