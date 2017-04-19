#include <stdio.h>
#include <string.h>
void main()
{
const unsigned char *post[] = {
 								"POST /xg/index.php/admin/upload/record\r\n", 				\
								"Host: www.hicoder.cn\r\n", 				\
								"Content-Type:application/x-www-form-urlencoded\r\n", 				\
								"Content-Length:37\r\n\r\n", 				\
								"key=iot&location=002&device=device001"  				\
						      };
	printf("%d\n",strlen(post));
}
