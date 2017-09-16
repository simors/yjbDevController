
uchar code dig[]={	0xFA,0x88,0xD3,0xD9,0xA9,0x79,0x7B,0xC8,0xFB,0xF9,
										0xEB,0x3B,0x72,0x9B,0x73,0x63
									}; // a b c d e f g h  <==>
										 // 6 7 3 4 1 5 0 2		
	
#define CHR_0 0xfa 		
#define CHR_1 0x88 		
#define CHR_2 0xd3 		
#define CHR_3 0xd9 		
#define CHR_4 0xa9 		
#define CHR_5 0x79 		
#define CHR_6 0x7b 		
#define CHR_7 0xc8 		
#define CHR_8 0xfb 		
#define CHR_9 0xf9
#define CHR__ 0x01
#define CHR_BL 0x10
#define CHR_dot 0x04 
									
#define CHR_A 0xeb
#define CHR_b 0x3b
#define CHR_C 0x72	
#define CHR_d 0x9b	
#define CHR_E 0x73	
#define CHR_F 0x63		
#define CHR_y 0xb9	
#define CHR_H 0xab	
#define CHR_S 0x79	
#define CHR_t 0x33	
#define CHR_P 0xe3	
#define CHR_L 0x32	
#define CHR_U 0xba	
#define CHR_r 0x03	

idata union { uchar buf[10];
				struct{ uchar dup[4];
								uchar ddn[4];
								uchar dig9;
								uchar dig10;
							}st;
					}un;

uchar bdata ubLed9; //dig9
sbit bZLLed=ubLed9^5; //F9
sbit bHSLed=ubLed9^0; //G9
sbit bFJLed=ubLed9^2; //H9
sbit bTXLed=ubLed9^6; //A9

sbit bXH0Led=ubLed9^7; //B9 //B9 C9 D9 E9-信号强度(渐增)
sbit bXH1Led=ubLed9^3; //C9
sbit bXH2Led=ubLed9^4; //D9
sbit bXH3Led=ubLed9^1; //E9

//bit bBJLed; //dig8--H8

uchar bdata ubLed10; //dig10
sbit bImgC1=ubLed10^6; //℃
sbit bImgMPa=ubLed10^7; //MPa
sbit bImgV=ubLed10^3; //V
sbit bImgF=ubLed10^4; //F

sbit bImgC2=ubLed10^1; //℃
sbit bImgKPa=ubLed10^5; //KPa
sbit bImgA=ubLed10^0; //A
sbit bImgBFB=ubLed10^2; //%


#define DIN P3_4 
#define SCK P3_5

#define LEVEL_OFF   0x80
#define LEVEL_1     0x88
#define LEVEL_2     0x89
#define LEVEL_4     0x8a
#define LEVEL_10    0x8b
#define LEVEL_11    0x8c
#define LEVEL_12    0x8d
#define LEVEL_13    0x8e
#define LEVEL_14    0x8f

#define DATA_SET_CMD 0x40 
#define DISP_CTRL_CMD 0x80
#define ADR_SET_CMD 0xc0

#define NNOP { _nop_();_nop_(); _nop_();_nop_(); _nop_();_nop_();\
							 _nop_();_nop_(); _nop_();_nop_(); _nop_();_nop_();\
						 }

void TM1640Start(void)
{	
	DIN=1; NNOP
	SCK=1; NNOP
	DIN=0; NNOP
	SCK=0; NNOP
}

void TM1640End(void)
{	 
	SCK=0; NNOP
	DIN=0; NNOP
	SCK=1; NNOP
	DIN=1; NNOP	
	SCK=1; NNOP
}

void TM1640Write(uchar da)
{ uchar i;
	NNOP
	for(i=8;i;i--)
		{ SCK=0; 				
			NNOP
			if(da&0x01) DIN=1;
			else DIN=0;
			NNOP
			SCK=1; 
			NNOP
			da>>=1; 	
		}
}

uchar code GxBuf[]={0,1,9,10,11,12,13,14,2,3}; 
void DataToTM1640Ram(void)
{ uchar j,t;
	
	TM1640Start();
	TM1640Write(0x44);
	TM1640End();

	for(j=0;j<sizeof(GxBuf);j++)
			{	
				t=GxBuf[j];
				t|=ADR_SET_CMD;
				TM1640Start();
				TM1640Write(t);
				t=un.buf[j];
				TM1640Write(t);
				TM1640End();
			}
			
	TM1640Start();
	TM1640Write(0x8a);
	TM1640End();
}