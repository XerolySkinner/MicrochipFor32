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
  * @file		bsp_IDLEUART.cpp
  * @brief		空闲接收字符
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Fri Jan 20 00:40:10 2023

  */
#include "bsp_IDLEUART.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
/**
 * @brief			title
 * @param	var 	vars
 * @return			res
 */
void bsp_IDLEUART::init(void){
	HAL_TIM_Base_Stop_IT(htim);
	HAL_UART_Receive_IT(huart,&temp,1);}
//----------------------------------------------------------------------------------------------------
void bsp_IDLEUART::callback_TIM(void){
	*buff='\0';
	buff=buffhead;
	HAL_TIM_Base_Stop_IT(htim);}
//----------------------------------------------------------------------------------------------------
void bsp_IDLEUART::callback_UART(void){
	__HAL_TIM_CLEAR_IT(htim,TIM_IT_UPDATE);
	HAL_TIM_Base_Start_IT(htim);
	__HAL_TIM_SetCounter(htim,0);
	*(buff++)=temp;
	len++;
	HAL_UART_Receive_IT(huart,&temp,1);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
	bsp_IDLEUART::bsp_IDLEUART(UART_HandleTypeDef *huart,TIM_HandleTypeDef *htim):bsp_PrintArt_STM32(huart){
	bsp_IDLEUART::huart=huart;
	bsp_IDLEUART::htim=htim;
	bsp_IDLEUART::len=0;
	buff=(u8*)bsp_malloc(128);
	bsp_IDLEUART::lenmax=128;
	buffhead=buff;}
//----------------------------------------------------------------------------------------------------
bsp_IDLEUART::bsp_IDLEUART(UART_HandleTypeDef *huart,TIM_HandleTypeDef *htim,u32 len):bsp_PrintArt_STM32(huart){
	bsp_IDLEUART::huart=huart;
	bsp_IDLEUART::htim=htim;
	bsp_IDLEUART::len=0;
	buff=(u8*)bsp_malloc(len);
	bsp_IDLEUART::lenmax=len;
	buffhead=buff;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
