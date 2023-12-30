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
  * @file		bsp_ESP8266.h
  * @brief		ESP8266
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Fri Dec 29 16:39:52 2023

  */
#ifndef _bsp_ESP8266_H
#define _bsp_ESP8266_H
#include "stdlib.h"
#include "varint.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include <rtthread.h>

#define esp_malloc malloc
#define osDelay(x) rt_thread_delay(x)
#define ESP_DEBUG_PRINT

#ifdef __cplusplus
extern "C"{
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	定义
/**
 * @brief			TODO
 */
enum{
	ESP_LINKING,
	ESP_UNLINK,
};

typedef struct{
	//	发送接口
	u8 (*transmit)(u8*,u32);
	u8* TX_buff;
	rt_sem_t semaphore_OK;
	u8 state;
	
	u8 *title;
	u32 value;
	u8 *msg;
}_esp_struct;
typedef _esp_struct* _esp;
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	定义
_esp esp_create(u8 (*transmit)(u8*,u32));
u8 esp_Callback(_esp obj,const char* str,u32 limit);
void esp_CIPSEND_With_ID(_esp obj,u32 id,u8* buff,u32 len);
void esp_CIPSEND_Without_ID(_esp obj,u8* buff,u32 len);
//----------------------------------------------------------------------------------------------------
void esp_AP_TCP_Server_Init(
	_esp obj,
	const char* Sname,
	const char* Spswd,
	const char* Sport);

void esp_AP_TCP_Client_Init(
	_esp obj,
	const char* Sname,
	const char* Spswd,
	const char* Cip,
	const char* Cport);
	
void esp_AP_UDP_Init(
	_esp obj,
	const char* Sname,
	const char* Spswd,
	const char* Cip,
	const char* Cport);
//----------------------------------------------------------------------------------------------------
void esp_STA_TCP_Client_Init(
	_esp obj,
	const char* Cname,
	const char* Cpswd,
	const char* Cip,
	const char* Cport);
	
void esp_STA_TCP_Server_Init(
	_esp obj,
	const char* Cname,
	const char* Cpswd,
	const char* Sport);
	
void esp_STA_UDP_Init(
	_esp obj,
	const char* Cname,
	const char* Cpswd,
	const char* Cip,
	const char* Cport);
//----------------------------------------------------------------------------------------------------
void esp_MQTT_Client_Init(
	_esp obj,
	const char* Sname,
	const char* Spswd,
	const char* Cip,
	const char* Cport,
	const char* mqtt_ID,
	const char* mqtt_user,
	const char* mqtt_psw);
	
void esp_MQTT_PUSH(
	_esp obj,
	const char* title,
	const char* msg);
	
void esp_MQTT_SUB(
	_esp obj,
	const char* title);

u32 parseMQTTMessage(_esp obj,const char *str);
//----------------------------------------------------------------------------------------------------
int esp_print(_esp obj,const char* format, ...);
const char* findSubstring(const char* haystack, const char* needle, uint32_t limit);
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif
