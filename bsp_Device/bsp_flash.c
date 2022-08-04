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
	名字:MainSystem
	时间:20220713-2238
	程序员:梁源康
	说明:主程序
*/

#include "main.h"
uint32_t FlashAddr = 0x08010000;									//起始地址
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
	uint32_t PageError = 0;											//错误号7
	HAL_FLASH_Unlock();												//解锁FLASH
	f.TypeErase = FLASH_TYPEERASE_PAGES;							//Flash擦除
	f.PageAddress = FlashAddr;										//擦除地址(起始页)
	f.NbPages = 1;													//擦除1页
	HAL_FLASHEx_Erase(&f,&PageError);								//调用擦除函数
	for(int i=0;i<num;i++)
		HAL_FLASH_Program(TYPEPROGRAM_WORD,FlashAddr+i*4,dat[i]);	//对FLASH烧写
	HAL_FLASH_Lock(); 												//锁住FLASH
	return PageError;}
//----------------------------------------------------------------------------------------------------
void bsp_ReadFlash(uint32_t *dat,uint32_t num){						//读入一串数据
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
