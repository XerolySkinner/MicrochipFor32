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
  * @file		bsp_Calculus.cpp
  * @brief		离散微积分
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-23 02:46
  */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "bsp_Calculus.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
/**
 * @brief			对数据微分
 * @param	var 	此处填入浮点数据
 * @return			此时的微分值
 */
float bsp_Differential::Differential(float var) {
	static float old=var;
	float result= (var - old) / dt;
	old = var;
	return result;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
/**
 * @brief			对数据积分
 * @param	var 	此处填入浮点数据
 * @return			从开始到现在的总积分值
 */
float bsp_Integral::Integral(float var) {
	results += var * dt;
	return results;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			重设当前积分值
 * @param	var 	要设置的积分值
 */
void bsp_Integral::Integral_set(float results) {
	bsp_Integral::results = results;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			赋予历史缓存长度
 * @param	var 	分配的缓存长度
 * @return			返回分配的内存位置,0为分配失败
 */
u32 bsp_Integral::Integral_makelist(u32 len) {
	result_list = (float*)malloc(sizeof(float)* len);
	result_len = len;
	Integral_clslist();
	return (u32)result_list;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			进行带有缓冲区的积分
 * @param	var 	需要积分的数值
 * @return			返回积分值
 */
float bsp_Integral::Integral_list(float var) {
	static u32 len=0;
	results += var * dt;
	//	保存历史
	result_list[len] = var * dt;
	//	轮盘转
	++len;
	if (len == result_len)len = 0;
	//	去除尾值
	if (len < result_len - 1)
		results -= result_list[len + 1];
	else
		results -= result_list[0];
	//	
	return results;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			删除并释放历史缓冲区
 */
void bsp_Integral::Integral_dellist(void) {
	free(result_list);
	result_len = 0;
	result_list = NULL;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			清空历史缓存区
 */
void bsp_Integral::Integral_clslist(void) {
	if (result_list == NULL)return;
	for (u32 i = 0; i < result_len; i++)
		result_list[i] = 0;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
