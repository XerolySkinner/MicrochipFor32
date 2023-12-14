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
  * @file		bsp_Complex.h
  * @brief		虚数运算库
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Sat May 13 02:26:52 2023

  */

#ifndef bsp_Complex_H
#define bsp_Complex_H
#ifdef __cplusplus
#include "varint.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	类目
/**
 * @brief			TODO
 */
class Complex {
	private:
		double real;
		double imag;
	public:
		Complex(double r=0, double i=0) : real(r), imag(i) {}
		Complex(const Complex& c) : real(c.real), imag(c.imag) {}
	public:
		double	getReal() const { return real; }
		double	getImag() const { return imag; }
		void	setReal(double r) { real = r; }
		void setImag(double i) { imag = i; }
	public:
		double	abs() const {return sqrtf(real*real+imag*imag);}
		double	angle() const {return atan2(imag, real);}
	public:
    Complex operator+(const Complex& c) const {
        return Complex(real + c.real, imag + c.imag);}
    Complex operator-(const Complex& c) const {
        return Complex(real - c.real, imag - c.imag);}
    Complex operator*(const Complex& c) const {
        return Complex(real * c.real - imag * c.imag,
                       real * c.imag + imag * c.real);}
    Complex operator/(const Complex& c) const {
        double denom = c.real * c.real + c.imag * c.imag;
        return Complex((real * c.real + imag * c.imag) / denom,
                       (imag * c.real - real * c.imag) / denom);}
    Complex operator=(const Complex& c) {
        real = c.real;
        imag = c.imag;
        return *this;}
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
#endif
