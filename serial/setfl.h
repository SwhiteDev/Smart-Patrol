#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

void set_fl(int fd, int flags);

void clr_fl(int fd, int flags);
