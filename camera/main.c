#include "header.h"
#include "init.h"
#include "video_capture.h"


int main(void)
{
	FILE *fp1,*fp2;

	BITMAPFILE_HEADER bf;
	BITMAPINFO_HEADER bi;

	fp1 = fopen(BMP, "wb");
	if(!fp1)
	{
		printf("open BMP error\n");
		return FALSE;
	}

	fp2 = fopen(YUV, "wb");
	if(!fp2)
	{
		printf("open YUV error\n");
		return FALSE;
	}

	if(init_v4l2() == FALSE)
	{
		return FALSE;
	}
	
	/*set bit_map_info_header*/
	bi.biSize = 40;
	bi.biWidth = IMAGEWIDTH;
	bi.biHeight = IMAGEHEIGHT;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biCompression = 0;
	bi.biSizeImage = IMAGEHEIGHT*IMAGEWIDTH*3;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	/*set bit_map_file_header*/
	bf.bfType = 0x4d42;
	bf.bfSize = 54 + bi.biSizeImage;
	bf.bfReserved = 0;
	bf.bfOffBits = 54;

	v4l2_grab();
	
	fwrite(buffers[0].start, 640*480*2, 1, fp2);
	printf("save YUV OK\n");

	yuyv_2_rgb888();
	fwrite(&bf, 14, 1, fp1);
	fwrite(&bi, 40, 1, fp1);
	fwrite(frame_buffer, bi.biSizeImage, 1, fp1);
	printf("save BMP OK\n");

	fclose(fp1);
	fclose(fp2);
	close_v4l2();
	return TRUE;
}
