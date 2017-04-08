#include <camera.h>
int init_v4l2(void)
{
	int i = 0;
	int ret = 0;

	//open dev
	if((fd_video = open(FILE_VIDEO,O_RDWR)) == -1)
	{
		printf("open v4l interface failed!\n");
		return (FALSE);
	}

	//query cap
	if(ioctl(fd_video,VIDIOC_QUERYCAP,&cap) == -1)
	{
		printf("open device %s failed:unable to query device!\n",FILE_VIDEO);
		return (FALSE);
	}
	else
	{
		printf("driver:\t\t%s\n",cap.driver);
		printf("card:\t\t%s\n",cap.card);
		printf("bus_info:\t%s\n",cap.bus_info);
		printf("version:\t%d\n",cap.version);
		printf("capabilities:\t%x\n",cap.capabilities);

		if((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == V4L2_CAP_VIDEO_CAPTURE)
		printf("Device %s:supports capture.\n",FILE_VIDEO);
		if((cap.capabilities & V4L2_CAP_STREAMING) == V4L2_CAP_STREAMING)
		printf("Device %s:supports streaming.\n",FILE_VIDEO);

		//emu all support fmt
		fmtdesc.index = 0;
		fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		printf("Support format:\n");
		while(ioctl(fd_video,VIDIOC_ENUM_FMT,&fmtdesc) != -1)
		{
			printf("\t%d.%s\n",fmtdesc.index+1,fmtdesc.description);
			fmtdesc.index++;
		} 

		//set fmt
		fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
		fmt.fmt.pix.height = IMAGEHEIGHT;
		fmt.fmt.pix.width = IMAGEWIDTH;
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;


	}
}
