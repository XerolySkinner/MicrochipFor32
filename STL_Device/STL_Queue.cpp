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
   * @file		STL_Queue.cpp
   * @brief		实现了STL库中的Queue
   * @mainpage	主要信息
   * @author		Yuankang Liang(XerolySkinner)
   * @email		zabbcccbbaz@163.com
   * @version		V1.0.0
   * @date		2022-11-09 01:03
   */

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  //----------------------------------------------------------------------------------------------------
  //	头文件
#include "STL_Queue.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
STL_rQueue::STL_rQueue(void) {
	room = 0;
	size = 0;
	dat = NULL;}
//----------------------------------------------------------------------------------------------------
STL_rQueue::~STL_rQueue(void) {
	free(dat);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	成员函数
/**
 * @brief			压入一个成员
 * @param	var 	需要压入的数值
 * @return			错误号
 */
u8 STL_rQueue::push(u8 var) {
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
			return QUEUES_REAL_ERROR;}		//	返回错误
		room = size;
		//	分配成功,压入数据
		dat[size - 1] = var;
		//	返回正确指数
		return QUEUES_OK;}
	//	空间剩余,压入数据
	dat[(++size) - 1] = var;
	//	返回正确指数
	return QUEUES_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			弹出一个成员
 * @return			错误号
 */
u8 STL_rQueue::pop(void) {
	//	若数据队列中大于1,缩短成员空间
	if (size > 1) {
		//	整体移动掉一位
		for (u32 i = 0; i < size - 1; i++)
			*(dat + i) = *(dat + i + 1);
		--size;								//	重新分配成员空间
		return QUEUES_OK;}
	//	若数据队列中等于1,重指定头
	else if (size == 1) {
		size = 0;							//	重新分配成员空间
		return QUEUES_OK;}					//	若数据队列为空,返回空队列错误号
	else
		return QUEUES_EMPTY;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			显示最后压入的数值
 * @param	&var 	最后压入数值的储存变量
 * @return			错误号
 */
u8 STL_rQueue::top(u8& var) {
	if (size) {
		var = dat[0];
		return QUEUES_OK;}
	return QUEUES_EMPTY;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			返回成员数量
 * @return			成员数量,为u8类型,如u32将占4个元素
 */
u32 STL_rQueue::The_size(void) {
	return size;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			返回占用的内存数
 * @return			内存数,u8类型
 */
u32 STL_rQueue::The_room(void) {
	return room;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			将申请的空间比对所需空间,腾出冗余空间
 * @return			错误号
 */
u8 STL_rQueue::clean(void) {
	//	保存分配前的数据头
	u8* temp_stacks = dat;
	//	如果有成员,重新分配空间
	if (size) {
		//	重新分配空间
		dat = static_cast<u8*>(realloc(dat, size));
		//	分配失败,善后并返回错误
		if (dat == NULL) {
			--size;								//	恢复原长度
			dat = temp_stacks;					//	恢复数据
			return QUEUES_REAL_ERROR;}			//	返回错误
		}
	//	无成员队列重新分配成员
	else {
		free(dat);								//	释放全部空间
		dat = NULL;
		size = 0;}								//	重指定首部
//	无数据返回空队列
	room = size;								//	新的空间大小
	return QUEUES_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			压入一个32位成员
 * @param	var 	需要压入的数值
 * @return			错误号
 */
u8	STL_rQueue::push32(u32 var) {
	push(((u8*)(&var))[3]);
	push(((u8*)(&var))[2]);
	push(((u8*)(&var))[1]);
	push(((u8*)(&var))[0]);
	return QUEUES_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			弹出并且返回一个成员
 * @return			弹出的成员值
 * @note			该函数不会检查成功与否
 */
u8 STL_rQueue::poptop(void) {
	u8 var = 0;
	top(var); pop();
	return var;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			弹出并且返回一个32位成员
 * @return			弹出的成员值
 * @note			该函数不会检查成功与否
 */
u32 STL_rQueue::poptop32(void) {
	u8 dat[4] = { 0,0,0,0 };
	top(dat[3]); pop();
	top(dat[2]); pop();
	top(dat[1]); pop();
	top(dat[0]); pop();
	return *((u32*)(dat));}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			弹出并且返回一个void(*)void函数
 * @note			该函数不会检查成功与否
 */
void(*STL_rQueue::poptopfun(void))(void) {
	return (void(*)(void))poptop32();}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			压入一个void(*)void函数
 * @note			该函数不会检查成功与否
 */
void STL_rQueue::pushfun(void(*fun)(void)) {
	push32((u32)fun);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	构造函数
STL_lQueue::STL_lQueue(void) {
	STL_lQueue::Hdat = NULL;
	STL_lQueue::Tdat = NULL;
	STL_lQueue::mem = 0;
	}
STL_lQueue::~STL_lQueue(void) {
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
u8 STL_lQueue::push(void*& var, u32 size) {
	_lQueue* newdat = (_lQueue*)malloc(sizeof(_lQueue));
	if (newdat == NULL)return QUEUES_MALL_ERROR;
	newdat->dat = var;
	newdat->size = size;
	newdat->back = NULL;
	if (mem == 0) {
		Hdat = newdat;
		Tdat = newdat;}
	else {
		Hdat->back = newdat;
		Hdat = newdat;}
	++mem;
	return QUEUES_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			弹出一个成员
 * @return			错误号
 * @note			无论push进去的是32位还是8位数,都用这个弹出
 */
u8 STL_lQueue::pop(void) {
	if (mem == 0) return QUEUES_EMPTY;
	_lQueue* savedat = Tdat;			//	保存尾部
	if (mem == 1) {
		Tdat = NULL;
		Hdat = NULL;}
	else if(mem>1) {
		Tdat = Tdat->back;}
	free(savedat->dat);
	free(savedat);
	--mem;
	return QUEUES_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			显示队列顶部成员
 * @param	*&var 	需要赋予的数值的地址
 * @param	&size 	需要赋予的数值的长度
 * @return			错误号
 */
u8 STL_lQueue::top(void*& var, u32& size) {
	if (mem == 0) return QUEUES_EMPTY;
	var = Tdat->dat;
	size = Tdat->size;
	return QUEUES_OK;}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
/**
 * @brief			压入一个8位成员
 * @param	var 	需要压入的8位数据
 * @return			错误号
 */
u8 STL_lQueue::push8(u8 var) {
	void* num = (u8*)malloc(sizeof(u8));
	if (num == NULL)return QUEUES_MALL_ERROR;
	*(u8*)num = var;
	push(num, sizeof(u8));
	return QUEUES_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			显示队列顶成员
 * @param	&var 	结果赋予给该变量
 * @return			错误号
 */
u8 STL_lQueue::top8(u8& var) {
	void* vars = NULL;
	u32 sizes = 0;
	if (top(vars, sizes) == QUEUES_EMPTY)
		return QUEUES_EMPTY;
	var = *((u8*)vars);
	return QUEUES_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			显示并且弹出一个队列顶成员
 * @return			返回弹出的数值
 */
u8 STL_lQueue::poptop8(void) {
	u8 temp = 0;
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
u8 STL_lQueue::push32(u32 var) {
	void* num = (u32*)malloc(sizeof(u32));
	if (num == NULL)return QUEUES_MALL_ERROR;
	*(u32*)num = var;
	push(num, sizeof(u32));
	return QUEUES_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			显示队列顶成员
 * @param	&var 	结果赋予给该变量
 * @return			错误号
 */
u8 STL_lQueue::top32(u32& var) {
	void* vars = NULL;
	u32 sizes = 0;
	if (top(vars, sizes) == QUEUES_EMPTY)
		return QUEUES_EMPTY;
	var = *((u32*)vars);
	return QUEUES_OK;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			显示并且弹出一个队列顶成员
 * @return			返回弹出的数值
 */
u32 STL_lQueue::poptop32(void) {
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
u8 STL_lQueue::pushfun(void(*fun)(void)) {
	u8 res;
	res = push32((u32)fun);
	return res;}
//----------------------------------------------------------------------------------------------------
/**
 * @brief			弹出一个void(*)(void)函数指针
 * @return			函数的指针
 * @note			可以通过poptopfun();弹出一个函数指针
 *					如果确定指针非空,可以通过poptopfun()();直接弹出并执行该函数
 */
void(*STL_lQueue::poptopfun(void))(void) {
	return (void(*)(void))poptop32();}
//////////////////////////////////////////////////////////////////////////////////////////////////////
