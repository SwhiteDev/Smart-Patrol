/************************************************************
����˵����
������ʵ�ֲ��ŷ���


����ͼƬ�Ĵ����ȡ������
��򿪹����еĵ��Թ����ļ��У��ҵ�sscom32.exe������Ҫ��ͼƬͨ������Ĵ��ļ���ť�򿪣�hex��ʾѡ��
���ڸ�����Ľ������ڻ���ʾ��ͼƬ��ʮ�����ƴ��룬Ȼ���Ƴ�����������ʱ��ʮ�����ƴ��룬keilҪʶ��hex
���뻹Ҫ��ÿ�������ǰ�����0X����ԭ���� FF 38 46 ...  Ҫ��Ϊ��0XFF,0X38,0X46...,ճ����keil�������
�����ԭ��������Ϳ����ˡ������ڴ����л�Ҫ�޸�����ͼƬ�����õĴ�С�������С�ڸղŴ�ͼƬ��ʱ������ʾ
"at+cmmsdown=\"pic\",4051,100000\r"	 �ж�4051��ͼƬ��С�����ݲ�ͬͼƬ��С���ı�
*************************************************************/





#include "stc12c5a.h"
#include "systerm.h"
#include "gprs.h"
#include "timer.h"
#include "picture.h"

uint i = 0;

void main()
{

//  �������뺯���ļ���ֵ���Ըı䴮�ڲ�����
//	Uart1Init(0,1,184);//��ʼ�����ڣ����ò�����4800
//	Uart2Init(0,1,220);//��ʼ�����ڣ����ò�����9600
//	Uart2Init(0,1,232);//��ʼ�����ڣ����ò�����14400
//	Uart1Init(0,1,253);//��ʼ�����ڣ����ò�����115200


	Timer0Init();
	Uart1Init(0,1,220);//��ʼ�����ڣ����ò�����9600
	Uart2Init(0,1,220);//��ʼ�����ڣ����ò�����9600


//����Sim300Ҫ���¸�λ�����3����
	GPRS_RST = 0;//Sim300 ��λ������
	DelaySec(3);//��ʱ3��
	GPRS_RST = 1;//Sim300 ��λ������
	//Sim300�������

	LED5_OFF;
	LED6_OFF;
	LED7_OFF;
	LED8_OFF;

	while(1)
	{
		if(KEY4_PRESS)//����4����ָ���ѯ��ǰ����״̬
		{
			while(KEY4_PRESS)
			{
				LED8_ON;	
			}
			LED8_OFF;
			Uart2Sends("at+cops?\r");//����ָ���ѯ��ǰ����״̬				
		}

		if(KEY5_PRESS)//����5����ָ���10086�绰����
		{
			while(KEY5_PRESS)
			{
				LED7_ON;	
			}
			LED7_OFF;
			Uart2Sends("at+cmmscurl=\"mmsc.monternet.com\"\r");	//����URL
			DelaySec(1);
			Uart2Sends("at+cmmsnetcfg=1,\"cmwap\"\r");//����APN
			DelaySec(1);
			Uart2Sends("at+cmmsproto=1,\"10.0.0.172\",80\r");//����mmsЭ������			
			DelaySec(1);
			Uart2Sends("at+cmmssendcfg=6,3,0,0,2,4\r");//����mms�ķ��Ͳ���			
			DelaySec(1);
			Uart2Sends("AT+CGATT?\r");//��ѯ��ģ���Ƿ�֧��mms
			DelaySec(1);
			Uart2Sends("AT+CMMSEDIT=0\r");//�رձ༭״̬��������ģ���buff�������ݽ���ɾ��						
			DelaySec(1);
			Uart2Sends("AT+CMMSEDIT=1\r");//�򿪱༭״̬�����״̬�ſ��Է���mms			
			DelaySec(1);
			Uart2Sends("at+cmmsdown=\"pic\",4051,100000\r");//���÷��͵�ͼƬ�Ĵ�С(byte)����Ҫ���������ʱ��100000ms��4051������ִ�sscom32.exe�õ��ģ���ͼƬ��ʱ����ʾ��������		
			DelaySec(1);
			i = 0;
			while(i<sizeof(hua))//����ͼƬ�����ݸ�ģ�飬��������sscom32.exe�õ���������ڵ��Թ����ļ�����
			{
				Uart2Send(hua[i]);
				i++;	
			}
			Uart2Sends("\r");//��������
			DelaySec(2);
			Uart2Sends("at+cmmsdown=\"title\",3,30000\r");//���÷��͵�mms�����֣���С��ʱ��		
			DelaySec(1);
			Uart2Sends("hua");//�������֣�hua			
			DelaySec(1);
			Uart2Sends("at+cmmsdown=\"text\",5,30000\r");//���÷��͵�mms���ı����ݣ�С��1000bytes			
			DelaySec(1);
			Uart2Sends("ilove");//�����ı�����			
			DelaySec(1);
			Uart2Sends("at+cmmsrecp=\"15296811486\"\r");//���͵ĺ��룬�Լ��޸�			
			DelaySec(1);
			Uart2Sends("at+cmmsview\r");//�鿴���͵������Ƿ��Ѿ�����ģ��
			DelaySec(1);
			Uart2Sends("at+cmmssend\r");//����mms			
			DelaySec(7);
//			Uart2Sends("at+cmmssave\r");//����mms��ģ�飬ģ��ֻ�ܱ�������mms			
//			DelaySec(1);
			Uart2Sends("AT+CMMSEDIT=0\r");//�رձ༭״̬			
			DelaySec(1);		
												
		}


	}
	
}

