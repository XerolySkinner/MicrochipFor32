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
  * @file		bsp_BMP.h
  * @brief		��������BMPͼƬ
  * @mainpage	��Ҫ��Ϣ
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
//	�ļ�ͷ
#pragma pack(1)
/**
 * @brief 							λͼ�ļ�ͷ
 */
typedef struct
{
	u16 bfType;						//�ļ���־.�̶�Ϊ'BM',����ʶ��BMPλͼ����
	u32 bfSize;						//�ļ���С,ռ�ĸ��ֽ�
	u16 bfReserved1;				//��������Ϊ0
	u16 bfReserved2;				//��������Ϊ0
	u32 bfOffBits;					//���ļ���ʼ��λͼ����(bitmap data)��ʼ֮��ĵ�ƫ����
}_BITMAPFILEHEADER;
/**
 * @brief 							λͼ��Ϣͷ
 */
typedef struct {
	u32 biSize;						//BITMAPINFOHEADER�ṹ����Ҫ��������
	u32 biWidth;					//ͼ��Ŀ�ȣ�������Ϊ��λ 
	u32 biHeight;					//ͼ��ĸ߶ȣ�������Ϊ��λ 
	u16 biPlanes;					//ΪĿ���豸˵��λ��������ֵ�����Ǳ���Ϊ1 
	u16 biBitCount;					//������/���أ���ֵΪ1��4��8��16��24����32
	u32 biCompression;				//ͼ������ѹ�������͡���ֵ����������ֵ֮һ��
										//BI_RGB��û��ѹ����
										//BI_RLE8��ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)��
										//BI_RLE4��ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����
										//BI_BITFIELDS��ÿ�����صı�����ָ�������������
	u32 biSizeImage;				//ͼ��Ĵ�С�����ֽ�Ϊ��λ������BI_RGB��ʽʱ��������Ϊ0
	u32 biXPelsPerMeter;			//ˮƽ�ֱ��ʣ�������/�ױ�ʾ
	u32 biYPelsPerMeter;			//��ֱ�ֱ��ʣ�������/�ױ�ʾ
	u32 biClrUsed;					//λͼʵ��ʹ�õĲ�ɫ���е���ɫ������
	u32 biClrImportant;				//��ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ��
}_BITMAPINFOHEADER;
/**
 * @brief 							��ɫ��
 */
typedef struct{
	u8 rgbBlue;						//ָ����ɫǿ��
	u8 rgbGreen;					//ָ����ɫǿ�� 
	u8 rgbRed;						//ָ����ɫǿ�� 
	u8 rgbReserved;					//����������Ϊ0 
	}_RGBQUAD;
/**
 * @brief 							BMP�ļ�ͷ
 */
typedef struct{
	_BITMAPFILEHEADER bmfHeader;	//λͼ�ļ�ͷ
	_BITMAPINFOHEADER bmiHeader;	//λͼ��Ϣͷ 
	_RGBQUAD bmiColors[256];		//��ɫ��
}_BITMAPINFO;
#pragma pack()
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
/**
 * @brief 							����һ��BMP��
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
		_BITMAPINFO BITMAPINFO;		///< �ļ�ͷ
		u32 Size;					///< �ļ���С
		u8* dat;					///< ������
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
