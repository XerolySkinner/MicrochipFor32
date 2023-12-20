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
  * @file		mbm_ModBusRTU.c
  * @brief		主机ModBusRTU
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Thu Sep 21 17:08:36 2023

  */
#include "mbm_ModBusRTU.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	函数
/**
 * @brief			mb_Slave_create
 * @param	var 	vars
 * @return			_mb_slave
 */
_mb_master mb_Master_create(const char* str,...){
	va_list list;
	va_start(list, str);
	char field[10] = {0};
	//	分配内存区
	_mb_master result=(_mb_struct_master*)mb_malloc(sizeof(_mb_struct_master));
	if(result==NULL)return NULL;
	//	指令集判定
	while (sscanf(str, "-%[^-]", field) == 1){
		if (!strcmp(field, "transmit")) {
			result->tramsmit=va_arg(list,mb_transmit);}
		if (!strcmp(field, "TxBuffSize")) {
			result->TxMaxLen=va_arg(list,u32);
			result->TxBuff=(u8*)mb_malloc(result->TxMaxLen);
			if(result->TxBuff==NULL){
				free(result);
				return NULL;}}
		if (!strcmp(field, "RxCoilBuff")){
			result->RxCoilMaxLen=va_arg(list,u32);
			result->RxCoilBuff=(u8*)mb_malloc(result->RxCoilMaxLen);
			if(result->RxCoilBuff==NULL){
				free(result);
				return NULL;}}
		if (!strcmp(field, "RxRegBuff")){
			result->RxRegMaxLen=va_arg(list,u32);
			result->RxRegBuff=(u16*)mb_malloc(result->RxRegMaxLen);
			if(result->RxRegBuff==NULL){
				free(result);
				return NULL;}}
		str += (strlen(field) + 1);
	}
	//	初始化值
	result->VarBuff=(void*)malloc(512);
	result->VarNum=0;
	
	va_end(list);
	return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_RD_OUT_COIL_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem){
	//	数据记录
	obj->TxID=ID;
	obj->TxFunc=MB_FUNC_RD_OUT_COIL;
	obj->TxAddr=Addr;
	
	obj->Mem=Mem;
	//	处理入值
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=ID;
	*Buff++=MB_FUNC_RD_OUT_COIL;
	//	数据导入
	*Buff++=Pn8(Addr,Dat_Endian);
	*Buff++=Pn8(Addr,!Dat_Endian);
	*Buff++=Pn8(Mem,Dat_Endian);
	*Buff++=Pn8(Mem,!Dat_Endian);
	//	计算CRC
	crc=mb_crc(obj->TxBuff,6);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,8);
	return 0;
}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_RD_IN_COIL_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem){
	//	数据记录
	obj->TxID=ID;
	obj->TxFunc=MB_FUNC_RD_IN_COIL;
	obj->TxAddr=Addr;
	
	obj->Mem=Mem;
	//	处理入值
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=ID;
	*Buff++=MB_FUNC_RD_IN_COIL;
	//	数据导入
	*Buff++=Pn8(Addr,Dat_Endian);
	*Buff++=Pn8(Addr,!Dat_Endian);
	*Buff++=Pn8(Mem,Dat_Endian);
	*Buff++=Pn8(Mem,!Dat_Endian);
	//	计算CRC
	crc=mb_crc(obj->TxBuff,6);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,8);
	return 0;
}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_RD_HOLD_REG_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem){
	//	数据记录
	obj->TxID=ID;
	obj->TxFunc=MB_FUNC_RD_HOLD_REG;
	obj->TxAddr=Addr;
	
	obj->Mem=Mem;
	//	处理入值
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=ID;
	*Buff++=MB_FUNC_RD_HOLD_REG;
	//	数据导入
	*Buff++=Pn8(Addr,Dat_Endian);
	*Buff++=Pn8(Addr,!Dat_Endian);
	*Buff++=Pn8(Mem,Dat_Endian);
	*Buff++=Pn8(Mem,!Dat_Endian);
	//	计算CRC
	crc=mb_crc(obj->TxBuff,6);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,8);
	return 0;
}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_RD_IN_REG_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem){
	//	数据记录
	obj->TxID=ID;
	obj->TxFunc=MB_FUNC_RD_IN_REG;
	obj->TxAddr=Addr;
	
	obj->Mem=Mem;
	//	处理入值
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=ID;
	*Buff++=MB_FUNC_RD_IN_REG;
	//	数据导入
	*Buff++=Pn8(Addr,Dat_Endian);
	*Buff++=Pn8(Addr,!Dat_Endian);
	*Buff++=Pn8(Mem,Dat_Endian);
	*Buff++=Pn8(Mem,!Dat_Endian);
	//	计算CRC
	crc=mb_crc(obj->TxBuff,6);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,8);
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_WR_COIL_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Data){
	//	数据记录
	u8* Buff=obj->TxBuff;
	u16 crc;
	Data=Data?0xFF00:0x0000;
	//	填入顺序项
	*Buff++=ID;
	*Buff++=MB_FUNC_WR_COIL;
	//	数据导入
	*Buff++=Pn8(Addr,Dat_Endian);
	*Buff++=Pn8(Addr,!Dat_Endian);
	*Buff++=Pn8(Data,Dat_Endian);
	*Buff++=Pn8(Data,!Dat_Endian);
	//	计算CRC
	crc=mb_crc(obj->TxBuff,6);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,8);
	return 0;
}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_WR_REG_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Data){
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=ID;
	*Buff++=MB_FUNC_WR_REG;
	//	数据导入
	*Buff++=Pn8(Addr,Dat_Endian);
	*Buff++=Pn8(Addr,!Dat_Endian);
	*Buff++=Pn8(Data,Dat_Endian);
	*Buff++=Pn8(Data,!Dat_Endian);
	//	计算CRC
	crc=mb_crc(obj->TxBuff,6);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,8);
	return 0;
}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_WR_REGS_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,u16* Data){
	u8 Byte=Mem*2;
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=ID;
	*Buff++=MB_FUNC_WR_REGS;
	*Buff++=Pn8(Addr,Dat_Endian);
	*Buff++=Pn8(Addr,!Dat_Endian);
	*Buff++=Pn8(Mem,Dat_Endian);
	*Buff++=Pn8(Mem,!Dat_Endian);
	*Buff++=Byte;
	//	数据导入
	for(u32 i=0;i<Mem;i++){
		*Buff++=Pn8(Data[i],Dat_Endian);
		*Buff++=Pn8(Data[i],!Dat_Endian);}
	//	计算CRC
	crc=mb_crc(obj->TxBuff,Byte+7);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,Byte+9);
	return 0;
}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_WR_COILS_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,u8* Data){
	u8 Byte=ceil_div(Mem,8);
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=ID;
	*Buff++=MB_FUNC_WR_COILS;
	*Buff++=Pn8(Addr,Dat_Endian);
	*Buff++=Pn8(Addr,!Dat_Endian);
	*Buff++=Pn8(Mem,Dat_Endian);
	*Buff++=Pn8(Mem,!Dat_Endian);
	*Buff++=Byte;
	u8* ByteHead=Buff;
	//	数据导入
	for(u32 i=0;i<Mem;i++){
		if(i%8==0)Buff++;
		MODBUS_SET_BIT(ByteHead,i,Data[i]);}
	//	计算CRC
	crc=mb_crc(obj->TxBuff,Byte+7);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,Byte+9);
	return 0;
}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_WR_REGS_Var_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,...){
	va_list list;
	va_start(list,Mem);
	
	u8 Byte=Mem*2;
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=ID;
	*Buff++=MB_FUNC_WR_REGS;
	*Buff++=Pn8(Addr,Dat_Endian);
	*Buff++=Pn8(Addr,!Dat_Endian);
	*Buff++=Pn8(Mem,Dat_Endian);
	*Buff++=Pn8(Mem,!Dat_Endian);
	*Buff++=Byte;
	//	数据导入
	u16 Data=0;
	for(u32 i=0;i<Mem;i++){
		Data=va_arg(list,u16);
		*Buff++=Pn8(Data,Dat_Endian);
		*Buff++=Pn8(Data,!Dat_Endian);}
	//	计算CRC
	crc=mb_crc(obj->TxBuff,Byte+7);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,Byte+9);
	
	va_end(list);
	return 0;
}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_WR_COILS_Var_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,...){
	va_list list;
	va_start(list,Mem);
	
	u8 Byte=ceil_div(Mem,8);
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=ID;
	*Buff++=MB_FUNC_WR_COILS;
	*Buff++=Pn8(Addr,Dat_Endian);
	*Buff++=Pn8(Addr,!Dat_Endian);
	*Buff++=Pn8(Mem,Dat_Endian);
	*Buff++=Pn8(Mem,!Dat_Endian);
	*Buff++=Byte;
	u8* ByteHead=Buff;
	//	数据导入
	u8 Data=0;
	for(u32 i=0;i<Mem;i++){
		Data=va_arg(list,u8);
		if(i%8==0)Buff++;
		MODBUS_SET_BIT(ByteHead,i,Data);}
	//	计算CRC
	crc=mb_crc(obj->TxBuff,Byte+7);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,Byte+9);
		
	va_end(list);
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_Unpack(_mb_master obj,u8* Buff,u32 len){
	if(len<=2)return 1;
	//	CRC断言
	#ifdef CRC_CHECK
	u16 crc=mb_crc(Buff,len-2);
	if(Pn8(crc,CRC_Endian)!=Buff[len-2] || Pn8(crc,!CRC_Endian)!=Buff[len-1])return 1;
	#endif
	//	通过测试-导入功能码
	obj->RxID=Buff[0];
	obj->RxFunc=Buff[1];
	
	u8* BuffHead=Buff+2;
	//	根据功能码分流
	switch(obj->RxFunc){
		case MB_FUNC_RD_OUT_COIL:
			obj->RxByte=*BuffHead++;
			if(obj->RxCoilMaxLen<obj->Mem)return 1;
			for(u32 i=0;i<obj->Mem;i++)
				obj->RxCoilBuff[i]=MODBUS_GET_BIT(BuffHead,i);
			break;
		case MB_FUNC_RD_IN_COIL:
			obj->RxByte=*BuffHead++;
			if(obj->RxCoilMaxLen<obj->Mem)return 1;
			for(u32 i=0;i<obj->Mem;i++)
				obj->RxCoilBuff[i]=MODBUS_GET_BIT(BuffHead,i);
			break;
		case MB_FUNC_RD_HOLD_REG:
			obj->RxByte=*BuffHead++;
			if(obj->RxRegMaxLen<obj->Mem)return 1;
			for(u32 i=0;i<obj->Mem;i++){
				Pn8(obj->RxRegBuff[i],Dat_Endian)=*BuffHead++;
				Pn8(obj->RxRegBuff[i],!Dat_Endian)=*BuffHead++;}
			break;
		case MB_FUNC_RD_IN_REG:
			obj->RxByte=*BuffHead++;
			if(obj->RxRegMaxLen<obj->Mem)return 1;
			for(u32 i=0;i<obj->Mem;i++){
				Pn8(obj->RxRegBuff[i],Dat_Endian)=*BuffHead++;
				Pn8(obj->RxRegBuff[i],!Dat_Endian)=*BuffHead++;}
			break;
	}
	//	分流
	if(obj->RxID!=obj->TxID)return 2;
	if(obj->RxFunc!=obj->TxFunc)return 2;
	
	if(obj->RxFunc == MB_FUNC_RD_OUT_COIL || obj->RxFunc == MB_FUNC_RD_IN_COIL){
		for(u32 i=0;i<obj->VarNum;i++)
			*((u8*)(obj->VarBuff[i]))=obj->RxCoilBuff[i];
		}
	
	if(obj->RxFunc == MB_FUNC_RD_HOLD_REG || obj->RxFunc == MB_FUNC_RD_IN_REG){
		for(u32 i=0;i<obj->VarNum;i++)
			*((u16*)(obj->VarBuff[i]))=obj->RxRegBuff[i];
		}
	return 0;
	}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_Lencount(u8* Buff){
	u32 result=0;
	switch(Buff[1]){
		case MB_FUNC_RD_OUT_COIL:return 5+Buff[2];break;
		case MB_FUNC_RD_IN_COIL:return 5+Buff[2];break;
		case MB_FUNC_RD_HOLD_REG:return 5+Buff[2];break;
		case MB_FUNC_RD_IN_REG:return 5+Buff[2];break;
		
		case MB_FUNC_WR_COIL:return 8;break;
		case MB_FUNC_WR_REG:return 8;break;
		case MB_FUNC_WR_COILS:return 8;break;
		case MB_FUNC_WR_REGS:return 8;break;
		default:break;}
	return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_RD_OUT_COIL_Var_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,...){
	va_list list;
	va_start(list,Mem);
	for(u32 i=0;i<Mem;i++)obj->VarBuff[i]=(void*)va_arg(list,void*);
	obj->VarNum=Mem;
	va_end(list);
	mb_Master_RD_OUT_COIL_Ask(obj,ID,Addr,Mem);
	return 0;}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_RD_IN_COIL_Var_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,...){
	va_list list;
	va_start(list,Mem);
	for(u32 i=0;i<Mem;i++)obj->VarBuff[i]=(void*)va_arg(list,void*);
	obj->VarNum=Mem;
	va_end(list);
	mb_Master_RD_IN_COIL_Ask(obj,ID,Addr,Mem);
	return 0;}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_RD_HOLD_REG_Var_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,...){
	va_list list;
	va_start(list,Mem);
	for(u32 i=0;i<Mem;i++)obj->VarBuff[i]=(void*)va_arg(list,void*);
	obj->VarNum=Mem;
	va_end(list);
	mb_Master_RD_HOLD_REG_Ask(obj,ID,Addr,Mem);
	return 0;}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_RD_IN_REG_Var_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,...){
	va_list list;
	va_start(list,Mem);
	for(u32 i=0;i<Mem;i++)obj->VarBuff[i]=(void*)va_arg(list,void*);
	obj->VarNum=Mem;
	va_end(list);
	mb_Master_RD_IN_REG_Ask(obj,ID,Addr,Mem);
	return 0;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_RD_OUT_COILS_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,u8* Data){
	for(u32 i=0;i<Mem;i++)obj->VarBuff[i]=(void*)(Data+i);
	obj->VarNum=Mem;
	mb_Master_RD_OUT_COIL_Ask(obj,ID,Addr,Mem);
	return 0;}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_RD_IN_COILS_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,u8* Data){
	for(u32 i=0;i<Mem;i++)obj->VarBuff[i]=(void*)(Data+i);
	obj->VarNum=Mem;
	mb_Master_RD_IN_COIL_Ask(obj,ID,Addr,Mem);
	return 0;}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_RD_HOLD_REGS_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,u16* Data){
	for(u32 i=0;i<Mem;i++)obj->VarBuff[i]=(void*)(Data+i);
	obj->VarNum=Mem;
	mb_Master_RD_HOLD_REG_Ask(obj,ID,Addr,Mem);
	return 0;}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Master_RD_IN_REGS_Ask(_mb_master obj,u8 ID,u16 Addr,u16 Mem,u16* Data){
	for(u32 i=0;i<Mem;i++)obj->VarBuff[i]=(void*)(Data+i);
	obj->VarNum=Mem;
	mb_Master_RD_IN_REG_Ask(obj,ID,Addr,Mem);
	return 0;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
