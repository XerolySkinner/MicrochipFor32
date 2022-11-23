/*----------------------------------------------------------------------------------------------------
 #
 #	Copyright (c) 2022 Yuankang Liang(XerolySkinner)
 #
 #	�������ԭ���ṩ,���κ���ʾ��ʾ
 #	���κ������,���߶����е��κ����⳥����
 #
 #	ʹ�õ��������:
 #	1.	�����������������Դ,�㲻���������д��ԭʼ���.
 #	2.	����������κ�Ŀ��,ǰ���ǰ�Ȩ�������������и�����.
 #		���Ұ�Ȩ�������������ͬʱ����.
 #	3.	����ʹ��,����,�޸�,�ַ�,�����۱���������.
 #	4.	������ڲ�Ʒ��ʹ��,��Ʒ�ĵ��е����������͵ĵ����Ǳ����.
 #	5.	��֪ͨ���ô��κ���Դɾ�������.
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
  * @brief		����SD���Ŀ�
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-22 03:50
  */

#pragma once
#ifdef __cplusplus
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
//	
#include "spi.h"
#include "varint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	����
//	
//----------------------------------------------------------------------------------------------------
//SD������
#define ERR 					0x00
#define MMC 					0x01
#define V1						0x02
#define V2						0x04
#define V2HC					0x06
#define DUMMY_BYTE				0xFF 
#define MSD_BLOCKSIZE			512
//----------------------------------------------------------------------------------------------------
//CMD����
#define CMD0					0					//����λ
#define CMD1					1
#define CMD8					8					//����8 ��SEND_IF_COND
#define CMD9					9					//����9 ����CSD����
#define CMD10					10					//����10����CID����
#define CMD12					12					//����12��ֹͣ���ݴ���
#define CMD16					16					//����16������SectorSize Ӧ����0x00
#define CMD17					17					//����17����sector
#define CMD18					18					//����18����Multi sector
#define CMD23					23					//����23�����ö�sectorд��ǰԤ�Ȳ���N��block
#define CMD24					24					//����24��дsector
#define CMD25					25					//����25��дMulti sector
#define CMD41					41					//����41��Ӧ����0x00
#define CMD55					55					//����55��Ӧ����0x01
#define CMD58					58					//����58����OCR��Ϣ
#define CMD59					59					//����59��ʹ��/��ֹCRC��Ӧ����0x00
//----------------------------------------------------------------------------------------------------
//����д���Ӧ������
#define MSD_DATA_OK 			0x05
#define MSD_DATA_CRC_ERROR		0x0B
#define MSD_DATA_WRITE_ERROR	0x0D
#define MSD_DATA_OTHER_ERROR	0xFF
//SD����Ӧ�����
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
//	��Ŀ
//	
/**
 * @brief			һ������SD������
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

