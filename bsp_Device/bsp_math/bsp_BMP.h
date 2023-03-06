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
  * @file		bsp_BMP.h
  * @brief		用来构造BMP图片
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-24 20:22
  */
#pragma once
#ifdef __cplusplus
#include "varint.h"
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	文件头
#pragma pack(1)
/**
 * @brief 							位图文件头
 */
typedef struct
{
	u16 bfType;						//文件标志.固定为'BM',用来识别BMP位图类型
	u32 bfSize;						//文件大小,占四个字节
	u16 bfReserved1;				//保留，总为0
	u16 bfReserved2;				//保留，总为0
	u32 bfOffBits;					//从文件开始到位图数据(bitmap data)开始之间的的偏移量
}_BITMAPFILEHEADER;
/**
 * @brief 							位图信息头
 */
typedef struct {
	u32 biSize;						//BITMAPINFOHEADER结构所需要的字数。
	u32 biWidth;					//图象的宽度，以象素为单位 
	u32 biHeight;					//图象的高度，以象素为单位 
	u16 biPlanes;					//为目标设备说明位面数，其值将总是被设为1 
	u16 biBitCount;					//比特数/象素，其值为1、4、8、16、24、或32
	u32 biCompression;				//图象数据压缩的类型。其值可以是下述值之一：
										//BI_RGB：没有压缩；
										//BI_RLE8：每个象素8比特的RLE压缩编码，压缩格式由2字节组成(重复象素计数和颜色索引)；
										//BI_RLE4：每个象素4比特的RLE压缩编码，压缩格式由2字节组成
										//BI_BITFIELDS：每个象素的比特由指定的掩码决定。
	u32 biSizeImage;				//图象的大小，以字节为单位。当用BI_RGB格式时，可设置为0
	u32 biXPelsPerMeter;			//水平分辨率，用象素/米表示
	u32 biYPelsPerMeter;			//垂直分辨率，用象素/米表示
	u32 biClrUsed;					//位图实际使用的彩色表中的颜色索引数
	u32 biClrImportant;				//对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要。
}_BITMAPINFOHEADER;
/**
 * @brief 							调色板
 */
typedef struct{
	u8 rgbBlue;						//指定蓝色强度
	u8 rgbGreen;					//指定绿色强度 
	u8 rgbRed;						//指定红色强度 
	u8 rgbReserved;					//保留，设置为0 
	}_RGBQUAD;
/**
 * @brief 							BMP文件头
 */
typedef struct{
	_BITMAPFILEHEADER bmfHeader;	//位图文件头
	_BITMAPINFOHEADER bmiHeader;	//位图信息头 
	_RGBQUAD bmiColors[256];		//调色板
}_BITMAPINFO;
#pragma pack()
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
/**
 * @brief 							构建一个BMP类
 */
class bsp_BMP {
	public:
		bsp_BMP(u32 Width, u32 Height);
		~bsp_BMP(void);
	public:
		void	pels(u32 x, u32 y);
		u32		giveData(void);
		void	delData(void);
		void	ColorsSet(u8 R, u8 G, u8 B,u32 i);
		void	sizeSet(u32 x, u32 y);
	public:
		_BITMAPINFO BITMAPINFO;		///< 文件头
		u32 Size;					///< 文件大小
		u8* dat;					///< 数据区
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
