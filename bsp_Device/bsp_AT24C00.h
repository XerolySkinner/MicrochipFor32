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
#ifndef _XEROLYSKINNER_AT24C00_H
#define _XEROLYSKINNER_AT24C00_H
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	写入数据
//	
#pragma pack(1)
struct struct_AT_Dat{
	char 	Var0;
	short	Var1;
	int		Var2;
	};
#pragma pack()
extern struct struct_AT_Dat AT_Dat;
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	程序
//	
void AT_WriteOneByte(char ID,char addr,char dat);
char AT_ReadOneByte(char ID,char addr,char dat);
void AT_WriteByte(char ID,char addr,char *dat,char len);
void AT_ReadByte(char ID,char addr,char *dat,char len);
void AT_Write_Pack(char ID,struct struct_AT_Dat *AT_Dat);
void AT_Read_Pack(char ID,struct struct_AT_Dat *AT_Dat);
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
