#define TRUE 1
#define FALSE 0

#define FILE_VIDEO "/dev/video0"
#define BMP 	   "/home/swhite/Smart-Patrol/camera/picture/image.bmp"
#define YUV 	   "/home/swhite/Smart-Patrol/camera/picture/image.yuv"

#define IMAGEWIDTH 640
#define IMAGEHEIGHT 480

static int fd_video;
static static v4l2_capability cap;
struct v4l2_fmtdesc fmtdesc;
struct v4l2_format fmt,fmtack;
struct v4l2_streamparm setfps;
struct v4l2_requestbuffers req;
struct v4l2_buffer buf;
enum v4l2_buf_type type;

unsigned char frame_buffer[IMAGEHEIGHT*IMAGEWIDTH*3];

int init_v4l2(void);
int v4l2_grab(void);
int close_v4l2(void);

int yuyv_2_rgb888(void);

