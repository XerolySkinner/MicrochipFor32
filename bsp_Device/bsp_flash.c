/*----------------------------------------------------------------------------------------------------
#	THIS FILE IS PART OF XEROLYSKINNER'S PROJECT
#
#	THIS PROGRAM IS FREE SOFTWARE
#
#	E-mail:ZABBCCCBBAZ@163.com
#	QQ:2715099320
#
#	Copyright (c) 2022 XerolySkinner
#	All rights reserved.
*/

/*----------------------------------------------------------------------------------------------------
	����:MainSystem
	ʱ��:20220713-2238
	����Ա:��Դ��
	˵��:������
*/

#include "main.h"
uint32_t FlashAddr = 0x08010000;									//��ʼ��ַ
//----------------------------------------------------------------------------------------------------
#pragma pack(4)
struct struct_bsp_Flash_Pack{
	char	Var0;
	short	Var1;
	int		Var2;
}bsp_Flash_Pack={0,0,0};
#pragma pack()
//----------------------------------------------------------------------------------------------------
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
void bsp_ReadFlash(uint32_t *dat,uint32_t num){						//����һ������
	for(int i=0;i<num;i++)
		dat[i]=*(__IO uint32_t*)(FlashAddr+i*4);}
//----------------------------------------------------------------------------------------------------
void bsp_WriteFlash_Pack(void){
	bsp_WriteFlashOnePage((uint32_t*)(&bsp_Flash_Pack),sizeof(struct struct_bsp_Flash_Pack));
	return;}
//----------------------------------------------------------------------------------------------------
void bsp_ReadFlash_Pack(void){
	bsp_ReadFlash((uint32_t*)(&bsp_Flash_Pack),sizeof(struct struct_bsp_Flash_Pack));
	return;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
