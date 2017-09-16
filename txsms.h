
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
		{ if(!ucSenErr[0]) {t+=sprintf(tempbuf+t,"%s%s","库温：",stmp1); t+=sprintf(tempbuf+t,"%s\n","℃");} //10	
			//if(!ucSenErr[1]) {t+=sprintf(tempbuf+t,"%s%s","管温：",stmp2); t+=sprintf(tempbuf+t,"%s\n","℃");} //10 //for NWK-380-04
			/* for NWK-380-03 */
			//if(!ucHumSenErr) {t+=sprintf(tempbuf+t,"%s%s","湿度：",shum); t+=sprintf(tempbuf+t,"%s\n","%");} //8
			t+=sprintf(tempbuf+t,"%s%s","A相：",sA); t+=sprintf(tempbuf+t,"%s","A\n"); //7
			t+=sprintf(tempbuf+t,"%s%s","B相：",sB); t+=sprintf(tempbuf+t,"%s","A\n"); //7
			t+=sprintf(tempbuf+t,"%s%sA","C相：",sC); //6
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
	t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器");
	t+=sprintf(tempbuf+t,"%s\n",warn[smswid-1]);
	LoadSmsRtsData(t,ucSmsWarn);
	MsgBuf(phone[phoneid[phonenum-(ucSmsWarn+1)/2]],tempbuf);
	ucSmsWarn--;
}

void SmsRtsDatLoad(void)
{ uchar t;
	t=sprintf(tempbuf,"%s%s\n",&mid[4],"号实时数据");
	LoadSmsRtsData(t,ucSmsRTS);
	MsgBuf(phone[phoneid[phonenum-(ucSmsRTS+1)/2]],tempbuf);
	ucSmsRTS--;
}

void Sms_CS_Load(void)
{ uchar t; 
	t=sprintf(tempbuf,"%s%s\n",&mid[4],"号实时数据");
	LoadSmsRtsData(t,uc_CS_);
	MsgBuf(rxSmsTel,tempbuf);
	uc_CS_--;
}

void Sms_CY_Load(void)
{ uchar t;
	if(uc_CY_==4)
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号压机类参数"); //15
			t+=sprintf(tempbuf+t,"%s%.1f","设定温度：",(float)iY01/10); t+=sprintf(tempbuf+t,"%s\n","℃"); //12
			t+=sprintf(tempbuf+t,"%s%.1f","控制温差：",(float)iY02/10); t+=sprintf(tempbuf+t,"%s\n","℃"); //11 
			if(!ucY03) t+=sprintf(tempbuf+t,"%s\n","探头故障压机停机");
			else t+=sprintf(tempbuf+t,"%s\n","探头故障压机间歇开停"); //12
			t+=sprintf(tempbuf+t,"%s%u%s","探头故障时压机开：",ucY04,"分"); //14
		}
	else if(uc_CY_==3)
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号压机类参数"); //15 
			t+=sprintf(tempbuf+t,"%s%u","探头故障时压机停：",ucY05); t+=sprintf(tempbuf+t,"%s\n","分"); //14	
			t+=sprintf(tempbuf+t,"%s%.1f","库温校准：",(float)iY06/10); t+=sprintf(tempbuf+t,"%s\n","℃"); //12
			t+=sprintf(tempbuf+t,"%s%.1f","库温超高温差：",(float)iY07/10); t+=sprintf(tempbuf+t,"%s\n","℃"); //13
			t+=sprintf(tempbuf+t,"%s%.1f","库温超低温差：",(float)iY08/10); t+=sprintf(tempbuf+t,"%s","℃"); //13
		}
	else if(uc_CY_==2)
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号压机类参数"); //15 
			t+=sprintf(tempbuf+t,"%s%u","压机停机延时：",uiY09); t+=sprintf(tempbuf+t,"%s\n","秒"); //12 
			if(!ucY10) t+=sprintf(tempbuf+t,"%s\n","峰谷用电模式：禁用"); //10
			else t+=sprintf(tempbuf+t,"%s\n","峰谷用电模式：启用");
			t+=sprintf(tempbuf+t,"%s%02u%s","谷电起始时间：",uiY11/100,"时"); //10
					t+=sprintf(tempbuf+t,"%02u%s\n",uiY11%100,"分"); //4 
			t+=sprintf(tempbuf+t,"%s%02u%s","谷电结束时间：",uiY12/100,"时"); //10
					t+=sprintf(tempbuf+t,"%02u%s",uiY12%100,"分"); //3
		}
	else		
		{	t=sprintf(tempbuf,"%s%s\n",&mid[4],"号压机类参数"); //15
			t+=sprintf(tempbuf+t,"%s%.1f","谷电控温温度：",(float)iY13/10); t+=sprintf(tempbuf+t,"%s\n","℃"); //12
			t+=sprintf(tempbuf+t,"%s%u%s","库温超高报警延时：",ucY14,"分");
		}	
	MsgBuf(rxSmsTel,tempbuf);
	uc_CY_--;
} 

void Sms_CH_Load(void)
{ uchar t;
	if(uc_CH_==2)
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号化霜类参数"); //15 
			if(!ucH01) t+=sprintf(tempbuf+t,"%s\n","化霜模式：电加热");
			else t+=sprintf(tempbuf+t,"%s\n","化霜模式：热气加热"); //11
			t+=sprintf(tempbuf+t,"%s%u%s","化霜周期：",ucH02,"小时\n"); //11
			t+=sprintf(tempbuf+t,"%s%u%s","化霜时间：",ucH03,"分\n"); //10
			t+=sprintf(tempbuf+t,"%s%.1f","化霜结束温度：",(float)iH04/10); t+=sprintf(tempbuf+t,"%s","℃"); //12
		}
	else
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号化霜类参数"); //15
			t+=sprintf(tempbuf+t,"%s%u%s","化霜滴水时间：",ucH05,"分"); //10 
			if(!ucH06) t+=sprintf(tempbuf+t,"%s\n","化霜周期计时方式：累计通电"); //14
			else t+=sprintf(tempbuf+t,"%s\n","化霜周期计时方式：累计制冷");
			t+=sprintf(tempbuf+t,"%s%.1f","化霜超温温差：",(float)iH07/10); t+=sprintf(tempbuf+t,"%s\n","℃"); //12
			if(ucH08) t+=sprintf(tempbuf+t,"%s","化霜时库温超高报警：启用");
			else t+=sprintf(tempbuf+t,"%s","化霜时库温超高报警：禁用");
		} 
	MsgBuf(rxSmsTel,tempbuf);
	uc_CH_--;
}

void Sms_CL_Load(void)
{ uchar t;
	if(uc_CL_==1)
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号湿度类参数"); //15 
			t+=sprintf(tempbuf+t,"%s%u","设定湿度：",ucL01); t+=sprintf(tempbuf+t,"%s\n","%"); //9
			t+=sprintf(tempbuf+t,"%s%u","上限差：",ucL02); t+=sprintf(tempbuf+t,"%s\n","%"); //8
			t+=sprintf(tempbuf+t,"%s%u","下限差：",ucL03); t+=sprintf(tempbuf+t,"%s\n","%"); //8
			t+=sprintf(tempbuf+t,"%s%u","报警上限差：",ucL04); t+=sprintf(tempbuf+t,"%s\n","%"); //10
			t+=sprintf(tempbuf+t,"%s%u","报警下限差：",ucL05); t+=sprintf(tempbuf+t,"%s\n","%"); //10
			t+=sprintf(tempbuf+t,"%s%d","湿度校正：",cL06); t+=sprintf(tempbuf+t,"%s","%"); //9
		}
	MsgBuf(rxSmsTel,tempbuf);
	uc_CL_--;
}

void Sms_CP_Load(void)
{ uchar t;
	if(uc_CP_==2)
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号系统类参数"); //15 
			t+=sprintf(tempbuf+t,"%s%s\n","手机绑定密码：",password); //12

			if(!ucP02) t+=sprintf(tempbuf+t,"%s\n","远程控制：禁用"); //8
			else t+=sprintf(tempbuf+t,"%s\n","远程控制：启用");

			if(!ucP03) t+=sprintf(tempbuf+t,"%s\n","短信远程开关机：禁止"); //11
			else t+=sprintf(tempbuf+t,"%s\n","短信远程开关机：允许");

			if(!ucP04) t+=sprintf(tempbuf+t,"%s\n","催款功能：禁用"); //8
			else t+=sprintf(tempbuf+t,"%s","催款功能：启用");
		}
	else
		{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号系统类参数"); //15
			if(!ucP05) t+=sprintf(tempbuf+t,"%s\n","催款控制模式：显示均为“-”"); //15
			else if(ucP05==1) t+=sprintf(tempbuf+t,"%s\n","催款控制模式：间歇开停机");
			else t+=sprintf(tempbuf+t,"%s\n","催款控制模式：停机");
			t+=sprintf(tempbuf+t,"%s%u","催款期间开机：",ucP06); t+=sprintf(tempbuf+t,"%s\n","分"); //11
			t+=sprintf(tempbuf+t,"%s%u","催款期间停机：",ucP07); t+=sprintf(tempbuf+t,"%s\n","分"); //11
			if(!*moneydate) t+=sprintf(tempbuf+t,"%s","催款日期：未设定");
			else t+=sprintf(tempbuf+t,"%s%s","催款日期：",moneydate); //13
		}
	MsgBuf(rxSmsTel,tempbuf);
	uc_CP_--;
}

void Sms_CM_Load(void)
{ uchar t,i;
	t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器绑定的号码:"); //19
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
	t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器:");
	sprintf(tempbuf+t,"%s","已关机!");
	MsgBuf(phone[phoneid[phonenum-uc_OFF_]],tempbuf);
	uc_OFF_--;
}

void Sms_ON_Load(void)
{ uchar t;
	t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器:");
	sprintf(tempbuf+t,"%s","已开机!");
	MsgBuf(phone[phoneid[phonenum-uc_ON_]],tempbuf);
	uc_ON_--;
}

void Sms_WH_Load(void)
{ uchar t;
	switch(uc_WH_)
		{ case 0x83:
			case 1:  
				t=sprintf(tempbuf,"%s\n","#CS#查实时数据"); 		//10	
				t+=sprintf(tempbuf+t,"%s\n","#CY#查压机参数"); 	//10
				//+=sprintf(tempbuf+t,"%s\n","#CH#查化霜参数"); 	//10 //for NWK-380-04
				//t+=sprintf(tempbuf+t,"%s\n","#CL#查湿度参数"); 	//10 //for NWK-380-03
				t+=sprintf(tempbuf+t,"%s\n","#CD#查电机参数"); 	//10
				t+=sprintf(tempbuf+t,"%s\n","#CT#查通信参数"); 	//10
				t+=sprintf(tempbuf+t,"%s","#CZ#查当前时间"); 		//9
				break;

			case 0x82:
				t=sprintf(tempbuf,"%s\n","#CP# 查系统参数"); //11	
				t+=sprintf(tempbuf+t,"%s\n","#CM# 查已绑定的所有管理员号码"); //18
				t+=sprintf(tempbuf+t,"%s\n","#A号码1,号码2# 绑定管理员号码"); //19
				t+=sprintf(tempbuf+t,"%s","#D号码1,号码2# 删除指定管理员号码"); //20
				break;

			case 0x81:
				t=sprintf(tempbuf,"%s\n","#D#删除所有管理员号码"); //13	
				t+=sprintf(tempbuf+t,"%s\n","#OFF#关机指令"); //10
				t+=sprintf(tempbuf+t,"%s\n","#ON#开机指令"); //9
				t+=sprintf(tempbuf+t,"%s\n","#K#开启催款功能"); //10 
				t+=sprintf(tempbuf+t,"%s\n","#KD年年年年月月日日#设定催款日期"); //19	
				t+=sprintf(tempbuf+t,"%s","#G#关闭催款功能"); //9 
				break;
		} 
	MsgBuf(rxSmsTel,tempbuf);
	uc_WH_--;		 
	if(!(uc_WH_&0x0f)) uc_WH_=0;
}