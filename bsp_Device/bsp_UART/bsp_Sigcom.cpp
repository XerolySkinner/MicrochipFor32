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
  * @file		bsp_Sigcom.cpp
  * @brief		实时控制台
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Wed Mar  1 16:44:13 2023
  */
#include "bsp_Sigcom.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
/**
 * @brief			title
 * @param	var 	vars
 * @return			res
 */
 void bsp_Sigcom::init(void){
	HAL_UART_Receive_IT(huart,&temp,1);}
//----------------------------------------------------------------------------------------------------
u32	bsp_Sigcom::callback_UART(void){
	//	功能按键
	if(seting.code && temp=='\b'){
		if(len){
			buff--;
			len--;}
		return bsp_Sigcom_OK;}
	//	回显
	if(seting.echo)print("%c",temp);
	//	接受数据
	*(buff++)=temp;
	len++;
	HAL_UART_Receive_IT(huart,&temp,1);
	if(len==lenmax)return bsp_Sigcom_FULL;
	//	判别数据回车
	if(seting.code && len>1 && buffhead[len-2] == '\r' && buffhead[len-1] == '\n')
		return bsp_Sigcom_CODE;
	
	return bsp_Sigcom_OK;}
//----------------------------------------------------------------------------------------------------
void bsp_Sigcom::clean(void){
	bsp_Sigcom::len=0;
	bsp_Sigcom::buff=bsp_Sigcom::buffhead;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
bsp_Sigcom::bsp_Sigcom(UART_HandleTypeDef *huart):bsp_PrintArt_STM32(huart){
	bsp_Sigcom::huart=huart;
	bsp_Sigcom::len=0;
	buff=(u8*)malloc(128);
	bsp_Sigcom::lenmax=128;
	buffhead=buff;
	seting.echo=1;
	seting.code=1;
}
 //----------------------------------------------------------------------------------------------------
 bsp_Sigcom::bsp_Sigcom(UART_HandleTypeDef *huart,u32 len):bsp_PrintArt_STM32(huart){
	bsp_Sigcom::huart=huart;
	bsp_Sigcom::len=0;
	buff=(u8*)malloc(len);
	bsp_Sigcom::lenmax=len;
	buffhead=buff;
	 seting.echo=1;
	 seting.code=1;
 }
//////////////////////////////////////////////////////////////////////////////////////////////////////
