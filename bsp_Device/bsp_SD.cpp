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

#include "bsp_SD.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	程序
//	
/**
 * @brief			片选信号
 * @return			无
 */
void bsp_SD::SD_CS(u8 p){
	HAL_GPIO_WritePin(GPIOx_CS, GPIO_Pin_CS, p == 0 ? GPIO_PIN_SET: GPIO_PIN_RESET);}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			写SD卡
 * @param	cmd		命令
 * @param	arg		
 * @param	crc		校验码
 * @return			
 */
u32 bsp_SD::SD_sendcmd(u8 cmd, u32 arg, u8 crc){
	u8 r1;
	u8 retry;
	SD_CS(0);
	__nop();
	SD_CS(1);
	do retry = spi_readwrite(DFF);while(retry != 0xFF);
	spi_readwrite(cmd | 0x40);
	spi_readwrite(arg >> 24);
	spi_readwrite(arg >> 16);
	spi_readwrite(arg >> 8);
	spi_readwrite(arg);
	spi_readwrite(crc);
	if (cmd == CMD12) spi_readwrite(DFF);
	do r1 = spi_readwrite(0xFF);while(r1 & 0X80);
	return r1;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			初始化SD卡
 * @return			返回值:0,ok;其他,失败.
 */
u8 bsp_SD::SD_init(void){
	u8 		r1;
	u8 		buff[6] = {0};
	u16		retry;
	u8		i;
	//	MX_SPI3_Init();
	SPI_setspeed(SPI_BAUDRATEPRESCALER_256);
	SD_CS(0);
	for (retry = 0; retry < 10; retry++) spi_readwrite(DFF);
	//	SD卡进入IDLE状态
	do r1 = SD_sendcmd(CMD0, 0, 0x95);while(r1 != 0x01);
	//	查看SD卡的类型
	SD_TYPE = 0;
	r1 = SD_sendcmd(CMD8, 0x1AA, 0x87);
	if (r1 == 0x01) {
		for (i = 0; i < 4; i++) buff[i] = spi_readwrite(DFF);					//Get trailing return value of R7 resp
		if (buff[2] == 0X01 && buff[3] == 0XAA) {								//卡是否支持2.7~3.6V
			retry = 0XFFFE;
			do {
				SD_sendcmd(CMD55, 0, 0X01);								 		//发送CMD55
				r1 = SD_sendcmd(CMD41, 0x40000000, 0X01);						//发送CMD41
				}while(r1 && retry--);
			if (retry && SD_sendcmd(CMD58, 0, 0X01) == 0) {						//鉴别SD2.0卡版本开始
				for (i = 0; i < 4; i++) buff[i] = spi_readwrite(0XFF);			//得到OCR值
				if (buff[0] &0x40) SD_TYPE = V2HC;
				else SD_TYPE = V2;}}
		else {
			SD_sendcmd(CMD55, 0, 0X01); 										//发送CMD55
			r1 = SD_sendcmd(CMD41, 0, 0X01); 									//发送CMD41
			if (r1 <= 1) {
				SD_TYPE = V1;
				retry = 0XFFFE;
				do {															//等待退出IDLE模式
					SD_sendcmd(CMD55, 0, 0X01);									//发送CMD55
					r1 = SD_sendcmd(CMD41, 0, 0X01);							//发送CMD41
					}while(r1 && retry--);}
			else {																	//MMC卡不支持CMD55+CMD41识别
				SD_TYPE = MMC;														//MMC V3
				retry = 0XFFFE;
				do r1 = SD_sendcmd(CMD1, 0, 0X01);while(r1 && retry--);}			//等待退出IDLE模式
			if (retry == 0 || SD_sendcmd(CMD16, 512, 0X01) != 0) SD_TYPE = ERR;}	//错误的卡
		}
	SD_CS(0);
	SPI_setspeed(SPI_BAUDRATEPRESCALER_2);
	if (SD_TYPE) return 0;
	else return 1;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			读取SD卡指定长度信息
 * @param	*data	数据缓存区
 * @param	len		长度
 * @return			返回值:0,ok;其他,失败.
 */
u8 bsp_SD::SD_ReceiveData(u8 * data, u16 len){
	u8 r1;
	SD_CS(1);
	do {
		r1 = spi_readwrite(0xFF);
		__nop();
		}while(r1 != 0xFE);
	while (len--) {
		*data = spi_readwrite(0xFF);
		data++;}
	spi_readwrite(0xFF);
	spi_readwrite(0xFF);
	return 0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			向SD卡写入一个扇区
 * @param	*buf	数据缓存区
 * @param	cmd		操作指令
 * @return			返回值:0,ok;其他,失败.
 */
u8 bsp_SD::SD_SendBlock(u8 * buf, u8 cmd){
	u16 t;
	u8 r1;
	do r1 = spi_readwrite(0xFF);while(r1 != 0xFF);
	spi_readwrite(cmd);
	if (cmd != 0XFD) {										//不是结束指令
		for (t = 0; t < 512; t++) spi_readwrite(buf[t]);	//提高速度,减少函数传参时间
		spi_readwrite(0xFF);								//忽略crc
		spi_readwrite(0xFF);
		t = spi_readwrite(0xFF);							//接收响应
		if ((t & 0x1F) != 0x05) return 2;}					//响应错误
	return 0;}												//写入成功
//----------------------------------------------------------------------------------------------------
/**
 * @brief			获取CID信息
 * @return			CID信息
 */
u8 bsp_SD::SD_GETCID(u8 * cid_data){
	u8 r1;
	r1 = SD_sendcmd(CMD10, 0, 0x01);						//读取CID寄存器
	if (r1 == 0x00) r1 = SD_ReceiveData(cid_data, 16);
	SD_CS(0);
	if (r1) return 1;
	else return 0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			获取CSD信息
 * @return			CSD信息
 */
u8 bsp_SD::SD_GETCSD(u8 * csd_data){
	u8 r1;
	r1 = SD_sendcmd(CMD9, 0, 0x01);							//发CMD9命令，读CSD寄存器
	if (r1 == 0) r1 = SD_ReceiveData(csd_data, 16);			//接收16个字节的数据 
	SD_CS(0);												//取消片选
	if (r1) return 1;
	else return 0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			获取SD卡的总扇区数 
 * @return			总扇区数
 */
u32 bsp_SD::SD_GetSectorCount(void){
	u8 		csd[16];
	u32		Capacity;
	u8 		n;
	u16		csize;
	//取CSD信息，如果期间出错，返回0
	if (SD_GETCSD(csd) != 0) return 0;
	//如果为SDHC卡，按照下面方式计算
	if ((csd[0] &0xC0) == 0x40) {							//V2.00的卡
		csize = csd[9] + ((u16) csd[8] << 8) + 1;
		Capacity = (u32)
		csize << 10;}										//得到扇区数
	else {													//V1.XX的卡
		n = (csd[5] &15) + ((csd[10] &128) >> 7) + ((csd[9] &3) << 1) + 2;
		csize = (csd[8] >> 6) + ((u16) csd[7] << 2) + ((u16) (csd[6] &3) << 10) + 1;
		Capacity = (u32)
		csize << (n - 9);}									//得到扇区数
	return Capacity;}
//----------------------------------------------------------------------------------------------------
int bsp_SD::MSD0_GetCardInfo(PMSD_CARDINFO SD0_CardInfo){
	u8 		r1;
	u8 		CSD_Tab[16];
	u8 		CID_Tab[16];
	/* Send CMD9, Read CSD */
	r1 = SD_sendcmd(CMD9, 0, 0xFF);
	if (r1 != 0x00) return r1;
	if (SD_ReceiveData(CSD_Tab, 16)) return 1;
	/* Send CMD10, Read CID */
	r1 = SD_sendcmd(CMD10, 0, 0xFF);
	if (r1 != 0x00) return r1;
	if (SD_ReceiveData(CID_Tab, 16)) return 2;
	/* Byte 0 */
	SD0_CardInfo->CSD.CSDStruct = (CSD_Tab[0] &0xC0) >> 6;
	SD0_CardInfo->CSD.SysSpecVersion = (CSD_Tab[0] &0x3C) >> 2;
	SD0_CardInfo->CSD.Reserved1 = CSD_Tab[0] &0x03;
	/* Byte 1 */
	SD0_CardInfo->CSD.TAAC = CSD_Tab[1];
	/* Byte 2 */
	SD0_CardInfo->CSD.NSAC = CSD_Tab[2];
	/* Byte 3 */
	SD0_CardInfo->CSD.MaxBusClkFrec = CSD_Tab[3];
	/* Byte 4 */
	SD0_CardInfo->CSD.CardComdClasses = CSD_Tab[4] << 4;
	/* Byte 5 */
	SD0_CardInfo->CSD.CardComdClasses |= (CSD_Tab[5] &0xF0) >> 4;
	SD0_CardInfo->CSD.RdBlockLen = CSD_Tab[5] &0x0F;
	/* Byte 6 */
	SD0_CardInfo->CSD.PartBlockRead = (CSD_Tab[6] &0x80) >> 7;
	SD0_CardInfo->CSD.WrBlockMisalign = (CSD_Tab[6] &0x40) >> 6;
	SD0_CardInfo->CSD.RdBlockMisalign = (CSD_Tab[6] &0x20) >> 5;
	SD0_CardInfo->CSD.DSRImpl = (CSD_Tab[6] &0x10) >> 4;
	SD0_CardInfo->CSD.Reserved2 = 0;				/* Reserved */
	SD0_CardInfo->CSD.DeviceSize = (CSD_Tab[6] &0x03) << 10;
	/* Byte 7 */
	SD0_CardInfo->CSD.DeviceSize |= (CSD_Tab[7]) << 2;
	/* Byte 8 */
	SD0_CardInfo->CSD.DeviceSize |= (CSD_Tab[8] &0xC0) >> 6;
	SD0_CardInfo->CSD.MaxRdCurrentVDDMin = (CSD_Tab[8] &0x38) >> 3;
	SD0_CardInfo->CSD.MaxRdCurrentVDDMax = (CSD_Tab[8] &0x07);
	/* Byte 9 */
	SD0_CardInfo->CSD.MaxWrCurrentVDDMin = (CSD_Tab[9] &0xE0) >> 5;
	SD0_CardInfo->CSD.MaxWrCurrentVDDMax = (CSD_Tab[9] &0x1C) >> 2;
	SD0_CardInfo->CSD.DeviceSizeMul = (CSD_Tab[9] &0x03) << 1;
	/* Byte 10 */
	SD0_CardInfo->CSD.DeviceSizeMul |= (CSD_Tab[10] &0x80) >> 7;
	SD0_CardInfo->CSD.EraseGrSize = (CSD_Tab[10] &0x7C) >> 2;
	SD0_CardInfo->CSD.EraseGrMul = (CSD_Tab[10] &0x03) << 3;
	/* Byte 11 */
	SD0_CardInfo->CSD.EraseGrMul |= (CSD_Tab[11] &0xE0) >> 5;
	SD0_CardInfo->CSD.WrProtectGrSize = (CSD_Tab[11] &0x1F);
	/* Byte 12 */
	SD0_CardInfo->CSD.WrProtectGrEnable = (CSD_Tab[12] &0x80) >> 7;
	SD0_CardInfo->CSD.ManDeflECC = (CSD_Tab[12] &0x60) >> 5;
	SD0_CardInfo->CSD.WrSpeedFact = (CSD_Tab[12] &0x1C) >> 2;
	SD0_CardInfo->CSD.MaxWrBlockLen = (CSD_Tab[12] &0x03) << 2;
	/* Byte 13 */
	SD0_CardInfo->CSD.MaxWrBlockLen |= (CSD_Tab[13] &0xc0) >> 6;
	SD0_CardInfo->CSD.WriteBlockPaPartial = (CSD_Tab[13] &0x20) >> 5;
	SD0_CardInfo->CSD.Reserved3 = 0;
	SD0_CardInfo->CSD.ContentProtectAppli = (CSD_Tab[13] &0x01);
	/* Byte 14 */
	SD0_CardInfo->CSD.FileFormatGrouop = (CSD_Tab[14] &0x80) >> 7;
	SD0_CardInfo->CSD.CopyFlag = (CSD_Tab[14] &0x40) >> 6;
	SD0_CardInfo->CSD.PermWrProtect = (CSD_Tab[14] &0x20) >> 5;
	SD0_CardInfo->CSD.TempWrProtect = (CSD_Tab[14] &0x10) >> 4;
	SD0_CardInfo->CSD.FileFormat = (CSD_Tab[14] &0x0C) >> 2;
	SD0_CardInfo->CSD.ECC = (CSD_Tab[14] &0x03);
	/* Byte 15 */
	SD0_CardInfo->CSD.CSD_CRC = (CSD_Tab[15] &0xFE) >> 1;
	SD0_CardInfo->CSD.Reserved4 = 1;
	if (SD0_CardInfo->CardType == V2HC) {
		/* Byte 7 */
		SD0_CardInfo->CSD.DeviceSize = (u16) (CSD_Tab[8]) * 256;
		/* Byte 8 */
		SD0_CardInfo->CSD.DeviceSize += CSD_Tab[9];}
	SD0_CardInfo->Capacity = SD0_CardInfo->CSD.DeviceSize * MSD_BLOCKSIZE * 1024;
	SD0_CardInfo->BlockSize = MSD_BLOCKSIZE;
	/* Byte 0 */
	SD0_CardInfo->CID.ManufacturerID = CID_Tab[0];
	/* Byte 1 */
	SD0_CardInfo->CID.OEM_AppliID = CID_Tab[1] << 8;
	/* Byte 2 */
	SD0_CardInfo->CID.OEM_AppliID |= CID_Tab[2];
	/* Byte 3 */
	SD0_CardInfo->CID.ProdName1 = CID_Tab[3] << 24;
	/* Byte 4 */
	SD0_CardInfo->CID.ProdName1 |= CID_Tab[4] << 16;
	/* Byte 5 */
	SD0_CardInfo->CID.ProdName1 |= CID_Tab[5] << 8;
	/* Byte 6 */
	SD0_CardInfo->CID.ProdName1 |= CID_Tab[6];
	/* Byte 7 */
	SD0_CardInfo->CID.ProdName2 = CID_Tab[7];
	/* Byte 8 */
	SD0_CardInfo->CID.ProdRev = CID_Tab[8];
	/* Byte 9 */
	SD0_CardInfo->CID.ProdSN = CID_Tab[9] << 24;
	/* Byte 10 */
	SD0_CardInfo->CID.ProdSN |= CID_Tab[10] << 16;
	/* Byte 11 */
	SD0_CardInfo->CID.ProdSN |= CID_Tab[11] << 8;
	/* Byte 12 */
	SD0_CardInfo->CID.ProdSN |= CID_Tab[12];
	/* Byte 13 */
	SD0_CardInfo->CID.Reserved1 |= (CID_Tab[13] &0xF0) >> 4;
	/* Byte 14 */
	SD0_CardInfo->CID.ManufactDate = (CID_Tab[13] &0x0F) << 8;
	/* Byte 15 */
	SD0_CardInfo->CID.ManufactDate |= CID_Tab[14];
	/* Byte 16 */
	SD0_CardInfo->CID.CID_CRC = (CID_Tab[15] &0xFE) >> 1;
	SD0_CardInfo->CID.Reserved2 = 1;
	return 0;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			写SD卡
 * @param	*buf	数据缓存区
 * @param	sector	起始扇区
 * @param	cnt		扇区数
 * @return			返回值:0,ok;其他,失败.
 */
u8 bsp_SD::SD_WriteDisk(u8 * buf, u32 sector, u8 cnt){
	u8 r1;
	if (SD_TYPE != V2HC) sector *= 512;				//转换为字节地址
	if (cnt == 1){
		r1 = SD_sendcmd(CMD24, sector, 0X01);		//读命令
		if (r1 == 0)								//指令发送成功
			r1 = SD_SendBlock(buf, 0xFE);}			//写512个字节
	else {
		if (SD_TYPE != MMC) {
			SD_sendcmd(CMD55, 0, 0X01);
			SD_sendcmd(CMD23, cnt, 0X01);}			//发送指令
		r1 = SD_sendcmd(CMD25, sector, 0X01);		//连续读命令
		if (r1 == 0) {
			do {
				r1 = SD_SendBlock(buf, 0xFC);		//接收512个字节
				buf += 512;}while(--cnt && r1 == 0);
			r1 = SD_SendBlock(0, 0xFD);}}			//接收512个字节
	SD_CS(0);										//取消片选
	return r1;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			读SD卡
 * @param	*buf	数据缓存区
 * @param	sector	起始扇区
 * @param	cnt		扇区数
 * @return			返回值:0,ok;其他,失败.
 */
u8 bsp_SD::SD_ReadDisk(u8 * buf, u32 sector, u8 cnt){
	u8 r1;
	if (SD_TYPE != V2HC) sector <<= 9;			//转换为字节地址
	if (cnt == 1) {
		r1 = SD_sendcmd(CMD17, sector, 0X01);	//读命令
		if (r1 == 0)							//指令发送成功
			r1 = SD_ReceiveData(buf, 512);}		//接收512个字节
	else {
		r1 = SD_sendcmd(CMD18, sector, 0X01);	//连续读命令
		do {
			r1 = SD_ReceiveData(buf, 512);		//接收512个字节	 
			buf += 512;}
		while(--cnt && r1 == 0);
		SD_sendcmd(CMD12, 0, 0X01);}				//发送停止命令
	SD_CS(0);										//取消片选
	return r1;}
//----------------------------------------------------------------------------------------------------
u8 bsp_SD::spi_readwrite(u8 Txdata){
	u8 Rxdata;
	HAL_SPI_TransmitReceive(hspi, &Txdata, &Rxdata, 1, 0xFF);
	return Rxdata;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			设置SPI的速率
 * @param	speed	速率
 * @return			无
 */
void bsp_SD::SPI_setspeed(u8 speed){
	hspi->Init.BaudRatePrescaler = speed;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			写入连贯的数据
 * @param	offset	写入位置
 * @param	*dat	数据缓冲区
 * @param	datlen	写入长度
 * @return			返回值:0,ok;其他,失败.
 */
u8 bsp_SD::offsetWrite(u64 offset,u8* dat,u64 datlen) {
	u8 sectorBuff[512] = { 0 };
	u64 sectorBuffptr = 0;
	
	u64 sectorSour		= offset / 512;					//	起始扇
	u64 sectorSourlen	= offset % 512;					//	起始扇内位

	//	填入数据
	SD_ReadDisk(sectorBuff,sectorSour,1);
	sectorBuffptr = sectorSourlen;
	for (u64 i = 0; i < datlen; i++) {
		//	写入数据
		sectorBuff[sectorBuffptr] = dat[i];
		sectorBuffptr++;
		//	扇区回写
		if (sectorBuffptr == 512 || i == datlen - 1) {
			SD_WriteDisk(sectorBuff,sectorSour,1);
			sectorBuffptr = 0;
			sectorSour++;
			if (i != datlen - 1)SD_ReadDisk(sectorBuff,sectorSour,1);}}
	return 0;
	}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			读取连贯的数据
 * @param	offset	读取位置
 * @param	*dat	数据缓冲区
 * @param	datlen	读取长度
 * @return			返回值:0,ok;其他,失败.
 */
u8 bsp_SD::offsetRead(u64 offset,u8* dat,u64 datlen) {
	u8 sectorBuff[512] = { 0 };
	u64 sectorBuffptr = 0;
	
	u64 sectorSour		= offset / 512;					//	起始扇
	u64 sectorSourlen	= offset % 512;					//	起始扇内位

	//	填入数据
	SD_ReadDisk(sectorBuff,sectorSour,1);
	sectorBuffptr = sectorSourlen;
	for (u64 i = 0; i < datlen; i++) {
		//	写入数据
		dat[i]=sectorBuff[sectorBuffptr];
		sectorBuffptr++;
		//	扇区回写
		if (sectorBuffptr == 512 || i == datlen - 1) {
			sectorBuffptr = 0;
			sectorSour++;
			if (i != datlen - 1)SD_ReadDisk(sectorBuff,sectorSour,1);}}
	return 0;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
//	
bsp_SD::bsp_SD(
	SPI_HandleTypeDef *hspi,
	GPIO_TypeDef *GPIOx_CS,
	uint16_t GPIO_Pin_CS){
	bsp_SD::hspi=hspi;
	bsp_SD::GPIOx_CS=GPIOx_CS;
	bsp_SD::GPIO_Pin_CS=GPIO_Pin_CS;
	bsp_SD::DFF=0xFF;
	bsp_SD::SD_TYPE=0x00;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
