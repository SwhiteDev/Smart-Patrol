#ifndef _TIMER_H_
#define _TIMER_H_

extern volatile unsigned char data timer0_cnt;
extern volatile int data sec_cnt;

void Timer0Init(void);
void DelaySec(unsigned char sec);

#endif