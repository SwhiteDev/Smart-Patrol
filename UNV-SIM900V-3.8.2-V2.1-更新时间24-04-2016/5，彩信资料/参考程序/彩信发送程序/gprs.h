#ifndef _GPRS_H_
#define _GPRS_H_

#include "stc12c5a.h"
#include "systerm.h"
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//ÉùÃ÷º¯Êý

char Uart2Init(char s2smod,char brtx12,unsigned char reload);
void Uart2Send(uchar i);
void Uart2Sends(uchar* data_at);
char Uart1Init(char smod,char brtx12,unsigned char reload);
void Uart1Send(uchar i);
void Uart1Sends(uchar* at);


#endif

