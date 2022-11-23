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
  * @file		bsp_flash.h
  * @brief		дSTM32��Flash��
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-07-13 22:38
  */


#include "main.h"
uint32_t FlashAddr = 0x08010000;									///< ��дFlash��ʼ��ַ,�������򲿷�
//----------------------------------------------------------------------------------------------------
#pragma pack(4)
/**
 * @brief			һ�����ݵ�����
 * @todo			��������ڲ����ݷ����ȡ
 */ 
struct struct_bsp_Flash_Pack{
	char	Var0;
	short	Var1;
	int		Var2;
}bsp_Flash_Pack={0,0,0};
#pragma pack()
//----------------------------------------------------------------------------------------------------
/**
 * @brief			д��һҳFlash�ռ�
 * @param	*dat 	Ҫд�������
 * @param	num 	Ҫд�������
 * @return			����0��ɹ�
 */ 
uint32_t bsp_WriteFlashOnePage(uint32_t *dat,uint32_t num){
	FLASH_EraseInitTypeDef f;
	uint32_t PageError = 0;											//�����7
	HAL_FLASH_Unlock();												//����FLASH
	f.TypeErase = FLASH_TYPEERASE_PAGES;							//Flash����
	f.PageAddress = FlashAddr;										//������ַ(��ʼҳ)
	f.NbPages = 1;													//����1ҳ
	HAL_FLASHEx_Erase(&f,&PageError);								//���ò�������
	for(int i=0;i<num;i++)
		HAL_FLASH_Program(TYPEPROGRAM_WORD,FlashAddr+i*4,dat[i]);	//��FLASH��д
	HAL_FLASH_Lock(); 												//��סFLASH
	return PageError;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			��ȡһҳFlash�ռ�
 * @param	*dat 	��ȡ���ݵĻ�����
 * @param	num 	��ȡ����
 * @return			�޷���
 */ 
void bsp_ReadFlash(uint32_t *dat,uint32_t num){						//����һ������
	for(int i=0;i<num;i++)
		dat[i]=*(__IO uint32_t*)(FlashAddr+i*4);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			��һ�����ݴ���Flash
 * @return			�޷���
 */ 
void bsp_WriteFlash_Pack(void){
	bsp_WriteFlashOnePage((uint32_t*)(&bsp_Flash_Pack),sizeof(struct struct_bsp_Flash_Pack));
	return;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			��Flash��ȡһ������
 * @return			�޷���
 */ 
void bsp_ReadFlash_Pack(void){
	bsp_ReadFlash((uint32_t*)(&bsp_Flash_Pack),sizeof(struct struct_bsp_Flash_Pack));
	return;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
