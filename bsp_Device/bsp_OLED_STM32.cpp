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
  * @file		 bsp_OLED_STM32.cpp
  * @brief		 在STM32下实现OLED通信
  * @mainpage	 主要信息
  * @author 	 Yuankang Liang(XerolySkinner)
  * @email		 zabbcccbbaz@163.com
  * @version	 V1.0.0
  * @date		 2022-11-07 13:19
  */

#ifdef __cplusplus
#include "bsp_IIC_STM32.h"
#include "bsp_OLED_STM32.h"
extern const u8 OLED_WORD_ASCII[];
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
//	
/**
 * @brief			发送一条指令给OLED
 * @param	cmd 	要发送的指令
 */ 
void bsp_STM32_OLED::Send_cmd(u8 cmd) {
	IIC_WriteOneByte(0x3C, 0x00, cmd);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送一条数据给OLED
 * @param	dat 	要发送的数据
 */ 
void bsp_STM32_OLED::Send_dat(u8 dat) {
	IIC_WriteOneByte(0x3C, 0x40, dat);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			发送一串定长指令给OLED
 * @param	*dat 	要发送的指令头
 * @param	len 	指令长度
 */ 
void bsp_STM32_OLED::Send_len_dat(u8* dat, u32 len) {
	IIC_Write(0x3C, 0x40, (u8*)dat, len);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			光标定位行中的位置
 * @param	column 	设定的该行位置
 */ 
void bsp_STM32_OLED::Column_set(u8 column) {
	Send_cmd(0x10 | (column >> 4));		//设置列地址高位
	Send_cmd(0x00 | (column & 0x0f));		//设置列地址低位
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			光标定位于一页
 * @param	page 	设定所处的页位置
 */ 
void bsp_STM32_OLED::Page_set(u8 page) {
	Send_cmd(0xb0 + page);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			全页绘制
 * @param	dat 	全页绘制的数据,0x00为清空,0xFF为全涂
 */
void bsp_STM32_OLED::Clear(u8 dat) {
	u8 page;
	for (page = 0; page < 8; page++) {
		Page_set(page);
		Column_set(0);
		IIC_Start();
		IIC_SendByte(0x3C << 1);
		IIC_WaitAck();
		IIC_SendByte(0x40);
		IIC_WaitAck();
		for (int i = 0; i < 128; i++) {
			IIC_SendByte(dat);
			IIC_WaitAck();}
		IIC_Stop();}}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				OLED绘图
 * @param	*ptr_pic	图片数据的头
 */
void bsp_STM32_OLED::Picture_display(const u8* ptr_pic) {
	u8 page;
	for (page = 0; page < (64 / 8); page++) {
		Page_set(page);
		Column_set(0);
		IIC_Start();
		IIC_SendByte(0x3C << 1);
		IIC_WaitAck();
		IIC_SendByte(0x40);
		IIC_WaitAck();
		for (int i = 0; i < 128; i++) {
			IIC_SendByte(ptr_pic[i]);
			IIC_WaitAck();}
		IIC_Stop();
		ptr_pic += 128;}}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				OLED反向绘图
 * @param	*ptr_pic	图片数据的头
 */
void bsp_STM32_OLED::Picture_ReverseDisplay(const u8* ptr_pic) {
	u8 page;
	for (page = 0; page < (64 / 8); page++) {
		Page_set(page);
		Column_set(0);
		IIC_Start();
		IIC_SendByte(0x3C << 1);
		IIC_WaitAck();
		IIC_SendByte(0x40);
		IIC_WaitAck();
		for (int i = 0; i < 128; i++) {
			IIC_SendByte(~(ptr_pic[i]));
			IIC_WaitAck();}
		IIC_Stop();
		ptr_pic += 128;}}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				OLED绘制ASCII字符
 * @param	H			行数
 * @param	V			列数
 * @param	word		所要显示的字符
 */
void bsp_STM32_OLED::Draw_ASCII(u32 H, u32 V, u8 word) {
	word -= 33;
	Page_set(V * 2);
	Column_set(H * 8);
	Send_len_dat((u8*)(OLED_WORD_ASCII + (word * 16)), 8);
	Page_set(V * 2 + 1);
	Column_set(H * 8);
	Send_len_dat((u8*)(OLED_WORD_ASCII + (word * 16) + 8), 8);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief				OLED初始化
 *						初始化显示屏的设置
 */
void bsp_STM32_OLED::Init(void) {
	for (int i = 0; i < 25; i++)
		Send_cmd(OLED_init_cmd[i]);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
