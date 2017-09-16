
#define uchar unsigned char
#define uint unsigned int	
#define ulong unsigned long
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#define TCNT 2
#define LTNT 100 	 
#include "STC15W4Kxx.h"	 
#include "TM1640.h"	
#include "R3950_5K.h"	
#include "GSMFUNC.h"	

#define TT(t) ((uint)t/TCNT)
#define LTT(t) ((uint)t/LTNT)
	

#define INIT_ADC (P1ASF=0x9f, ADC_CONTR=0x80)
#define YJJDQ 	P0_3 //压机
#define HSJDQ 	P0_1 //化霜
#define FJJDQ 	P0_2 //风机
#define JSJDQ 	P2_6 //加湿
#define QSJDQ 	P2_5 //除湿
#define BYJDQ 	P2_4 //备用
#define BUZZER 	P2_7

uchar xdata val=0;
										 
uchar xdata gsmInitT=LTT(8000);
uchar xdata ucStartT=LTT(3000);
uchar xdata ucKeyX=0,ucKeyT=0,ucKLen;
uchar xdata ucSet=0,ucEnSetT=0; 
uint xdata sert=0;
uchar xdata ucFSet=0;
uchar xdata ucBellT=0,ucBellNum=0;

uchar xdata ucRun=0x24;
uint xdata uiYJWorkT=0,uiYJStopT=0;
uint xdata uiYJRunAllT=0,uiHSPeriod=0,uiDSTime=0;
uchar xdata ucHSTime=0;
uint xdata uiFJT=0;
uchar xdata ucFJId=0;
uint xdata ucTmp1HT=0; uchar xdata ucTmp1LT=0;
uchar xdata ucTmp2HT=0;
uchar xdata ucHumHT=0,ucHumLT=0;

uint ucOLT=0;
uchar xdata ucLPT=0;
uint xdata ui1Hour=0;
uint xdata uiHourV=0,uiMinV=0; 	
uchar xdata ucWarn=0;

bit bEnShowUpdata,bFlash;
bit bEnDataOut;
bit bYJ,bHS,bFJ,bJS,bQS;
bit bHSEnable;
bit bEnTmp1HWarn;
bit bOFF;
bit bAdj;
bit bDatChange,bSaveDat;
bit bShowCurHum; //0-cur, 1-hum
bit bDisWarnBell;
bit bPressMoney;
bit bIs380v=1;

uchar bdata ubWarn;
sbit bTmp1HWarn=ubWarn^0;
sbit bTmp1LWarn=ubWarn^1;
sbit bTmp1Open=ubWarn^2;
sbit bTmp1Short=ubWarn^3;
sbit bTmp2HWarn=ubWarn^4;
sbit bTmp2Open=ubWarn^5;
sbit bTmp2Short=ubWarn^6;
sbit bHumOpen=ubWarn^7;
uchar bdata ubWarn2;
sbit bHumShort=ubWarn2^0;
sbit bHumHWarn=ubWarn2^1;
sbit bHumLWarn=ubWarn2^2;
sbit bOLLock=ubWarn2^3; //sbit bOLWarn=ubWarn2^3;
sbit bLPWarn=ubWarn2^4;
sbit bPwrLP=ubWarn2^5; //E14
sbit bPOE=ubWarn2^6; //E15
sbit bE16=ubWarn2^7;
uchar bdata ubWarn3;
sbit bE17=ubWarn3^0;
sbit bE18=ubWarn3^1;


int iTmp1,iTmp2;
uchar xdata ucHum=0;					 
uchar  ucSenErr[2];
uchar  ucCur[3];
uchar  ucOLNum;
uchar  ucHumSenErr;
uint xdata uiAdj[3]={230,230,230};
uint xdata uiFltOut[6];
uint xdata aAD=0,bAD=0,cAD=0;

uchar xdata ucZJ=0;
uchar xdata ucCur6s=0;
uchar xdata watchhs=0;
uchar xdata ucXWarnT=0;
						
#define BCD0 	P5_4 
#define BCD1 	P3_3
#define BCD2 	P1_6
#define BCD3 	P1_5

#define WD_K 			2 //温度设定
#define HS_K 			1 //化霜设定
#define DL_K  		0 //电流设定
#define SET_K 		3 //设置/解锁
#define INC_K  		9 //增加/制冷
#define DEC_K  		8 //减小/化霜

uchar bdata ubBCD=0x0f;
sbit bBCD0=ubBCD^0;	
sbit bBCD1=ubBCD^1;
sbit bBCD2=ubBCD^2;
sbit bBCD3=ubBCD^3;

										
#include "code.h" 
#include "SetPara.h"
#include "bycall.h"
#include "Display.h"

#define SN 10
uint xdata iaAD[6][SN];
#define AN 20
uint xdata iaVal[6][AN];

#define TN 50
uint xdata aTmp[2][TN];

uchar code chad[]={4,3,0,1,2,7}; //4-库温，3-管温，0-I1, 1-I2, 2-I3
void AnalogDigitalChange(void)
{ static  uchar ucCH;
	xdata uint it,ik;
	xdata uchar t,m,k;
							
	ucCH++; ucCH%=6;
	it=StcAdc(chad[ucCH]);
	it<<=2;
	it|=ADC_RESL;
			
	ik=it;
	for(t=0;t<SN-1;t++)
		{ iaAD[ucCH][t]=iaAD[ucCH][t+1]; 
			it+=iaAD[ucCH][t];
		}
	iaAD[ucCH][SN-1]=ik;
	it=it/SN;
	
	if(ucCH<2)
		{ for(t=0;t<UBTTAB-1;t++) if(it>rtAdTab[t+1]) break; 
			it=(uint)t*10 + (rtAdTab[t]-it)*10/(rtAdTab[t]-rtAdTab[t+1]);
		}
	else if(ucCH==5) it=(ulong)it*500/3069;
					 
	ik=it;
	for(t=0;t<AN-1;t++)
		{ iaVal[ucCH][t]=iaVal[ucCH][t+1]; 
			it+=iaVal[ucCH][t];
		}
	iaVal[ucCH][AN-1]=ik;
	it=it/AN;	

	if(ucCH>=2) uiFltOut[ucCH]=it;
	else
	if(it<=1*10) ucSenErr[ucCH]=1;
	else
		if(it>=(UBTTAB-1)*10) ucSenErr[ucCH]=2;
		else
			if(it>2*10 && it<(UBTTAB-2)*10)
				{ ucSenErr[ucCH]=0;
					if(it<3*10) it=3*10;
					else if(it>(UBTTAB-3)*10) it=(UBTTAB-3)*10;
					//uiFltOut[ucCH]=it;
							 
					ik=it;
					for(t=0;t<TN-1;t++)
						{ aTmp[ucCH][t]=aTmp[ucCH][t+1]; 
							it+=aTmp[ucCH][t];
						}
					aTmp[ucCH][TN-1]=ik;
					uiFltOut[ucCH]=it/TN;	
				}	

	ucSenErr[1]=0; //for NWK-380-04
				
	if(ucStartT>=LTT(1000)) return;
			
	if(_testbit_(bEnDataOut))
		{ if(!ucSenErr[0]) iTmp1=uiFltOut[0]-530+iY06;
			if(!ucSenErr[1]) iTmp2=uiFltOut[1]-530;
			ucCur[0]=(ulong)uiFltOut[2]*30/uiAdj[0];
			ucCur[1]=(ulong)uiFltOut[3]*30/uiAdj[1];
			ucCur[2]=(ulong)uiFltOut[4]*30/uiAdj[2];
			if(bAdj) {aAD=uiFltOut[2]; bAD=uiFltOut[3]; cAD=uiFltOut[4];}

			/* //for NWK-380-03
			if(uiFltOut[5]>=120) ucHumSenErr=1;
			else if(uiFltOut[5]<=95) ucHumSenErr=0;

			if(!ucHumSenErr)
				{ it=uiFltOut[5]+cL06;
					if(it>=0x8000) ucHum=0;
					else ucHum=it;
					if(ucHum>99) ucHum=99;
				}*/
		}
				
	if(ucStartT) return;
	//----------------------------

	if(bOFF) {bYJ=bHS=bFJ=bJS=bQS=0; ucRun=0; ucFJId=0; ucOLT=0;}
	else if(bPressMoney && ucP05==2) {bYJ=bHS=bFJ=bJS=bQS=0; ucRun=0;}
	else
	{
		if(ucOLT==1 || ucOLT==0xff || bLPWarn) ucRun=0;
		else
		if(!ucSenErr[0])
			if(bPressMoney && ucP05==1) {if(ucRun<=0x10) {ucRun=8; ucFJId=0;}}
			else
				{ if(!ucY10 || !bPinPass) it=iY01;
					else
						if(uiY11<uiY12)
							if(uiRT>=uiY11 && uiRT<uiY12) it=iY13;
							else it=iY01;
						else
							if(uiY11>uiY12)
								if(uiRT>=uiY12 && uiRT<uiY11) it=iY01;
								else it=iY13;
							else it=iY01;
															
					if(ucRun==7) ucRun=0;
					if(!ucRun) if(iTmp1>=(int)it+iY02) ucRun=1;
					if(ucRun<=0x10) if(iTmp1<=(int)it) {ucRun=0; bEnTmp1HWarn=1;}
		
					if(iTmp1>=(int)it+iY02+iY07) {if(bEnTmp1HWarn) if(!ucTmp1HT) ucTmp1HT=ucY14*600+1;}
					else {ucTmp1HT=0; bTmp1HWarn=0;}
					if(iTmp1<=(int)it-iY08) {if(!ucTmp1LT) ucTmp1LT=LTT(3000);}
					else {ucTmp1LT=0; bTmp1LWarn=0;}
				}
		else
			{	ucTmp1HT=ucTmp1LT=0; bTmp1HWarn=bTmp1LWarn=0;
				if(ucRun<=0x10) {ucRun=7; ucFJId=0;}
			} 
			
		if(!ucSenErr[1])
			{ if(ucRun==0x21) if(iTmp2>=iH04) ucRun=0x22;
				if(iTmp2>=iH04+iH07) {if(!ucTmp2HT) ucTmp2HT=LTT(3000);}
				else {ucTmp2HT=0; bTmp2HWarn=0;}
			}
		else {ucTmp2HT=0; bTmp2HWarn=0;}
		//----------------------------
		
		if(ucOLT==1) if(uiYJStopT>=uiY09*LTT(1000)) ucOLT=0;
	
		if(!ucD02) {ucOLT=0; ucOLNum=0;}
		else
			if(ucOLT!=0xff)
				if(uiYJWorkT>=LTT(5000))
					if(ucCur[1]>=ucD02) {if(!ucOLT) ucOLT=(uint)ucD03*10+1;}
					else ucOLT=0;	 
	
		t=0; m=0;
		for(k=2;k<5;k++) {if(uiFltOut[k]>20) t++; 	if(uiFltOut[k]<10) m++;}  
		if(t==2 && m==1) {if(!ucLPT && !bLPWarn) ucLPT=LTT(2000);}
		else ucLPT=0;
	
		if(!ucD01) {ucCur6s=0; bE16=bE17=0;}
		else
			if(bYJ)
				if(uiFltOut[3]<=10) {if(ucCur6s<=0x80) ucCur6s=0x80+LTT(6000);}
				else ucCur6s=0x80;
			else
				if(uiFltOut[3]>=10) {if(!ucCur6s || ucCur6s>=0x80) ucCur6s=LTT(6000);}
				else ucCur6s=0;
		//----------------------------
	
		/* //for NWK-380-03
		if(ucHumSenErr) {bJS=bQS=0; bHumHWarn=bHumLWarn=0; ucHumHT=ucHumLT=0;}
		else
			{ if(ucHum>=ucL01+ucL02) bQS=1;
				else if(ucHum<=ucL01) bQS=0;
				if(ucHum<=ucL01-ucL03) bJS=1;
				else if(ucHum>=ucL01) bJS=0;
	
				if(ucHum>=ucL01+ucL02+ucL04) {if(!ucHumHT) ucHumHT=LTT(2000);}
				else {ucHumHT=0; bHumHWarn=0;}	
				if(ucHum<=ucL01-ucL03-ucL05) {if(!ucHumLT) ucHumLT=LTT(2000);}
				else {ucHumLT=0; bHumLWarn=0;}
			}*/
	}
}

void Work(void)
{ static uchar oldrun;

	if(ucRun==7)
		if(!ucY03) bYJ=0;
		else
			{ if(uiYJStopT>=(uint)ucY05*LTT(60000)) {bYJ=1; bFJ=1;}
				if(uiYJWorkT>=(uint)ucY04*LTT(60000)) {bYJ=0; bFJ=0;}
			}
			
	if(ucRun==8)
		{ if(uiYJStopT>=(uint)ucP07*LTT(60000)) bYJ=1;
			if(uiYJWorkT>=(uint)ucP04*LTT(60000)) bYJ=0;
		}

	if(ucRun==1) if(uiYJStopT>=uiY09*LTT(1000)) ucRun=2;

	if(ucRun!=oldrun)
		{ oldrun=ucRun;
			switch(ucRun)
				{ case 0: bYJ=0; break;
					case 2: bYJ=1; ucFJId=1; break;

					case 0x20: bFJ=0;
							bYJ=ucH01; ucHSTime=0; uiHSPeriod=0; uiYJRunAllT=0; ucRun=0x21;
							if(!ucSenErr[1]) if(iTmp2>=iH04) ucRun=0x22; 		 
							if(!bHSEnable) ucRun=0;
							break;
					case 0x22: uiDSTime=0; bYJ=0; ucRun=0x23; if(!ucH05) ucRun=0x24; break;
					case 0x24: ucRun=0; break; 	
				}
		}

	if(ucRun<0x10)
		if(!ucF01)
			{ if(ucFJId==1) if(uiYJWorkT>=(uint)ucF04*LTT(6000)+1) {bFJ=1; ucFJId=2;}
				if(ucFJId==2) if(uiYJStopT>=(uint)ucF05*LTT(6000)+1) {bFJ=0; ucFJId=3; uiFJT=0;}
			}
		else { ucFJId=0; if(iTmp2<iTmp1) bFJ=1; else if(iTmp2>=iTmp1+10) bFJ=0;}

	if(bTmp1LWarn || (ubWarn2&0xf8) || ubWarn3) {bYJ=bFJ=bHS=0; ucRun=ucFJId=0;}
	
	if(ucRun && ucRun<=10)
		{ if(bYJ) {bZLLed=1; yjztV=2;}
			else {bZLLed=bFlash; yjztV=1;}
		}
	else { bZLLed=0; yjztV=0;}

	/*if(ucRun>0x10) {bFJLed=0; fjztV=0;}
	else
	if(ucFJId==1) {bFJLed=bFlash; fjztV=1;}
	else
		if(bFJ) {bFJLed=1; fjztV=2;}
		else {bFJLed=0; fjztV=0;}*/ //for NWK-380-04
		
	if(ucRun==0x23) { bHSLed=bFlash; bHS=0; hsztV=1;}
	else if(ucRun==0x21) {bHSLed=bHS=1; hsztV=2;}
				else {bHSLed=bHS=0; hsztV=0;}

	jsztV=(uchar)bJS; qsztV=(uchar)bQS;

	if(!ucZJ) {YJJDQ=bYJ; HSJDQ=bHS; /*FJJDQ=bFJ; //for NWK-380-04*/ JSJDQ=bJS; QSJDQ=bQS;}
}

bit bLongT;
uchar  ucAPN,ucBPN,ucCPN;
uchar  ucBCV[2];
void T0OVR(void) interrupt TF0_VECTOR using 1
{ static  uchar ucLongT=TT(LTNT); 
	static  uchar ucAX,ucBX,ucCX;
	static  uchar ucAWT,ucBWT,ucCWT;
	
	bEnShowUpdata=1;
	if(ucKeyX==1) if(!--ucKeyT) ucKeyX=2;
	if(!--ucLongT) {ucLongT=TT(LTNT); bLongT=1;}
	if(ucBellT) ucBellT--;
	if(sert>1) if(--sert==1) ucKeyX=9;
	if(ucKey05s) ucKey05s--;
	
	TXSPACET;
	RXTIME;

		 
	if(bIs380v)
		{ if(ucAX==1) if(!--ucAWT) ucAX=2;
			if(ucBX==1) if(!--ucBWT) ucBX=2;
			if(ucCX==1) if(!--ucCWT) ucCX=2;
		
			if(!P2_2)
				{ if(!ucAX) {ucAWT=1; ucAX=1;}
					else
						if(ucAX==2)
							{ if(ucStartT && !bPOE) if(ucBCV[0]==0xc && ucBCV[1]==0xb) bPOE=1;
								ucAX=3; ucBCV[0]=0; ucBCV[1]=0; ucAPN=0;
							}
				}
			else ucAX=0;
		
			if(!P2_3)
				{ if(!ucBX) {ucBWT=1; ucBX=1;}
					else if(ucBX==2) {ucBX=3; ucBPN=0; if(!ucBCV[0]) ucBCV[0]=0xb; else ucBCV[1]=0xb;}
				}
			else ucBX=0;
		
			if(!P2_0)
				{ if(!ucCX) {ucCWT=1; ucCX=1;}
					else if(ucCX==2) {ucCX=3; ucCPN=0; if(!ucBCV[0]) ucBCV[0]=0xc; else ucBCV[1]=0xc;}
				}
			else ucCX=0;
		}
}

void LongTime(void)
{ static uchar xdata ucSecFlash=LTT(500);
	static uchar xdata uc6s=LTT(6000);
	static uchar xdata uc3s=LTT(3000);
	static uchar xdata uc1m=10;
		
	if(ucKeyX==0x80) if(!--ucKeyT) ucKeyX=0x81;
	if(ucEnSetT) if(!--ucEnSetT) {ucSet=0; ucFSet=0;}
	if(ucBellNum) ucBellNum--;
	
	if(!--ucSecFlash) 
		{ ucSecFlash=LTT(500); bFlash=~bFlash; bEnDataOut=1;
			ucShowABC++; ucShowABC%=12;
			if(pinNoteT) if(!--pinNoteT) pinNoteTyp=0;
			if(pinAnswerT) if(!--pinAnswerT) {pinNoteTyp=1; pinNoteT=6; TcpApp(ePinP);}
			if(watchhs) watchhs--;
			
			if(ucZJ>1)
				{ ucZJ--;
					switch(ucZJ)
					{ case 12: YJJDQ=0; HSJDQ=1; break;
						case 11: HSJDQ=0; FJJDQ=1; break;
						case 10: FJJDQ=0; JSJDQ=1; break;
						case 9: JSJDQ=0; QSJDQ=1; break;
						case 8: QSJDQ=0; BYJDQ=1; break;
						case 7: BYJDQ=0; break;
					}
				}
		}

	if(bYJ) {uiYJStopT=0; if(~uiYJWorkT) uiYJWorkT++;}
	else {uiYJWorkT=0; if(~uiYJStopT) uiYJStopT++;}

	if(ucFJId==3)
		{ uiFJT++;
			if(!bFJ) {if(uiFJT>=(uint)ucF02*LTT(60000)) {uiFJT=0; if(ucF03) bFJ=1;}}
			else {if(uiFJT>=(uint)ucF03*LTT(60000)) { uiFJT=0; if(ucF02) bFJ=0;}}
		}

	if(ucOLT!=0xff)
		{ if(!ucOLNum) ui1Hour=0;
			else if(++ui1Hour==3600) {ui1Hour=0; ucOLNum=1;}
			if(ucOLT>1) if(--ucOLT==1) if(++ucOLNum>=ucD04) ucOLT=0xff;
		}
	if(ucLPT)if(!--ucLPT) bLPWarn=1;

	if(ucTmp1HT)if(!--ucTmp1HT) bTmp1HWarn=1;
	if(ucTmp1LT)if(!--ucTmp1LT) bTmp1LWarn=1;
	if(ucHumHT)if(!--ucHumHT) bHumHWarn=1;
	if(ucHumLT)if(!--ucHumLT) bHumLWarn=1;
	if(ucTmp2HT)if(!--ucTmp2HT) bTmp2HWarn=1;

	if(ucCur6s>0x80) {if(--ucCur6s==0x80) bE16=1;}
	else if(ucCur6s) if(!--ucCur6s) bE17=1;
	if(ucXWarnT) if(!--ucXWarnT) bE18=1;
	
	if(ucStartT) ucStartT--;
	
	if(!--uc6s)
		{ uc6s=LTT(6000);
			if(bHSEnable)
				{ if(ucRun<0x20)
						{ uiHSPeriod++;
							if(bYJ) uiYJRunAllT++;
							if(!ucH06) {if(uiHSPeriod>=(uint)ucH02*600) ucRun=0x20;}
							else if(uiYJRunAllT>=(uint)ucH02*600) ucRun=0x20;
						}
					if(ucRun==0x21)
						{ ucHSTime++;
							if(ucHSTime>=(uint)ucH03*10) ucRun=0x22;
						}	 
					if(ucRun==0x23)
						{ uiDSTime++;
							if(uiDSTime>=(uint)ucH05*10) ucRun=0x24;
						} 
				}

			if(~uiHourV) uiHourV++;
			if(ucT02) if(uiHourV>=(uint)ucT02*600) {uiHourV=0; RTSData(); ucSmsRTS=phonenum*2;}
			if(~uiMinV) uiMinV++;
			if(bPinPass) if(ucT03) if(uiMinV>=(uint)ucT03*10) {uiMinV=0; RTSData(); TcpApp(eDataP);}
			if(!--uc1m)
				{	uc1m=10;
					if(!bPinAck) TcpApp(ePinP);
					TcpApp(eBeatP);
				}
		}
	
	if(!--uc3s)
		{ uc3s=LTT(3000); if(!gsmInitT) Append(eCSQ);
			if(uc3mLockK) uc3mLockK--;
		}

	if(gsmInitT) if(!--gsmInitT) ucTxSpaceT=1;
	RxTimeOver();

			
	if(bIs380v)
		if(ucBCV[0] || ucBCV[1])
		{ if(ucAPN<10) ucAPN++;
			if(ucBPN<10) ucBPN++;
			if(ucCPN<10) ucCPN++;
			if(ucAPN==10 || ucBPN==10 || ucCPN==10) bPwrLP=1;
			else bPwrLP=0;
		}
}

#define GSMRET P5_5
uchar xdata oldset=0;
bit bOldOFF;
void main(void)
{ uchar t,i; uchar xdata* p;

	GSMRET=0;	
	YJJDQ=HSJDQ=FJJDQ=JSJDQ=QSJDQ=BYJDQ=0;
	INIT_ADC;

	mid[0]=0x31; mid[1]=0x30; mid[2]=0x30; mid[3]=0x31; //mid[4]=0x30; mid[5]=0x31;
	mid[4]=*(uchar code*)0xdff1; mid[5]=*(uchar code*)0xdff2;
	mid[6]=*(uchar code*)0xdff3; mid[7]=*(uchar code*)0xdff4;  mid[8]=*(uchar code*)0xdff5;
	mid[9]=*(uchar code*)0xdff6; mid[10]=*(uchar code*)0xdff7; mid[11]=*(uchar code*)0xdff8; mid[12]=0;
	//pin=每位分别+073741再分别*258369再分别+mid[4/5] (mid[4/5]=1~99)
	pin[0]=((mid[6]-0x30+0)*2+((mid[4]-0x30)*10+mid[5]-0x30)) %10+0x30;
	pin[1]=((mid[7]-0x30+7)*5+((mid[4]-0x30)*10+mid[5]-0x30)) %10+0x30;
	pin[2]=((mid[8]-0x30+3)*8+((mid[4]-0x30)*10+mid[5]-0x30)) %10+0x30;
	pin[3]=((mid[9]-0x30+7)*3+((mid[4]-0x30)*10+mid[5]-0x30)) %10+0x30;
	pin[4]=((mid[10]-0x30+4)*6+((mid[4]-0x30)*10+mid[5]-0x30)) %10+0x30;
	pin[5]=((mid[11]-0x30+1)*9+((mid[4]-0x30)*10+mid[5]-0x30)) %10+0x30;
	pin[6]=0;
						
	P0M1=P0M0=0; P1M1=P1M0=0; P2M1=P2M0=0; P3M1=P3M0=0; P4M1=P4M0=0;
	P0M0=0x0e; P2M0=0xf0;

	if(!P3_1)
		{ for(t=0;t<255;t++) {_nop_();_nop_();}
			if(!P3_1)
				{ for(t=0;t<255;t++) {_nop_();_nop_();}
					if(!P3_1) bIs380v=0;
				}
		}

	if(RdEeprom(0x02,0)==0x5a) 
		for(t=0;t<sizeof(adr)/2;t++) {p=(uchar*)adr[t]; *p=RdEeprom(0x02,t*2+1); *(p+1)=RdEeprom(0x02,t*2+2);}
	
	for(t=0;t<8;t++) phone[t][0]=0;	
	if(RdEeprom(0x04,0)==0xcc)
		for(t=0;t<8;t++) for(i=0;i<13;i++) phone[t][i]=RdEeprom(0x04,t*13+i+1);

	for(t=0;t<sizeof(adr)/2;t++) para[t]=**(adr+t);
	inpw[4]=0;
		
	if(RdEeprom(0x06,7)==0xdc)
		{ uiAdj[0]=RdEeprom(0x06,1); uiAdj[0]<<=8; uiAdj[0]|=RdEeprom(0x06,2);
			uiAdj[1]=RdEeprom(0x06,3); uiAdj[1]<<=8; uiAdj[1]|=RdEeprom(0x06,4);
			uiAdj[2]=RdEeprom(0x06,5); uiAdj[2]<<=8; uiAdj[2]|=RdEeprom(0x06,6);
		}
		
	if(RdEeprom(0x08,0)==0xcc) for(t=0;t<8;t++) moneydate[t]=RdEeprom(0x08,t+1);


	TMOD=0x00;
	TH0=0xf1; TL0=0x99;
	TR0=1; ET0=1;
	
	AUXR1=0x40; //B7B6: 00 P3.0/1, 01 P3.6/7, 10 P1.6/7
	AUXR=T2R|S1ST2;
	T2L=-(uint)((22.1184*1000000)/48/115200); 
	T2H=-(uint)((22.1184*1000000)/48/115200)>>8;
	SCON=0x50; 
	TI=0;RI=0; PS=1;
	ES=1;
	EA=1;

	PackLeadPro();

	TcpApp(ePinP);
	TcpApp(eParaP);
	TcpApp(eDelAllWP);

	while(1)
		{	PhonePro();	
			if(_testbit_(bEnShowUpdata))
				{	if(!ucZJ) ToShowBuffer();
					else ToZJBuf();
					DataToTM1640Ram();
					ScaneKey();
				}
			if(ucKeyX==9) KeyProcess();
			AnalogDigitalChange(); 
			/*if(ucH02 && ucH03) bHSEnable=1;
			else {bHSEnable=0; if(ucRun>=0x20) ucRun=0x24;}*/  //for NWK-380-04

			if(!ucWarn) bDisWarnBell=0;
			if(ucBellNum)
				if(ucBellNum%2) BUZZER=1;
				else BUZZER=0;
			else
				if(ucWarn && !bDisWarnBell) BUZZER=bFlash;
				else BUZZER=ucBellT;

			if(ucWarn && !bDisWarnBell) BYJDQ=1;
			else BYJDQ=0;
			if(!ucStartT) Work();

			if(oldset && !ucSet) bDatChange=1;
			oldset=ucSet;

			if(_testbit_(bDatChange))
				for(t=0;t<sizeof(adr)/2;t++)
					if(para[t]!=**(adr+t))
						{	bSaveDat=1;
							for(t=0;t<sizeof(adr)/2;t++) para[t]=**(adr+t);
							TcpApp(eParaP);
							break;
						}

			if(_testbit_(bSaveDat)) Savedata();
			if(_testbit_(bSavePhone)) SavePhone();

			if(_testbit_(bLongT)) LongTime();
			
			bBCD0=BCD0; bBCD1=BCD1; bBCD2=BCD2; bBCD3=BCD3;
			if(!P2_1) {ucXWarnT=0; bE18=0;}
			else if(!ucXWarnT) ucXWarnT=LTT(2000);
			if(!ucStartT) RdWarn();

			if(bOFF^bOldOFF)
				{ bOldOFF=bOFF;
					if(bOFF) uc_OFF_=phonenum;
					else uc_ON_=phonenum;
				}
			
			TxdProcess();																							
			if(_testbit_(bRxPro)) RxdPro();
			if(!bNoCard && !bNoModel) if(ucTxSpaceT==1 && *atcmd) TxdLoad();
 
			if(!ucP04) bPressMoney=0;
			else
				if(*moneydate)
					{ sprintf(tempbuf,"%s%s%s",year,month,day);
						if(strcmp(tempbuf,moneydate)!=-1) bPressMoney=1;
						else bPressMoney=0;
					}
		}
}