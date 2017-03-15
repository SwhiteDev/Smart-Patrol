#include "timer.h" 
#include "stc12c5a.h"

volatile unsigned char data timer0_cnt = 0;
volatile int data sec_cnt = 0;

void Timer0Init(void)
{

	TMOD=0x01;                     //���ö�ʱ��0Ϊ������ʽ1
	TH0=(65536-45872)/256;         //�����ֵ,11.0592M,50ms
	TL0=(65536-45872)%256;

	EA=1;                          //�����ж�
	ET0=1;                        //����ʱ��0�ж�
    TR0=1;                         //������ʱ��0
}


void timer0() interrupt 1
{
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;

	timer0_cnt++;

	if(timer0_cnt == 20)
	{
		timer0_cnt = 0;
		sec_cnt++;
	}
		
}

void DelaySec(unsigned char sec)
{
	sec_cnt = 0;
	while(sec_cnt < sec);		
}


