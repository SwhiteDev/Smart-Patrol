#include "rfid.h"


int rfid_init(const char *DEV)
{
	int fd = serial_open(DEV);
	if(-1 == fd){
		fprintf(stderr, "open rfid serial faild\n");
		return -1;
	}

	serial_attr attr = {0};
	attr.baudrate = 9600;
	attr.databits = BITS_DATA_8;
	attr.parity   = BITS_PARITY_NONE;
	attr.stopbits = BITS_STOP_1;
	if(0 != set_serial_attr(fd, &attr)){
		fprintf(stderr, "set rfid serial_attr failed\n");
	}

	return fd;
}


/*
 *card_check
 */
static int card_check(const char *card_buff)
{
	return (card_buff[0]^card_buff[1]^card_buff[2]^card_buff[3] == card_buff[4]);
}


/*
 *read rfid card_id
 */
int rfid_read(int fd, char *card_id)
{
	char card_buff[16];
	int ret = -1;
	if(fd < 0 || NULL == card_id){
		fprintf(stderr, "bad param\n");
		return -1;
	}

	memset(card_buff, 0xff, 8);
	if((ret = serial_read(fd, card_buff, 16)) > 0){
		if(!card_check(card_buff)){
			fprintf(stderr, "card check failed\n");
			return -1;
		}
		card_buff[ret] = '\0';
		printf("read card:%s\n", card_buff);
		sprintf(card_id, "%02x%02x%02x%02x", card_buff[0], card_buff[1], card_buff[2], card_buff[3]);
	}

	return ret;
}
