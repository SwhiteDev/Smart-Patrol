/*
 *
 *
 *
 *
 *
 *
 */
#include "./serial/serial.h"
#include "./record_sql/record.h"
#include "./gprs/gprs.h"
#include "./rfid/rfid.h"

unsigned char *device_id = "device007";   
//full path
#define RECORD_FILE_NAME "/home/swhite/Smart-Patrol/record_sql/record.db"
#define RFID_DEV_NAME "/dev/ttyUSB0"
#define GPRS_DEV_NAME "/dev/ttyUSB1"
#define TABLE_NAME "record"
#define KEY_ID "iot"

#define RFID_DVR_NAME "cp210x"
#define GPRS_DVR_NAME "ch341-uart"


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
	int rfid_fd = -1;
	int gprs_fd = -1;
	int flag = 0;
	sqlite3 *db = NULL;
	unsigned char card_id[16] = {0};
	char *rfid_dev_name = NULL, *gprs_dev_name = NULL;
	int ret = sqlite3_open(RECORD_FILE_NAME, &db);
	if(ret)
	{
		fprintf(stderr, "can't open database: %s\n", sqlite3_errmsg(db));
	}
	sql_create_table(db, TABLE_NAME);
	sleep(1);
	if(parser_usb_dev(&rfid_dev_name, &gprs_dev_name) == -1){
		printf("dev name parser error:rfid:%s gprs:%s\n",rfid_dev_name, gprs_dev_name);
		return -1;
	}

	printf("rfid_name:%s  gprs_name:%s\n", rfid_dev_name, gprs_dev_name);
	if((rfid_fd = rfid_init(rfid_dev_name)) < 0){
		fprintf(stderr, "open rfid serial error\n");
		goto rfid_error;
	}
	if((gprs_fd = gprs_init(gprs_dev_name)) < 0){
		fprintf(stderr, "open gprs serial error\n");
		goto gprs_error;
	}

	while(1)
	{
		memset(card_id, 0x00, 16);
		flag = rfid_read(rfid_fd, card_id);
		printf("waiting card...\n");
		sleep(1);
		printf("card_id:%s\n", card_id);
		if(flag > 0)
		{
			printf("card_id:%s\n", card_id);
			if(sql_insert(db,TABLE_NAME, card_id, device_id) < 0){
				//fprintf(stderr, "insert error\n");
				
			}
			printf("gprs_fd:%d\n", gprs_fd);
			if(gprs_send(gprs_fd,KEY_ID, card_id, device_id) < 0){
				fprintf(stderr, "send error\n");
				continue;
			}
		}
	}

gprs_error:
	serial_close(gprs_fd);
rfid_error:
	serial_close(rfid_fd);
	return 0;
}
