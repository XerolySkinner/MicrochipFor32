/*----------------------------------------------------------------------------------------------------
 #
 #	Copyright (c) 2022 Yuankang Liang(XerolySkinner)
 #
 #	�������ԭ���ṩ,���κ���ʾ��ʾ
 #	���κ������,���߶����е��κ����⳥����
 #
 #	ʹ�õ��������:
 #	1.	�����������������Դ,�㲻���������д��ԭʼ���.
 #	2.	����������κ�Ŀ��,ǰ���ǰ�Ȩ�������������и�����.
 #		���Ұ�Ȩ�������������ͬʱ����.
 #	3.	����ʹ��,����,�޸�,�ַ�,�����۱���������.
 #	4.	������ڲ�Ʒ��ʹ��,��Ʒ�ĵ��е����������͵ĵ����Ǳ����.
 #	5.	��֪ͨ���ô��κ���Դɾ�������.
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
  * @brief		 ��STM32��ʵ��OLEDͨ��
  * @mainpage	 ��Ҫ��Ϣ
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
//	�ຯ��
//	
/**
 * @brief			����һ��ָ���OLED
 * @param	cmd 	Ҫ���͵�ָ��
 */ 
void bsp_STM32_OLED::Send_cmd(u8 cmd) {
	IIC_WriteOneByte(0x3C, 0x00, cmd);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����һ�����ݸ�OLED
 * @param	dat 	Ҫ���͵�����
 */ 
void bsp_STM32_OLED::Send_dat(u8 dat) {
	IIC_WriteOneByte(0x3C, 0x40, dat);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			����һ������ָ���OLED
 * @param	*dat 	Ҫ���͵�ָ��ͷ
 * @param	len 	ָ���
 */ 
void bsp_STM32_OLED::Send_len_dat(u8* dat, u32 len) {
	IIC_Write(0x3C, 0x40, (u8*)dat, len);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			��궨λ���е�λ��
 * @param	column 	�趨�ĸ���λ��
 */ 
void bsp_STM32_OLED::Column_set(u8 column) {
	Send_cmd(0x10 | (column >> 4));		//�����е�ַ��λ
	Send_cmd(0x00 | (column & 0x0f));		//�����е�ַ��λ
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			��궨λ��һҳ
 * @param	page 	�趨������ҳλ��
 */ 
void bsp_STM32_OLED::Page_set(u8 page) {
	Send_cmd(0xb0 + page);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			ȫҳ����
 * @param	dat 	ȫҳ���Ƶ�����,0x00Ϊ���,0xFFΪȫͿ
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
 * @brief				OLED��ͼ
 * @param	*ptr_pic	ͼƬ���ݵ�ͷ
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
 * @brief				OLED�����ͼ
 * @param	*ptr_pic	ͼƬ���ݵ�ͷ
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
 * @brief				OLED����ASCII�ַ�
 * @param	H			����
 * @param	V			����
 * @param	word		��Ҫ��ʾ���ַ�
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
 * @brief				OLED��ʼ��
 *						��ʼ����ʾ��������
 */
void bsp_STM32_OLED::Init(void) {
	for (int i = 0; i < 25; i++)
		Send_cmd(OLED_init_cmd[i]);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
