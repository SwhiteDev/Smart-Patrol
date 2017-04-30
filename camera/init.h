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

#define FILE_VIDEO "/dev/video2"
#define BMP 	   "/home/swhite/Smart-Patrol/camera/picture/image.bmp"
#define YUV 	   "/home/swhite/Smart-Patrol/camera/picture/image.yuv"

#define IMAGEWIDTH 640  
#define IMAGEHEIGHT 480

int fd_video;
unsigned char frame_buffer[IMAGEHEIGHT*IMAGEWIDTH*3];
static struct v4l2_capability cap;    //设备属性
struct v4l2_fmtdesc fmtdesc;          //帧格式
struct v4l2_format fmt,fmtack;        
struct v4l2_streamparm setfps;

int init_v4l2(void);
int close_v4l2(void);

