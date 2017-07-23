#ifndef RFID_H
#define RFID_H
#include "../serial/serial.h"


int rfid_init(const char *DEV);
int rfid_read(int fd, char *card_id);


#endif
