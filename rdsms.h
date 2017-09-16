

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
								sprintf(tempbuf,"%s%s\n%s",&mid[4],"�ſ�����","�����ֻ������Ѱ�!");
								MsgBuf(rxSmsTel,tempbuf); bSavePhone=1;
							}
						else MsgBuf(rxSmsTel,"��֤����,����ʧ��!");
						break;

					case 1: //"#A����1,����2,������7#"
						if(strcmp(phone[0],rxSmsTel)!=0) {MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!"); break;}
						if(GetDigitalStr(t,tempbuf,rxSmsTel)==0) {MsgBuf(phone[0],"û��Ҫ�󶨵ĺ���"); break;}
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
						if(!n) { MsgBuf(phone[0],"�¼ӵĹ���Ա�����Ѵ���!"); break;}
						k=0; for(i=1;i<8;i++) if(phone[i][0]) k++;
						if(n+k>7) MsgBuf(phone[0],"������������,����ʧ��!");
						else
							{ t=1;
								for(i=0;i<n;i++)
									{ for(;t<8;t++) if(!phone[t][0]) break;
										GetDigitalStr(a[i],tempbuf,phone[t++]);
									}
								i=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����");
								sprintf(tempbuf+i,"%s%u%s","����Ա����󶨳ɹ�!��",(uint)(n+k),"��");
								MsgBuf(phone[0],tempbuf); bSavePhone=1;
							}
						break;

					case 2: //"#D����1,����2,������7#"
						if(strcmp(phone[0],rxSmsTel)!=0) {MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!"); break;}
						if(strcmp(tempbuf,"#D#")==0)
							{for(t=1;t<8;t++) phone[t][0]=0; MsgBuf(phone[0],"���й���Ա����ɾ���ɹ�!"); bSavePhone=1; break;}
						t=0; n=0;
						while(1)
							{ if(t>=Len(tempbuf)) break;
								t=GetDigitalStr(t,tempbuf,rxSmsTel);
								if(!t) break;
								for(i=1;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) {phone[i][0]=0; n++; break;}
							}
						sprintf(tempbuf,"%s%u%s","��ɾ��",(uint)n,"������Ա����!");
						MsgBuf(phone[0],tempbuf); bSavePhone=1;
						break;

					case 3: //"#?#"	
						if(strcmp(tempbuf,"#?#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else
							if(i) uc_WH_=0x01;
							else uc_WH_=0x83;
						break;

					case 4: //"#CS#"	
						if(strcmp(tempbuf,"#CS#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else {RTSData(); uc_CS_=2;}
						break;

					case 5: //"#CY#" 	
						if(strcmp(tempbuf,"#CY#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else uc_CY_=4;
						break;
					/*	
					case 6: //"#CF#" 
						if(strcmp(tempbuf,"#CF#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else
							{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ŷ�������"); //15
								t+=sprintf(tempbuf+t,"%s%u\n","����ģʽ��",(int)ucF01); //7
								t+=sprintf(tempbuf+t,"%s%u%s","ͣ��ʱ�䣺",(int)ucF02,"��"); t+=sprintf(tempbuf+t,"%s","\n"); //9 
								t+=sprintf(tempbuf+t,"%s%u%s","����ʱ�䣺",(int)ucF03,"��"); t+=sprintf(tempbuf+t,"%s","\n"); //9 
								t+=sprintf(tempbuf+t,"%s%.1f","������ʱ��",(float)ucF04/10); t+=sprintf(tempbuf+t,"%s\n","��"); //10
								t+=sprintf(tempbuf+t,"%s%.1f","ͣ����ʱ��",(float)ucF05/10); t+=sprintf(tempbuf+t,"%s","��");	
								MsgBuf(rxSmsTel,tempbuf);
							}
						break;	
						
					case 7: //"#CH#"
						if(strcmp(tempbuf,"#CH#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else uc_CH_=2;
						break;
					*/ //for NWK-380-04	

					/*case 8: //"#CL#" 
						if(strcmp(tempbuf,"#CL#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else uc_CL_=1;
						break;
						*/ //for NWK-380-03
						
					case 9: //"#CD#"
						if(strcmp(tempbuf,"#CD#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else
							{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����"); //13 
								if(!ucD01) t+=sprintf(tempbuf+t,"%s\n","ѹ��������ϼ�⣺����"); //12
								else t+=sprintf(tempbuf+t,"%s\n","ѹ��������ϼ�⣺����");
								t+=sprintf(tempbuf+t,"%s%u%s","���ص���ֵ��",(uint)ucD02,"A\n"); //10	
								t+=sprintf(tempbuf+t,"%s%u%s","���ر����ָ�������",(uint)ucD04,"��/Сʱ"); //15
								MsgBuf(rxSmsTel,tempbuf);
							}
						break;

					case 10: //"#CT#"
						if(strcmp(tempbuf,"#CT#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else
							{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����"); //13 
								if(!ucT01) t+=sprintf(tempbuf+t,"%s\n","ͨ��ģʽ����GPRS");
								else if(ucT01==1)  t+=sprintf(tempbuf+t,"%s\n","ͨ��ģʽ����GSM");
								else  t+=sprintf(tempbuf+t,"%s\n","ͨ��ģʽ��GPRS��GSM"); //14

								t+=sprintf(tempbuf+t,"%s%u%s","GSM���ͼ����",(uint)ucT02,"Сʱ\n");
								t+=sprintf(tempbuf+t,"%s%u%s","GPRS���ͼ����",(uint)ucT03,"����");
								MsgBuf(rxSmsTel,tempbuf);	
							}
						break;
						
					case 11://"#CZ#" //��ѯ��������ǰʱ��	
						if(strcmp(tempbuf,"#CZ#")!=0) break;
						for(i=0;i<8;i++) if(strcmp(rxSmsTel,phone[i])==0) break;
						if(i==8) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else
							{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����"); //13 
								t+=sprintf(tempbuf+t,"%s%s",year,"��"); t+=sprintf(tempbuf+t,"%s%s",month,"��"); 
								t+=sprintf(tempbuf+t,"%s%s",day,"��"); t+=sprintf(tempbuf+t,"%s%s",hour,"ʱ"); 
								t+=sprintf(tempbuf+t,"%s%s",mintue,"��"); //t+=sprintf(tempbuf+t,"%s%s",sec,"��");
								MsgBuf(rxSmsTel,tempbuf);	
							}
						break;
						
					case 12: //"#CP#" //��ϵͳ����� //ֻ�г����������
						if(strcmp(tempbuf,"#CP#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else uc_CP_=2;
						break;
						
					case 13: //"#CM#" //��ѯ�Ѱ󶨵����й���Ա����
						if(strcmp(tempbuf,"#CM#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else
							if(phonenum==1)
								{ sprintf(tempbuf,"%s%s",&mid[4],"�ſ�����δ���κκ���");
									MsgBuf(phone[0],tempbuf);
								}
							else
								if(phonenum-1>4) uc_CM_=0x82;
								else uc_CM_=0x01;
						break;

					case 14: //"#CI#" //��ID��PIN��
						if(strcmp(tempbuf,"#CI#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else
							{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����"); //13
								t+=sprintf(tempbuf+t,"%s%s\n","�豸PIN�룺",pin);
								t+=sprintf(tempbuf+t,"%s%s","�豸���룺",mid);
								MsgBuf(phone[0],tempbuf);
							}
						break;

					case 15: //"#OFF#"
						if(strcmp(tempbuf,"#OFF#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else
							if(ucP03) 
								{ if(bOFF)
										{ sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����Ϊ�ػ�״̬");
											MsgBuf(phone[0],tempbuf);
										}
									bOFF=1;
								}
							else
								{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����"); //13
									t+=sprintf(tempbuf+t,"%s\n","��ֹ����������ſ��ػ�");
									if(!bOFF) sprintf(tempbuf+t,"%s","ע����ǰΪ����״̬");
									else sprintf(tempbuf+t,"%s","ע����ǰΪ�ػ�״̬");
									MsgBuf(phone[0],tempbuf);
								}
						break;
						
					case 16: //"#ON#"
						if(strcmp(tempbuf,"#ON#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else
							if(ucP03) 
								{ if(!bOFF)
										{ sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����Ϊ����״̬");
											MsgBuf(phone[0],tempbuf);
										}
									bOFF=0;
								}
							else
								{ t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����"); //13
									t+=sprintf(tempbuf+t,"%s\n","��ֹ����������ſ��ػ�");
									if(!bOFF) sprintf(tempbuf+t,"%s","ע����ǰΪ����״̬");
									else sprintf(tempbuf+t,"%s","ע����ǰΪ�ػ�״̬");
									MsgBuf(phone[0],tempbuf);
								}
						break;

					case 17: //"#K#"
						if(strcmp(tempbuf,"#K#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else
							{ if(!ucP04) {ucP04=1; bSaveDat=1;}
								t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����"); //13
								t+=sprintf(tempbuf+t,"%s","�߿��������");
								if(!*moneydate) t+=sprintf(tempbuf+t,"%s","\nע���߿�����δ�趨");
								MsgBuf(phone[0],tempbuf);
							}
						break;
						
					case 18: //"#G#"
						if(strcmp(tempbuf,"#G#")!=0) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else
							{ if(ucP04) {ucP04=0; bSaveDat=1;}
								t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����"); //13
								t+=sprintf(tempbuf+t,"%s","�߿���ѹر�");
								MsgBuf(phone[0],tempbuf);
							}
						break;
						
					case 19: //"#KD"
						if(Len(tempbuf)!=12) break;
						for(t=3;t<11;t++) if(tempbuf[t]<0x30 || tempbuf[t]>0x39) break;
						if(t!=11) break;
						if(strcmp(phone[0],rxSmsTel)!=0) MsgBuf(rxSmsTel,"Ȩ�޲���,����ʧ��!");
						else
							{ for(t=0;t<8;t++) moneydate[t]=tempbuf[t+3];
								EraseEeprom(0x08,1); WrEeprom(0x08,0,0xcc);
								for(t=0;t<8;t++) WrEeprom(0x08,t+1,moneydate[t]);
								t=sprintf(tempbuf,"%s%s\n",&mid[4],"�ſ�����"); //13
								t+=sprintf(tempbuf+t,"%s%s%s","�߿�����(",moneydate,")�趨�ɹ�");
								if(ucP04) sprintf(tempbuf+t,"%s","\nע���߿��Ϊ����״̬");
								else sprintf(tempbuf+t,"%s","\nע���߿��Ϊ�ر�״̬");
								MsgBuf(phone[0],tempbuf);
							}
						break;
				}
		}
}
