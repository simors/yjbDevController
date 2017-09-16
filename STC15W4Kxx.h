#ifndef __STC15F2K60S2_H_
#define __STC15F2K60S2_H_


/////////////////////////////////////////////////

//�ں����⹦�ܼĴ���        // ��λֵ   ����
sfr ACC         =   0xE0;   //0000,0000 �ۼ���Accumulator
sfr B           =   0xF0;   //0000,0000 B�Ĵ���
sfr PSW         =   0xD0;   //0000,0000 ����״̬��
sbit CY         =   PSW^7;
sbit AC         =   PSW^6;
sbit F0         =   PSW^5;
sbit RS1        =   PSW^4;
sbit RS0        =   PSW^3;
sbit OV         =   PSW^2;
sbit P          =   PSW^0;
sfr SP          =   0x81;   //0000,0111 ��ջָ��
sfr DPL         =   0x82;   //0000,0000 ����ָ����ֽ�
sfr DPH         =   0x83;   //0000,0000 ����ָ����ֽ�

//I/O �����⹦�ܼĴ���
sfr P0          =   0x80;   //1111,1111 �˿�0
sbit P0_0=P0^0; sbit P0_1=P0^1; sbit P0_2=P0^2; sbit P0_3=P0^3; sbit P0_4=P0^4; sbit P0_5=P0^5; sbit P0_6=P0^6; sbit P0_7 = P0^7;

sfr P1          =   0x90;   //1111,1111 �˿�1
sbit P1_0=P1^0; sbit P1_1=P1^1; sbit P1_2=P1^2; sbit P1_3=P1^3; sbit P1_4=P1^4; sbit P1_5=P1^5; sbit P1_6=P1^6; sbit P1_7 = P1^7;

sfr P2          =   0xA0;   //1111,1111 �˿�2
sbit P2_0=P2^0; sbit P2_1=P2^1; sbit P2_2=P2^2; sbit P2_3=P2^3; sbit P2_4=P2^4; sbit P2_5=P2^5; sbit P2_6=P2^6; sbit P2_7 = P2^7;

sfr P3          =   0xB0;   //1111,1111 �˿�3
sbit P3_0=P3^0; sbit P3_1=P3^1; sbit P3_2=P3^2; sbit P3_3=P3^3; sbit P3_4=P3^4; sbit P3_5=P3^5; sbit P3_6=P3^6; sbit P3_7 = P3^7;

sfr P4          =   0xC0;   //1111,1111 �˿�4
sbit P4_0=P4^0; sbit P4_1=P4^1; sbit P4_2=P4^2; sbit P4_3=P4^3; sbit P4_4=P4^4; sbit P4_5=P4^5; sbit P4_6=P4^6; sbit P4_7 = P4^7;

sfr P5          =   0xC8;   //xxxx,1111 �˿�5
sbit P5_0=P5^0; sbit P5_1=P5^1; sbit P5_2=P5^2; sbit P5_3=P5^3; sbit P5_4=P5^4; sbit P5_5=P5^5; sbit P5_6=P5^6; sbit P5_7 = P5^7;

sfr P6          =   0xE8;   //0000,0000 �˿�6
sbit P6_0=P6^0; sbit P6_1=P6^1; sbit P6_2=P6^2; sbit P6_3=P6^3; sbit P6_4=P6^4; sbit P6_5=P6^5; sbit P6_6=P6^6; sbit P6_7 = P6^7;

sfr P7          =   0xF8;   //0000,0000 �˿�7
sbit P7_0=P7^0; sbit P7_1=P7^1; sbit P7_2=P7^2; sbit P7_3=P7^3; sbit P7_4=P7^4; sbit P7_5=P7^5; sbit P7_6=P7^6; sbit P7_7 = P7^7;

sfr P0M0        =   0x94;   //0000,0000 �˿�0ģʽ�Ĵ���0
sfr P0M1        =   0x93;   //0000,0000 �˿�0ģʽ�Ĵ���1
sfr P1M0        =   0x92;   //0000,0000 �˿�1ģʽ�Ĵ���0
sfr P1M1        =   0x91;   //0000,0000 �˿�1ģʽ�Ĵ���1
sfr P2M0        =   0x96;   //0000,0000 �˿�2ģʽ�Ĵ���0
sfr P2M1        =   0x95;   //0000,0000 �˿�2ģʽ�Ĵ���1
sfr P3M0        =   0xB2;   //0000,0000 �˿�3ģʽ�Ĵ���0
sfr P3M1        =   0xB1;   //0000,0000 �˿�3ģʽ�Ĵ���1
sfr P4M0        =   0xB4;   //0000,0000 �˿�4ģʽ�Ĵ���0
sfr P4M1        =   0xB3;   //0000,0000 �˿�4ģʽ�Ĵ���1
sfr P5M0        =   0xCA;   //0000,0000 �˿�5ģʽ�Ĵ���0
sfr P5M1        =   0xC9;   //0000,0000 �˿�5ģʽ�Ĵ���1
sfr P6M0        =   0xCC;   //0000,0000 �˿�6ģʽ�Ĵ���0
sfr P6M1        =   0xCB;   //0000,0000 �˿�6ģʽ�Ĵ���1
sfr P7M0        =   0xE2;   //0000,0000 �˿�7ģʽ�Ĵ���0
sfr P7M1        =   0xE1;   //0000,0000 �˿�7ģʽ�Ĵ���1

//ϵͳ�������⹦�ܼĴ���
sfr PCON        =   0x87;   //0001,0000 ��Դ���ƼĴ���
sfr AUXR        =   0x8E;   //0000,0000 �����Ĵ���
		#define T0x12       0x80
		#define T1x12       0x40
		#define UART_M0x6   0x20
		#define T2R         0x10
		#define BRTx12      0x04
		#define EXTRAM      0x02
		#define S1ST2       0x01
sfr AUXR1       =   0xA2;   //0000,0000 �����Ĵ���1
sfr P_SW1       =   0xA2;   //0000,0000 ����˿��л��Ĵ���1
sfr CLK_DIV     =   0x97;   //0000,0000 ʱ�ӷ�Ƶ���ƼĴ���
sfr BUS_SPEED   =   0xA1;   //xx10,x011 �����ٶȿ��ƼĴ���
sfr P1ASF       =   0x9D;   //0000,0000 �˿�1ģ�⹦�����üĴ���
sfr P_SW2       =   0xBA;   //0xxx,x000 ����˿��л��Ĵ���

//�ж����⹦�ܼĴ���
sfr IE          =   0xA8;   //0000,0000 �жϿ��ƼĴ���
sbit EA         =   IE^7;
sbit ELVD       =   IE^6;
sbit EADC       =   IE^5;
sbit ES         =   IE^4;
sbit ET1        =   IE^3;
sbit EX1        =   IE^2;
sbit ET0        =   IE^1;
sbit EX0        =   IE^0;
sfr IP          =   0xB8;   //0000,0000 �ж����ȼ��Ĵ���
sbit PPCA       =   IP^7;
sbit PLVD       =   IP^6;
sbit PADC       =   IP^5;
sbit PS         =   IP^4;
sbit PT1        =   IP^3;
sbit PX1        =   IP^2;
sbit PT0        =   IP^1;
sbit PX0        =   IP^0;
sfr IE2         =   0xAF;   //0000,0000 �жϿ��ƼĴ���2
sfr IP2         =   0xB5;   //xxxx,xx00 �ж����ȼ��Ĵ���2
sfr INT_CLKO    =   0x8F;   //0000,0000 �ⲿ�ж���ʱ��������ƼĴ���

//��ʱ�����⹦�ܼĴ���
sfr TCON        =   0x88;   //0000,0000 T0/T1���ƼĴ���
sbit TF1        =   TCON^7;
sbit TR1        =   TCON^6;
sbit TF0        =   TCON^5;
sbit TR0        =   TCON^4;
sbit IE1        =   TCON^3;
sbit IT1        =   TCON^2;
sbit IE0        =   TCON^1;
sbit IT0        =   TCON^0;
sfr TMOD        =   0x89;   //0000,0000 T0/T1ģʽ�Ĵ���
sfr TL0         =   0x8A;   //0000,0000 T0���ֽ�
sfr TL1         =   0x8B;   //0000,0000 T1���ֽ�
sfr TH0         =   0x8C;   //0000,0000 T0���ֽ�
sfr TH1         =   0x8D;   //0000,0000 T1���ֽ�
sfr T4T3M       =   0xD1;   //0000,0000 T3/T4ģʽ�Ĵ���
sfr T3T4M       =   0xD1;   //0000,0000 T3/T4ģʽ�Ĵ���
sfr T4H         =   0xD2;   //0000,0000 T4���ֽ�
sfr T4L         =   0xD3;   //0000,0000 T4���ֽ�
sfr T3H         =   0xD4;   //0000,0000 T3���ֽ�
sfr T3L         =   0xD5;   //0000,0000 T3���ֽ�
sfr T2H         =   0xD6;   //0000,0000 T2���ֽ�
sfr T2L         =   0xD7;   //0000,0000 T2���ֽ�
sfr WKTCL       =   0xAA;   //0000,0000 ���绽�Ѷ�ʱ�����ֽ�
sfr WKTCH       =   0xAB;   //0000,0000 ���绽�Ѷ�ʱ�����ֽ�
sfr WDT_CONTR   =   0xC1;   //0000,0000 ���Ź����ƼĴ���

//���п����⹦�ܼĴ���
sfr SCON        =   0x98;   //0000,0000 ����1���ƼĴ���
sbit SM0        =   SCON^7;
sbit SM1        =   SCON^6;
sbit SM2        =   SCON^5;
sbit REN        =   SCON^4;
sbit TB8        =   SCON^3;
sbit RB8        =   SCON^2;
sbit TI         =   SCON^1;
sbit RI         =   SCON^0;
sfr SBUF        =   0x99;   //xxxx,xxxx ����1���ݼĴ���
sfr S2CON       =   0x9A;   //0000,0000 ����2���ƼĴ���
sfr S2BUF       =   0x9B;   //xxxx,xxxx ����2���ݼĴ���
sfr S3CON       =   0xAC;   //0000,0000 ����3���ƼĴ���
sfr S3BUF       =   0xAD;   //xxxx,xxxx ����3���ݼĴ���
sfr S4CON       =   0x84;   //0000,0000 ����4���ƼĴ���
sfr S4BUF       =   0x85;   //xxxx,xxxx ����4���ݼĴ���
sfr SADDR       =   0xA9;   //0000,0000 �ӻ���ַ�Ĵ���
sfr SADEN       =   0xB9;   //0000,0000 �ӻ���ַ���μĴ���

				//S4CON
				#define S4RI  0x01              //S4CON.0
				#define S4TI  0x02              //S4CON.1
				#define S4RB8 0x04              //S4CON.2
				#define S4TB8 0x08              //S4CON.3	 
				#define S4REN 0x10              //S4CON.4	 
				#define S4ST4 0x40              //S4CON.6 
				#define S4SM0 0x80              //S4CON.7

//ADC ���⹦�ܼĴ���
sfr ADC_CONTR   =   0xBC;   //0000,0000 A/Dת�����ƼĴ���
sfr ADC_RES     =   0xBD;   //0000,0000 A/Dת�������8λ
sfr ADC_RESL    =   0xBE;   //0000,0000 A/Dת�������2λ

//SPI ���⹦�ܼĴ���
sfr SPSTAT      =   0xCD;   //00xx,xxxx SPI״̬�Ĵ���
sfr SPCTL       =   0xCE;   //0000,0100 SPI���ƼĴ���
sfr SPDAT       =   0xCF;   //0000,0000 SPI���ݼĴ���

//IAP/ISP ���⹦�ܼĴ���
sfr IAP_DATA    =   0xC2;   //0000,0000 EEPROM���ݼĴ���
sfr IAP_ADRH    =   0xC3;   //0000,0000 EEPROM��ַ���ֽ�
sfr IAP_ADRL    =   0xC4;   //0000,0000 EEPROM��ַ���ֽ�
sfr IAP_CMD     =   0xC5;   //xxxx,xx00 EEPROM����Ĵ���
sfr IAP_TRIG    =   0xC6;   //0000,0000 EEPRPM������Ĵ���
sfr IAP_CONTR   =   0xC7;   //0000,x000 EEPROM���ƼĴ���

//PCA/PWM ���⹦�ܼĴ���
sfr CCON        =   0xD8;   //00xx,xx00 PCA���ƼĴ���
sbit CF         =   CCON^7;
sbit CR         =   CCON^6;
sbit CCF2       =   CCON^2;
sbit CCF1       =   CCON^1;
sbit CCF0       =   CCON^0;
sfr CMOD        =   0xD9;   //0xxx,x000 PCA ����ģʽ�Ĵ���
sfr CL          =   0xE9;   //0000,0000 PCA���������ֽ�
sfr CH          =   0xF9;   //0000,0000 PCA���������ֽ�
sfr CCAPM0      =   0xDA;   //0000,0000 PCAģ��0��PWM�Ĵ���
sfr CCAPM1      =   0xDB;   //0000,0000 PCAģ��1��PWM�Ĵ���
sfr CCAPM2      =   0xDC;   //0000,0000 PCAģ��2��PWM �Ĵ���
sfr CCAP0L      =   0xEA;   //0000,0000 PCAģ��0�Ĳ�׽/�ȽϼĴ������ֽ�
sfr CCAP1L      =   0xEB;   //0000,0000 PCAģ��1�Ĳ�׽/�ȽϼĴ������ֽ�
sfr CCAP2L      =   0xEC;   //0000,0000 PCAģ��2�Ĳ�׽/�ȽϼĴ������ֽ�
sfr PCA_PWM0    =   0xF2;   //xxxx,xx00 PCAģ��0��PWM�Ĵ���
sfr PCA_PWM1    =   0xF3;   //xxxx,xx00 PCAģ��1��PWM�Ĵ���
sfr PCA_PWM2    =   0xF4;   //xxxx,xx00 PCAģ��1��PWM�Ĵ���
sfr CCAP0H      =   0xFA;   //0000,0000 PCAģ��0�Ĳ�׽/�ȽϼĴ������ֽ�
sfr CCAP1H      =   0xFB;   //0000,0000 PCAģ��1�Ĳ�׽/�ȽϼĴ������ֽ�
sfr CCAP2H      =   0xFC;   //0000,0000 PCAģ��2�Ĳ�׽/�ȽϼĴ������ֽ�

//�Ƚ������⹦�ܼĴ���
sfr CMPCR1      =   0xE6;   //0000,0000 �Ƚ������ƼĴ���1
sfr CMPCR2      =   0xE7;   //0000,0000 �Ƚ������ƼĴ���2

//��ǿ��PWM���η��������⹦�ܼĴ���
sfr PWMCFG      =   0xf1;   //x000,0000 PWM���üĴ���
#define	C2INI	0x01	// PWM����˿ڵĳ�ʼ��ƽΪ�ߵ�ƽ 
#define	C3INI	0x02
#define	C4INI	0x04
#define	C5INI	0x08
#define	C6INI	0x10
#define	C7INI	0x20
#define	CBTADC	0x40	// PWM����������ʱ�Զ�����ADCת������ע��ǰ��������PWM��ADC���뱻ʹ�ܣ���ENPWM==1����ADCON==1�� 

sfr PWMCR       =   0xf5;   //0000,0000 PWM���ƼĴ���	
#define	ENPWM	0x80	// ʹ��PWM���η�������PWM��������ʼ���� 
#define	ECBI	0x40	// ʹ��PWM�����������ж� 
#define	ENC7O	0x20	// ��ӦPWMͨ���Ķ˿�����ΪPWM����ڣ���PWM���η��������� 
#define	ENC6O	0x10
#define	ENC5O	0x08
#define	ENC4O	0x04
#define	ENC3O	0x02
#define	ENC2O	0x01

sfr PWMIF       =   0xf6;   //x000,0000 PWM�жϱ�־�Ĵ���	
#define	CBIF	0x40	// PWM�����������жϱ�־λ 
#define	C7IF	0x20
#define	C6IF	0x10	// ��nͨ����PWM�жϱ�־λ 
#define	C5IF	0x08
#define	C4IF	0x04
#define	C3IF	0x02
#define	C2IF	0x01

sfr PWMFDCR     =   0xf7;   //xx00,0000 PWM�ⲿ�쳣�����ƼĴ���


//�������⹦�ܼĴ���λ����չRAM����
//������Щ�Ĵ���,���Ƚ�P_SW2��BIT7����Ϊ1,�ſ�������д
#define	PWMCH	0xFFF0	// PWM���������ֽ�  
#define	PWMCL	0xFFF1	// PWM���������ֽ�  
#define	PWMCKS	0xFFF2	// PWMʱ��ѡ��      

#define	PWM2T1H	0xFF00	// PWM2T1�������ֽ� 
#define	PWM2T1L	0xFF01	// PWM2T1�������ֽ� 
#define	PWM2T2H	0xFF02	// PWM2T2�������ֽ� 
#define	PWM2T2L	0xFF03	// PWM2T2�������ֽ� 
#define	PWM2CR	0xFF04	// PWM2����         

#define	PWM3T1H	0xFF10	// PWM3T1�������ֽ� 
#define	PWM3T1L	0xFF11	// PWM3T1�������ֽ� 
#define	PWM3T2H	0xFF12	// PWM3T2�������ֽ� 
#define	PWM3T2L	0xFF13	// PWM3T2�������ֽ� 
#define	PWM3CR	0xFF14	// PWM3����         

#define	PWM4T1H	0xFF20	// PWM4T1�������ֽ� 
#define	PWM4T1L	0xFF21	// PWM4T1�������ֽ� 
#define	PWM4T2H	0xFF22	// PWM4T2�������ֽ� 
#define	PWM4T2L	0xFF23	// PWM4T2�������ֽ� 
#define	PWM4CR	0xFF24	// PWM4����         

#define	PWM5T1H	0xFF30	// PWM5T1�������ֽ� 
#define	PWM5T1L	0xFF31	// PWM5T1�������ֽ� 
#define	PWM5T2H	0xFF32	// PWM5T2�������ֽ� 
#define	PWM5T2L	0xFF33	// PWM5T2�������ֽ� 
#define	PWM5CR	0xFF34	// PWM5����         

#define	PWM6T1H	0xFF40	// PWM6T1�������ֽ� 
#define	PWM6T1L	0xFF41	// PWM6T1�������ֽ� 
#define	PWM6T2H	0xFF42	// PWM6T2�������ֽ� 
#define	PWM6T2L	0xFF43	// PWM6T2�������ֽ� 
#define	PWM6CR	0xFF44	// PWM6����         

#define	PWM7T1H	0xFF50	// PWM7T1�������ֽ� 
#define	PWM7T1L	0xFF51	// PWM7T1�������ֽ� 
#define	PWM7T2H	0xFF52	// PWM7T2�������ֽ� 
#define	PWM7T2L	0xFF53	// PWM7T2�������ֽ� 
#define	PWM7CR	0xFF54	// PWM7����         

//PWMnCR:  PWMn����   -   -   -   -   PWMn_PS  EPWMnI  ECnT2SI  ECnT1SI   0000,0000
#define PWMnPS 0x08
#define EPWMnI 0x04
#define ECnT2SI 0x02
#define ECnT1SI 0x01

#define	ENFD		0x20	// ʹ��PWM���ⲿ�쳣��⹦ 
#define	FLTFLIO		0x10	// ����WM�ⲿ�쳣ʱ��PWM�����������������Ϊ��������ģʽ����ע��ֻ��ENCnO==1����Ӧ�Ķ˿ڲŻᱻǿ�����գ� 
#define	EFDI		0x08	// ʹ��PWM�쳣����ж� 
#define	FDCMP		0x04	// ���Ƚ���������ɵͱ��ʱ������PWM�쳣 
#define	FDIO		0x02	// ��P2.4�ĵ�ƽ�ɵͱ��ʱ������PWM�쳣 
#define	FDIF		0x01	// ������PWM�쳣���Ƚ���������ɵͱ�߻���P2.4�ĵ�ƽ�ɵͱ�ߣ�ʱ��Ӳ���Զ�����λ��1, ����λ�жϱ�־.��Ҫ������� 

/////////////////////////////////////////////////
//STC15W4K32S4ϵ���ж�����
#define IE0_VECTOR	0  	// 0x03 External Interrupt 0 
#define TF0_VECTOR	1  	// 0x0B Timer 0 
#define IE1_VECTOR	2  	// 0x13 External Interrupt  
#define TF1_VECTOR	3  	// 0x1B Timer 1 
#define SIO_VECTOR	4  	// 0x23 Serial port (UART1)

#define ADC_VECTOR  5 	// 0x2b ADC SPI Interrupt
#define LVD_VECTOR  6   // 0x33										
#define PCA_VECTOR  7   // 0x3B										
#define SIO2_VECTOR 8   // 0x43 Serial 2 port (UART2)	 									
#define SPI_VECTOR  9   // 0x4B
#define IE2_VECTOR	10  // 0x53 External Interrupt 2 
#define IE3_VECTOR	11  // 0x5b External Interrupt 3
#define TF2_VECTOR	12  // 0x63 Timer 2 
#define IE4_VECTOR	16  // 0x83 External Interrupt 4 
 
#define SIO3_VECTOR  	17  // 0x8B Serial 3 port (UART3)
#define SIO4_VECTOR  	18  // 0x93 Serial 4 port (UART4)	
#define TF3_VECTOR		19  // 0x9B Timer 3
#define TF4_VECTOR		20  // 0xA3 Timer 4  
#define	CMP_VECTOR		21  // 0xAB Comparator
#define	PWM_VECTOR		22	// 0xB3
#define	PWMFD_VECTOR	23	// 0xBB


																																							 
///////////////////////////////////////////////////////////////////////////////////////

#define ADC90CLK  0x60  
#define ADC180CLK 0x40 
#define ADC360CLK 0x20 
#define ADC540CLK 0x00 

#define ADC_START  3
#define ADC_FLAG   4
#define ADC_POWER  7

#define ADCCH0 0  
#define ADCCH1 1
#define ADCCH2 2
#define ADCCH3 3
#define ADCCH4 4
#define ADCCH5 5
#define ADCCH6 6
#define ADCCH7 7

#define ISP_DISABLE (IAP_CONTR=0,IAP_CMD=0,IAP_TRIG=0,IAP_ADRH=0x80,IAP_ADRL=0)

uchar StcAdc(uchar ch)
{ uchar i,t;	
	t=1<<ADC_POWER | ADC540CLK; t|=ch; 
	ADC_CONTR=t; 
	for(i=30;i;i--);
	t|=1<<ADC_START; 
	ADC_CONTR=t;
	_nop_();_nop_();_nop_();_nop_();
	while(!(ADC_CONTR&(1<<ADC_FLAG)));
	i=ADC_RES;
	t&=~(1<<ADC_FLAG | 1<<ADC_START);
	ADC_CONTR=t;
	return i;
}

uchar RdEeprom(uchar adrH,uchar adrL)
{ 									 
	IAP_ADRH=adrH;
	IAP_ADRL=adrL;									
	IAP_CONTR=0x83;
	IAP_CMD=0x01;
	IAP_TRIG=0x5a;
	IAP_TRIG=0xa5;
	ISP_DISABLE;
	return IAP_DATA;
}
 
void WrEeprom(uchar adrH,uchar adrL,uchar da)
{						
	IAP_ADRH=adrH;
	IAP_ADRL=adrL;
	IAP_CONTR=0x83;
	IAP_CMD=0x02; 	 
	IAP_DATA=da;
	IAP_TRIG=0x5a;
	IAP_TRIG=0xa5;
	ISP_DISABLE;
}
 
void EraseEeprom(uchar adrH,uchar adrL)
{			  	
	IAP_ADRH=adrH;
	IAP_ADRL=adrL;
	IAP_CONTR=0x83;
	IAP_CMD=0x03; 
	IAP_TRIG=0x5a;
	IAP_TRIG=0xa5;
	ISP_DISABLE;
}

#endif

