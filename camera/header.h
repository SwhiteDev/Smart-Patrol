typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef signed int LONG;
typedef unsigned int DWORD;

typedef struct tagBITMAPFILE_HEADER
{
	WORD  bfType;
	DWORD bfSize;
	DWORD bfReserved;
	DWORD bfOffBits;
}BITMAPFILE_HEADER;

typedef struct tagBITMAPINFO_HEADER
{
	DWORD biSize;
	DWORD biWidth;
	DWORD biHeight;
	WORD  biPlanes;
	WORD  biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	DWORD biXPelsPerMeter;
	DWORD biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
}BITMAPINFO_HEADER;
