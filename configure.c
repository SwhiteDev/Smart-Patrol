/*
 * 配置文件，用来判断用哪个USB设备进行PPP拨号
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <termios.h>
#define RFID_DEV_NAME "/dev/ttyUSB0"
#define GPRS_DEV_NAME "/dev/ttyUSB1"
#define RFID_DVR_NAME "cp210x"
#define GPRS_DVR_NAME "ch341-uart"
#define WVDIAL_CONFIG "/home/swhite/Smart-Patrol/wvdial.config"
#define WVDIAL_CONFIG_SYS "/etc/wvdial.conf"

char *rfid_dev_name = NULL;
char *gprs_dev_name = NULL;

char *config[] = {
					"[Dialer Defaults]\r\n",
					"Modem=%s\r\n",
					"Baud=9600\r\n",
					"Phone=*99***1#\r\n",
					"Init1=ATZ\r\n",
					"Init2=AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n",
					"Init3=ATQ0 V1 E1 S0=0 &C1 &D2 S11=55 +FCLASS=0\r\n",
					"Username=a\r\n",
					"Password=a\r\n",
					"New PPPD=1\r\n"
				};

/*
 * popen进程间通信,将执行命令的结果fgets入缓冲
 */
static int system_ret(char *ret_buffer, int size, char *cmd)
{
	FILE *fstream=NULL;    
     
    if(NULL == (fstream=popen(cmd,"r")))    
    {   
        fprintf(stderr,"execute command failed: %s",strerror(errno));    
        return -1;    
    }   
    if(NULL != fgets(ret_buffer, size, fstream))   
    {   
        printf("%s",ret_buffer);  
    }   
    else  
    {  
        pclose(fstream);  
        return -1;  
    }  
    pclose(fstream);
    return 0;
}

/*
 * 获取USB名
 */
int parser_usb_dev(char **rfid_dev_name, char **gprs_dev_name)
{
	char buffer_usb0[1024];  
	char buffer_usb1[1024];
    memset(buffer_usb0, 0x00, sizeof(buffer_usb0)); 
    memset(buffer_usb1, 0x00, sizeof(buffer_usb1));
	if(-1 == system_ret(buffer_usb0, sizeof(buffer_usb0), "dmesg | grep ttyUSB0")){
		printf("popen exec 0 error\n");
		return -1;
	}
	if(-1 == system_ret(buffer_usb1, sizeof(buffer_usb1), "dmesg | grep ttyUSB1")){
		printf("popen exec 1 error\n");
		return -1;
	}
	if(strstr(buffer_usb0, RFID_DVR_NAME) != NULL && strstr(buffer_usb1, GPRS_DVR_NAME)){
		*rfid_dev_name = RFID_DEV_NAME;
		*gprs_dev_name = GPRS_DEV_NAME;
		return 0;
	}
	else if(strstr(buffer_usb0, GPRS_DVR_NAME) != NULL && strstr(buffer_usb1, RFID_DVR_NAME)){
		*rfid_dev_name = GPRS_DEV_NAME;
		*gprs_dev_name = RFID_DEV_NAME;
		return 0;
	}

	return -1;
}

int main(int argc, char **argv)
{
	int fd = -1;
	int ret;
	int i = 0;
	char temp[32] = {0};

	if(parser_usb_dev(&rfid_dev_name, &gprs_dev_name) == -1){
		printf("device name error!");
		exit(0);
	}
	printf("gprs dev name: %s, rfid dev name: %s\n", gprs_dev_name, rfid_dev_name);
	sprintf(temp, config[1], gprs_dev_name);
	if((fd = open(WVDIAL_CONFIG, O_WRONLY | O_TRUNC)) < 0){
		printf("open wvdial.config failed!\n");
		return -1;
	}

	/* 到此已判断好RFID & GPRS USB设备，写入wvdial.config */
	write(fd, config[0], strlen(config[0]));
	write(fd, temp, strlen(temp));
	for(i = 2;i < 10;i++){
		if((ret = write(fd, config[i], strlen(config[i])) < 0)){
			printf("write config info failed!\n");
			return -1;
		}
	}
	printf("configure ok!\nnow you can run pppd to connect with ISP.\n");

}
