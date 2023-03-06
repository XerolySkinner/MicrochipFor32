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
  * @file		bsp_PID.h
  * @brief		实现了PID算法
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-09 03:12
  */

#ifdef __cplusplus
#pragma once
#include "varint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
/**
 * @brief 					位置法为基础的PID算法
 */
class bsp_Position_PID{
	public:
		bsp_Position_PID(void);
		bsp_Position_PID(
			float Kp, float Ki, float Kd, float target,
			float result_H, float result_L);
		~bsp_Position_PID(void);
	public:
		float	PID(float temp);
		void	clean(void);
		void	set(float P, float I, float D);
	public:
		float target;		///< 设定值
		float Kp;			///< 比例系数
		float Kd;			///< 积分系数
		float Ki;			///< 微分系数
		float result;		///< 输出值
	private:
		float integral;		///< 积分值
		float lasterror;	///< 前一拍偏差

		float result_H;		///< 输出最高值
		float result_L;		///< 输出最低值
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
/**
 * @brief 					增量法为基础的PID算法
 */
class bsp_Increment_PID {
	public:
		bsp_Increment_PID(void);
		bsp_Increment_PID(
			float Kp, float Ki, float Kd, float target,
			float result_H, float result_L);
		~bsp_Increment_PID(void);
	public:
		float	PID(float temp);
		void	clean(void);
		void	set(float P, float I, float D);
	public:
		float target;		///< 设定值
		float Kp;			///< 比例系数
		float Kd;			///< 积分系数
		float Ki;			///< 微分系数
		float result;		///< 输出值
	private:
		float lasterror;	///< 前一拍偏差
		float preerror;		///< 前两拍偏差

		float result_H;		///< 输出最高值
		float result_L;		///< 输出最低值
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
