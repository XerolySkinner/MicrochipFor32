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
	����:bsp_AT24C00
	ʱ��:20220802-2220
	����Ա:��Դ��
	˵��:
*/
#ifndef _XEROLYSKINNER_AT24C00_H
#define _XEROLYSKINNER_AT24C00_H
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	д������
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
//	����
//	
void AT_WriteOneByte(char ID,char addr,char dat);
char AT_ReadOneByte(char ID,char addr,char dat);
void AT_WriteByte(char ID,char addr,char *dat,char len);
void AT_ReadByte(char ID,char addr,char *dat,char len);
void AT_Write_Pack(char ID,struct struct_AT_Dat *AT_Dat);
void AT_Read_Pack(char ID,struct struct_AT_Dat *AT_Dat);
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
