#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <termios.h>
#include <linux/videodev2.h>

#define TRUE 1
#define FALSE 0


#define IMAGEWIDTH 640
#define IMAGEHEIGHT 480

extern int fd_video;
extern unsigned char frame_buffer[IMAGEHEIGHT*IMAGEWIDTH*3];
struct v4l2_requestbuffers req;       //申请缓冲区
struct v4l2_buffer buf;

/*获取缓存信息，并mmap到用户空间*/
struct buffer
{
	void *start;
	unsigned int length;
} *buffers;

enum v4l2_buf_type type;

int v4l2_grab(void);
int yuyv_2_rgb888(void);

