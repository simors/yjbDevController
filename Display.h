
uchar code setcod[][3]={	CHR_y,CHR_0,CHR_1,
													CHR_y,CHR_0,CHR_2,
													CHR_y,CHR_0,CHR_3,
													CHR_y,CHR_0,CHR_4,
													CHR_y,CHR_0,CHR_5,
													CHR_y,CHR_0,CHR_6,
													CHR_y,CHR_0,CHR_7,
													CHR_y,CHR_0,CHR_8,
													CHR_y,CHR_0,CHR_9,
													CHR_y,CHR_1,CHR_0,
													
													CHR_y,CHR_1,CHR_1,
													CHR_y,CHR_1,CHR_1,
													CHR_y,CHR_1,CHR_2,
													CHR_y,CHR_1,CHR_2,
													
													CHR_y,CHR_1,CHR_3,
													CHR_y,CHR_1,CHR_4,
													//----------------

													CHR_H,CHR_0,CHR_1,
													CHR_H,CHR_0,CHR_2,
													CHR_H,CHR_0,CHR_3,
													CHR_H,CHR_0,CHR_4,
													CHR_H,CHR_0,CHR_5,
													CHR_H,CHR_0,CHR_6,
													CHR_H,CHR_0,CHR_7,
													CHR_H,CHR_0,CHR_8,
													//----------------
													
													CHR_F,CHR_0,CHR_1,
													CHR_F,CHR_0,CHR_2,
													CHR_F,CHR_0,CHR_3,
													CHR_F,CHR_0,CHR_4,
													CHR_F,CHR_0,CHR_5,
													//----------------
													
													CHR_L,CHR_0,CHR_1,
													CHR_L,CHR_0,CHR_2,
													CHR_L,CHR_0,CHR_3,
													CHR_L,CHR_0,CHR_4,
													CHR_L,CHR_0,CHR_5,
													CHR_L,CHR_0,CHR_6,
													//----------------
													
													CHR_d,CHR_0,CHR_1,
													CHR_d,CHR_0,CHR_2,
													CHR_d,CHR_0,CHR_3,
													CHR_d,CHR_0,CHR_4,
													//----------------
													
													CHR_t,CHR_0,CHR_1,
													CHR_t,CHR_0,CHR_2,
													CHR_t,CHR_0,CHR_3,
													//----------------
													
													CHR_P,CHR_d,CHR__, //41
													CHR_P,CHR_d,CHR__, //42
													CHR_P,CHR_d,CHR__, //43
													CHR_P,CHR_d,CHR__, //44

													CHR_P,CHR_0,CHR_2,
													CHR_P,CHR_0,CHR_3,
													CHR_P,CHR_0,CHR_4,
													CHR_P,CHR_0,CHR_5,
													CHR_P,CHR_0,CHR_6,
													CHR_P,CHR_0,CHR_7,

													CHR_P,CHR_0,CHR_1, //51
													CHR_P,CHR_0,CHR_1, //52
													CHR_P,CHR_0,CHR_1, //53
													CHR_P,CHR_0,CHR_1, //54
											};

uchar xdata ucShowABC=0;	 

uchar code signal[]={0x80,0x88,0x98,0x9a};

void HexToBCD(uint hex,uchar data*p,uchar len)
{ do{ *p--=hex%10; hex/=10;
	}while(--len);
}

void Show(uint hex,uchar idata* p,uchar len,uchar nbd)
{ uchar i;
	bit bNeg;
	
	bNeg=0;
	if(hex>=0x8000) {hex=-hex; bNeg=1;}
	i=len;
	do{p[i-1]=dig[hex%10]; hex/=10;}
 	while(--i);

	for(i=0;i<len-nbd-1;i++)
		if(p[i]==CHR_0) p[i]=0;
		else break;						 
	if(bNeg)
		if(i) p[i-1]=CHR__;
		else p[0]|=CHR__;
	if(nbd) p[len-nbd-1]|=CHR_dot;
}

void ToShowBuffer(void)
{ uchar t; 
	uchar a[2];
	for(t=0;t<10;t++) un.buf[t]=0; ubLed10=0;

	if(ucStartT)
		{ if(bIs380v) {un.st.dup[0]=CHR_3; un.st.dup[1]=CHR_8; un.st.dup[2]=CHR_0; un.st.dup[3]=CHR__;}
			else {un.st.dup[0]=CHR_2; un.st.dup[1]=CHR_2; un.st.dup[2]=CHR_0; un.st.dup[3]=CHR__;}
			un.st.ddn[1]=CHR_0; un.st.ddn[2]=CHR_1;
			return;
		}

	if(!ucSet)
		{ bImgC1=1;
			/*if(watchhs)
				{ if(!ucSenErr[1]) Show(iTmp2,un.st.dup,4,1);
					else {un.st.dup[1]=CHR__; un.st.dup[2]=CHR__;}
					if(watchhs%2) bImgC1=1; else bImgC1=0;
				}
			else*/ //for NWK-380-04
				if(!ucSenErr[0]) Show(iTmp1,un.st.dup,4,1);
				else {un.st.dup[1]=CHR__; un.st.dup[2]=CHR__;}

			if(!ucWarn || ucShowABC<9)
				{	if(!ucWarn) if(ucShowABC>=9) ucShowABC=0;
					if(!bShowCurHum)
						{	bImgA=1; bImgBFB=0;
							if(ucShowABC<3) {t=ucCur[0]; un.st.ddn[0]=CHR_A;}
							else if(ucShowABC<6) {t=ucCur[1]; un.st.ddn[0]=CHR_b;}
							else {t=ucCur[2]; un.st.ddn[0]=CHR_C;}
							Show(t,&un.st.ddn[1],3,0);
						}
					else {Show(ucHum,&un.st.ddn[1],3,0); bImgA=0; bImgBFB=1;}
				}
			else
				{ un.st.ddn[1]=CHR_E;
					HexToBCD(ucWarn,&a[1],2);
					un.st.ddn[2]=dig[a[0]]; un.st.ddn[3]=dig[a[1]];
					bImgA=0;
				}
		}
	else
		{ un.st.dup[1]=setcod[ucSet-1][0]; un.st.dup[2]=setcod[ucSet-1][1]; un.st.dup[3]=setcod[ucSet-1][2];
			switch(ucSet)
			{ case 1: Show(iY01,un.st.ddn,4,1); break;
				case 2: Show(iY02,un.st.ddn,4,1); break;
				case 3: Show(ucY03,un.st.ddn,4,0); break;
				case 4: Show(ucY04,un.st.ddn,4,0); break;
				case 5: Show(ucY05,un.st.ddn,4,0); break;
				case 6: Show(iY06,un.st.ddn,4,1); break;
				case 7: Show(iY07,un.st.ddn,4,1); break;
				case 8: Show(iY08,un.st.ddn,4,1); break;
				case 9: Show(uiY09,un.st.ddn,4,0); break;
				case 10: Show(ucY10,un.st.ddn,4,0); break;
				
				case 11:
					HexToBCD(uiY11/100,&a[1],2); un.st.ddn[0]=dig[a[0]]; un.st.ddn[1]=dig[a[1]];
					HexToBCD(uiY11%100,&a[1],2); un.st.ddn[2]=dig[a[0]]; un.st.ddn[3]=dig[a[1]];
					if(!bFlash && ubBCD!=INC_K && ubBCD!=DEC_K) {un.st.ddn[0]=un.st.ddn[1]=0;}
					un.st.ddn[1]|=CHR_dot;
					break;
				case 12:
					HexToBCD(uiY11/100,&a[1],2); un.st.ddn[0]=dig[a[0]]; un.st.ddn[1]=dig[a[1]];
					HexToBCD(uiY11%100,&a[1],2); un.st.ddn[2]=dig[a[0]]; un.st.ddn[3]=dig[a[1]];
					if(!bFlash && ubBCD!=INC_K && ubBCD!=DEC_K) {un.st.ddn[2]=un.st.ddn[3]=0;}
					un.st.ddn[1]|=CHR_dot;
					break; 
				case 13:
					HexToBCD(uiY12/100,&a[1],2); un.st.ddn[0]=dig[a[0]]; un.st.ddn[1]=dig[a[1]];
					HexToBCD(uiY12%100,&a[1],2); un.st.ddn[2]=dig[a[0]]; un.st.ddn[3]=dig[a[1]];
					if(!bFlash && ubBCD!=INC_K && ubBCD!=DEC_K) {un.st.ddn[0]=un.st.ddn[1]=0;}
					un.st.ddn[1]|=CHR_dot;
					break;
				case 14:
					HexToBCD(uiY12/100,&a[1],2); un.st.ddn[0]=dig[a[0]]; un.st.ddn[1]=dig[a[1]];
					HexToBCD(uiY12%100,&a[1],2); un.st.ddn[2]=dig[a[0]]; un.st.ddn[3]=dig[a[1]];
					if(!bFlash && ubBCD!=INC_K && ubBCD!=DEC_K) {un.st.ddn[2]=un.st.ddn[3]=0;}
					un.st.ddn[1]|=CHR_dot;
					break;
					
				case 15: Show(iY13,un.st.ddn,4,1); break;
				case 16: Show(ucY14,un.st.ddn,4,0); break;
			//--------------------------
			
				case 17: Show(ucH01,un.st.ddn,4,0); break;
				case 18: Show(ucH02,un.st.ddn,4,0); break;
				case 19: Show(ucH03,un.st.ddn,4,0); break;
				case 20: Show(iH04,un.st.ddn,4,1); break;
				case 21: Show(ucH05,un.st.ddn,4,0); break;
				case 22: Show(ucH06,un.st.ddn,4,0); break;
				case 23: Show(iH07,un.st.ddn,4,1); break;
				case 24: Show(ucH08,un.st.ddn,4,0); break;
			//--------------------------
			
				case 25: Show(ucF01,un.st.ddn,4,0); break;
				case 26: Show(ucF02,un.st.ddn,4,0); break;
				case 27: Show(ucF03,un.st.ddn,4,0); break;
				case 28: Show(ucF04,un.st.ddn,4,1); break;
				case 29: Show(ucF05,un.st.ddn,4,1); break;
			//--------------------------
			
				case 30: Show(ucL01,un.st.ddn,4,0); break;
				case 31: Show(ucL02,un.st.ddn,4,0); break;
				case 32: Show(ucL03,un.st.ddn,4,0); break;
				case 33: Show(ucL04,un.st.ddn,4,0); break;
				case 34: Show(ucL05,un.st.ddn,4,0); break;
				case 35: Show(cL06,un.st.ddn,4,0); break;
			//--------------------------
			
				case 36: Show(ucD01,un.st.ddn,4,0); break;
				case 37: Show(ucD02,un.st.ddn,4,0); break;
				case 38: Show(ucD03,un.st.ddn,4,0); break;
				case 39: Show(ucD04,un.st.ddn,4,0); break;
			//--------------------------
			
				case 40: Show(ucT01,un.st.ddn,4,0); break;
				case 41: Show(ucT02,un.st.ddn,4,0); break;
				case 42: Show(ucT03,un.st.ddn,4,0); break;
			//--------------------------
			
				case 43: case 44: case 45: case 46: 												  												 
					if(!inpw[0]) un.st.ddn[0]=CHR_BL;
					else un.st.ddn[0]=dig[inpw[0]-0x30];

					if(!inpw[1]) un.st.ddn[1]=CHR_BL;
					else un.st.ddn[1]=dig[inpw[1]-0x30];

					if(!inpw[2]) un.st.ddn[2]=CHR_BL;
					else un.st.ddn[2]=dig[inpw[2]-0x30];

					if(!inpw[3]) un.st.ddn[3]=CHR_BL;
					else un.st.ddn[3]=dig[inpw[3]-0x30];
					
					if(!bFlash && ubBCD!=INC_K && ubBCD!=DEC_K)
						if(ucSet==43) un.st.ddn[0]=0;
						else if(ucSet==44) un.st.ddn[1]=0;
						else if(ucSet==45) un.st.ddn[2]=0;
						else un.st.ddn[3]=0;
					break;

				case 47: Show(ucP02,un.st.ddn,4,0); break;
				case 48: Show(ucP03,un.st.ddn,4,0); break;
				case 49: Show(ucP04,un.st.ddn,4,0); break;
				case 50: Show(ucP05,un.st.ddn,4,0); break;
				case 51: Show(ucP06,un.st.ddn,4,0); break;
				case 52: Show(ucP07,un.st.ddn,4,0); break;	
					
				case 53: case 54: case 55: case 56:
					un.st.ddn[0]=dig[password[0]-0x30]; un.st.ddn[1]=dig[password[1]-0x30];
					un.st.ddn[2]=dig[password[2]-0x30]; un.st.ddn[3]=dig[password[3]-0x30];
					if(!bFlash && ubBCD!=INC_K && ubBCD!=DEC_K)
						if(ucSet==53) un.st.ddn[0]=0;
						else if(ucSet==54) un.st.ddn[1]=0;
						else if(ucSet==55) un.st.ddn[2]=0;
						else un.st.ddn[3]=0;
					break;
			}
		}

	if(bOFF)if(!ucSet) {un.st.ddn[0]=0; un.st.ddn[1]=CHR_0; un.st.ddn[2]=CHR_F; un.st.ddn[3]=CHR_F; bImgA=0;}
	if(bPressMoney)if(!ucSet) {for(t=0;t<4;t++) {un.st.dup[t]=CHR__; un.st.ddn[t]=CHR__;}}

	if(pinNoteTyp==3 || pinNoteTyp==4)
		{	un.st.ddn[0]=0; un.st.ddn[1]=0; un.st.ddn[2]=0; un.st.ddn[3]=0; bImgA=0;
			if(pinNoteTyp==3) {if(pinNoteT%2) {un.st.ddn[1]=CHR_E; un.st.ddn[2]=CHR_P; un.st.ddn[3]=CHR_S;}}
			else {if(pinNoteT%2) {un.st.ddn[1]=CHR_E; un.st.ddn[2]=CHR_P; un.st.ddn[3]=CHR_F;}}
		}
	
	if(bNoModel) {bTXLed=0; t=0;}
	else
		{ if(!bNoCard) bTXLed=1;
			else bTXLed=bFlash;
			if(!ucRssi) t=0; else t=signal[ucRssi/8];
		}
	un.st.dig9=ubLed9|t; un.st.dig10=ubLed10;

	if(ucWarn || ucOLT==1)if(bFlash) un.st.ddn[3]|=CHR_dot;

	if(pinNoteTyp==1)
		if(pinNoteT%2) un.st.dig9|=0xda;
		else un.st.dig9&=~0xda;

	//Show(val,un.st.ddn,4,0);
}

void ToZJBuf(void)
{ uchar t; uint it; 
	
	for(t=0;t<10;t++) un.buf[t]=0;
	if(bAdj)
		{
			if(ucShowABC<4) {t=ucCur[0]; un.st.ddn[0]=CHR_A; it=aAD;}
			else if(ucShowABC<8) {t=ucCur[1]; un.st.ddn[0]=CHR_b; it=bAD;}
			else {t=ucCur[2]; un.st.ddn[0]=CHR_C; it=cAD;}
			Show(it,&un.st.dup,4,0); un.st.dup[0]|=CHR_dot; un.st.dup[1]|=CHR_dot; un.st.dup[2]|=CHR_dot;
			Show(t,&un.st.ddn[1],3,0); un.st.dig10=1;
		}
	else
	if(ucZJ>11)
		{ un.st.dup[1]=CHR_U; un.st.dup[2]=CHR_E; un.st.dup[3]=CHR_r;
			un.st.ddn[1]=CHR_1|CHR_dot; un.st.ddn[2]=CHR_5;
		}
	else if(ucZJ>1) {un.buf[8]=un.buf[9]=0xff; for(t=0;t<4;t++) {un.st.dup[t]=un.st.ddn[t]=dig[ucZJ-2]|CHR_dot;}}
	else for(t=0;t<4;t++) {un.st.dup[t]=dig[mid[t+4]-0x30]; un.st.ddn[t]=dig[mid[t+8]-0x30];}
}