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
  * @file		bsp_ESP8266.c
  * @brief		ESP8266
  * @mainpage	主要信息
  * @author		Yuankang Liang(XerolySkinner)
  * @email		zabbcccbbaz@163.com
  * @version		V1.0.0
  * @date		Fri Dec 29 16:39:52 2023

  */
#include "bsp_ESP8266.h"
#include "vartable.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	函数
/**
 * @brief			title
 * @param	var 	vars
 * @return			res
 */
_esp esp_create(u8 (*transmit)(u8*,u32)){
	_esp obj=(_esp)esp_malloc(sizeof(_esp_struct));
	if(obj==NULL)return NULL;
	
	obj->TX_buff = (u8*)malloc(512);
	if(obj->TX_buff==NULL)return NULL;
	obj->title = (u8*)malloc(128);
	if(obj->title==NULL)return NULL;
	obj->msg = (u8*)malloc(128);
	if(obj->msg==NULL)return NULL;
	
	obj->transmit=transmit;
	obj->semaphore_OK = rt_sem_create("OK", 0, RT_IPC_FLAG_FIFO);
	if(obj->semaphore_OK==NULL)return NULL;	
	obj->state=ESP_UNLINK;
	return obj;}
//----------------------------------------------------------------------------------------------------
u8 esp_Callback(_esp obj,const char* str,u32 limit){
	if(findSubstring(str,"OK\r\n",limit) != NULL)rt_sem_release(obj->semaphore_OK);
	if(findSubstring(str,"+MQTTDISCONNECTED",limit) != NULL)reboots();
	return obj->state;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
void esp_AP_TCP_Server_Init(
	_esp obj,
	const char* Sname,
	const char* Spswd,
	const char* Sport){
	osDelay(2000);
		
	while(1){
		rt_kprintf("Set WIFI Mode to AP\r\n");
		esp_print(obj,"AT+CWMODE=2\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	rt_kprintf("Reset\r\n");
	esp_print(obj,"AT+RST\r\n");
	osDelay(2000);
		
	while(1){
		rt_kprintf("Create the WIFI\r\n");
		esp_print(obj,"AT+CWSAP=\"%s\",\"%s\",1,4\r\n",Sname,Spswd);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
	
	osDelay(1000);
		
	while(1){
		rt_kprintf("MUX is 1\r\n");
		esp_print(obj,"AT+CIPMUX=1\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
		
	while(1){
		rt_kprintf("Port in %s\r\n",Sport);
		esp_print(obj,"AT+CIPSERVER=1,%s\r\n",Sport);
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	rt_kprintf("[Success]\r\n");
	osDelay(1000);
	obj->state=ESP_LINKING;}
//----------------------------------------------------------------------------------------------------
void esp_AP_TCP_Client_Init(
	_esp obj,
	const char* Sname,
	const char* Spswd,
	const char* Cip,
	const char* Cport){
	osDelay(2000);
		
	while(1){
		rt_kprintf("Set WIFI Mode to AP\r\n");
		esp_print(obj,"AT+CWMODE=2\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	rt_kprintf("Reset\r\n");
	esp_print(obj,"AT+RST\r\n");
	osDelay(2000);
		
	while(1){
		rt_kprintf("Create the WIFI\r\n");
		esp_print(obj,"AT+CWSAP=\"%s\",\"%s\",1,4\r\n",Sname,Spswd);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
	
	osDelay(1000);
		
	while(1){
		rt_kprintf("MUX is 0\r\n");
		esp_print(obj,"AT+CIPMUX=0\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
		
	while(1){
		rt_kprintf("Link TCP as %s:%s\r\n",Cip,Cport);
		esp_print(obj,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",Cip,Cport);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
	
	while(1){
		rt_kprintf("Transparent transmission mode\r\n");
		esp_print(obj,"AT+CIPMODE=1\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	rt_kprintf("[Success]\r\n");
	osDelay(1000);
	obj->state=ESP_LINKING;}
//----------------------------------------------------------------------------------------------------
void esp_AP_UDP_Init(
	_esp obj,
	const char* Sname,
	const char* Spswd,
	const char* Cip,
	const char* Cport){
	osDelay(2000);
		
	while(1){
		rt_kprintf("Set WIFI Mode to AP\r\n");
		esp_print(obj,"AT+CWMODE=2\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	rt_kprintf("Reset\r\n");
	esp_print(obj,"AT+RST\r\n");
	osDelay(2000);
		
	while(1){
		rt_kprintf("Create the WIFI\r\n");
		esp_print(obj,"AT+CWSAP=\"%s\",\"%s\",1,4\r\n",Sname,Spswd);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
	
	osDelay(1000);
		
	while(1){
		rt_kprintf("MUX is 0\r\n");
		esp_print(obj,"AT+CIPMUX=0\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
		
	while(1){
		rt_kprintf("Link UDP as %s:%s\r\n",Cip,Cport);
		esp_print(obj,"AT+CIPSTART=\"UDP\",\"%s\",%s\r\n",Cip,Cport);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
	
	while(1){
		rt_kprintf("Transparent transmission mode\r\n");
		esp_print(obj,"AT+CIPMODE=1\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	rt_kprintf("[Success]\r\n");
	osDelay(1000);
	obj->state=ESP_LINKING;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
void esp_STA_TCP_Client_Init(
	_esp obj,
	const char* Sname,
	const char* Spswd,
	const char* Cip,
	const char* Cport){
	
	osDelay(2000);
		
	while(1){
		rt_kprintf("Set WIFI Mode to STA\r\n");
		esp_print(obj,"AT+CWMODE=1\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	rt_kprintf("Reset\r\n");
	esp_print(obj,"AT+RST\r\n");
	osDelay(2000);
	
	while(1){
		rt_kprintf("Join the WIFI\r\n");
		esp_print(obj,"AT+CWJAP=\"%s\",\"%s\"\r\n",Sname,Spswd);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
		
	while(1){
		rt_kprintf("MUX is 0\r\n");
		esp_print(obj,"AT+CIPMUX=0\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	while(1){
		rt_kprintf("Link TCP as %s:%s\r\n",Cip,Cport);
		esp_print(obj,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",Cip,Cport);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
	
	while(1){
		rt_kprintf("Transparent transmission mode\r\n");
		esp_print(obj,"AT+CIPMODE=1\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	rt_kprintf("Transmit start\r\n");
	esp_print(obj,"AT+CIPSEND\r\n");
	osDelay(1000);

	rt_kprintf("[Success]\r\n");
	osDelay(1000);
	obj->state=ESP_LINKING;}
//----------------------------------------------------------------------------------------------------
void esp_STA_TCP_Server_Init(
	_esp obj,
	const char* Cname,
	const char* Cpswd,
	const char* Sport){
	
	osDelay(2000);
		
	while(1){
		rt_kprintf("Set WIFI to STA mode\r\n");
		esp_print(obj,"AT+CWMODE=1\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	rt_kprintf("Reset\r\n");
	esp_print(obj,"AT+RST\r\n");
	osDelay(2000);
	
	while(1){
		rt_kprintf("Link to WIFI\r\n");
		esp_print(obj,"AT+CWJAP=\"%s\",\"%s\"\r\n",Cname,Cpswd);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
	
	osDelay(2000);
		
	while(1){
		rt_kprintf("MUX is 1\r\n");
		esp_print(obj,"AT+CIPMUX=1\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	osDelay(2000);
		
	while(1){
		rt_kprintf("Port in %s\r\n",Sport);
		esp_print(obj,"AT+CIPSERVER=1,%s\r\n",Sport);
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	rt_kprintf("[Success]\r\n");
	osDelay(1000);
	obj->state=ESP_LINKING;}
//----------------------------------------------------------------------------------------------------
void esp_STA_UDP_Init(
	_esp obj,
	const char* Cname,
	const char* Cpswd,
	const char* Cip,
	const char* Cport){
	
	osDelay(2000);
		
	while(1){
		rt_kprintf("Set WIFI to STA mode\r\n");
		esp_print(obj,"AT+CWMODE=1\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	rt_kprintf("Reset\r\n");
	esp_print(obj,"AT+RST\r\n");
	osDelay(2000);
	
	while(1){
		rt_kprintf("Link to WIFI\r\n");
		esp_print(obj,"AT+CWJAP=\"%s\",\"%s\"\r\n",Cname,Cpswd);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
	
	osDelay(1000);
		
	while(1){
		rt_kprintf("MUX is 0\r\n");
		esp_print(obj,"AT+CIPMUX=0\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	osDelay(1000);
		
	while(1){
		rt_kprintf("Link UDP as %s:%s\r\n",Cip,Cport);
		esp_print(obj,"AT+CIPSTART=\"UDP\",\"%s\",%s\r\n",Cip,Cport);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
	
	rt_kprintf("[Success]\r\n");
	osDelay(1000);
	obj->state=ESP_LINKING;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
void esp_MQTT_Client_Init(
	_esp obj,
	const char* Sname,
	const char* Spswd,
	const char* Cip,
	const char* Cport,
	const char* mqtt_ID,
	const char* mqtt_user,
	const char* mqtt_psw){
	
	osDelay(2000);
		
	while(1){
		rt_kprintf("Set WIFI Mode to STA\r\n");
		esp_print(obj,"AT+CWMODE=1\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	rt_kprintf("Reset\r\n");
	esp_print(obj,"AT+RST\r\n");
	osDelay(2000);
	
	while(1){
		rt_kprintf("Join the WIFI\r\n");
		esp_print(obj,"AT+CWJAP=\"%s\",\"%s\"\r\n",Sname,Spswd);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
		
	while(1){
		rt_kprintf("MUX is 0\r\n");
		esp_print(obj,"AT+CIPMUX=0\r\n");
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	
	while(1){
		rt_kprintf("Set MQTT as %s-%s-%s\r\n",mqtt_ID,mqtt_user,mqtt_psw);
		esp_print(obj,"AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"s\",0,0,\"\"\r\n",mqtt_ID,mqtt_user,mqtt_psw);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
	
	while(1){
		rt_kprintf("Link MQTT as %s-%s\r\n",Cip,Cport);
		esp_print(obj,"AT+MQTTCONN=0,\"%s\",%s,0\r\n",Cip,Cport);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}

	rt_kprintf("[Success]\r\n");
	osDelay(1000);
	obj->state=ESP_LINKING;}
//----------------------------------------------------------------------------------------------------	
void esp_MQTT_PUSH(
	_esp obj,
	const char* title,
	const char* msg){

	
	while(1){
		esp_print(obj,"AT+MQTTPUB=0,\"%s\",\"%s\",0,0\r\n",title,msg);
		if(rt_sem_take(obj->semaphore_OK,5000) == 0)break;}
	}
//----------------------------------------------------------------------------------------------------	
void esp_MQTT_SUB(
	_esp obj,
	const char* title){
	while(1){
		esp_print(obj,"AT+MQTTSUB=0,\"%s\",1\r\n",title);
		if(rt_sem_take(obj->semaphore_OK,1000) == 0)break;}
	}
//----------------------------------------------------------------------------------------------------		
////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------
extern _esp wire_Eye;

void bsp_MQTT_Init(void){
	u8 list[128]={0};
	for(u32 i=0;i<Reg_ENUM_SIZE;i++){
		rt_kprintf("[%d/%d]",i,i<Reg_PAGE_SIZE?0:1);
		sprintf((char*)list,"%d/%d",i,i<Reg_PAGE_SIZE?0:1);
		esp_MQTT_SUB(wire_Eye,(const char*)list);}
	rt_kprintf("\r\nLOAD SUCCESS!\r\n");}

void bsp_MQTT_msgpush(_esp obj,int enu,int group,short value){
	static char str[32]={0};
	static char val[32]={0};
	sprintf(str,"%d/%d",enu,group);
	sprintf(val,"%hd",value);
	esp_MQTT_PUSH(obj,str,val);
	//rt_kprintf("%s-%s\r\n",str,val);
	return;}
//----------------------------------------------------------------------------------------------------		
u32 parseMQTTMessage(_esp obj,const char *str){
    return sscanf(str, "+MQTTSUBRECV:0,\"%[^\"]\",%u,%[^\n]", obj->title, &obj->value, obj->msg);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	常用
void esp_CIPSEND_With_ID(_esp obj,u32 id,u8* buff,u32 len){
	esp_print(obj,"AT+CIPSEND=%d,%d\r\n",id,len);
	osDelay(100);
	obj->transmit(buff,len);}

void esp_CIPSEND_Without_ID(_esp obj,u8* buff,u32 len){
	esp_print(obj,"AT+CIPSEND=%d\r\n",len);
	obj->transmit(buff,len);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
const char* findSubstring(const char* haystack, const char* needle, uint32_t limit) {
    if (*needle == '\0') return haystack;
    while (*haystack != '\0' && limit > 0) {
        const char* h = haystack;
        const char* n = needle;
        while (*n != '\0' && *h == *n)h++,n++;
        if (*n == '\0')return haystack;
        haystack++;
        limit--;}
    return NULL;}
//----------------------------------------------------------------------------------------------------
int esp_print(_esp obj,const char* format, ...) {
	u32 res;																//	返回状态码
	va_list args;															//	不定长变量
	va_start(args, format);													//	初始化不定长变量
	res=vsprintf((char*)(obj->TX_buff),(const char*)format, args);			//	组合
	obj->transmit((obj->TX_buff), strlen((const char*)(obj->TX_buff)));		//	发送
	va_end(args);															//	收尸
	return res;}
//////////////////////////////////////////////////////////////////////////////////////////////////////
