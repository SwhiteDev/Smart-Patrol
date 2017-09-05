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
#define WVDIAL_CONFIG "/home/swhite/Smart-Patrol/gprs/wvdial.config"

char *rfid_dev_name = NULL;
char *gprs_dev_name = NULL;

//exec shell and ret results
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

//get /dev/ttyUSBx return two param 
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
	if(parser_usb_dev(&rfid_dev_name, &gprs_dev_name) == -1){
		printf("device name error!");
		exit(0);
	}
	if((fd = open(WVDIAL_CONFIG, O_WRONLY)) < 0){
		printf("open wvdial.config failed!\n");
		return -1;
	}
	lseek(fd, 6, SEEK_SET);
	if((ret = write(fd, gprs_dev_name, strlen(gprs_dev_name))< 0)){
		printf("write device name failed!\n");
		return -1;
	}

}
