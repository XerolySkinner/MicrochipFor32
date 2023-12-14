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
  * @file		mbs_ModBusRTU.c
  * @brief		从机ModBusRTU
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Thu Sep 21 17:08:59 2023

  */
#include "mbs_ModBusRTU.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	函数
/**
 * @brief			mb_Slave_create
 * @param	var 	vars
 * @return			_mb_slave
 */
_mb_slave mb_Slave_create(const char* str,...){
	va_list list;
	va_start(list, str);
	char field[10] = {0};
	//	分配内存区
	_mb_slave result=(_mb_struct_slave*)mb_malloc(sizeof(_mb_struct_slave));
	if(result==NULL)return NULL;
	//	初始化区
	result->mask=0x00;
	result->mask_id=0x00;
	//	指令集判定
	while (sscanf(str, "-%[^-]", field) == 1){
		if (!strcmp(field, "transmit")) {
			result->tramsmit=va_arg(list,mb_transmit);}
		if (!strcmp(field, "ID")) {
			result->ID=va_arg(list,u32);}
		if (!strcmp(field, "mask")) {
			u32 mask=va_arg(list,u32);
			result->mask=mask;}
		if (!strcmp(field, "mask_id")) {
			u32 mask_id=va_arg(list,u32);
			result->mask_id=mask_id;}
		if (!strcmp(field, "TxBuffSize")) {
			result->TxMaxLen=va_arg(list,u32);
			result->TxBuff=(u8*)mb_malloc(result->TxMaxLen);
			if(result->TxBuff==NULL){
				free(result);
				return NULL;}}
		if (!strcmp(field, "RxBuffSize")) {
			result->RxMaxLen=va_arg(list,u32);
			result->RxBuff=(u8*)mb_malloc(result->RxMaxLen);
			if(result->RxBuff==NULL){
				free(result);
				return NULL;}}
		
		if (!strcmp(field, "InCoil")) {
			result->InCoilPoolSize=va_arg(list,u32);
			result->InCoilPool=(u8*)mb_malloc(result->InCoilPoolSize);
			if(result->InCoilPool==NULL){
				free(result);
				return NULL;}}
		if (!strcmp(field, "OutCoil")) {
			result->OutCoilPoolSize=va_arg(list,u32);
			result->OutCoilPool=(u8*)mb_malloc(result->OutCoilPoolSize);
			if(result->OutCoilPool==NULL){
				free(result);
				return NULL;}}
		if (!strcmp(field, "InRegPool")) {
			result->InRegPoolSize=va_arg(list,u32);
			result->InRegPool=(u16*)mb_malloc(result->InRegPoolSize);
			if(result->InRegPool==NULL){
				free(result);
				return NULL;}}
		if (!strcmp(field, "HoldRegPool")) {
			result->HoldRegPoolSize=va_arg(list,u32);
			result->HoldRegPool=(u16*)mb_malloc(result->HoldRegPoolSize);
			if(result->HoldRegPool==NULL){
				free(result);
				return NULL;}}
				
		str += (strlen(field) + 1);
	}
	va_end(list);
	return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Slave_WR_COIL_Ack(_mb_slave obj,u16 Addr,u16 Data){
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=obj->ID;
	*Buff++=MB_FUNC_WR_COIL;
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
u8 mb_Slave_WR_REG_Ack(_mb_slave obj,u16 Addr,u16 Data){
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=obj->ID;
	*Buff++=MB_FUNC_WR_REG;
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
u8 mb_Slave_WR_REGS_Ack(_mb_slave obj,u16 Addr,u16 Mem){
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=obj->ID;
	*Buff++=MB_FUNC_WR_REGS;
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
u8 mb_Slave_WR_COILS_Ack(_mb_slave obj,u16 Addr,u16 Mem){
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=obj->ID;
	*Buff++=MB_FUNC_WR_COILS;
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
u8 mb_Slave_RD_OUT_COIL_Ack(_mb_slave obj,u16 Mem,u8* Data){
	u8 Byte=ceil_div(Mem,8);
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=obj->ID;
	*Buff++=MB_FUNC_RD_OUT_COIL;
	*Buff++=Byte;
	u8* ByteHead=Buff;
	//	数据导入
	for(u8 i=0;i<Mem;i++){
		if(i%8==0)Buff++;
		MODBUS_SET_BIT(ByteHead,i,Data[i]);}
	//	计算CRC
	crc=mb_crc(obj->TxBuff,3+Byte);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,5+Byte);
	return 0;
}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Slave_RD_IN_COIL_Ack(_mb_slave obj,u16 Mem,u8* Data){
	u8 Byte=ceil_div(Mem,8);
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=obj->ID;
	*Buff++=MB_FUNC_RD_IN_COIL;
	*Buff++=Byte;
	u8* ByteHead=Buff;
	//	数据导入
	for(u8 i=0;i<Mem;i++){
		if(i%8==0)Buff++;
		MODBUS_SET_BIT(ByteHead,i,Data[i]);}
	//	计算CRC
	crc=mb_crc(obj->TxBuff,3+Byte);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,5+Byte);
	return 0;
}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Slave_RD_HOLD_REG_Ack(_mb_slave obj,u8 Mem,u16* Data){
	u8 Byte=Mem*2;
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=obj->ID;
	*Buff++=MB_FUNC_RD_HOLD_REG;
	*Buff++=Byte;
	//	数据导入
	for(u8 i=0;i<Mem;i++){
		*Buff++=Pn8(Data[i],Dat_Endian);
		*Buff++=Pn8(Data[i],!Dat_Endian);}
	//	计算CRC
	crc=mb_crc(obj->TxBuff,3+Byte);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,5+Byte);
	return 0;
}
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Slave_RD_IN_REG_Ack(_mb_slave obj,u8 Mem,u16* Data){
	u8 Byte=Mem*2;
	u8* Buff=obj->TxBuff;
	u16 crc;
	//	填入顺序项
	*Buff++=obj->ID;
	*Buff++=MB_FUNC_RD_IN_REG;
	*Buff++=Byte;
	//	数据导入
	for(u8 i=0;i<Mem;i++){
		*Buff++=Pn8(Data[i],Dat_Endian);
		*Buff++=Pn8(Data[i],!Dat_Endian);}
	//	计算CRC
	crc=mb_crc(obj->TxBuff,3+Byte);
	*Buff++=Pn8(crc,CRC_Endian);
	*Buff++=Pn8(crc,!CRC_Endian);
	//	发送值
	obj->tramsmit(obj->TxBuff,5+Byte);
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	向外发送
u8 mb_Slave_Unpack(_mb_slave obj,u8* Buff,u32 len){
	if(len<=2)return 1;
	//	CRC断言
	#ifdef CRC_CHECK
	u16 crc=mb_crc(Buff,len-2);
	if(Pn8(crc,CRC_Endian)!=Buff[len-2] || Pn8(crc,!CRC_Endian)!=Buff[len-1])return 1;
	#endif
	//	导入功能码
	obj->Func=Buff[1];
	u8* BuffHead=Buff+2;
	
	//	ID检定
	if(	obj->Func == MB_FUNC_RD_OUT_COIL		||
		obj->Func == MB_FUNC_RD_IN_COIL 		||
		obj->Func == MB_FUNC_RD_HOLD_REG		||
		obj->Func == MB_FUNC_RD_IN_REG){if(Buff[0]!=obj->ID)return 2;}
	else{
		if(	Buff[0]!=obj->ID && Buff[0]!=0x00)return 2;}
	//	根据功能码分流
	if(	obj->Func == MB_FUNC_RD_OUT_COIL	||
		obj->Func ==MB_FUNC_RD_IN_COIL 		||
		obj->Func ==MB_FUNC_RD_HOLD_REG		||
		obj->Func ==MB_FUNC_RD_IN_REG){
			Pn8(obj->Addr,Dat_Endian)=*BuffHead++;
			Pn8(obj->Addr,!Dat_Endian)=*BuffHead++;
			Pn8(obj->Mem,Dat_Endian)=*BuffHead++;
			Pn8(obj->Mem,!Dat_Endian)=*BuffHead++;
		}
	if(	obj->Func == MB_FUNC_WR_COIL	||
		obj->Func ==MB_FUNC_WR_REG){
			Pn8(obj->Addr,Dat_Endian)=*BuffHead++;
			Pn8(obj->Addr,!Dat_Endian)=*BuffHead++;
			Pn8(obj->Data,Dat_Endian)=*BuffHead++;
			Pn8(obj->Data,!Dat_Endian)=*BuffHead++;
		}
	if(	obj->Func == MB_FUNC_WR_COILS	||
		obj->Func ==MB_FUNC_WR_REGS){
			Pn8(obj->Addr,Dat_Endian)=*BuffHead++;
			Pn8(obj->Addr,!Dat_Endian)=*BuffHead++;
			Pn8(obj->Mem,Dat_Endian)=*BuffHead++;
			Pn8(obj->Mem,!Dat_Endian)=*BuffHead++;
			obj->Byte=*BuffHead++;
			for(u32 i=0;i<obj->Byte;i++)obj->RxBuff[i]=*BuffHead++;
		}
	//	填入数据池
	mb_Slave_Pool(obj);
	//	回复信息	
	if(Buff[0]==obj->ID)mb_Slave_Ack(obj);
	return 0;
	}
//----------------------------------------------------------------------------------------------------
u8 mb_Slave_Lencount(u8* Buff){
	u32 result=0;
	switch(Buff[1]){
		case MB_FUNC_RD_OUT_COIL:return 8;break;
		case MB_FUNC_RD_IN_COIL:return 8;break;
		case MB_FUNC_RD_HOLD_REG:return 8;break;
		case MB_FUNC_RD_IN_REG:return 8;break;
		
		case MB_FUNC_WR_COIL:return 8;break;
		case MB_FUNC_WR_REG:return 8;break;
		case MB_FUNC_WR_COILS:return 9+Buff[6];break;
		case MB_FUNC_WR_REGS:return 9+Buff[6];break;
		default:break;}
	return result;
}
//----------------------------------------------------------------------------------------------------
u8 mb_Slave_Pool(_mb_slave obj){
	switch(obj->Func){
		case MB_FUNC_WR_COIL:
			obj->OutCoilPool[obj->Addr]=!!obj->Data;break;
		case MB_FUNC_WR_REG:
			obj->HoldRegPool[obj->Addr]=obj->Data;break;
		case MB_FUNC_WR_COILS:
			for(u32 i=0;i<obj->Mem;i++)
				obj->OutCoilPool[obj->Addr+i]=MODBUS_GET_BIT(obj->RxBuff,i);
			break;
		case MB_FUNC_WR_REGS:
			for(u32 i=0;i<(obj->Byte)/2;i++){
				Pn8(obj->HoldRegPool[obj->Addr+i],Dat_Endian)=Pn8(Ln16(obj->RxBuff,i),0);
				Pn8(obj->HoldRegPool[obj->Addr+i],!Dat_Endian)=Pn8(Ln16(obj->RxBuff,i),1);}
			break;
		default:break;
		}
	return 0;
	}
//----------------------------------------------------------------------------------------------------
u8 mb_Slave_Ack(_mb_slave obj){
	switch(obj->Func){
		case MB_FUNC_RD_OUT_COIL:
			mb_Slave_RD_OUT_COIL_Ack(obj,obj->Mem,obj->OutCoilPool+obj->Addr);
			break;
		case MB_FUNC_RD_IN_COIL:
			mb_Slave_RD_IN_COIL_Ack(obj,obj->Mem,obj->InCoilPool+obj->Addr);
			break;
		case MB_FUNC_RD_HOLD_REG:
			mb_Slave_RD_HOLD_REG_Ack(obj,obj->Mem,obj->HoldRegPool+obj->Addr);
			break;
		case MB_FUNC_RD_IN_REG:
			mb_Slave_RD_IN_REG_Ack(obj,obj->Mem,obj->InRegPool+obj->Addr);
			break;
#ifdef ModBus_ACK
		case MB_FUNC_WR_COIL:
			mb_Slave_WR_COIL_Ack(obj,obj->Addr,obj->Data);break;
		case MB_FUNC_WR_REG:
			mb_Slave_WR_REG_Ack(obj,obj->Addr,obj->Data);break;
		case MB_FUNC_WR_COILS:
			mb_Slave_WR_COILS_Ack(obj,obj->Addr,obj->Mem);break;
		case MB_FUNC_WR_REGS:
			mb_Slave_WR_REGS_Ack(obj,obj->Addr,obj->Mem);break;
#endif
		default:break;
		}
	return 0;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
