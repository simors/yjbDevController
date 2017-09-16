

uchar code* code msgcod[]={	"#P",		"#A",		"#D",		"#?#", 		//0-3
														"#CS#",	"#CY#",	"#CF",	"#CH#",		//4-7
														"#CL#",	"#CD#",	"#CT#",	"#CZ#",		//8-11
														"#CP#",	"#CM#",	"#CI#",	"#OFF#", 	//12-15
														"#ON#",	"#K#",	"#G#", 	"#KD",		//16-19
													};


void RTSData(void);
void LoadSmsRtsData(uchar t,uchar num);

bit bSavePhone;

void SavePhone(void)
{ uchar t,i;
	EraseEeprom(0x04,0);
	WrEeprom(0x04,0,0xcc);
	for(t=0;t<sizeof(phone)/sizeof(phone[0]);t++)
		for(i=0;i<sizeof(phone[0]);i++) WrEeprom(0x04,t*sizeof(phone[0])+i+1,phone[t][i]);
}

void RdSMSPro(void)
{ uchar t,n,i,k;
	uchar xdata a[15];

	ucBellNum=4;
	t=FindString(0,"+86",0); GetDigitalStr(t,rxbuf,rxSmsTel); GetSMSMsg(tempbuf,2);
	if(tempbuf[0]!='#' || tempbuf[Len(tempbuf)-1]!='#') return;
	for(t=0;t<sizeof(msgcod)/2;t++) if(FindString(0,msgcod[t],0)) break;
	if(t<sizeof(msgcod)/2)
		{ switch(t)
				{ case 0: //"#Pxxxx#" 
						sprintf(a,"#P%s#",password);
						if(!strcmp(a,tempbuf)) 
							{ sprintf(phone[0],"%s",rxSmsTel);
								sprintf(tempbuf,"%s%s\n%s",&mid[4],"号控制器","超级手机号码已绑定!");
								MsgBuf(rxSmsTel,tempbuf); bSavePhone=1;
							}
						else MsgBuf(rxSmsTel,"验证错误,操作失败!");
						break;

					case 1: //"#A号码1,号码2,…号码7#"
						if(strcmp(phone[0],rxSmsTel)!=0) {MsgBuf(rxSmsTel,"权限不够,操作失败!"); break;}
						if(GetDigitalStr(t,tempbuf,rxSmsTel)==0) {MsgBuf(phone[0],"没有要绑定的号码"); break;}
						for(t=0;t<8;t++) a[t]=0;
						t=0; n=0;
						while(1)
							{ 				 
								if(t>=Len(tempbuf)) break;
								t=GetDigitalStr(t,tempbuf,rxSmsTel);
								if(!t) break;
								for(i=1;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
								if(i==8) a[n++]=t-Len(rxSmsTel);
							}
						if(!n) { MsgBuf(phone[0],"新加的管理员号码已存在!"); break;}
						k=0; for(i=1;i<8;i++) if(phone[i][0]) k++;
						if(n+k>7) MsgBuf(phone[0],"号码数量超限,操作失败!");
						else
							{ t=1;
								for(i=0;i<n;i++)
									{ for(;t<8;t++) if(!phone[t][0]) break;
										GetDigitalStr(a[i],tempbuf,phone[t++]);
									}
								i=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器");
								sprintf(tempbuf+i,"%s%u%s","管理员号码绑定成功!共",(uint)(n+k),"个");
								MsgBuf(phone[0],tempbuf); bSavePhone=1;
							}
						break;

					case 2: //"#D号码1,号码2,…号码7#"
						if(strcmp(phone[0],rxSmsTel)!=0) {MsgBuf(rxSmsTel,"权限不够,操作失败!"); break;}
						if(strcmp(tempbuf,"#D#")==0)
							{for(t=1;t<8;t++) phone[t][0]=0; MsgBuf(phone[0],"所有管理员号码删除成功!"); bSavePhone=1; break;}
						t=0; n=0;
						while(1)
							{ if(t>=Len(tempbuf)) break;
								t=GetDigitalStr(t,tempbuf,rxSmsTel);
								if(!t) break;
								for(i=1;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) {phone[i][0]=0; n++; break;}
							}
						sprintf(tempbuf,"%s%u%s","已删除",(uint)n,"个管理员号码!");
						MsgBuf(phone[0],tempbuf); bSavePhone=1;
						break;

					case 3: //"#?#"	
						if(strcmp(tempbuf,"#?#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else
							if(i) uc_WH_=0x01;
							else uc_WH_=0x83;
						break;

					case 4: //"#CS#"	
						if(strcmp(tempbuf,"#CS#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else {RTSData(); uc_CS_=2;}
						break;

					case 5: //"#CY#" 	
						if(strcmp(tempbuf,"#CY#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else uc_CY_=4;
						break;
					/*	
					case 6: //"#CF#" 
						if(strcmp(tempbuf,"#CF#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else
							{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号风机类参数"); //15
								t+=sprintf(tempbuf+t,"%s%u\n","工作模式：",(int)ucF01); //7
								t+=sprintf(tempbuf+t,"%s%u%s","停机时间：",(int)ucF02,"分"); t+=sprintf(tempbuf+t,"%s","\n"); //9 
								t+=sprintf(tempbuf+t,"%s%u%s","开机时间：",(int)ucF03,"分"); t+=sprintf(tempbuf+t,"%s","\n"); //9 
								t+=sprintf(tempbuf+t,"%s%.1f","开机延时：",(float)ucF04/10); t+=sprintf(tempbuf+t,"%s\n","分"); //10
								t+=sprintf(tempbuf+t,"%s%.1f","停机延时：",(float)ucF05/10); t+=sprintf(tempbuf+t,"%s","分");	
								MsgBuf(rxSmsTel,tempbuf);
							}
						break;	
						
					case 7: //"#CH#"
						if(strcmp(tempbuf,"#CH#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else uc_CH_=2;
						break;
					*/ //for NWK-380-04	

					/*case 8: //"#CL#" 
						if(strcmp(tempbuf,"#CL#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else uc_CL_=1;
						break;
						*/ //for NWK-380-03
						
					case 9: //"#CD#"
						if(strcmp(tempbuf,"#CD#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else
							{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器"); //13 
								if(!ucD01) t+=sprintf(tempbuf+t,"%s\n","压机触点故障检测：禁用"); //12
								else t+=sprintf(tempbuf+t,"%s\n","压机触点故障检测：启用");
								t+=sprintf(tempbuf+t,"%s%u%s","过载电流值：",(uint)ucD02,"A\n"); //10	
								t+=sprintf(tempbuf+t,"%s%u%s","过载保护恢复次数：",(uint)ucD04,"次/小时"); //15
								MsgBuf(rxSmsTel,tempbuf);
							}
						break;

					case 10: //"#CT#"
						if(strcmp(tempbuf,"#CT#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else
							{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器"); //13 
								if(!ucT01) t+=sprintf(tempbuf+t,"%s\n","通信模式：仅GPRS");
								else if(ucT01==1)  t+=sprintf(tempbuf+t,"%s\n","通信模式：仅GSM");
								else  t+=sprintf(tempbuf+t,"%s\n","通信模式：GPRS及GSM"); //14

								t+=sprintf(tempbuf+t,"%s%u%s","GSM发送间隔：",(uint)ucT02,"小时\n");
								t+=sprintf(tempbuf+t,"%s%u%s","GPRS发送间隔：",(uint)ucT03,"分钟");
								MsgBuf(rxSmsTel,tempbuf);	
							}
						break;
						
					case 11://"#CZ#" //查询控制器当前时间	
						if(strcmp(tempbuf,"#CZ#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else
							{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器"); //13 
								t+=sprintf(tempbuf+t,"%s%s",year,"年"); t+=sprintf(tempbuf+t,"%s%s",month,"月"); 
								t+=sprintf(tempbuf+t,"%s%s",day,"日"); t+=sprintf(tempbuf+t,"%s%s",hour,"时"); 
								t+=sprintf(tempbuf+t,"%s%s",mintue,"分"); //t+=sprintf(tempbuf+t,"%s%s",sec,"秒");
								MsgBuf(rxSmsTel,tempbuf);	
							}
						break;
						
					case 12: //"#CP#" //查系统类参数 //只有超级号码可用
						if(strcmp(tempbuf,"#CP#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else uc_CP_=2;
						break;
						
					case 13: //"#CM#" //查询已绑定的所有管理员号码
						if(strcmp(tempbuf,"#CM#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else
							if(phonenum==1)
								{ sprintf(tempbuf,"%s%s",&mid[4],"号控制器未绑定任何号码");
									MsgBuf(phone[0],tempbuf);
								}
							else
								if(phonenum-1>4) uc_CM_=0x82;
								else uc_CM_=0x01;
						break;

					case 14: //"#CI#" //查ID及PIN码
						if(strcmp(tempbuf,"#CI#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else
							{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器"); //13
								t+=sprintf(tempbuf+t,"%s%s\n","设备PIN码：",pin);
								t+=sprintf(tempbuf+t,"%s%s","设备编码：",mid);
								MsgBuf(phone[0],tempbuf);
							}
						break;

					case 15: //"#OFF#"
						if(strcmp(tempbuf,"#OFF#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else
							if(ucP03) 
								{ if(bOFF)
										{ sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器为关机状态");
											MsgBuf(phone[0],tempbuf);
										}
									bOFF=1;
								}
							else
								{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器"); //13
									t+=sprintf(tempbuf+t,"%s\n","禁止超级号码短信开关机");
									if(!bOFF) sprintf(tempbuf+t,"%s","注：当前为开机状态");
									else sprintf(tempbuf+t,"%s","注：当前为关机状态");
									MsgBuf(phone[0],tempbuf);
								}
						break;
						
					case 16: //"#ON#"
						if(strcmp(tempbuf,"#ON#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else
							if(ucP03) 
								{ if(!bOFF)
										{ sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器为开机状态");
											MsgBuf(phone[0],tempbuf);
										}
									bOFF=0;
								}
							else
								{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器"); //13
									t+=sprintf(tempbuf+t,"%s\n","禁止超级号码短信开关机");
									if(!bOFF) sprintf(tempbuf+t,"%s","注：当前为开机状态");
									else sprintf(tempbuf+t,"%s","注：当前为关机状态");
									MsgBuf(phone[0],tempbuf);
								}
						break;

					case 17: //"#K#"
						if(strcmp(tempbuf,"#K#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else
							{ if(!ucP04) {ucP04=1; bSaveDat=1;}
								t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器"); //13
								t+=sprintf(tempbuf+t,"%s","催款功能已启用");
								if(!*moneydate) t+=sprintf(tempbuf+t,"%s","\n注：催款日期未设定");
								MsgBuf(phone[0],tempbuf);
							}
						break;
						
					case 18: //"#G#"
						if(strcmp(tempbuf,"#G#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else
							{ if(ucP04) {ucP04=0; bSaveDat=1;}
								t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器"); //13
								t+=sprintf(tempbuf+t,"%s","催款功能已关闭");
								MsgBuf(phone[0],tempbuf);
							}
						break;
						
					case 19: //"#KD"
						if(Len(tempbuf)!=12) break;
						for(t=3;t<11;t++) if(tempbuf[t]<0x30 || tempbuf[t]>0x39) break;
						if(t!=11) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"权限不够,操作失败!");
						else
							{ for(t=0;t<8;t++) moneydate[t]=tempbuf[t+3];
								EraseEeprom(0x08,1); WrEeprom(0x08,0,0xcc);
								for(t=0;t<8;t++) WrEeprom(0x08,t+1,moneydate[t]);
								t=sprintf(tempbuf,"%s%s\n",&mid[4],"号控制器"); //13
								t+=sprintf(tempbuf+t,"%s%s%s","催款日期(",moneydate,")设定成功");
								if(ucP04) sprintf(tempbuf+t,"%s","\n注：催款功能为启用状态");
								else sprintf(tempbuf+t,"%s","\n注：催款功能为关闭状态");
								MsgBuf(phone[0],tempbuf);
							}
						break;
				}
		}
}
