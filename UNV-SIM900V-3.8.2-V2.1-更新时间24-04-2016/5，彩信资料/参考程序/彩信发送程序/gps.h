#ifndef _GPS_H_
#define _GPS_H_

#include "stc12c5a.h"
char gps_uart1_initial(char smod,char brtx12,unsigned char reload);
void gps_uart1_send(char i);
void gps_uart1_sends(char* at);

#endif
