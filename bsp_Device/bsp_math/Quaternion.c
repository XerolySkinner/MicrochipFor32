/*----------------------------------------------------------------------------------------------------
#	THIS FILE IS PART OF XEROLYSKINNER'S PROJECT
#	Quaternion - The core part of the project
#
#	THIS PROGRAM IS FREE SOFTWARE
#
#	Copyright (c) 2021 XerolySkinner
#	E-mail:ZABBCCCBBAZ@163.COM
#	QQ:2715099320
#
#	All rights reserved.
*/

/*----------------------------------------------------------------------------------------------------
	����:Quaternion
	ʱ��:20211229-2153
	����Ա:��Դ��
	˵��:��Ԫ�ػ���
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	ͷ�ļ�
#include "Quaternion.h"
#include "math.h"

#define		Kp 100.0f//��������֧�������������ٶȼ�/��ǿ��
//#define	Ki 0.002f//��������֧���ʵ�������ƫ�����ν�
#define		Ki 0.020f//��������֧���ʵ�������ƫ�����ν�
#define		halfT 0.005f//�������ڵ�һ��

float 		q0=0.1,q1=0.1,q2=0.1,q3=0.1;			//��Ԫ����Ԫ��,������Ʒ���
float 		exInt=0.1,eyInt=0.1,ezInt=0.1;			//��������С�������
float 		Yaw=0,Pitch=0,Roll=0;					//ƫ����,������,������
float		KalmanPitch;
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//	����
//	
float IMUupdate(float gx,float gy,float gz,float ax,float ay,float az){
	float norm;
	float vx,vy,vz;
	float ex,ey,ez;
	//����������
	norm=sqrt(ax*ax+ay*ay+az*az);
	ax=ax/norm;//��λ��
	ay=ay/norm;
	az=az/norm;
	//���Ʒ��������
	vx=2*(q1*q3-q0*q2);
	vy=2*(q0*q1+q2*q3);
	vz=q0*q0-q1*q1-q2*q2+q3*q3;
	//���������ͷ��򴫸��������ο�����֮��Ľ���˻����ܺ�
	ex=(ay*vz-az*vy);
	ey=(az*vx-ax*vz);
	ez=(ax*vy-ay*vx);
	//������������������
	exInt=exInt+ex*Ki;
	eyInt=eyInt+ey*Ki;
	ezInt=ezInt+ez*Ki;
	//������������ǲ���
	gx=gx+Kp*ex+exInt;
	gy=gy+Kp*ey+eyInt;
	gz=gz+Kp*ez+ezInt;
	//������Ԫ���ʺ�������
	q0=q0+(-q1*gx-q2*gy-q3*gz)*halfT;
	q1=q1+(q0*gx+q2*gz-q3*gy)*halfT;
	q2=q2+(q0*gy-q1*gz+q3*gx)*halfT;
	q3=q3+(q0*gz+q1*gy-q2*gx)*halfT;
	//��������Ԫ
	norm=sqrt(q0*q0+q1*q1+q2*q2+q3*q3);
	q0=q0/norm;
	q1=q1/norm;
	q2=q2/norm;
	q3=q3/norm;
	Pitch=asin(-2*q1*q3+2*q0*q2)*57.3;//pitch,ת��Ϊ����
	//Roll=atan2(2*q2*q3+2*q0*q1,-2*q1*q1-2*q2*q2+1)*57.3;//rollv
	//Yaw=atan2(2*(q1*q2+q0*q3),q0*q0+q1*q1-q2*q2-q3*q3)*57.3;//�˴�û�м�ֵ,ע��
	return Pitch;}
