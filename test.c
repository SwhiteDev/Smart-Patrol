#include <stdio.h>
#include <string.h>
void main()
{
unsigned char *post[] = {"POST /xg/index.php/admin/upload/record\r\n", 				\
							   "Host: www.hicoder.cn\r\n", 				\
						       "Content-Type:application/x-www-form-urlencoded\r\n", 				\
						   	   "Content-Length:37\r\n\r\n", 				\
							   "key=iot&location=002&device=device001"  				\
							  };
	int i;
	for(i = 0;i < 5;i++)
	{
	printf("%s\n",post[i]);
	printf("%d\n",strlen(post));
	}
}
