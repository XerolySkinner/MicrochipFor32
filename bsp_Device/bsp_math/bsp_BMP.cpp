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
  * @file		bsp_BMP.cpp
  * @brief		��������BMPͼƬ
  * @mainpage	��Ҫ��Ϣ
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-24 20:22
  */
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "bsp_BMP.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	�ຯ��
/**
 * @brief			��������
 * @param	x		x����
 * @param	y		y����
 */
void bsp_BMP::pels(u32 x, u32 y) {
	bsp_BMP::BITMAPINFO.bmiHeader.biXPelsPerMeter = x;
	bsp_BMP::BITMAPINFO.bmiHeader.biYPelsPerMeter = y;}
/**
 * @brief			�������ݿռ�
 * @return			���ظ��������ͷ
 */
u32 bsp_BMP::giveData(void) {
	free(dat);
	dat = (u8*)malloc(Size);
	return (u32)dat;}
/**
 * @brief			�ͷ����ݿռ�
 */
void bsp_BMP::delData(void) {
	free(dat);}
/**
 * @brief			���õ�ɫ��
 * @param	R		��ɫ
 * @param	G		��ɫ
 * @param	B		��ɫ
 * @param	i		������
 */
void bsp_BMP::ColorsSet(u8 R, u8 G, u8 B,u32 i) {
	BITMAPINFO.bmiColors[i].rgbBlue = B;
	BITMAPINFO.bmiColors[i].rgbGreen = G;
	BITMAPINFO.bmiColors[i].rgbRed = R;
	BITMAPINFO.bmiColors[i].rgbReserved = 0;}
/**
 * @brief			����ͼƬ��С
 * @param	Width 	ͼƬ���
 * @param	Height 	ͼƬ�߶�
 */
void bsp_BMP::sizeSet(u32 x, u32 y) {
	free(dat);
	Size = x * y;
	BITMAPINFO.bmiHeader.biWidth = x;			//	ɫ�ʿ��
	BITMAPINFO.bmiHeader.biHeight = y;			//	ɫ�ʸ߶�
	BITMAPINFO.bmfHeader.bfOffBits =
		sizeof(_BITMAPINFO);					//	λͼ����ƫ��
	BITMAPINFO.bmfHeader.bfSize =
		x * y +
		BITMAPINFO.bmfHeader.bfOffBits;			//	�ļ���С
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	���캯��
/**
 * @brief			����BMP����ͷ
 * @param	Width 	ͼƬ���
 * @param	Height 	ͼƬ�߶�
 */
bsp_BMP::bsp_BMP(u32 Width, u32 Height) {
	bsp_BMP::dat = NULL;
	bsp_BMP::Size = Width * Height;
	BITMAPINFO.bmiHeader.biWidth = Width;			//	ɫ�ʿ��
	BITMAPINFO.bmiHeader.biHeight = Height;			//	ɫ�ʸ߶�
	BITMAPINFO.bmfHeader.bfType = 0x4D42;			//	��Ϊ������
	BITMAPINFO.bmfHeader.bfReserved1 = 0;			//	������
	BITMAPINFO.bmfHeader.bfReserved2 = 0;			//	������
	BITMAPINFO.bmiHeader.biCompression = 0;			//	��ѹ��
	BITMAPINFO.bmiHeader.biSizeImage = 0;			//	��ѹ����Ϊ0
	BITMAPINFO.bmiHeader.biPlanes = 1;				//	��Ϊ������
	BITMAPINFO.bmiHeader.biClrUsed = 0;				//	ʹ��ȫ����ɫ
	BITMAPINFO.bmiHeader.biClrImportant = 0;		//	ȫ����ɫ����Ҫ
	BITMAPINFO.bmiHeader.biXPelsPerMeter = 0;		//	����-��̫��Ҫ
	BITMAPINFO.bmiHeader.biYPelsPerMeter = 0;		//	����-��̫��Ҫ
	BITMAPINFO.bmiHeader.biSize = 40;				//	��Ϣͷ��С
	BITMAPINFO.bmfHeader.bfOffBits = 
		sizeof(_BITMAPINFO);						//	λͼ����ƫ��
	BITMAPINFO.bmfHeader.bfSize = 
		Width * Height+ 
		BITMAPINFO.bmfHeader.bfOffBits;				//	�ļ���С
	BITMAPINFO.bmiHeader.biBitCount = 8;			//	ɫ�����
	}
//----------------------------------------------------------------------------------------------------
bsp_BMP::~bsp_BMP(void) {
	free(dat);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
