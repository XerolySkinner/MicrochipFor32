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
  * @file		STL_Stack.h
  * @brief		实现了STL库中的Stack
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		2022-11-08 16:41
  */

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	头文件
#include "STL_Stack.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
STL_rStack::STL_rStack(void) {
	room = 0;
	size = 0;
	dat = NULL;}
//----------------------------------------------------------------------------------------------------
STL_rStack::~STL_rStack(void) {
	free(dat);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	成员函数
/**
 * @brief			压入一个成员
 * @param	var 	需要压入的数值
 * @return			错误号
 */
u8 STL_rStack::push(u8 var) {
	//	保存分配前的数据头
	u8* temp_stacks = dat;
	//	若所需空间小于现有空间
	if (size >= room) {
		//	分配新长度
		dat = static_cast<u8*>(realloc(dat, ++size));
		//	分配失败,善后并且返回错误
		if (dat == NULL) {
			--size;					//	恢复原长度
			dat = temp_stacks;		//	恢复数据
			return STACKS_REAL_ERROR;
		}		//	返回错误
		room = size;
		//	分配成功,压入数据
		dat[size - 1] = var;
		//	返回正确指数
		return STACKS_OK;}
	//	空间剩余,压入数据
	dat[(++size) - 1] = var;
	//	返回正确指数
	return STACKS_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			弹出一个成员
 * @return			错误号
 */
u8 STL_rStack::pop(void) {
	//	若数据栈中大于1,缩短成员空间
	if (size > 1) {
		--size;								//	重新分配成员空间
		return STACKS_OK;}
	//	若数据栈中等于1,重指定头
	else if (size == 1) {
		size = 0;							//	重新分配成员空间
		return STACKS_OK;}
	//	若数据栈为空,返回空栈错误号
	else
		return STACKS_EMPTY;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			显示最后压入的数值
 * @param	&var 	最后压入数值的储存变量
 * @return			错误号
 */
u8 STL_rStack::top(u8 &var) {
	if (size) {
		var = dat[size-1];
		return STACKS_OK;}
	return STACKS_EMPTY;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			返回成员数量
 * @return			成员数量,为u8类型,如u32将占4个元素
 */
u32 STL_rStack::The_size(void) {
	return size;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			返回占用的内存数
 * @return			内存数,u8类型
 */
u32 STL_rStack::The_room(void) {
	return room;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			将申请的空间比对所需空间,腾出冗余空间
 * @return			错误号
 */
u8 STL_rStack::clean(void) {
	//	保存分配前的数据头
	u8* temp_stacks = dat;
	//	如果有成员,重新分配空间
	if (size) {
		//	重新分配空间
		dat = static_cast<u8*>(realloc(dat,size));
		//	分配失败,善后并返回错误
		if (dat == NULL) {
			--size;								//	恢复原长度
			dat = temp_stacks;					//	恢复数据
			return STACKS_REAL_ERROR;}			//	返回错误
		}
	//	无成员栈重新分配成员
	else {
		free(dat);								//	释放全部空间
		dat = NULL;
		size = 0;}								//	重指定首部
//	无数据返回空栈
	room = size;								//	新的空间大小
	return STACKS_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			压入一个32位成员
 * @param	var 	需要压入的数值
 * @return			错误号
 */
u8	STL_rStack::push32(u32 var) {
	push(((u8*)(&var))[3]);
	push(((u8*)(&var))[2]);
	push(((u8*)(&var))[1]);
	push(((u8*)(&var))[0]);
	return STACKS_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			弹出并且返回一个成员
 * @return			弹出的成员值
 * @note			该函数不会检查成功与否
 */
u8 STL_rStack::poptop(void) {
	u8 var = 0;
	top(var);pop();
	return var;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			弹出并且返回一个32位成员
 * @return			弹出的成员值
 * @note			该函数不会检查成功与否
 */
u32 STL_rStack::poptop32(void) {
	u8 dat[4] = { 0,0,0,0 };
	top(dat[0]); pop();
	top(dat[1]); pop();
	top(dat[2]); pop();
	top(dat[3]); pop();
	return *((u32*)(dat));}

//----------------------------------------------------------------------------------------------------
/**
 * @brief			弹出并且返回一个void(*)void函数
 * @note			该函数不会检查成功与否
 */
void(*STL_rStack::poptopfun(void))(void) {
	return (void(*)(void))poptop32();}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			压入一个void(*)void函数
 * @note			该函数不会检查成功与否
 */
void STL_rStack::pushfun(void(*fun)(void)){
	push32((u32)fun);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
STL_lStack::STL_lStack(void) {
	mem = 0;
	dat = NULL;}
//----------------------------------------------------------------------------------------------------
STL_lStack::~STL_lStack(void) {
	if (mem)pop();}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	成员函数
/**
 * @brief			压入一个成员
 * @param	*&var 	需要压入的数值的地址
 * @param	size 	需要压入的数值的长度
 * @return			错误号
 */
u8 STL_lStack::push(void* &var,u32 size) {
	_lStack* newdat = (_lStack*)malloc(sizeof(_lStack));
	if (newdat == NULL)return STACKS_MALL_ERROR;
	newdat->size = size;
	newdat->front = dat;
	newdat->dat = var;
	dat = newdat;
	++mem;
	return STACKS_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			弹出一个成员
 * @return			错误号
 * @note			无论push进去的是32位还是8位数,都用这个弹出
 */
u8 STL_lStack::pop(void) {
	if (mem == 0) return STACKS_EMPTY;
	_lStack* savedat = dat;				//	保存首部
	dat = dat->front;					//	弹出
	free(savedat->dat);					//	回收目标指针
	free(savedat);						//	回收
	--mem;								//	成员自减
	return STACKS_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			显示栈顶部成员
 * @param	*&var 	需要赋予的数值的地址
 * @param	&size 	需要赋予的数值的长度
 * @return			错误号
 */
u8 STL_lStack::top(void* &var,u32 &size) {
	if (mem==0) return STACKS_EMPTY;
	var = dat->dat;
	size = dat->size;
	return STACKS_OK;}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
/**
 * @brief			压入一个8位成员
 * @param	var 	需要压入的8位数据
 * @return			错误号
 */
u8 STL_lStack::push8(u8 var) {
	void* num=(u8*)malloc(sizeof(u8));
	if (num == NULL)return STACKS_MALL_ERROR;
	*(u8*)num = var;
	push(num, sizeof(u8));
	return STACKS_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			显示栈顶成员
 * @param	&var 	结果赋予给该变量
 * @return			错误号
 */
u8 STL_lStack::top8(u8& var) {
	void* vars=NULL;
	u32 sizes=0;
	if (top(vars, sizes) == STACKS_EMPTY)
		return STACKS_EMPTY;
	var = *((u8*)vars);
	return STACKS_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			显示并且弹出一个栈顶成员
 * @return			返回弹出的数值
 */
u8 STL_lStack::poptop8(void) {
	u8 temp=0;
	top8(temp);
	pop();
	return temp;}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
/**
 * @brief			压入一个32位成员
 * @param	var 	需要压入的32位数据
 * @return			错误号
 */
u8 STL_lStack::push32(u32 var) {
	void* num = (u32*)malloc(sizeof(u32));
	if (num == NULL)return STACKS_MALL_ERROR;
	*(u32*)num = var;
	push(num, sizeof(u32));
	return STACKS_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			显示栈顶成员
 * @param	&var 	结果赋予给该变量
 * @return			错误号
 */
u8 STL_lStack::top32(u32& var) {
	void* vars = NULL;
	u32 sizes = 0;
	if (top(vars, sizes) == STACKS_EMPTY)
		return STACKS_EMPTY;
	var = *((u32*)vars);
	return STACKS_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			显示并且弹出一个栈顶成员
 * @return			返回弹出的数值
 */
u32 STL_lStack::poptop32(void) {
	u32 temp = 0;
	top32(temp);
	pop();
	return temp;}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
/**
 * @brief			压入一个void(*)(void)函数指针
 * @param	*fun 	需要压入的函数
 * @return			错误号
 * @note			如果有个函数是
 *					void fun(void);
 *					可以通过pushfun(fun);将其压入
 */
u8 STL_lStack::pushfun(void(*fun)(void)) {
	u8 res;
	res=push32((u32)fun);
	return res;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			弹出一个void(*)(void)函数指针
 * @return			函数的指针
 * @note			可以通过poptopfun();弹出一个函数指针
 *					如果确定指针非空,可以通过poptopfun()();直接弹出并执行该函数
 */
void(*STL_lStack::poptopfun(void))(void) {
	return (void(*)(void))poptop32();}
//////////////////////////////////////////////////////////////////////////////////////////////////////
