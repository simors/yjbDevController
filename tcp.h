

//包头部分: 1-控制器ID，2-控制器型号，3-支持的协议版本号
#define CTRLMODEL 		"1001000016" 	//控制器型号 NWK380-01
#define CTRLVER				"11"					//支持的协议版本号
#define DATA_PACK 		"00000901," 		//实时数据包
#define WARN_PACK 		"00000902," 		//报警数据包
#define PARA_PACK 		"00000903," 		//控制参数包
#define PIN_PACK			"00000904," 		//PIN验证包
#define BEAT_PACK			"00000905" 			//心跳包 (包头,00000905)
#define DELWARN_PACK	"00000906" 			//报警解除包
												

enum netpack {eDataP=1,eWarnP,eParaP,ePinP,eBeatP,eDelWarnP,eAnswerP,eDateP,eDelAllWP};


bit bPinPass;
uchar xdata pinNoteT=0,pinNoteTyp=0;
uchar xdata pinAnswerT=0;

/* 包头部分: 1-控制器ID，2-控制器型号，3-支持的协议版本号 */
uchar xdata packlead[46];
uchar xdata machineid[19];
uchar xdata rpacklead[42];
uchar xdata rleadchk=0;
 
uchar xdata revercod[10];
bit bTcpAnsOk;
	
//------------------------------------------------ 

void PackLeadPro(void)
{ uchar t;
	sprintf(machineid,"%06u%s",(uint)1,mid);

	t=sprintf(packlead,"%06u%s,",(uint)1,mid);
	t+=sprintf(packlead+t,"%06u%s,",(uint)2,CTRLMODEL);
	t+=sprintf(packlead+t,"%06u%s,",(uint)3,CTRLVER);

	t=sprintf(rpacklead,"%06u%s,",(uint)1,mid);
	t+=sprintf(rpacklead+t,"%06u%s,",(uint)8,pin);
	t+=sprintf(rpacklead+t,"%06u%s,",(uint)3,CTRLVER);
	
	t=0; while(rpacklead[t]) {rleadchk+=rpacklead[t]; t++;}
}

uint GetBreak(uint pos,uchar* to)
{ uint i=0;
	if(pos<Len(rxbuf) && rxbuf[pos]>=0x20)
		while(1)
			{ if(rxbuf[pos]==',' || rxbuf[pos]=='\r') {*(to+i)='\0'; break;}
				*(to+i++)=rxbuf[pos++];
			}
	if(!i) return 0;
	else return pos+1;
}

uchar DigLen(uchar* p)
{ uchar t;
	t=0;
	while(*(p)) {if(*p>=0x30 && *p<=0x39) t++; p++;}
	return t;
}

uint code mux[]={1000,100,10,1};
uint GetHex(uchar* p)
{ uint d; uchar t;
	bit bneg;
	bneg=0; d=0;
	if(*p=='-') {bneg=1; p++;}
	t=DigLen(p);
	if(t<=sizeof(mux)/2)
		{ t=sizeof(mux)/2-t;
			while(*p)
				{ if(*p>=0x30 && *p<=0x39) d+=(*p-48)*mux[t++];
					p++;
				}
			if(bneg) d=(d^0xffff)+1;
		}
	return d;
}

uint GetStr(uint pos,uchar xdata*p,uchar len)
{ 
	while(len--) *p++=rxbuf[pos++];
	*p=0;
	return pos;
}

void RxTcpDataPro(void)
{ uint xdata t,d; uchar xdata i,j,k;
	uint xdata m;
	uchar xdata a[11];
	bit bfloat;

	t=FindString(0,",",0);
	t=FindString(t,",",0);
	GetDigitalStr(t,rxbuf,tempbuf);
	if(strcmp(machineid,tempbuf)!=0) return;

	if(FindString(0,"000008003",0)) 
		{	bPinPass=1; pinNoteTyp=3; pinNoteT=6; pinAnswerT=0; ucBellNum=6;
			if(k=FindString(t,"000004",0))
				{ k=GetStr(k,year,4); k=GetStr(k,month,2); k=GetStr(k,day,2);
					k=GetStr(k,hour,2);  k=GetStr(k,mintue,2); GetStr(k,sec,2);
					sprintf(tempbuf,"%s%s",hour,mintue); uiRT=GetHex(tempbuf);
					bPinAck=1;
				}
			return;
		}
	if(FindString(0,"000008004",0)) {bPinPass=0; pinNoteTyp=4; pinNoteT=6; pinAnswerT=0; bPinAck=1; return;}

	if(k=FindString(t,"000009052",0))
		{ k=GetStr(k-1,year,4); k=GetStr(k,month,2); k=GetStr(k,day,2);
			k=GetStr(k,hour,2);  k=GetStr(k,mintue,2); GetStr(k,sec,2);
			sprintf(tempbuf,"%s%s",hour,mintue); uiRT=GetHex(tempbuf);
			return;
		}

	if(t=FindString(t,rpacklead,0))
	{ d=t; while(d=GetBreak(d,tempbuf));
		for(i=0;i<6;i++) a[i]=tempbuf[i]; a[6]=0;	
		 
		TcpApp(eAnswerP); bTcpAnsOk=0; GetBreak(t,revercod);

		if(strcmp(a,"00000C")==0)
			{ d=FindString(t,"00000C",0);
				j=rleadchk; for(m=t;m<d-6;m++) j+=rxbuf[m];
				sprintf(a,"%s%u","00000C",(uint)j);
		 
				if(strcmp(a,tempbuf)==0)
					if(t=GetBreak(t,tempbuf))
						{ for(i=0;i<sizeof(reverse)/2;i++) if(strcmp(tempbuf,reverse[i])==0) break;
							if(i<sizeof(reverse)/2)
							{ bTcpAnsOk=1;
								switch(i)
									{ case 0: bOFF=0; break;
										case 1: bOFF=1; break;
										case 2:	if(!ucP02) break;
											while(t=GetBreak(t,tempbuf))
												{ for(i=0;i<6;i++) a[i]=tempbuf[i]; a[6]=0;
													for(j=0;j<sizeof(paracod)/2;j++) if(strcmp(a,paracod[j])==0) break;
													if(j<sizeof(paracod)/2)
														{ 
															for(i=0;i<sizeof(floatadr)/2;i++) if(*(parcodadr+j)==*(floatadr+i)) break;
															if(i==sizeof(floatadr)/2) bfloat=0; else bfloat=1;
															k=Len(tempbuf);
															for(i=6;i<k;i++) if(tempbuf[i]=='.') break;
															if(i==k) {if(bfloat) {tempbuf[i]='.'; tempbuf[i+1]='0'; tempbuf[i+2]=0;}}
															else
																{ tempbuf[i+2]=0;
																	if(!bfloat) tempbuf[i]=0;
																}
	
															**(parcodadr+j)=GetHex(&tempbuf[6]);
															bDatChange=1;
														}
												}
											break;
										case 3: TcpApp(eDataP); break;
										case 4: TcpApp(eParaP); break;
										case 5: TcpApp(eDateP); break;
									}
							}
					}	
			}
	}
}

void RxUdpDataPro(void)
{}


uint DataPack(uint t)
{
	//t+=sprintf(tcpdat+t,"%s",DATA_PACK);
	if(!ucSenErr[0]) t+=sprintf(tcpdat+t,"%s%s,","101011",stmp1);
	else t+=sprintf(tcpdat+t,"%s%s,","101011","--");

	//if(!ucSenErr[1]) t+=sprintf(tcpdat+t,"%s%s,","101021",stmp2); //for NWK-380-04
	//else t+=sprintf(tcpdat+t,"%s%s,","101021","--");

	//if(!ucHumSenErr) t+=sprintf(tcpdat+t,"%s%s,","102011",shum);
	//else t+=sprintf(tcpdat+t,"%s%s,","102011","--"); //for NWK-380-03

	t+=sprintf(tcpdat+t,"%s%s,","103011",sA);
	t+=sprintf(tcpdat+t,"%s%s,","103021",sB);
	t+=sprintf(tcpdat+t,"%s%s,","103031",sC);
	t+=sprintf(tcpdat+t,"%s%u,","S01010",(uint)yjztV);
	//t+=sprintf(tcpdat+t,"%s%u,","S01020",(uint)hsztV); //for NWK-380-04
	//t+=sprintf(tcpdat+t,"%s%u,","S01030",(uint)fjztV); //for NWK-380-04
	//t+=sprintf(tcpdat+t,"%s%u,","S01040",(uint)jsztV); //for NWK-380-03  
	//t+=sprintf(tcpdat+t,"%s%u","S01050",(uint)qsztV); //for NWK-380-03
	return t;
}

uchar LoadTcpDat(void)
{ uint xdata t; uchar xdata i,j;
	uchar xdata en=0;
	bit bfloat;

	switch(tcptype[0])
		{
			case ePinP:	
				t=sprintf(tcpdat,"%s",packlead);
				t+=sprintf(tcpdat+t,"%s",PIN_PACK);	
				t+=sprintf(tcpdat+t,"%06u%s",(uint)8,pin); //8-为PIN码的网络代码
				pinAnswerT=15;
				en=1;
				break;
	
			case eDataP:
				if(!bPinPass || ucT01==1) break;
				RTSData();
				t=sprintf(tcpdat,"%s",packlead);
				t+=sprintf(tcpdat+t,"%s",DATA_PACK);
				DataPack(t);
				en=1;
				break;
	
			case eParaP:
				if(!bPinPass || ucT01==1) break;
				t=sprintf(tcpdat,"%s",packlead);
				t+=sprintf(tcpdat+t,"%s",PARA_PACK);
				for(i=0;i<sizeof(paracod)/2;i++)
					{ for(j=0;j<sizeof(floatadr)/2;j++) if(*(parcodadr+i)==*(floatadr+j)) break;
						if(j==sizeof(floatadr)/2) bfloat=0; else bfloat=1;
	
						if(bfloat)
							{ t+=sprintf(tcpdat+t,"%s%.1f",paracod[i],(float)**(parcodadr+i)/10); t+=sprintf(tcpdat+t,"%s",",");}
						else t+=sprintf(tcpdat+t,"%s%d,",paracod[i],**(parcodadr+i));
					}
				en=1;
				break;
	
			case eWarnP:
				if(!bPinPass || ucT01==1) break;
				t=sprintf(tcpdat,"%s",packlead);
				t+=sprintf(tcpdat+t,"%s",WARN_PACK);
				for(i=0;i<sizeof(netwid);i++) if(netwid[i]) t+=sprintf(tcpdat+t,"%s,",netwarn[i]);
				DataPack(t);
				en=1;
				break;
				
			case eDelWarnP:
				if(!bPinPass || ucT01==1) break;
				t=sprintf(tcpdat,"%s",packlead);
				t+=sprintf(tcpdat+t,"%s",DELWARN_PACK);
				for(i=0;i<sizeof(netwid);i++) if(netwid[i]) t+=sprintf(tcpdat+t,",%s",netwarn[i]);
				en=1;
				break;
				
			case eDelAllWP:
				if(!bPinPass || ucT01==1) break;
				t=sprintf(tcpdat,"%s",packlead);
				sprintf(tcpdat+t,"%s",DELWARN_PACK);
				en=1;
				break;
				
			case eBeatP:
				t=sprintf(tcpdat,"%s",packlead);
				t+=sprintf(tcpdat+t,"%s",BEAT_PACK);
				en=1;
				break;

			case eAnswerP: 
				t=sprintf(tcpdat,"%s,",revercod);
				if(!bTcpAnsOk) t+=sprintf(tcpdat+t,"%s","00000A05");
				else t+=sprintf(tcpdat+t,"%s","00000A01");
				en=1;
				break;

			case eDateP:
				t=sprintf(tcpdat,"%s",rpacklead);
				t+=sprintf(tcpdat+t,"%s%s%s","000004",year,month);
				t+=sprintf(tcpdat+t,"%s%s%s",day,hour,mintue);
				en=1;
				break;
		}
	return en;
}