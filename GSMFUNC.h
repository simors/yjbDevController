
#ifndef __GSMFUNC_H__
#define __GSMFUNC_H__

enum {	eAT=1,		eTSIMINS,	eSeeCPIN, eCPAS, 	eCSQ, 	eATE0,	eATH,
				eCNMI, 	eCMGF1,  	eCMGR, 	eCMGD,  			
				eCMGF0, 			eCMGS,				eTxMsgDat, 	eCMGDALL,
				eZPPPOPEN,	eSeeZDNSSERV,		eSetZDNSSERV,		
				eZDNSGETIP, 	eZIPSETUP, 	eZIPSEND,		eTxTcpDat,
				eZPPPOPENU,	eSeeZDNSSERVU,	eSetZDNSSERVU,	
				eZDNSGETIPU, 	eZIPSETUPU,	eZIPSENDU,	eTxUdpDat,
				eZIPCLOSE, 	eZIPCLOSEU,		eZPWROFF,
				eEnd
		};
 
uchar idata atcmd[15]={	eAT,eATE0,eTSIMINS,eCPAS,eSeeCPIN,eCNMI,};
											
uchar code* code TESTIP=""; //"120.24.179.213"
uchar code* code DNS="\"www.yunkongs.com\"";
uchar code* code PORT="8089";		

uchar xdata rxbuf[500]="";
uchar xdata msgdis=0,tcpdis=0,udpdis=0;
uchar xdata ucTxSpaceT=0; 
uchar xdata ucRxT=0;
uint xdata nullpos=0;
uint rxId;

uchar xdata ucRxdTOver=0;
uchar xdata tcpdat[500]="\r";
uchar xdata ucRssi=0;	

extern uchar idata rxMsgId[][4];
extern uchar idata tcptype[];

bit bRxPro;

void QueuePro(uchar cmd);
void Append(uchar d);
uint Len(uchar* p);
uint FindString(uint startpos,uchar* p,uint strlen);
uint GetDigitalStr(uint pos,uchar* from,uchar xdata* to);
uchar GetSMSMsg(uchar xdata* to,uchar d);
void LoadSendSMS(uchar* tel,uchar* str); 

void TxdLoad(void);
void RxdPro(void);	
void NextTcp(void);
void TcpApp(uchar d);


#include "hz.h"	
 uchar code hzsectorlen=sizeof(hzsector)/2;
 uchar code hznum=sizeof(hz)/sizeof(hz[0]);

#endif