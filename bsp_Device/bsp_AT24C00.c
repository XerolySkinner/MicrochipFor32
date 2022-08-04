/*----------------------------------------------------------------------------------------------------
#	THIS FILE IS A PART OF XerolySkinner's PROJECT
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
	名字:bsp_AT24C00
	时间:20220802-2220
	程序员:梁源康
	说明:
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "vartable.h"

#define	IIC_ADDR_24C02	0x50
#define	AT_PAGE			8
#define AT_IIC_COM		bspIIC0
struct struct_AT_Dat	AT_Dat={0,0,0};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	程序
//	
void AT_Delay(void){
	HAL_Delay(5);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//	基础实现
void AT_WriteOneByte(char ID,char addr,char dat){
	IIC_WriteOneByte(AT_IIC_COM,IIC_ADDR_24C02+ID,addr,dat);
	AT_Delay();}
char AT_ReadOneByte(char ID,char addr,char dat){
	return IIC_ReadOneByte(AT_IIC_COM,IIC_ADDR_24C02+ID,addr);}
//----------------------------------------------------------------------------------------------------
void AT_WriteByte(char ID,char addr,char *dat,char len){
	unsigned int member=0;
	IIC_Start(AT_IIC_COM);
	IIC_SendByte(AT_IIC_COM,(IIC_ADDR_24C02+ID)<<1);
	IIC_WaitAck(AT_IIC_COM);
	IIC_SendByte(AT_IIC_COM,addr);
	IIC_WaitAck(AT_IIC_COM);
	do{
		IIC_SendByte(AT_IIC_COM,dat[member]);
		IIC_WaitAck(AT_IIC_COM);
		member++;
		if(((member+addr)%AT_PAGE)==0){
			IIC_Stop(AT_IIC_COM);
			AT_Delay();
			IIC_Start(AT_IIC_COM);
			IIC_SendByte(AT_IIC_COM,(IIC_ADDR_24C02+ID)<<1);
			IIC_WaitAck(AT_IIC_COM);
			IIC_SendByte(AT_IIC_COM,addr+member);
			IIC_WaitAck(AT_IIC_COM);}
		}while(member!=len);
	IIC_Stop(AT_IIC_COM);
	AT_Delay();}
void AT_ReadByte(char ID,char addr,char *dat,char len){
	IIC_ReadByte(AT_IIC_COM,IIC_ADDR_24C02+ID,addr,dat,len);}
//----------------------------------------------------------------------------------------------------
void AT_Write_Pack(char ID,struct struct_AT_Dat *AT_Dat){
	AT_WriteByte(ID,0,(char*)AT_Dat,sizeof(struct struct_AT_Dat));}
void AT_Read_Pack(char ID,struct struct_AT_Dat *AT_Dat){
	AT_ReadByte(ID,0,(char*)AT_Dat,sizeof(struct struct_AT_Dat));}
//////////////////////////////////////////////////////////////////////////////////////////////////////
