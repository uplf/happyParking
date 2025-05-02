#include "detCalc.h"



void PIDgroupInit(){

	//角度PID
	UPPID.circleCalc=0;
	
	UPPID.P=1;
	UPPID.I=0.0005;
	UPPID.D=0.015;

	UPPID.IntegralError=0;
	UPPID.LastError=0;
	UPPID.PrevError=0;
	UPPID.current=0;
	UPPID.target=100;
}

void pidCalc(PIDgroup* G,int16_t* output)
{
  int16_t Outpid,SetPoint,NextPoint;                                        //当前误差
	int16_t pid[6];
	int8_t cur;
	
	SetPoint=G->current;
	NextPoint=G->target;
	int16_t LastError=G->LastError;
	int16_t PrevError=G->PrevError;
	int16_t IntegralError=G->IntegralError;
	
  int16_t iError=NextPoint-SetPoint;   	//增量计算
	if(G->circleCalc)CirCal(&iError);
	*output=G->P*iError+G->I*IntegralError+G->D*(PrevError-LastError);
	
  G->PrevError=LastError;                                      //存储误差，用于下次计算
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
void linePatrol(uint8_t endFlag,uint8_t dist){
	UPPID.target=dist;
	while(openMV2_mes!=endFlag){
		Delay_ms(UPSampleRate);
		UPPID.current=openMV1_mes;
		pidCalc(&UPPID,&UPLF_DIR);
		OLED_ShowNum(2,1,openMV1_mes,3);
		OLED_ShowSignedNum(3,1,UPLF_DIR,5);
		drive_setDir(UPLF_DIR);
	}
}