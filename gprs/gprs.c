#include "gprs.h"

#define TIMEOUT 3
#define GPRS_READ_BUFF_SIZE 1024
#define FLAGS "HTTP/1.1"
#define CLEAR(x) memset(x, '\0', sizeof(x))

unsigned char *cmd[] = {
						"AT\r",
						"AT+CCID\r",
						"AT+CSQ\r",
						"AT+CGCLASS=\"B\"\r",
						"AT+CGDCONT=1,\"IP\",\"CMNET\"\r",
						"AT+CGATT=1\r",
						"AT+CIPCSGP=1,\"CMNET\"\r",
						"AT+CIPSTART=\"TCP\",\"182.254.244.212\",\"80\"\r",
						"AT+CIPSEND\r",
						"AT+CIPCLOSE\r"
					   };
unsigned char *post[] = {
						"POST /xg/index.php/admin/upload/record HTTP/1.1\r\n",
						"Host: www.hicoder.cn\r\n",
						"Content-Type: application/x-www-form-urlencoded\r\n",
						"Content-Length: %d\r\n\r\n",
						"key=%s&location=%s&device=%s"
						};


int gprs_init(const char *DEV)
{
	int i;
	serial_attr attr = {0};
	int fd = -1;
	char rbuff[GPRS_READ_BUFF_SIZE] = {0};
	if(-1 == (fd = serial_open(DEV))){
		fprintf(stderr, "gprs serial open failed\n");
		return -1;
	}
	
	attr.baudrate = 9600;
	attr.databits = BITS_DATA_8;
	attr.parity   = BITS_PARITY_NONE;
	attr.stopbits = BITS_STOP_1;
	if(0 != set_serial_attr(fd, &attr)){
		fprintf(stderr, "set gprs serial_attr failed\n");
		return -1;
	}


	for(i = 0;i < 7;i++){
		if(-1 == gprs_run_cmd(fd, rbuff, cmd[i]))
			return -1;
	}
	return fd;
}


int gprs_send(int fd, const char *key_id, const char *location_id, const char *device_id)
{
	int i,j;
	int timeout = 0;
	char over_flag = 0x1a;
	char rbuff[GPRS_READ_BUFF_SIZE] = {0};
	char http_len[32] = {0};
	char http_payload[128] = {0};
	if(fd < 0 || key_id == NULL || location_id == NULL || device_id == NULL){
		fprintf(stderr, "bad param!\n");
		return -1;
	}

	//do{
		/*TCP connect*/
		for(i = 7;i < 9;i++){
			serial_flushio(fd);
			if(-1 == gprs_run_cmd(fd, rbuff, cmd[i]))
				return -1;
		}

		/*send post*/
		for(j = 0;j < 3;j++){
			if(-1 == gprs_send_string(fd, rbuff, post[j]))
				return -1;
		}
		
		CLEAR(http_payload);
		sprintf(http_payload, post[4], key_id, location_id, device_id);
		CLEAR(http_len);
		sprintf(http_len, post[3], strlen(http_payload));

		/*send http_len*/
		if(-1 == gprs_send_string(fd, rbuff, http_len))
			return -1;

		/*send http_payload*/
		if(-1 == gprs_send_string(fd, rbuff, http_payload))
			return -1;

		/*send over_flag*/
		if(-1 == gprs_send_string(fd, rbuff, &over_flag))
			return -1;
//	}while(gprs_2_web_ok(rbuff) && (++timeout) < TIMEOUT);

	if(-1 == gprs_run_cmd(fd, rbuff, cmd[9])){
		fprintf(stdout, "close gprs failed!");
		return -1;
	}

	return 0;
}

int gprs_run_cmd(int fd, char *rbuff, char *cmd)
{
	int r_ret, w_ret;

	CLEAR(rbuff);
	if(-1 == (w_ret = serial_write(fd, cmd, strlen(cmd)))){
		printf("gprs write AT CMD: %s faild\n", cmd);
		return -1;
	}
	printf("gprs write AT CMD: %s\n", cmd);
	printf("write size: %d\n", w_ret);
	sleep(2);

	if((r_ret = serial_read(fd, rbuff, GPRS_READ_BUFF_SIZE)) > 0){
		rbuff[r_ret] = '\0';
		printf("GPRS return: %s\n", rbuff);
		printf("return size: %d\n", r_ret);
		sleep(2);
	}
	
	return 0;
}

int gprs_send_string(int fd, char *rbuff, char *str)
{
	int r_ret, w_ret;

	CLEAR(rbuff);
	if(-1 == (w_ret = serial_write(fd, str, strlen(str)))){
		printf("GPRS write string: %s failed\n", str);
		return -1;
	}
	printf("GPRS write string: %s\n", str);
	printf("write size: %d\n", w_ret);
	usleep(150000);

	if(*str == 0x1a){
		if((r_ret = serial_read(fd, rbuff, GPRS_READ_BUFF_SIZE)) > 0){
			rbuff[r_ret] = '\0';
			printf("Web server return: %s\n", rbuff);
			printf("return size: %d\n", r_ret);
			usleep(1);
		}
	}
	return 0;
}

/*
 *check web return is ok
 */
int gprs_2_web_ok(const char *rbuffer)
{
	char *flag = strstr(rbuffer, FLAGS);
	if(flag == NULL){
		return !0;
	}
	return strncmp("200", flag+9, 3);
}
