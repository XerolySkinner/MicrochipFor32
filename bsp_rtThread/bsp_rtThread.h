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
  * @file		bsp_rtThread.h
  * @brief		初始化rtThread
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Thu Dec 14 16:55:59 2023

  */
#ifndef _bsp_rtThread_H
#define _bsp_rtThread_H
#include "vartable.h"
#include "varint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	定义
/**
 * @brief			TODO
 */
#define THREAD_ADD_INIT(name) 						\
		do{											\
			rt_thread_init(							\
				&(name##_Thread),					\
				#name,								\
				name##_entry,						\
				RT_NULL,							\
				name##_stack,						\
				sizeof(name##_stack),				\
				0,									\
				10);								\
			rt_thread_startup(&(name##_Thread));	\
		}while(0)
		
#define THREAD_DEFINE_INIT(name,size)				\
        static char name##_stack[size];				\
        static struct rt_thread name##_Thread		\
		
#define THREAD_EXTERN_INIT(name) void name##_entry(void* parameter)
	
#define osDelay(x) rt_thread_delay(x)
#define taskENTER_CRITICAL() rt_interrupt_enter()
#define taskEXIT_CRITICAL()	rt_interrupt_leave()
//----------------------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"{
#endif
void bsp_rtThread_Init(void);
THREAD_EXTERN_INIT(bsp_app0);
#ifdef __cplusplus
}
#endif
//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
