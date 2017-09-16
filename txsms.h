
uchar xdata ucSmsWarn=0;
uchar xdata ucSmsRTS=0;
uchar xdata uc_CS_=0;
uchar xdata uc_CY_=0;
uchar xdata uc_CH_=0;
uchar xdata uc_CL_=0;

uchar xdata uc_CP_=0;
uchar xdata uc_CM_=0;

uchar xdata uc_OFF_=0;
uchar xdata uc_ON_=0;
uchar xdata uc_WH_=0; //#?#


void MsgBuf(uchar *tel,uchar* msg)
{ sprintf(msgtel,"%s",tel); sprintf(msgdat,"%s",msg);}


void LoadSmsRtsData(uchar t,uchar num)
{
	if(!(num%2))
		{ if(!ucSenErr[0]) {t+=sprintf(tempbuf+t,"%s%s","���£�",stmp1); t+=sprintf(tempbuf+t,"%s\n","��");} //10	
			//if(!ucSenErr[1]) {t+=sprintf(tempbuf+t,"%s%s","���£�",stmp2); t+=sprintf(tempbuf+t,"%s\n","��");} //10 //for NWK-380-04
			/* for NWK-380-03 */
			//if(!ucHumSenErr) {t+=sprintf(tempbuf+t,"%s%s","ʪ�ȣ�",shum); t+=sprintf(tempbuf+t,"%s\n","%");} //8
			t+=sprintf(tempbuf+t,"%s%s","A�ࣺ",sA); t+=sprintf(tempbuf+t,"%s","A\n"); //7
			t+=sprintf(tempbuf+t,"%s%s","B�ࣺ",sB); t+=sprintf(tempbuf+t,"%s","A\n"); //7
			t+=sprintf(tempbuf+t,"%s%sA","C�ࣺ",sC); //6
		}
	else
		{ t+=sprintf(tempbuf+t,"%s\n",yjzt[yjztV]);
			//t+=sprintf(tempbuf+t,"%s\n",hszt[hsztV]); //for NWK-380-04
			//t+=sprintf(tempbuf+t,"%s\n",fjzt[fjztV]); //for NWK-380-04
			//t+=sprintf(tempbuf+t,"%s\n",jszt[jsztV]); //for NWK-380-03
			//t+=sprintf(tempbuf+t,"%s",qszt[qsztV]); //for NWK-380-03
		}
}


void SmsWarnLoad(void)
{ uchar t;
	t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����");
	t+=sprintf(tempbuf+t,"%s\n",warn[smswid-1]);
	LoadSmsRtsData(t,ucSmsWarn);
	MsgBuf(phone[phoneid[phonenum-(ucSmsWarn+1)/2]],tempbuf);
	ucSmsWarn--;
}

void SmsRtsDatLoad(void)
{ uchar t;
	t=sprintf(tempbuf,"%s%s\n",&mid[4],"��ʵʱ����");
	LoadSmsRtsData(t,ucSmsRTS);
	MsgBuf(phone[phoneid[phonenum-(ucSmsRTS+1)/2]],tempbuf);
	ucSmsRTS--;
}

void Sms_CS_Load(void)
{ uchar t; 
	t=sprintf(tempbuf,"%s%s\n",&mid[4],"��ʵʱ����");
	LoadSmsRtsData(t,uc_CS_);
	MsgBuf(rxSmsTel,tempbuf);
	uc_CS_--;
}

void Sms_CY_Load(void)
{ uchar t;
	if(uc_CY_==4)
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"��ѹ�������"); //15
			t+=sprintf(tempbuf+t,"%s%.1f","�趨�¶ȣ�",(float)iY01/10); t+=sprintf(tempbuf+t,"%s\n","��"); //12
			t+=sprintf(tempbuf+t,"%s%.1f","�����²",(float)iY02/10); t+=sprintf(tempbuf+t,"%s\n","��"); //11 
			if(!ucY03) t+=sprintf(tempbuf+t,"%s\n","̽ͷ����ѹ��ͣ��");
			else t+=sprintf(tempbuf+t,"%s\n","̽ͷ����ѹ����Ъ��ͣ"); //12
			t+=sprintf(tempbuf+t,"%s%u%s","̽ͷ����ʱѹ������",ucY04,"��"); //14
		}
	else if(uc_CY_==3)
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"��ѹ�������"); //15 
			t+=sprintf(tempbuf+t,"%s%u","̽ͷ����ʱѹ��ͣ��",ucY05); t+=sprintf(tempbuf+t,"%s\n","��"); //14	
			t+=sprintf(tempbuf+t,"%s%.1f","����У׼��",(float)iY06/10); t+=sprintf(tempbuf+t,"%s\n","��"); //12
			t+=sprintf(tempbuf+t,"%s%.1f","���³����²",(float)iY07/10); t+=sprintf(tempbuf+t,"%s\n","��"); //13
			t+=sprintf(tempbuf+t,"%s%.1f","���³����²",(float)iY08/10); t+=sprintf(tempbuf+t,"%s","��"); //13
		}
	else if(uc_CY_==2)
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"��ѹ�������"); //15 
			t+=sprintf(tempbuf+t,"%s%u","ѹ��ͣ����ʱ��",uiY09); t+=sprintf(tempbuf+t,"%s\n","��"); //12 
			if(!ucY10) t+=sprintf(tempbuf+t,"%s\n","����õ�ģʽ������"); //10
			else t+=sprintf(tempbuf+t,"%s\n","����õ�ģʽ������");
			t+=sprintf(tempbuf+t,"%s%02u%s","�ȵ���ʼʱ�䣺",uiY11/100,"ʱ"); //10
					t+=sprintf(tempbuf+t,"%02u%s\n",uiY11%100,"��"); //4 
			t+=sprintf(tempbuf+t,"%s%02u%s","�ȵ����ʱ�䣺",uiY12/100,"ʱ"); //10
					t+=sprintf(tempbuf+t,"%02u%s",uiY12%100,"��"); //3
		}
	else		
		{	t=sprintf(tempbuf,"%s%s\n",&mid[4],"��ѹ�������"); //15
			t+=sprintf(tempbuf+t,"%s%.1f","�ȵ�����¶ȣ�",(float)iY13/10); t+=sprintf(tempbuf+t,"%s\n","��"); //12
			t+=sprintf(tempbuf+t,"%s%u%s","���³��߱�����ʱ��",ucY14,"��");
		}	
	MsgBuf(rxSmsTel,tempbuf);
	uc_CY_--;
} 

void Sms_CH_Load(void)
{ uchar t;
	if(uc_CH_==2)
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"�Ż�˪�����"); //15 
			if(!ucH01) t+=sprintf(tempbuf+t,"%s\n","��˪ģʽ�������");
			else t+=sprintf(tempbuf+t,"%s\n","��˪ģʽ����������"); //11
			t+=sprintf(tempbuf+t,"%s%u%s","��˪���ڣ�",ucH02,"Сʱ\n"); //11
			t+=sprintf(tempbuf+t,"%s%u%s","��˪ʱ�䣺",ucH03,"��\n"); //10
			t+=sprintf(tempbuf+t,"%s%.1f","��˪�����¶ȣ�",(float)iH04/10); t+=sprintf(tempbuf+t,"%s","��"); //12
		}
	else
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"�Ż�˪�����"); //15
			t+=sprintf(tempbuf+t,"%s%u%s","��˪��ˮʱ�䣺",ucH05,"��"); //10 
			if(!ucH06) t+=sprintf(tempbuf+t,"%s\n","��˪���ڼ�ʱ��ʽ���ۼ�ͨ��"); //14
			else t+=sprintf(tempbuf+t,"%s\n","��˪���ڼ�ʱ��ʽ���ۼ�����");
			t+=sprintf(tempbuf+t,"%s%.1f","��˪�����²",(float)iH07/10); t+=sprintf(tempbuf+t,"%s\n","��"); //12
			if(ucH08) t+=sprintf(tempbuf+t,"%s","��˪ʱ���³��߱���������");
			else t+=sprintf(tempbuf+t,"%s","��˪ʱ���³��߱���������");
		} 
	MsgBuf(rxSmsTel,tempbuf);
	uc_CH_--;
}

void Sms_CL_Load(void)
{ uchar t;
	if(uc_CL_==1)
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"��ʪ�������"); //15 
			t+=sprintf(tempbuf+t,"%s%u","�趨ʪ�ȣ�",ucL01); t+=sprintf(tempbuf+t,"%s\n","%"); //9
			t+=sprintf(tempbuf+t,"%s%u","���޲",ucL02); t+=sprintf(tempbuf+t,"%s\n","%"); //8
			t+=sprintf(tempbuf+t,"%s%u","���޲",ucL03); t+=sprintf(tempbuf+t,"%s\n","%"); //8
			t+=sprintf(tempbuf+t,"%s%u","�������޲",ucL04); t+=sprintf(tempbuf+t,"%s\n","%"); //10
			t+=sprintf(tempbuf+t,"%s%u","�������޲",ucL05); t+=sprintf(tempbuf+t,"%s\n","%"); //10
			t+=sprintf(tempbuf+t,"%s%d","ʪ��У����",cL06); t+=sprintf(tempbuf+t,"%s","%"); //9
		}
	MsgBuf(rxSmsTel,tempbuf);
	uc_CL_--;
}

void Sms_CP_Load(void)
{ uchar t;
	if(uc_CP_==2)
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"��ϵͳ�����"); //15 
			t+=sprintf(tempbuf+t,"%s%s\n","�ֻ������룺",password); //12

			if(!ucP02) t+=sprintf(tempbuf+t,"%s\n","Զ�̿��ƣ�����"); //8
			else t+=sprintf(tempbuf+t,"%s\n","Զ�̿��ƣ�����");

			if(!ucP03) t+=sprintf(tempbuf+t,"%s\n","����Զ�̿��ػ�����ֹ"); //11
			else t+=sprintf(tempbuf+t,"%s\n","����Զ�̿��ػ�������");

			if(!ucP04) t+=sprintf(tempbuf+t,"%s\n","�߿�ܣ�����"); //8
			else t+=sprintf(tempbuf+t,"%s","�߿�ܣ�����");
		}
	else
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"��ϵͳ�����"); //15
			if(!ucP05) t+=sprintf(tempbuf+t,"%s\n","�߿����ģʽ����ʾ��Ϊ��-��"); //15
			else if(ucP05==1) t+=sprintf(tempbuf+t,"%s\n","�߿����ģʽ����Ъ��ͣ��");
			else t+=sprintf(tempbuf+t,"%s\n","�߿����ģʽ��ͣ��");
			t+=sprintf(tempbuf+t,"%s%u","�߿��ڼ俪����",ucP06); t+=sprintf(tempbuf+t,"%s\n","��"); //11
			t+=sprintf(tempbuf+t,"%s%u","�߿��ڼ�ͣ����",ucP07); t+=sprintf(tempbuf+t,"%s\n","��"); //11
			if(!*moneydate) t+=sprintf(tempbuf+t,"%s","�߿����ڣ�δ�趨");
			else t+=sprintf(tempbuf+t,"%s%s","�߿����ڣ�",moneydate); //13
		}
	MsgBuf(rxSmsTel,tempbuf);
	uc_CP_--;
}

void Sms_CM_Load(void)
{ uchar t,i;
	t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ������󶨵ĺ���:"); //19
	if(uc_CM_&0x80)
		if(uc_CM_==0x82)
			{ for(i=1;i<4;i++) t+=sprintf(tempbuf+t,"%s\n",phone[phoneid[i]]);
				t+=sprintf(tempbuf+t,"%s",phone[phoneid[4]]);
			}
		else
			{ for(i=5;i<phonenum-1;i++) t+=sprintf(tempbuf+t,"%s\n",phone[phoneid[i]]);
				t+=sprintf(tempbuf+t,"%s",phone[phoneid[i]]);
			}
	else
		{ for(i=1;i<phonenum-1;i++) t+=sprintf(tempbuf+t,"%s\n",phone[phoneid[i]]);
			t+=sprintf(tempbuf+t,"%s",phone[phoneid[i]]);
		}
	MsgBuf(rxSmsTel,tempbuf);
	uc_CM_--;
	if(!(uc_CM_&0x0f)) uc_CM_=0;
} 

void Sms_OFF_Load(void)
{ uchar t;
	t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����:");
	sprintf(tempbuf+t,"%s","�ѹػ�!");
	MsgBuf(phone[phoneid[phonenum-uc_OFF_]],tempbuf);
	uc_OFF_--;
}

void Sms_ON_Load(void)
{ uchar t;
	t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����:");
	sprintf(tempbuf+t,"%s","�ѿ���!");
	MsgBuf(phone[phoneid[phonenum-uc_ON_]],tempbuf);
	uc_ON_--;
}

void Sms_WH_Load(void)
{ uchar t;
	switch(uc_WH_)
		{ case 0x83:
			case 1:  
				t=sprintf(tempbuf,"%s\n","#CS#��ʵʱ����"); 		//10	
				t+=sprintf(tempbuf+t,"%s\n","#CY#��ѹ������"); 	//10
				//+=sprintf(tempbuf+t,"%s\n","#CH#�黯˪����"); 	//10 //for NWK-380-04
				//t+=sprintf(tempbuf+t,"%s\n","#CL#��ʪ�Ȳ���"); 	//10 //for NWK-380-03
				t+=sprintf(tempbuf+t,"%s\n","#CD#��������"); 	//10
				t+=sprintf(tempbuf+t,"%s\n","#CT#��ͨ�Ų���"); 	//10
				t+=sprintf(tempbuf+t,"%s","#CZ#�鵱ǰʱ��"); 		//9
				break;

			case 0x82:
				t=sprintf(tempbuf,"%s\n","#CP# ��ϵͳ����"); //11	
				t+=sprintf(tempbuf+t,"%s\n","#CM# ���Ѱ󶨵����й���Ա����"); //18
				t+=sprintf(tempbuf+t,"%s\n","#A����1,����2# �󶨹���Ա����"); //19
				t+=sprintf(tempbuf+t,"%s","#D����1,����2# ɾ��ָ������Ա����"); //20
				break;

			case 0x81:
				t=sprintf(tempbuf,"%s\n","#D#ɾ�����й���Ա����"); //13	
				t+=sprintf(tempbuf+t,"%s\n","#OFF#�ػ�ָ��"); //10
				t+=sprintf(tempbuf+t,"%s\n","#ON#����ָ��"); //9
				t+=sprintf(tempbuf+t,"%s\n","#K#�����߿��"); //10 
				t+=sprintf(tempbuf+t,"%s\n","#KD����������������#�趨�߿�����"); //19	
				t+=sprintf(tempbuf+t,"%s","#G#�رմ߿��"); //9 
				break;
		} 
	MsgBuf(rxSmsTel,tempbuf);
	uc_WH_--;		 
	if(!(uc_WH_&0x0f)) uc_WH_=0;
}