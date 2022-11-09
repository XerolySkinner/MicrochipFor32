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
  * @file		STL_Stack.h
  * @brief		实现了STL库中的Stack
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-08 16:41
  */

#ifdef __cplusplus
#pragma once
#include "varint.h"
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	返回值枚举
//	
/**
 * @brief 					栈的返回值
 */
enum STACKS_RES{
	STACKS_OK,				///< 成功
	STACKS_EMPTY,			///< 栈是空的
	STACKS_REAL_ERROR,		///< 重分配出错realloc
	STACKS_MALL_ERROR		///< 重分配出错malloc
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
/**
 * @brief 					一个栈的类
 * @note					使用realloc重新分配方式组织
 *							栈的内存空间的连续的,适合小数据常规速度交换数据
 */
class STL_rStack
{
	public:
		STL_rStack(void);
		~STL_rStack(void);
	public:
		u8		push		(u8 var);
		u8		pop			(void);
		u8		top			(u8& var);
		u32		The_size	(void);
		u32		The_room	(void);
		u8		clean		(void);

		u8		poptop		(void);

		u8		push32		(u32 var);
		u32		poptop32	(void);

		void	pushfun(void(*fun)(void));
		void	(*poptopfun(void))(void);
	private:
		u32		room;		//	分配空间
		u32		size;		//	已有成员
		u8*		dat;		//	数据头
};
//----------------------------------------------------------------------------------------------------
/**
 * @brief 					链表方式栈的节点
 */
struct _lStack {
	struct _lStack*	front;		///< 前一个节点的指针
	void*			dat;		///< 数据的指针
	u32				size;		///< 该数据的大小
	};
typedef struct _lStacks _lStacks;
/**
 * @brief 					一个栈的类
 * @note					使用链表重新分配方式组织
 *							栈的内存空间是非连续的,适合快速交换数据
 */
class STL_lStack{
	public:
		STL_lStack(void);
		~STL_lStack(void);
	public:
		u8		push(void* &var, u32 size);
		u8		pop(void);
		u8		top(void* &var, u32& size);

		u8		push8(u8 var);
		u8		top8(u8& var);
		u8		poptop8(void);

		u8		push32(u32 var);
		u8		top32(u32& var);
		u32		poptop32(void);

		u8		pushfun(void(*fun)(void));
		void	(*poptopfun(void))(void);
	private:
		u32			mem;		//	已有成员
		_lStack*	dat;		//	栈顶成员
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
