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
  * @file		bsp_TP2210.c
  * @brief		解包器
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Mon Sep 11 21:19:33 2023

  */
#include "bsp_TP2210.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	函数
void bsp_TP2210_Unpack(u8* instr, u8* outstr, u32* outlen) {
    if (instr == NULL)return;
    if (outstr == NULL)return;
    if (outlen == NULL)return;
    u32 result=0;
    u8 buff[128] = {0};
    u32 inlen = 0;
    result=sscanf((const char*)instr, "+NNMI:%*[^,],%d,%s", &inlen, buff);

    char hex[3];
    *outlen = inlen;

    for (u32 i = 0; i < (*outlen); i++){
        strncpy(hex, (const char*)(buff + i * 2), 2);
        hex[2] = '\0';
        outstr[i] = (u8)strtol(hex, NULL, 16);
    }
}

void bsp_TP2210_pack(u8* instr, u32 inlen, u8* outstr, u32* outlen) {
    if (instr == NULL)return;
    if (outstr == NULL)return;
    if (outlen == NULL)return;
    u8 buff[128] = {0};
    *outlen = inlen;
    for (u32 i = 0; i < inlen; i++)
        sprintf((char*)(buff + i * 2), "%02X", instr[i]);
    sprintf((char*)outstr, "AT+SEND=0000,%d,%s\r\n",*outlen,buff);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
