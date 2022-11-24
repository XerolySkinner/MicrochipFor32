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
  * @file		bsp_BMP.cpp
  * @brief		用来构造BMP图片
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-24 20:22
  */
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "bsp_BMP.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类函数
/**
 * @brief			设置像素
 * @param	x		x像素
 * @param	y		y像素
 */
void bsp_BMP::pels(u32 x, u32 y) {
	bsp_BMP::BITMAPINFO.bmiHeader.biXPelsPerMeter = x;
	bsp_BMP::BITMAPINFO.bmiHeader.biYPelsPerMeter = y;}
/**
 * @brief			给予数据空间
 * @return			返回给与的数据头
 */
u32 bsp_BMP::giveData(void) {
	free(dat);
	dat = (u8*)malloc(Size);
	return (u32)dat;}
/**
 * @brief			释放数据空间
 */
void bsp_BMP::delData(void) {
	free(dat);}
/**
 * @brief			设置调色板
 * @param	R		红色
 * @param	G		绿色
 * @param	B		蓝色
 * @param	i		索引号
 */
void bsp_BMP::ColorsSet(u8 R, u8 G, u8 B,u32 i) {
	BITMAPINFO.bmiColors[i].rgbBlue = B;
	BITMAPINFO.bmiColors[i].rgbGreen = G;
	BITMAPINFO.bmiColors[i].rgbRed = R;
	BITMAPINFO.bmiColors[i].rgbReserved = 0;}
/**
 * @brief			设置图片大小
 * @param	Width 	图片宽度
 * @param	Height 	图片高度
 */
void bsp_BMP::sizeSet(u32 x, u32 y) {
	free(dat);
	Size = x * y;
	BITMAPINFO.bmiHeader.biWidth = x;			//	色彩宽度
	BITMAPINFO.bmiHeader.biHeight = y;			//	色彩高度
	BITMAPINFO.bmfHeader.bfOffBits =
		sizeof(_BITMAPINFO);					//	位图数据偏倚
	BITMAPINFO.bmfHeader.bfSize =
		x * y +
		BITMAPINFO.bmfHeader.bfOffBits;			//	文件大小
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
/**
 * @brief			构造BMP数据头
 * @param	Width 	图片宽度
 * @param	Height 	图片高度
 */
bsp_BMP::bsp_BMP(u32 Width, u32 Height) {
	bsp_BMP::dat = NULL;
	bsp_BMP::Size = Width * Height;
	BITMAPINFO.bmiHeader.biWidth = Width;			//	色彩宽度
	BITMAPINFO.bmiHeader.biHeight = Height;			//	色彩高度
	BITMAPINFO.bmfHeader.bfType = 0x4D42;			//	恒为保护字
	BITMAPINFO.bmfHeader.bfReserved1 = 0;			//	保留字
	BITMAPINFO.bmfHeader.bfReserved2 = 0;			//	保留字
	BITMAPINFO.bmiHeader.biCompression = 0;			//	无压缩
	BITMAPINFO.bmiHeader.biSizeImage = 0;			//	无压缩下为0
	BITMAPINFO.bmiHeader.biPlanes = 1;				//	恒为保护字
	BITMAPINFO.bmiHeader.biClrUsed = 0;				//	使用全部颜色
	BITMAPINFO.bmiHeader.biClrImportant = 0;		//	全部颜色都重要
	BITMAPINFO.bmiHeader.biXPelsPerMeter = 0;		//	像素-不太重要
	BITMAPINFO.bmiHeader.biYPelsPerMeter = 0;		//	像素-不太重要
	BITMAPINFO.bmiHeader.biSize = 40;				//	信息头大小
	BITMAPINFO.bmfHeader.bfOffBits = 
		sizeof(_BITMAPINFO);						//	位图数据偏倚
	BITMAPINFO.bmfHeader.bfSize = 
		Width * Height+ 
		BITMAPINFO.bmfHeader.bfOffBits;				//	文件大小
	BITMAPINFO.bmiHeader.biBitCount = 8;			//	色彩深度
	}
//----------------------------------------------------------------------------------------------------
bsp_BMP::~bsp_BMP(void) {
	free(dat);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
