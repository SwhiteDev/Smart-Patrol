#ifndef GPRS_H
#define GPRS_H

#include "../serial/serial.h"


int gprs_init(const char *DEV);
int gprs_send(int fd, const char *key_id, const char *location_id, const char *device_id);
int gprs_send_string(int fd, char *rbuff, char *str);
int gprs_run_cmd(int fd, char *rbuff, char *cmd);
int gprs_2_web_ok(const char *http_ret_buff);

#endif
