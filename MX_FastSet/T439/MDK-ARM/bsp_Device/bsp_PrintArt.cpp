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
  * @file		bsp_PrintArt.cpp
  * @brief		print重定向的艺术
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-27 02:15
  */
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类声明
#include "bsp_PrintArt.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
/**
 * @brief			重定向后的发射数据
 * @param	format 	格式化的字符串
 * @param	... 	其参数
 * @return			成功与否
 */
int bsp_PrintArt::print(const char* format, ...) {
	u8* dat = (u8*)malloc(Bufflen);						//	分配内存
	if(dat==NULL)return 1;								//	判断分配成功与否
	u32 res;											//	返回状态码
	va_list args;										//	不定长变量
	va_start(args, format);								//	初始化不定长变量
	res=vsprintf((char*)dat,(const char*)format, args);	//	组合
	Transmit(dat, strlen((const char*)dat));			//	发送
	va_end(args);										//	收尸
	free(dat);											//	回收内存
	return res;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
bsp_PrintArt::bsp_PrintArt(void) {
	Bufflen = 128;}
/**
 * @brief			重定向后的发射数据
 * @param	len 	缓冲区大小
 */
bsp_PrintArt::bsp_PrintArt(u32 len) {
	Bufflen = len;}
//----------------------------------------------------------------------------------------------------
bsp_PrintArt_STM32::bsp_PrintArt_STM32(UART_HandleTypeDef *huart,u32 Bufflen):bsp_PrintArt(Bufflen){
	bsp_PrintArt_STM32::huart=huart;}
//----------------------------------------------------------------------------------------------------
bsp_PrintArt_STM32::bsp_PrintArt_STM32(UART_HandleTypeDef *huart):bsp_PrintArt(){
	bsp_PrintArt_STM32::huart=huart;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
