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
  * @file		bsp_flash.h
  * @brief		写STM32的Flash库
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-07-13 22:38
  */


#include "main.h"
uint32_t FlashAddr = 0x08010000;									///< 读写Flash起始地址,跳过程序部分
//----------------------------------------------------------------------------------------------------
#pragma pack(4)
/**
 * @brief			一包数据的内容
 * @todo			随意更改内部内容方便读取
 */ 
struct struct_bsp_Flash_Pack{
	char	Var0;
	short	Var1;
	int		Var2;
}bsp_Flash_Pack={0,0,0};
#pragma pack()
//----------------------------------------------------------------------------------------------------
/**
 * @brief			写入一页Flash空间
 * @param	*dat 	要写入的数据
 * @param	num 	要写入的数量
 * @return			返回0则成功
 */ 
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
/**
 * @brief			读取一页Flash空间
 * @param	*dat 	读取数据的缓冲区
 * @param	num 	读取数量
 * @return			无返回
 */ 
void bsp_ReadFlash(uint32_t *dat,uint32_t num){						//读入一串数据
	for(int i=0;i<num;i++)
		dat[i]=*(__IO uint32_t*)(FlashAddr+i*4);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			将一包数据存入Flash
 * @return			无返回
 */ 
void bsp_WriteFlash_Pack(void){
	bsp_WriteFlashOnePage((uint32_t*)(&bsp_Flash_Pack),sizeof(struct struct_bsp_Flash_Pack));
	return;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			从Flash读取一包数据
 * @return			无返回
 */ 
void bsp_ReadFlash_Pack(void){
	bsp_ReadFlash((uint32_t*)(&bsp_Flash_Pack),sizeof(struct struct_bsp_Flash_Pack));
	return;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
