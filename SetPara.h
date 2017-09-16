

int xdata iY01=-50,iY02=30,iY06=0,iY07=50,iY08=50,iY13=-100;
uint xdata ucY03=0,ucY04=15,ucY05=5,ucY10=0,ucY14=0;
uint xdata uiY09=180,uiY11=2300,uiY12=600;

uint xdata ucH01=0,ucH02=24,ucH03=25,ucH05=5,ucH06=0,ucH08=1; int xdata iH04=250,iH07=200;
 
uint xdata ucF01=0,ucF02=0,ucF03=0,ucF04=20,ucF05=50;

uint xdata ucL01=60,ucL02=5,ucL03=5,ucL04=30,ucL05=30; int xdata cL06=0;

uint xdata ucD01=0,ucD02=8, ucD03=5,ucD04=3;

uint xdata ucT01=2,ucT02=0,ucT03=5;

/*uint xdata uiP01=0;*/ uint xdata ucP02=1,ucP03=1,ucP04=0;
uint xdata ucP05=0,ucP06=20,ucP07=5;

uchar xdata password[5]="0000";
uchar xdata inpw[5];


int xdata* code adr[]={
	&iY01, &iY02, &iY06, &iY07, &iY08, &iY13,
	&ucY03, &ucY04, &ucY05, &ucY10,
	&uiY09, &uiY11, &uiY12, &ucY14,
	&ucH01, &ucH02, &ucH03, &ucH05, &ucH06, &iH04, &iH07, &ucH08,
	&ucF01, &ucF02, &ucF03, &ucF04, &ucF05,
	&ucL01, &ucL02, &ucL03, &ucL04, &ucL05, &cL06,
	&ucD01, &ucD02, &ucD03, &ucD04,
	&ucT01,&ucT02, &ucT03,

	/*&uiP01,*/ &ucP02, &ucP03, &ucP04, &ucP05, 
	&ucP06, &ucP07,
	password, &password[2],
};	

uint xdata para[sizeof(adr)/2];

//------------------------------
int xdata* code parcodadr[]=
{
	&iY01, &iY02, &iY06, &iY07, &iY08, &iY13,
	&ucY03, &ucY04, &ucY05, &ucY10,
	&uiY09, &uiY11, &uiY12, &ucY14,
	&ucH01, &ucH02, &ucH03, &ucH05, &ucH06, &iH04, &iH07, &ucH08,
	&ucF01, &ucF02, &ucF03, &ucF04, &ucF05,
	&ucL01, &ucL02, &ucL03, &ucL04, &ucL05, &cL06,
	&ucD01, &ucD02, &ucD03, &ucD04,
	&ucT02, &ucT03,
};

uchar code* code paracod[]=
{
"101031","101041","101051","101061","101071","101081", 					//iY01, iY02, iY06, iY07, iY08, iY13,
"X01010","106016","106026","X01020", 														//ucY03, ucY04, ucY05, ucY10,	
"106037","10604C","10605C","106166", 														//uiY09, uiY11, uiY12, ucY14
"X01030","106065","106076","106086","X01040","101091", 					//ucH01,ucH02,ucH03,ucH05,ucH06,iH04,
"101101","X01070",																							//iH07,ucH08
"X01050","106096","106106","106116","106126", 									//ucF01, ucF02, ucF03, ucF04, ucF05,
"102021","102031","102041","102051","102061","102071", 					//ucL01, ucL02, ucL03, ucL04, ucL05, cL06,
"X01060","103041","106137","N01010", 														//ucD01, ucD02, ucD03, ucD04,
"106145","106156", 																							//ucT02, ucT03,
};
int xdata* code floatadr[]={	&iY01, &iY02, &iY06, &iY07, &iY08, &iY13,
															&iH04, &iH07,
															&ucF04,&ucF05,
														}; 
//------------------------------
														
uchar xdata uc3mLockK=60;

void IncFun(void)
{ ucEnSetT=LTT(5000);
	if(!sert) sert=TT(1000);
	else sert=TT(120);
	switch(ucSet)
		{ case 1: if(iY01<499) iY01++; break; 	//101031 //yes
			case 2: if(iY02<200) iY02++; break; 	//101041 //yes
			case 3: if(!ucY03) ucY03=1; break; 		//X01010
			case 4: if(ucY04<100) ucY04++; break; //106016
			case 5: if(ucY05<100) ucY05++; break; //106026
			case 6: if(iY06<100) iY06++; break; 	//101051
			case 7: if(iY07<200) iY07++; break; 	//101061 //yes
			case 8: if(iY08<200) iY08++; break; 	//101071 //yes
			case 9: if(uiY09<600) uiY09++; break; //106037
			case 10: if(!ucY10) ucY10=1; break; 	//X01020

			case 11: if(uiY11/100<23) uiY11+=100; break; //10604C
			case 12: if(uiY11%100<59) uiY11++; break;

			case 13: if(uiY12/100<23) uiY12+=100; break; //10605C
			case 14: if(uiY12%100<59) uiY12++; break;

			case 15: if(iY13<499) iY13++; break; //101081

			case 16: if(ucY14<60) ucY14++; break;
			//--------------------------

			case 17: if(!ucH01) ucH01=1; break; 		//X01030
			case 18: if(ucH02<100) ucH02++; break; 	//106065 //yes
			case 19: if(ucH03<100) ucH03++; break; 	//106076 //yes
			case 20: if(iH04<400) iH04++; break; 		//101091 //yes
			case 21: if(ucH05<30) ucH05++; break; 	//106086 //yes
			case 22: if(!ucH06) ucH06=1; break;			//X01040
			case 23: if(iH07<500) iH07++; break;		//101101
			case 24: if(!ucH08) ucH08=1; break;
			//--------------------------

			case 25: if(!ucF01) ucF01=1; break;			//X01050
			case 26: if(ucF02<99) ucF02++; break; 	//106096
			case 27: if(ucF03<99) ucF03++; break; 	//106106
			case 28: if(ucF04<200) ucF04+=5; break;	//106116
			case 29: if(ucF05<200) ucF05+=5; break;	//106126
			//--------------------------

			case 30: if(ucL01<89) ucL01++; break;	//102021
			case 31: if(ucL02<20) ucL02++; break; //102031
			case 32: if(ucL03<20) ucL03++; break; //102041
			case 33: if(ucL04<30) ucL04++; break; //102051
			case 34: if(ucL05<30) ucL05++; break; //102061
			case 35: if(cL06<10) cL06++; break;		//102071
			//--------------------------

			case 36: if(!ucD01) ucD01=1; break; 	//X01060
			case 37: if(!ucD02) ucD02=3;					//103041 //yes 
					else if(ucD02<80) ucD02++; break;
			case 38: if(ucD03<30) ucD03++; break;	//106137 //yes
			case 39: if(ucD04<10) ucD04++; break;	//N01010
			//--------------------------

			case 40: if(ucT01<2) ucT01++; break;	//X01080
			case 41: if(ucT02<24) ucT02++; break; //106145
			case 42: if(ucT03<60) ucT03++; break;	//106156
			//--------------------------

			case 43: 	if(!inpw[0]) inpw[0]=0x30;
								else if(inpw[0]<0x39) inpw[0]++;
								break; 
			case 44: 	if(!inpw[1]) inpw[1]=0x30;
								else if(inpw[1]<0x39) inpw[1]++;
								break;
			case 45: 	if(!inpw[2]) inpw[2]=0x30;
								else if(inpw[2]<0x39) inpw[2]++;
								break;
			case 46: 	if(!inpw[3]) inpw[3]=0x30;
								else if(inpw[3]<0x39) inpw[3]++;
								break;

			case 47: if(!ucP02) ucP02=1; break;
			case 48: if(!ucP03) ucP03=1; break;
			case 49: if(!ucP04) ucP04=1; break;
			case 50: if(ucP05<2) ucP05++; break;
			case 51: if(ucP06<99) ucP06++; break;
			case 52: if(ucP07<99) ucP07++; break;	
								
			case 53: 	if(password[0]<0x39) password[0]++; break;
			case 54: 	if(password[1]<0x39) password[1]++; break;
			case 55: 	if(password[2]<0x39) password[2]++; break;
			case 56: 	if(password[3]<0x39) password[3]++; break; 
		}
}

void DecFun(void)
{ ucEnSetT=LTT(5000);
	if(!sert) sert=TT(1000);
	else sert=TT(120);
	switch(ucSet)
		{ case 1: if(iY01>-499) iY01--; break;
			case 2: if(iY02>1) iY02--; break;
			case 3: if(ucY03) ucY03=0; break;
			case 4: if(ucY04>1) ucY04--; break;
			case 5: if(ucY05>1) ucY05--; break;
			case 6: if(iY06>-100) iY06--; break;
			case 7: if(iY07>10) iY07--; break;
			case 8: if(iY08>10) iY08--; break;
			case 9: if(uiY09) uiY09--; break;
			case 10: if(ucY10) ucY10=0; break;

			case 11: if(uiY11/100) uiY11-=100; break;
			case 12: if(uiY11%100) uiY11--; break;

			case 13: if(uiY12/100) uiY12-=100; break;
			case 14: if(uiY12%100) uiY12--; break;

			case 15: if(iY13>-499) iY13--; break;

			case 16: if(ucY14) ucY14--; break;
			//--------------------------

			case 17: if(ucH01) ucH01=0; break;
			case 18: if(ucH02) ucH02--; break;
			case 19: if(ucH03) ucH03--; break;
			case 20: if(iH04>0) iH04--; break;
			case 21: if(ucH05) ucH05--; break;
			case 22: if(ucH06) ucH06=0; break;
			case 23: if(iH07>10) iH07--; break;
			case 24: if(ucH08) ucH08=0;
			//--------------------------
			
			case 25: if(ucF01) ucF01=0; break;
			case 26: if(ucF02) ucF02--; break;
			case 27: if(ucF03) ucF03--; break;
			case 28: if(ucF04) ucF04-=5; break;
			case 29: if(ucF05) ucF05-=5; break;
			//-------------------------- 

			case 30: if(ucL01>20) ucL01--; break;
			case 31: if(ucL02>1) ucL02--; break;
			case 32: if(ucL03>1) ucL03--; break;
			case 33: if(ucL04>1) ucL04--; break;
			case 34: if(ucL05>1) ucL05--; break;
			case 35: if(cL06>-10) cL06--; break;
			//--------------------------

			case 36: if(ucD01) ucD01=0; break;
			case 37: if(ucD02>3) ucD02--; else if(ucD02==3) ucD02=0; break;
			case 38: if(ucD03>0) ucD03--; break;
			case 39: if(ucD04>1) ucD04--; break;
			//-------------------------- 

			case 40: if(ucT01) ucT01--; break;
			case 41: if(ucT02) ucT02--; break;
			case 42: if(ucT03) ucT03--; break;
			//-------------------------- 

			case 43: 	if(!inpw[0]) inpw[0]=0x30;
								else if(inpw[0]>0x30) inpw[0]--;
								break; 
			case 44: 	if(!inpw[1]) inpw[1]=0x30;
								else if(inpw[1]>0x30) inpw[1]--;
								break;
			case 45: 	if(!inpw[2]) inpw[2]=0x30;
								else if(inpw[2]>0x30) inpw[2]--;
								break;
			case 46: 	if(!inpw[3]) inpw[3]=0x30;
								else if(inpw[3]>0x30) inpw[3]--;
								break;

			case 47: if(ucP02) ucP02=0; break;
			case 48: if(ucP03) ucP03=0; break;
			case 49: if(ucP04) ucP04=0; break;
			case 50: if(ucP05) ucP05--; break;
			case 51: if(ucP06>1) ucP06--; break;
			case 52: if(ucP07>1) ucP07--; break; 
								
			case 53: 	if(password[0]>0x30) password[0]--; break;
			case 54: 	if(password[1]>0x30) password[1]--; break;
			case 55: 	if(password[2]>0x30) password[2]--; break;
			case 56: 	if(password[3]>0x30) password[3]--; break; 
		}
}

uchar ucKeyId,ucKey05s;
code uchar mmtab[]={INC_K,DEC_K,INC_K,DEC_K,INC_K,INC_K,DEC_K};

void KeyOrderPro(void)
{	
	if(ucKey05s)
		{ ucKey05s=TT(500);
			if(ubBCD!=mmtab[ucKeyId]) ucKey05s=0;
			else
				if(ucKeyId==sizeof(mmtab)-1)
					{ ucZJ=13; EraseEeprom(0x02,1); EraseEeprom(0x04,1); EraseEeprom(0x08,1); YJJDQ=1; Append(eCMGDALL);}
				else ucKeyId++;
		}
}
#define FIRSTK {if(!ucKey05s) {ucKey05s=TT(500); ucKeyId=0;}}

void AffirmAdjust(void)
{	bAdj=0;
	if(uiFltOut[2]>200 && uiFltOut[3]>200 && uiFltOut[4]>200) 
		{ uiAdj[0]=uiFltOut[2]-2;
			uiAdj[1]=uiFltOut[3]-2;
			uiAdj[2]=uiFltOut[4]-2;
			EraseEeprom(0x06,1);
			WrEeprom(0x06,1,uiAdj[0]>>8); WrEeprom(0x06,2,uiAdj[0]);
			WrEeprom(0x06,3,uiAdj[1]>>8); WrEeprom(0x06,4,uiAdj[1]);
			WrEeprom(0x06,5,uiAdj[2]>>8); WrEeprom(0x06,6,uiAdj[2]);		
			WrEeprom(0x06,7,0xdc); 
		}	
}

void KeyProcess(void)
{  
	ucKeyX=10; 
	if(ucWarn && !bDisWarnBell) {bDisWarnBell=1; return;}

	if(!sert) ucBellT=TT(80);
	if(uc3mLockK) uc3mLockK=60;

	if(ubBCD==SET_K)
		if(bAdj) AffirmAdjust();
		else
			{	if(!uc3mLockK) uc3mLockK=60;
				if(!ucSet) { ucKeyT=LTT(3000); ucKeyX=0x80; ucKLen=1;}
				else
					{ 
						ucSet++; ucEnSetT=LTT(5000);
						if(ucSet==43) {inpw[0]=inpw[1]=inpw[2]=inpw[3]=0;}
						if(ucSet==47) if(strcmp(inpw,password)!=0) {ucSet=0; ucEnSetT=0;}
						if(ucSet>56) {ucSet=0; ucEnSetT=0;}
	
						if(ucSet==17) ucSet=36; //for NWK-380-01 
					}
			}

	if(ubBCD==INC_K)
		if(!ucSet) {FIRSTK; ucKeyT=LTT(3000); ucKeyX=0x80; ucKLen=2;}
		else IncFun();
			
	if(ubBCD==DEC_K)
		if(!ucSet) { ucKeyT=LTT(5000); ucKeyX=0x80; ucKLen=3;}
		else DecFun();
		
	if(ubBCD==WD_K)
		if(ucZJ>1) {if(!bAdj) bAdj=1;}
		else if(!ucZJ)
		if(uc3mLockK)
		{ ucEnSetT=LTT(5000);
			if(ucFSet!=1) {ucFSet=1; ucSet=1;}
			else
				switch(ucSet)
				{ case 1: ucSet=2; break;
					case 2: ucSet=7; break;
					case 7: ucSet=8; break;
					case 8: ucSet=0; ucFSet=0; ucEnSetT=0; break;
				}
		}
		
	/*if(ubBCD==HS_K)
		if(bAdj) AffirmAdjust();
		else 
			if(!ucZJ)
				if(uc3mLockK)
					//if(!bShowCurHum) bShowCurHum=1;
					//else
					{ ucEnSetT=LTT(5000);
						if(ucFSet!=2) {ucFSet=2; ucSet=18;}
						else ucSet++; if(ucSet>21) {ucSet=0; ucFSet=0; ucEnSetT=0;}
					}*/ 
		
	if(ubBCD==DL_K)
		if(bAdj) {bAdj=0; ucZJ=0;}
		else if(!ucZJ)
		if(uc3mLockK)
		//if(bShowCurHum) bShowCurHum=0;
		//else
		{ ucEnSetT=LTT(5000);
			if(ucFSet!=3) {ucFSet=3; ucSet=37;}
			else ucSet++; if(ucSet>38) {ucSet=0; ucFSet=0; ucEnSetT=0;}
		} 
		
	if(gsmInitT) KeyOrderPro();
}

void ScaneKey(void)
{ 
	if(ubBCD!=0x0f)
		switch(ucKeyX)
			{ case 0: ucKeyT=TT(50); ucKeyX=1; break;
				case 2:  ucKeyX=9; if(ucZJ==1) {ucZJ=0; ucKeyX=10;} break;
				case 0x81: 
					if(ucKLen==1) {ucSet=1; ucFSet=0; ucEnSetT=LTT(5000);}
					else if(ucKLen==2) {if(ucRun==1) ucRun=2;}
					//else if(ucKLen==3) {if(ucRun<0x20) ucRun=0x20;} //for NWK-380-04
					ucKeyX=0x82;
					break;
			}
	else
		{ //if(!ucSet) if(ucKLen==2 && ucKeyX!=0x82) bShowCurHum=~bShowCurHum; //for NWK-380-03
			//if(!ucSet) if(ucKLen==3 && ucKeyX!=0x82) watchhs=6; //for NWK-380-04
			ucKeyX=0; sert=0; ucKLen=0;
		}
}

void Savedata(void)
{ uchar t; uchar xdata* p;
	EraseEeprom(0x02,0);
	WrEeprom(0x02,0,0x5a);
	for(t=0;t<sizeof(adr)/2;t++)
		{ p=(uchar*)adr[t]; WrEeprom(0x02,t*2+1,*p); WrEeprom(0x02,t*2+2,*(p+1));}
}