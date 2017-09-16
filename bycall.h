 
#define RXTIME {if(ucRxT) if(!--ucRxT) {rxbuf[rxId]='\0'; nullpos=rxId; rxId=0; bRxPro=1;}}
#define TXSPACET {if(ucTxSpaceT>1) ucTxSpaceT--;} 

uchar xdata msgtel[15]="";
uchar xdata msgdat[142];


uchar xdata mid[13],pin[7];		

uchar xdata tempbuf[200];

uchar xdata phone[8][13];
uchar xdata phonenum=0;
uchar xdata phoneid[8];

uchar xdata rxSmsTel[15];	

uchar xdata year[5]="",month[3]="",day[3]="",hour[3]="",mintue[3]="",sec[3]="";
uint xdata uiRT;
uchar xdata moneydate[9]="";

bit bNoCard;
bit bNoModel;
bit bPinAck;

#include "txsms.h"
#include "rdsms.h" 
#include "tcp.h"


void NextSend(uchar t)
{ QueuePro(t); ucTxSpaceT=TT(400);}

void PhonePro(void)
{ uchar i,t;
	t=0; for(i=0;i<8;i++) if(phone[i][0]) {phoneid[t]=i; t++;}
	phonenum=t;
}

void RxTimeOver(void)
{ static xdata uchar oldcmd=0,num=0;
	if(ucRxdTOver)
		if(!--ucRxdTOver)
			{ ucTxSpaceT=1;
				if(msgdis==1 || tcpdis==1 || udpdis==1) num++;
				else if(*atcmd==oldcmd) {if(!num) num=1; num++;}
				else num=0; 
				oldcmd=*atcmd;

				if(num>=3)
					{ num=0;
						if(msgdis==1) msgdis=0;
						if(tcpdis==1) {tcpdis=0; if(tcptype[0]==ePinP) TcpApp(ePinP);}
						if(udpdis==1) udpdis=0;
						switch(*atcmd) 
							{ case eAT: bNoModel=1; break;
								case eTSIMINS: bNoCard=1; break;
							}
						NextSend(0);
					}
				else
					{ if(msgdis==1) NextSend(eCMGF0);
						else if(tcpdis==1) NextSend(eZPPPOPEN);
						else if(udpdis==1) NextSend(eZPPPOPENU);
					}
			}
}

void RTSData(void)
{	
	sprintf(stmp1,"%.1f",(float)iTmp1/10);
	//sprintf(stmp2,"%.1f",(float)iTmp2/10); //for NWK-380-04
	//sprintf(shum,"%u",(uint)ucHum); //for NWK-380-03	
	sprintf(sA,"%u",(uint)ucCur[0]);
	sprintf(sB,"%u",(uint)ucCur[1]);
	sprintf(sC,"%u",(uint)ucCur[2]);
}

uchar code one[]={1,2,4,8,16,32,64,128};
void RdWarn(void)
{ static uchar xdata oldWarn=0;
	static uchar xdata oldwn=0,oldwn2=0,oldwn3=0;
	uchar i,t;
	bit bincw,bdecw;

	if(ucOLT==0xff) bOLLock=1;
	else bOLLock=0;

	if(!ucSenErr[0]) {bTmp1Open=0; bTmp1Short=0;}
	else if(ucSenErr[0]==1) {bTmp1Open=1; bTmp1Short=0;}
	else {bTmp1Open=0; bTmp1Short=1;}
	 
	if(!ucSenErr[1]) {bTmp2Open=0; bTmp2Short=0;}
	else if(ucSenErr[1]==1) {bTmp2Open=1; bTmp2Short=0;}
	else {bTmp2Open=0; bTmp2Short=1;} 

	if(!ucHumSenErr) {bHumOpen=0; bHumShort=0;}
	else if(ucHumSenErr==1) {bHumOpen=1; bHumShort=0;}
	else {bHumOpen=0; bHumShort=1;}

	if(ubWarn || ubWarn2 || ubWarn3)
		{ for(i=0;i<8;i++) if(ubWarn&(1<<i)) {t=i+1; break;}
			if(i==8) for(i=0;i<8;i++) if(ubWarn2&(1<<i)) {t=i+9; break;}
			if(i==8) for(i=0;i<2;i++) if(ubWarn3&(1<<i)) {t=i+17; break;}
			ucWarn=t;
		}
	else ucWarn=0;
	if(!ucSmsWarn) if(ucWarn!=oldWarn) {oldWarn=ucWarn; if(ucWarn){RTSData(); ucSmsWarn=phonenum*2; smswid=ucWarn;}}
	 
	if(!*tcpdat)
	if(ubWarn^oldwn || ubWarn2^oldwn2 || ubWarn3^oldwn3)
		{ bincw=0; bdecw=0; RTSData();
			t=ubWarn^oldwn;
			for(i=0;i<8;i++)
				if(t&one[i]) {netwid[i]=1; if(oldwn&one[i]) bdecw=1; else bincw=1;}
				else netwid[i]=0;

			t=ubWarn2^oldwn2;
			for(i=0;i<8;i++)
				if(t&one[i]) {netwid[i+8]=1; if(oldwn2&one[i]) bdecw=1; else bincw=1;}
				else netwid[i+8]=0;

			t=ubWarn3^oldwn3;
			for(i=0;i<2;i++)
				if(t&one[i]) {netwid[i+16]=1; if(oldwn3&one[i]) bdecw=1; else bincw=1;}
				else netwid[i+16]=0;

			if(bincw) TcpApp(eWarnP);	
			if(bdecw) TcpApp(eDelWarnP);

			oldwn=ubWarn; oldwn2=ubWarn2; oldwn3=ubWarn3;
		}
}


void TxdProcess(void)
{ static uchar xdata oldmsgdis=0;
	static bit bOnce=1;

	if(oldmsgdis && !msgdis) *msgtel=0;
	oldmsgdis=msgdis;

	if(!*msgtel)
		if(*atcmd<eCMGF1 || *atcmd>eTxMsgDat)
			if(ucT01!=0)
				{ 
					if(uc_CS_) Sms_CS_Load();
					else if(uc_CY_) Sms_CY_Load();
					else if(uc_CH_) Sms_CH_Load();
					else if(uc_CL_) Sms_CL_Load();
					else if(uc_CP_) Sms_CP_Load();
					else if(uc_CM_) Sms_CM_Load(); 
					else if(uc_OFF_) Sms_OFF_Load();
					else if(uc_ON_) Sms_ON_Load();
					else if(uc_WH_) Sms_WH_Load();
					else if(ucSmsWarn) SmsWarnLoad();
					else if(ucSmsRTS) SmsRtsDatLoad();
					else if(*rxMsgId[0]) Append(eCMGF1);
				}
			else if(*rxMsgId[0]) Append(eCMGDALL);
	if(*msgtel && !msgdis) {msgdis=2; LoadSendSMS(msgtel,msgdat);}


	if(!*tcpdat)
		if(*tcptype)
			if(LoadTcpDat()) Append(eZPPPOPEN);
			else NextTcp();
		else if(_testbit_(bOnce)) Append(eZIPSETUPU);
}