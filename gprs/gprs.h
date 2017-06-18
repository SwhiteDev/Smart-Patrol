#ifndef GPRS_H
#define GPRS_H

#include "../serial/serial.h"


int gprs_init(const char *DEV);
int gprs_send(int fd, const char *key_id, const char *location_id, const char *device_id);
int gprs_send_string(int fd, char *str);
int gprs_run_cmd(int fd, char *cmd);
int gprs_is_200_ok(const char *http_ret_buff);

#endif
