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
  * @file		bsp_SD.cpp
  * @brief		操作SD卡的库
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-22 03:50
  */

#pragma once
#ifdef __cplusplus
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
//	
#include "spi.h"
#include "varint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	数据
//	
//----------------------------------------------------------------------------------------------------
//SD卡类型
#define ERR 					0x00
#define MMC 					0x01
#define V1						0x02
#define V2						0x04
#define V2HC					0x06
#define DUMMY_BYTE				0xFF 
#define MSD_BLOCKSIZE			512
//----------------------------------------------------------------------------------------------------
//CMD定义
#define CMD0					0					//卡复位
#define CMD1					1
#define CMD8					8					//命令8 ，SEND_IF_COND
#define CMD9					9					//命令9 ，读CSD数据
#define CMD10					10					//命令10，读CID数据
#define CMD12					12					//命令12，停止数据传输
#define CMD16					16					//命令16，设置SectorSize 应返回0x00
#define CMD17					17					//命令17，读sector
#define CMD18					18					//命令18，读Multi sector
#define CMD23					23					//命令23，设置多sector写入前预先擦除N个block
#define CMD24					24					//命令24，写sector
#define CMD25					25					//命令25，写Multi sector
#define CMD41					41					//命令41，应返回0x00
#define CMD55					55					//命令55，应返回0x01
#define CMD58					58					//命令58，读OCR信息
#define CMD59					59					//命令59，使能/禁止CRC，应返回0x00
//----------------------------------------------------------------------------------------------------
//数据写入回应字意义
#define MSD_DATA_OK 			0x05
#define MSD_DATA_CRC_ERROR		0x0B
#define MSD_DATA_WRITE_ERROR	0x0D
#define MSD_DATA_OTHER_ERROR	0xFF
//SD卡回应标记字
#define MSD_RESPONSE_NO_ERROR	0x00
#define MSD_IN_IDLE_STATE		0x01
#define MSD_ERASE_RESET 		0x02
#define MSD_ILLEGAL_COMMAND 	0x04
#define MSD_COM_CRC_ERROR		0x08
#define MSD_ERASE_SEQUENCE_ERROR 0x10
#define MSD_ADDRESS_ERROR		0x20
#define MSD_PARAMETER_ERROR 	0x40
#define MSD_RESPONSE_FAILURE	0xFF
//----------------------------------------------------------------------------------------------------
enum _CD_HOLD {
	HOLD = 0, 
	RELEASE = 1, 
	};
//----------------------------------------------------------------------------------------------------
typedef struct {									/* Card Specific Data */
	u8 				CSDStruct;						/* CSD structure */
	u8 				SysSpecVersion; 				/* System specification version */
	u8 				Reserved1;						/* Reserved */
	u8 				TAAC;							/* Data read access-time 1 */
	u8 				NSAC;							/* Data read access-time 2 in CLK cycles */
	u8 				MaxBusClkFrec;					/* Max. bus clock frequency */
	u16				CardComdClasses;				/* Card command classes */
	u8 				RdBlockLen; 					/* Max. read data block length */
	u8 				PartBlockRead;					/* Partial blocks for read allowed */
	u8 				WrBlockMisalign;				/* Write block misalignment */
	u8 				RdBlockMisalign;				/* Read block misalignment */
	u8 				DSRImpl;						/* DSR implemented */
	u8 				Reserved2;						/* Reserved */
	u32				DeviceSize; 					/* Device Size */
	u8 				MaxRdCurrentVDDMin; 			/* Max. read current @ VDD min */
	u8 				MaxRdCurrentVDDMax; 			/* Max. read current @ VDD max */
	u8 				MaxWrCurrentVDDMin; 			/* Max. write current @ VDD min */
	u8 				MaxWrCurrentVDDMax; 			/* Max. write current @ VDD max */
	u8 				DeviceSizeMul;					/* Device size multiplier */
	u8 				EraseGrSize;					/* Erase group size */
	u8 				EraseGrMul; 					/* Erase group size multiplier */
	u8 				WrProtectGrSize;				/* Write protect group size */
	u8 				WrProtectGrEnable;				/* Write protect group enable */
	u8 				ManDeflECC; 					/* Manufacturer default ECC */
	u8 				WrSpeedFact;					/* Write speed factor */
	u8 				MaxWrBlockLen;					/* Max. write data block length */
	u8 				WriteBlockPaPartial;			/* Partial blocks for write allowed */
	u8 				Reserved3;						/* Reserded */
	u8 				ContentProtectAppli;			/* Content protection application */
	u8 				FileFormatGrouop;				/* File format group */
	u8 				CopyFlag;						/* Copy flag (OTP) */
	u8 				PermWrProtect;					/* Permanent write protection */
	u8 				TempWrProtect;					/* Temporary write protection */
	u8 				FileFormat; 					/* File Format */
	u8 				ECC;							/* ECC code */
	u8 				CSD_CRC;						/* CSD CRC */
	u8 				Reserved4;						/* always 1*/
} MSD_CSD;

//----------------------------------------------------------------------------------------------------
typedef struct {									/*Card Identification Data*/
	u8				ManufacturerID; 				/* ManufacturerID */
	u16				OEM_AppliID;					/* OEM/Application ID */
	u32				ProdName1;						/* Product Name part1 */
	u8				ProdName2;						/* Product Name part2*/
	u8				ProdRev;						/* Product Revision */
	u32				ProdSN; 						/* Product Serial Number */
	u8				Reserved1;						/* Reserved1 */
	u16				ManufactDate;					/* Manufacturing Date */
	u8				CID_CRC;						/* CID CRC */
	u8				Reserved2;						/* always 1 */
} MSD_CID;
//----------------------------------------------------------------------------------------------------
typedef struct {
	MSD_CSD			CSD;
	MSD_CID			CID;
	u32				Capacity;						/* Card Capacity */
	u32				BlockSize;						/* Card Block Size */
	u16				RCA;
	u8				CardType;
	u32				SpaceTotal;						/* Total space size in file system */
	u32				SpaceFree;
} /* Free space size in file system */
//----------------------------------------------------------------------------------------------------
MSD_CARDINFO, *PMSD_CARDINFO;
extern MSD_CARDINFO SD0_CardInfo;
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
//	
/**
 * @brief			一个操作SD卡的类
 */
class bsp_SD{
	public:
		bsp_SD(SPI_HandleTypeDef *hspi,GPIO_TypeDef *GPIOx_CS,uint16_t GPIO_Pin_CS);
	public:
		u8					SD_init(void);
		u8					SD_ReadDisk(u8 * buf, u32 sector, u8 cnt);
		u8					SD_WriteDisk(u8 * buf, u32 sector, u8 cnt);
		u32					SD_GetSectorCount(void);
		u8 					offsetWrite(u64 offset,u8* dat,u64 datlen);
		u8 					offsetRead(u64 offset,u8* dat,u64 datlen);
	private:
		SPI_HandleTypeDef	*hspi;
		GPIO_TypeDef		*GPIOx_CS;
		uint16_t			GPIO_Pin_CS;

		u8					DFF;
		u8					SD_TYPE;
		MSD_CARDINFO		SD0_CardInfo;
		
		void				SD_CS(u8 p);
		u8					SD_GETCID(u8 * cid_data);
		u8					SD_GETCSD(u8 * csd_data);
		int					MSD0_GetCardInfo(PMSD_CARDINFO SD0_CardInfo);
		u8					SD_ReceiveData(u8 * data, u16 len);
		u8					SD_SendBlock(u8 * buf, u8 cmd);
		u32					SD_sendcmd(u8 cmd, u32 arg, u8 crc);

		void				SPI_setspeed(u8 speed);
		u8					spi_readwrite(u8 Txdata);
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

