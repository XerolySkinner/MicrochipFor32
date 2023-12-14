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
  * @file		bsp_W25Q.cpp
  * @brief		储存芯片
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Mon Oct  9 08:32:28 2023

  */
#include "bsp_W25Q.h"
u8 W25Q_ReadByte(void){
	u8 res=0;
	HAL_SPI_Receive(&hspi3,&res,1,0xFF);
	return res;}

void W25Q_WriteByte(u8 val){
	HAL_SPI_Transmit(&hspi3,&val,1,0xFF);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
void W25QXX_Delay(void){
	u8 i=0;
	while(--i);}

//4Kbytes为一个Sector
//16个扇区为1个Block
//W25Q128
//容量为16M字节,共有128个Block,4096个Sector 
u16 W25QXX_TYPE;	//默认是W25Q128

void W25QXX_Init(void){
	W25QXX_TYPE = W25QXX_ReadID(); //读取FLASH ID.
}

//读取芯片ID
//返回值如下:				   
//0XEF13,表示芯片型号为W25Q80  
//0XEF14,表示芯片型号为W25Q16    
//0XEF15,表示芯片型号为W25Q32  
//0XEF16,表示芯片型号为W25Q64 
//0XEF17,表示芯片型号为W25Q128
u16  W25QXX_ReadID(void)  	    		//读取FLASH ID
{
	u16 temp = 0;
	W25QXX_CS_L;
	
	W25Q_WriteByte(0x90);
	W25Q_WriteByte(0x00);
	W25Q_WriteByte(0x00);
	W25Q_WriteByte(0x00);
	temp |= W25Q_ReadByte() << 8;
	temp |= W25Q_ReadByte();
	W25QXX_CS_H;
	return temp;
}

//读取W25QXX的状态寄存器
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
u8	 W25QXX_ReadSR(void)        		//读取状态寄存器 
{
	u8 type = 0;
	W25QXX_CS_L; //使能器件  
	W25Q_WriteByte(W25X_ReadStatusReg); //发送读取状态寄存器命令
	type = W25Q_ReadByte(); //读取一个字节
	W25QXX_CS_H; //取消片选
	return type;
}

//写W25QXX状态寄存器
//只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
void W25QXX_Write_SR(u8 sr)  			//写状态寄存器
{
	W25QXX_CS_L;
	W25Q_WriteByte(W25X_WriteStatusReg);
	W25Q_WriteByte(sr);
	W25QXX_CS_H;
}

//W25QXX写使能	
//将WEL置位 
void W25QXX_Write_Enable(void)  		//写使能 
{
	W25QXX_CS_L;
	W25Q_WriteByte(W25X_WriteEnable);
	W25QXX_CS_H;
}

//W25QXX写禁止	
//将WEL清零 
void W25QXX_Write_Disable(void)		//写保护
{
	W25QXX_CS_L;
	W25Q_WriteByte(W25X_WriteDisable);
	W25QXX_CS_H;
}

//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!
void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
	u16 i;
	W25QXX_Write_Enable();
	W25QXX_CS_L;
	W25Q_WriteByte(W25X_PageProgram); //发送写页命令
	W25Q_WriteByte((u8)(WriteAddr >> 16)); //发送24bit地址
	W25Q_WriteByte((u8)(WriteAddr >> 8));
	W25Q_WriteByte((u8)(WriteAddr));
	
	for(i=0;i<NumByteToWrite;i++)
		W25Q_WriteByte(pBuffer[i]);
	W25QXX_CS_H;
	W25QXX_Wait_Busy();
}

//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
	u16 pageremain;
	pageremain = 256 - WriteAddr%256; //单页剩余的字节数
	if(NumByteToWrite <= pageremain)
	{ //不大于256个字节
		pageremain = NumByteToWrite;
	}
	while(1)
	{
		W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite == pageremain)
		{ //写入结束了
			break;
		}
		else
		{
			pBuffer += pageremain;
			WriteAddr += pageremain;
			
			NumByteToWrite -= pageremain; //减去已经写入了的字节数
			if(NumByteToWrite > 256)
			{ //一次可以写入256个字节
				pageremain = 256;
			}
			else
			{
				pageremain = NumByteToWrite; //不够256个字节了
			}
		}
	}
}

//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   //读取flash
{
	u16 i;
	W25QXX_CS_L;
	W25Q_WriteByte(W25X_ReadData); //发送读指令
	W25Q_WriteByte((u8)(ReadAddr >> 16));	//发送24bit地址
	W25Q_WriteByte((u8)(ReadAddr >> 8));
	W25Q_WriteByte((u8)(ReadAddr));
	
	for(i=0;i<NumByteToRead;i++)
	{
		pBuffer[i] = W25Q_ReadByte(); // 读取数据
	}
	W25QXX_CS_H;
}

//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)						
//NumByteToWrite:要写入的字节数(最大65535) 
u8 W25QXX_BUFFER[4096];
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)//写入flash
{
	u32 secpos;
	u16 secoff;
	u16 secremain;
	u16 i;
	u8 * W25QXX_BUF;
	W25QXX_BUF = W25QXX_BUFFER;
	secpos = WriteAddr / 4096; //扇区地址 
	secoff = WriteAddr % 4096; //在扇区内的偏移
	secremain = 4096 - secoff; //扇区剩余空间大小
	if(NumByteToWrite <= secremain)
	{ //不大于4096个字节
		secremain = NumByteToWrite;
	}
	while(1)
	{
		W25QXX_Read(W25QXX_BUF,secpos*4096,4096); //读出整个扇区的内容
		for(i=0;i<secremain;i++)
		{ //校验数据
			if(W25QXX_BUF[secoff+i] != 0xFF)
			{ //需要擦除 
				break;
			}
		}
		if(i<secremain)
		{ //需要擦除
			W25QXX_Erase_Sector(secpos); //擦除这个扇区
			for(i=0;i<secremain;i++)
			{ //复制
				W25QXX_BUF[i+secoff] = pBuffer[i];
			}
			W25QXX_Write_NoCheck(W25QXX_BUF,secpos*4096,4096); //写入整个扇区
		}
		else
		{	
			W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain); //写已经擦除了的,直接写入扇区剩余区间. 
		}
		
		if(NumByteToWrite == secremain)
		{ //写入结束了
			break;
		}
		else
		{ //写入未结束
			secpos++; //扇区地址增1
			secoff = 0; //偏移位置为0
			pBuffer += secremain; //指针偏移
			WriteAddr += secremain; //写地址偏移	
			NumByteToWrite -= secremain; //字节数递减
			if(NumByteToWrite>4096)
			{ //下一个扇区还是写不完
				secremain = 4096;
			}
			else
			{ //下一个扇区可以写完了
				secremain = NumByteToWrite;
			}
		}		
	}
}

//擦除整个芯片		  
//等待时间超长...
void W25QXX_Erase_Chip(void)    	  	//整片擦除
{
	W25QXX_Write_Enable(); //SET WEL
	W25QXX_Wait_Busy();
	
	W25QXX_CS_L; //使能器件
	W25Q_WriteByte(W25X_ChipErase); //发送片擦除命令 
	W25QXX_CS_H; //取消片选
	
	W25QXX_Wait_Busy(); //等待芯片擦除结束
}

//擦除一个扇区
//Dst_Addr:扇区地址 根据实际容量设置
//擦除一个扇区的最少时间:150ms
void W25QXX_Erase_Sector(u32 Dst_Addr)	//扇区擦除
{
	Dst_Addr *= 4096;
	W25QXX_Write_Enable(); //SET WEL 
	W25QXX_Wait_Busy();
	W25QXX_CS_L;
	W25Q_WriteByte(W25X_SectorErase); //发送扇区擦除指令
	W25Q_WriteByte((u8)(Dst_Addr >> 16)); //发送24bit地址
	W25Q_WriteByte((u8)(Dst_Addr >> 8));
	W25Q_WriteByte((u8)Dst_Addr);
	W25QXX_CS_H; //取消片选
	W25QXX_Wait_Busy(); //等待擦除完成
}

void W25QXX_Wait_Busy(void)           	//等待空闲
{
	while(W25QXX_ReadSR() & 0x01);
}
void W25QXX_PowerDown(void)        	//进入掉电模式
{
	W25QXX_CS_L;
	W25Q_WriteByte(W25X_PowerDown);
	W25QXX_CS_H;
	W25QXX_Delay();
}
void W25QXX_WAKEUP(void)				//唤醒
{
	W25QXX_CS_L;
	W25Q_WriteByte(W25X_ReleasePowerDown);
	W25QXX_CS_H;
	W25QXX_Delay();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
