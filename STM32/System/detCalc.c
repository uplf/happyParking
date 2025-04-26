#include "detCalc.h"



void PIDgroupInit(){

	//�Ƕ�PID
	UPPID.circleCalc=0;
	
	UPPID.P=0.1;
	UPPID.I=0;
	UPPID.D=0;

	UPPID.IntegralError=0;
	UPPID.LastError=0;
	UPPID.PrevError=0;
	UPPID.current=0;
}

void pidCalc(PIDgroup* G,int16_t* output)
{
  int16_t Outpid,SetPoint,NextPoint;                                        //��ǰ���
	int16_t pid[6];
	int8_t cur;
	
	SetPoint=G->current;
	NextPoint=G->target;
	int16_t LastError=G->LastError;
	int16_t PrevError=G->PrevError;
	int16_t IntegralError=G->IntegralError;
	
  int16_t iError=NextPoint-SetPoint;   	//��������
	if(G->circleCalc)CirCal(&iError);
	*output=G->P*iError+G->I*LastError+G->D*(PrevError-LastError);
	
  G->PrevError=LastError;                                      //�洢�������´μ���
  G->LastError=iError;
  G->IntegralError+=iError;

}

void CirCal(int16_t *Ang){
	if(*Ang>180)*Ang-=360;
	if(*Ang<-180)*Ang+=360;
}
void CirCalF(float *Ang){
	if(*Ang>180)*Ang-=360;
	if(*Ang<-180)*Ang+=360;
}
