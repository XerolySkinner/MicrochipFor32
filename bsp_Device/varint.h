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
 * @file		varint
 * @brief		全局共用的标准类型表
 * @mainpage	主要信息
 * @author		Yuankang Liang(XerolySkinner)
 * @email		zabbcccbbaz@163.com
 * @version		V1.0.0
 * @date		2022-11-07 18:50
 */

#pragma once
#include "stdint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	程序
//	
typedef uint8_t			u8;		///< 8位无符号数类型
typedef uint16_t		u16;	///< 16位无符号数类型
typedef uint32_t		u32;	///< 32位无符号数类型
typedef uint64_t		u64;	///< 64位无符号数类型

typedef int8_t			i8;		///< 8位有符号数类型
typedef int16_t			i16;	///< 16位有符号数类型
typedef int32_t			i32;	///< 32位有符号数类型
typedef int64_t			i64;	///< 64位有符号数类型

typedef volatile u8		vu8;	///< 8位无符号易变类型
typedef volatile u16 	vu16;	///< 16位无符号易变类型
typedef volatile u32 	vu32;	///< 32位无符号易变类型
typedef volatile u64 	vu64;	///< 64位无符号易变类型

typedef volatile i8		vi8;	///< 8位有符号易变类型
typedef volatile i16 	vi16;	///< 16位有符号易变类型
typedef volatile i32 	vi32;	///< 32位有符号易变类型
typedef volatile i64 	vi64;	///< 64位有符号易变类型
//////////////////////////////////////////////////////////////////////////////////////////////////////

