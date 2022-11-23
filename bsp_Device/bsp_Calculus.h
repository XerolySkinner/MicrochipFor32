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
  * @file		bsp_Calculus.h
  * @brief		离散微积分
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-23 02:46
  */
#pragma once
#include <stdlib.h>
#include "varint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
/**
 * @brief 					一个微分对象
 */
class bsp_Differential{
	public:
		bsp_Differential(float dt) {
			bsp_Differential::dt = dt;}
	public:
		float Differential(float var);
	public:
		float dt;			///< 时间参数
	};
//----------------------------------------------------------------------------------------------------
/**
 * @brief 					一个积分对象
 * @note					不应当混用Integral和Integral_list
 * @note					选定一种方式(带缓冲区或者不带)后,就不应该更改使用方式
 * @note					虽然带缓冲区方式对算法时间影响不大,但是为了避免浪费空间,不建议使用过大的缓冲区
 */
class bsp_Integral {
	public:
		bsp_Integral(float dt) {
			bsp_Integral::result_list = NULL;
			bsp_Integral::dt = dt;
			bsp_Integral::results = 0;}
		~bsp_Integral(void) {
			free(result_list);
			result_list = NULL;}
	public:
		float Integral(float var);
		void Integral_set(float results);

		float Integral_list(float var);
		u32 Integral_makelist(u32 len);
		void Integral_dellist(void);
		void Integral_clslist(void);
	public:
		float	*result_list;	///< 数据历史
		u32		result_len;		///< 历史缓冲区长度
		float	results;		///< 积分缓存
		float	dt;				///< 时间参数
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
