/************************************************************
程序说明：
本程序实现彩信发送


关于图片的代码获取方法：
请打开光盘中的调试工具文件夹，找到sscom32.exe，将需要的图片通过软件的打开文件按钮打开，hex显示选上
，在该软件的接收区内会显示该图片的十六进制代码，然后复制出来，不过此时是十六进制代码，keil要识别hex
代码还要在每个代码的前面加上0X，如原来是 FF 38 46 ...  要改为：0XFF,0X38,0X46...,粘贴到keil上组成数
组代替原来的数组就可以了。不过在代码中还要修改设置图片是设置的大小，这个大小在刚才打开图片的时候有显示
"at+cmmsdown=\"pic\",4051,100000\r"	 中断4051是图片大小，根据不同图片大小而改变
*************************************************************/





#include "stc12c5a.h"
#include "systerm.h"
#include "gprs.h"
#include "timer.h"
#include "picture.h"

uint i = 0;

void main()
{

//  调整输入函数的加载值可以改变串口波特率
//	Uart1Init(0,1,184);//初始化串口，设置波特率4800
//	Uart2Init(0,1,220);//初始化串口，设置波特率9600
//	Uart2Init(0,1,232);//初始化串口，设置波特率14400
//	Uart1Init(0,1,253);//初始化串口，设置波特率115200


	Timer0Init();
	Uart1Init(0,1,220);//初始化串口，设置波特率9600
	Uart2Init(0,1,220);//初始化串口，设置波特率9600


//启动Sim300要按下复位键大概3秒钟
	GPRS_RST = 0;//Sim300 复位键拉低
	DelaySec(3);//延时3秒
	GPRS_RST = 1;//Sim300 复位键拉高
	//Sim300启动完成

	LED5_OFF;
	LED6_OFF;
	LED7_OFF;
	LED8_OFF;

	while(1)
	{
		if(KEY4_PRESS)//按键4发送指令查询当前服务状态
		{
			while(KEY4_PRESS)
			{
				LED8_ON;	
			}
			LED8_OFF;
			Uart2Sends("at+cops?\r");//发送指令查询当前服务状态				
		}

		if(KEY5_PRESS)//按键5发送指令拨打10086电话号码
		{
			while(KEY5_PRESS)
			{
				LED7_ON;	
			}
			LED7_OFF;
			Uart2Sends("at+cmmscurl=\"mmsc.monternet.com\"\r");	//设置URL
			DelaySec(1);
			Uart2Sends("at+cmmsnetcfg=1,\"cmwap\"\r");//设置APN
			DelaySec(1);
			Uart2Sends("at+cmmsproto=1,\"10.0.0.172\",80\r");//设置mms协议属性			
			DelaySec(1);
			Uart2Sends("at+cmmssendcfg=6,3,0,0,2,4\r");//设置mms的发送参数			
			DelaySec(1);
			Uart2Sends("AT+CGATT?\r");//查询该模块是否支持mms
			DelaySec(1);
			Uart2Sends("AT+CMMSEDIT=0\r");//关闭编辑状态，这样在模块的buff区的数据将被删除						
			DelaySec(1);
			Uart2Sends("AT+CMMSEDIT=1\r");//打开编辑状态，这个状态才可以发送mms			
			DelaySec(1);
			Uart2Sends("at+cmmsdown=\"pic\",4051,100000\r");//设置发送的图片的大小(byte)和需要用来传输的时间100000ms，4051这个数字从sscom32.exe得到的，打开图片的时候显示在最上面		
			DelaySec(1);
			i = 0;
			while(i<sizeof(hua))//发送图片的数据给模块，该数据用sscom32.exe得到，该软件在调试工具文件夹中
			{
				Uart2Send(hua[i]);
				i++;	
			}
			Uart2Sends("\r");//结束符号
			DelaySec(2);
			Uart2Sends("at+cmmsdown=\"title\",3,30000\r");//设置发送的mms的名字，大小，时间		
			DelaySec(1);
			Uart2Sends("hua");//发送名字，hua			
			DelaySec(1);
			Uart2Sends("at+cmmsdown=\"text\",5,30000\r");//设置发送的mms的文本内容，小于1000bytes			
			DelaySec(1);
			Uart2Sends("ilove");//发送文本内容			
			DelaySec(1);
			Uart2Sends("at+cmmsrecp=\"15296811486\"\r");//发送的号码，自己修改			
			DelaySec(1);
			Uart2Sends("at+cmmsview\r");//查看发送的内容是否已经存入模块
			DelaySec(1);
			Uart2Sends("at+cmmssend\r");//发送mms			
			DelaySec(7);
//			Uart2Sends("at+cmmssave\r");//保存mms到模块，模块只能保存两个mms			
//			DelaySec(1);
			Uart2Sends("AT+CMMSEDIT=0\r");//关闭编辑状态			
			DelaySec(1);		
												
		}


	}
	
}

