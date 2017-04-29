#include "video_capture.h"

/*****************************************************
 *函数名 : v4l2_grab()
 *功 能  : 为摄像头分配内存，以及采集数据，并将YUV格式的
 		   数据转换为BMP
 *参数   : void
 *返回值 : int 返回FALSE出错，TRUE成功
 ******************************************************/
int v4l2_grab(void)
{
	unsigned int n_buffers;

	/*申请缓存区*/
	req.count = 4;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;
	if(ioctl(fd_video, VIDIOC_REQBUFS, &req) == -1)
	{
		printf("request for buffers error\n");
	}


	/*mmap for buffers*/
	buffers = malloc(req.count*sizeof(*buffers));
	if(!buffers)
	{
		printf("Out of memory\n");
		return FALSE;
	}

	for(n_buffers = 0;n_buffers < req.count;n_buffers++)
	{
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = n_buffers;

		/*query buffers*/
		if(ioctl(fd_video, VIDIOC_QUERYBUF, &buf) == -1)
		{
			printf("query buffer error\n");
			return FALSE;
		}

		buffers[n_buffers].length = buf.length;

		/*map*/
		buffers[n_buffers].start = mmap(NULL, buf.length,\
										PROT_READ | PROT_WRITE, MAP_SHARED, \
									   	fd_video, buf.m.offset);
		if(buffers[n_buffers].start == MAP_FAILED)
		{
			printf("buffer map error");
			return FALSE;
		}
	}

	/*queue*/
	for(n_buffers = 0;n_buffers < req.count;n_buffers++)
	{
		buf.index = n_buffers;
		ioctl(fd_video, VIDIOC_QBUF, &buf);
	}

	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl(fd_video, VIDIOC_STREAMON, &type);

	ioctl(fd_video, VIDIOC_DQBUF, &buf);

	printf("grab yuyv OK\n");
	return TRUE;
}


int yuyv_2_rgb888(void)
{
     int i,j;
     unsigned char y1,y2,u,v;
     int r1,g1,b1,r2,g2,b2;
     char * pointer;
     
     pointer = buffers[0].start;
     
     for(i=0;i<480;i++)
     {
         for(j=0;j<320;j++)
         {
             y1 = *( pointer + (i*320+j)*4);
             u  = *( pointer + (i*320+j)*4 + 1);
             y2 = *( pointer + (i*320+j)*4 + 2);
             v  = *( pointer + (i*320+j)*4 + 3);
             
             r1 = y1 + 1.042*(v-128);
             g1 = y1 - 0.34414*(u-128) - 0.71414*(v-128);
             b1 = y1 + 1.772*(u-128);
             
             r2 = y2 + 1.042*(v-128);
             g2 = y2 - 0.34414*(u-128) - 0.71414*(v-128);
             b2 = y2 + 1.772*(u-128);
             
             if(r1>255)
                 r1 = 255;
             else if(r1<0)
                 r1 = 0;
             
             if(b1>255)
                 b1 = 255;
             else if(b1<0)
                 b1 = 0;    
             
             if(g1>255)
                 g1 = 255;
             else if(g1<0)
                 g1 = 0;    
                 
             if(r2>255)
                 r2 = 255;
             else if(r2<0)
                 r2 = 0;
             
             if(b2>255)
                 b2 = 255;
             else if(b2<0)
                 b2 = 0;    
             
             if(g2>255)
                 g2 = 255;
             else if(g2<0)
                 g2 = 0;        
                 
             *(frame_buffer + ((480-1-i)*320+j)*6    ) = (unsigned char)b1;
             *(frame_buffer + ((480-1-i)*320+j)*6 + 1) = (unsigned char)g1;
             *(frame_buffer + ((480-1-i)*320+j)*6 + 2) = (unsigned char)r1;
             *(frame_buffer + ((480-1-i)*320+j)*6 + 3) = (unsigned char)b2;
             *(frame_buffer + ((480-1-i)*320+j)*6 + 4) = (unsigned char)g2;
             *(frame_buffer + ((480-1-i)*320+j)*6 + 5) = (unsigned char)r2;
         }
     }
     printf("change to RGB OK \n");
}
