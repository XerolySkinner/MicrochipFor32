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
  * @file		bsp_PID.cpp
  * @brief		实现了PID算法
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-09 03:12
  */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
//	
#include "bsp_PID.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
//	
/**
 * @brief				PID算法
 * @param	temp 		目前变量
 * @return				返回调整量
 */
float bsp_Position_PID::PID(float temp) {
	float thisError;
	thisError = target - temp;		//当前误差等于设定值减去当前值
	integral += thisError;			//误差积分，把所有误差累加起来
	result = 
		Kp * thisError + 
		Ki * integral + 
		Kd * (thisError - lasterror);
	lasterror = thisError;

	if (result_H == result_L)return result;
	if (result >= result_H)result == result_H;
	else if (result <= result_L)result == result_L;
	return result;
}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				PID算法
 * @param	temp		目前变量
 * @return				返回调整量
 */
float bsp_Increment_PID::PID(float temp) {
	float thisError=target - temp;	//当前误差等于设定值减去当前值
	float increment;
	float pError, dError, iError;

	pError = thisError - lasterror;
	iError = thisError;
	dError = thisError - 2 * lasterror + preerror;

	increment = 
		Kp * pError + 
		Ki * iError + 
		Kd * dError;				//增量计算
	preerror = lasterror;			//存放偏差用于下次运算
	lasterror = thisError;			//存放偏差用于下次运算
	result += increment;			//上次结果叠加增量

	if (result_H == result_L)return result;
	if (result >= result_H)result == result_H;
	else if (result <= result_L)result == result_L;
	return result;}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
/**
 * @brief			清理历史数据
 * @return			清除PID运算数据
 */
void bsp_Position_PID::clean(void) {
	integral = 0;		//积分值
	lasterror = 0;		//前一拍偏差
	result = 0;			//输出值
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			清理历史数据
 * @return			清除PID运算数据
 */
void bsp_Increment_PID::clean(void) {
	lasterror = 0;		//前一拍偏差   
	preerror = 0;		//前两拍偏差
	result = 0;			//输出值
	}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
/**
 * @brief			PID参数设置
 * @param	P	 	P参数
 * @param	I	 	I参数
 * @param	D	 	D参数
 */
void bsp_Position_PID::set(float P, float I, float D) {
	Kp = P; Ki = I; Kd = D;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			PID参数设置
 * @param	P	 	P参数
 * @param	I	 	I参数
 * @param	D	 	D参数
 */
void bsp_Increment_PID::set(float P, float I, float D) {
	Kp = P; Ki = I; Kd = D;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
//	
bsp_Position_PID::bsp_Position_PID(void) {
	bsp_Position_PID::target = 0;
	bsp_Position_PID::lasterror = 0;
	bsp_Position_PID::Kp = 0;
	bsp_Position_PID::Ki = 0;
	bsp_Position_PID::Kd = 0;
	bsp_Position_PID::integral = 0;
	bsp_Position_PID::result = 0;
	bsp_Position_PID::result_H = 0;
	bsp_Position_PID::result_L = 0;
}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				PID算法
 * @param	Kp			P参数
 * @param	Ki			I参数
 * @param	Kd			D参数
 * @param	target		目标值
 * @param	result_H	输出最大值
 * @param	result_L	输出最小值
 */
bsp_Position_PID::bsp_Position_PID(
		float Kp, float Ki, float Kd, float target,
		float result_H, float result_L) {
	bsp_Position_PID::target = target;
	bsp_Position_PID::lasterror = 0;
	bsp_Position_PID::Kp = Kp;
	bsp_Position_PID::Ki = Ki;
	bsp_Position_PID::Kd = Kd;
	bsp_Position_PID::integral = 0;
	bsp_Position_PID::result = 0;
	bsp_Position_PID::result_H = 0;
	bsp_Position_PID::result_L = 0;
}
//----------------------------------------------------------------------------------------------------
bsp_Position_PID::~bsp_Position_PID(void) {}
//----------------------------------------------------------------------------------------------------
bsp_Increment_PID::bsp_Increment_PID(void) {
	bsp_Increment_PID::target = 0;
	bsp_Increment_PID::lasterror = 0;
	bsp_Increment_PID::preerror = 0;
	bsp_Increment_PID::Kp = 0;
	bsp_Increment_PID::Ki = 0;
	bsp_Increment_PID::Kd = 0;
	bsp_Increment_PID::result = 0;
	bsp_Increment_PID::result_H = 0;
	bsp_Increment_PID::result_L = 0;
}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				PID算法
 * @param	Kp			P参数
 * @param	Ki			I参数
 * @param	Kd			D参数
 * @param	target		目标值
 * @param	result_H	输出最大值
 * @param	result_L	输出最小值
 */
bsp_Increment_PID::bsp_Increment_PID(
		float Kp, float Ki, float Kd, float target,
	float result_H, float result_L) {
	bsp_Increment_PID::target = target;
	bsp_Increment_PID::lasterror = 0;
	bsp_Increment_PID::preerror = 0;
	bsp_Increment_PID::Kp = Kp;
	bsp_Increment_PID::Ki = Ki;
	bsp_Increment_PID::Kd = Kd;
	bsp_Increment_PID::result = 0;
	bsp_Increment_PID::result_H = 0;
	bsp_Increment_PID::result_L = 0;
}
//----------------------------------------------------------------------------------------------------
bsp_Increment_PID::~bsp_Increment_PID(void) {}
//////////////////////////////////////////////////////////////////////////////////////////////////////
