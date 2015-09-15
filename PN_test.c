/*
 ** Copyright (C) Mox Products, Australia
 **
 ** FILE NAME: pn_test.c
 **
 ** AUTHOR: Benson Chen
 **
 ** DATE: 19 - Aug - 2015
 **
 ** FILE DESCRIPTION:
 **
 ** FUNCTIONS:
 **
 ** NOTES:
 **
 */

/*** Standard ***/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*** OS ***/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


//#include <fcntl.h>
//#include <errno.h>
//#include <signal.h>
//#include <time.h>
//#include <cutils/log.h>
//#include <cutils/atomic.h>
//#include <linux/sched.h> 
//#include <sys/ioctl.h>
//#include <android/log.h>
//#include <hardware/hardware.h>

/*** Library Local ***/
//#include "../dido_hv/hal_dido.h"

/********* Macro *********/
//#define msleep(x) usleep(x*1000)

#define Tag "PN_test"
#define success 1
#define fail 	0

#define addr_test "/Users/Benson/GitHub/mx20_PN"
#define PN_test "704-4511-1011-1000-00"
#define PN_length 21

#define HARDWARE 	"/hardware.ini"
#define MAC 		"/mac.ini"


#define Inch_7 "1"
#define Inch_10 "2"

typedef struct PN_Parameter 
{	
	char PN[PN_length];
	unsigned int  ScreenSize;   /* 1: 7 LCD 1024*600 CTP ;2: 10 LCD 1024*600 CTP ;3: Reserved */
	unsigned int  language; /* 00:Chinese 01:English 02:Hybrew 03 :Reserved 04:Thai*/
	unsigned int  EthDiDoRS485;
	unsigned int  Product;
	unsigned int  configure;
}PNParameter;

typedef struct PN_Analyze   
{	
	//Example 704-45ab-cdde-wxxx-yy
	char type[2];//45
	int a;
	char material[1];//a
	int b;
	char CTPSize[1];//b
	int c;
	char EthDiDoRS485[1];//c
	int dd;
	char Appearance[2];//dd
	int e;
	char mounting[1];//e
	int w;
	char Product[1];//w
	int xxx;
	char configure[3];//xxx
	int yy;
	char language[2];//yy
}PNAnalyze;

enum material
{
	materialTitaniumTNM = 1,
	materialPlatinumIIPT2,
	materialPlatinumPDM,
	materialPlatinumIIPDM2
};

enum CTPSize
{
	CTPSize7Inch = 1,
	CTPSize10Inch
};

enum EthDiDoRS485
{
	Eth1Di10Do0RS4850 = 1,
	Eth2Di10Do2RS4850,
	Eth2Di10Do2RS4852
};

enum Appearance
{
	AppearanceAluminumGolden_1 = 1,
	AppearanceAluminumSilver_1,
	AppearancePlasticGolden,
	AppearancePlasticSilver,
	
	AppearanceAcrylicBalck = 10,
	AppearanceAcrylicPearlWhite,
	AppearanceAcrylicWooden,
	AppearanceAluminumSilver_2,
	AppearanceAluminumGolden_2,
	
	AppearanceSilverFrame = 20,
	AppearanceGoldenFrame
};

enum mounting
{
	mountingWall = 1,
	mountingFlush
};

enum Product
{
	ProductCLT = 1,
	ProductLE,
	ProductHV,
	ProductLT
};

enum configure
{
	configureBasice = 0,
	configureAPP = 1,
	configureLC = 2,
	configureIPCamera = 4,
	configureAC = 8,
	configureThirdPartyProtocol = 16
};

enum language
{
	languageChinese = 0,
	languageEnglish,
	languageHybrew,
	languageReserved,
	languageThai
};

#define dug() printf("[%s -%d ]\n",__func__,__LINE__)
/********** Implement ****************************************************************/

int printfPN(char pn[],PNAnalyze *PnAnalyze)
{   
    printf("PN = %s \n",pn);
	memcpy(PnAnalyze->type,pn+4,2);	
	memcpy(PnAnalyze->material,pn+6,1);	
	memcpy(PnAnalyze->CTPSize,pn+7,1);
	memcpy(PnAnalyze->EthDiDoRS485,pn+9,1);	
	memcpy(PnAnalyze->Appearance,pn+10,2);
	memcpy(PnAnalyze->mounting,pn+12,1);	
	memcpy(PnAnalyze->Product,pn+14,1);	
	memcpy(PnAnalyze->configure,pn+15,3);	
	memcpy(PnAnalyze->language,pn+19,2);
	printf("PnAnalyze->type = %s\n",PnAnalyze->type);
	printf("PnAnalyze->material = %s\n",PnAnalyze->material);
	printf("PnAnalyze->CTPSize = %s\n",PnAnalyze->CTPSize);
	printf("PnAnalyze->EthDiDoRS485 = %s\n",PnAnalyze->EthDiDoRS485);
	printf("PnAnalyze->Appearance = %s\n",PnAnalyze->Appearance);
	printf("PnAnalyze->mounting = %s\n",PnAnalyze->mounting);
	printf("PnAnalyze->Product = %s\n",PnAnalyze->Product);
	printf("PnAnalyze->configure = %s\n",PnAnalyze->configure);
	printf("PnAnalyze->language = %s\n",PnAnalyze->language);
    return success;
}

int AnalyticalSize(PNParameter *PnParameter ,PNAnalyze *PnAnalyze )
{
	if(strcmp(PnAnalyze->CTPSize,Inch_7) == 0)
	{
		PnParameter->ScreenSize = CTPSize7Inch;
		printf("[%s -%d ] 7 Inch LCD 1024*600 CTP\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->CTPSize,Inch_10) == 0)
	{
		PnParameter->ScreenSize = CTPSize10Inch;
		printf("[%s -%d ] 10 Inch LCD 1024*600 CTP\n",__func__,__LINE__);
	}else
	{
		printf("[%s -%d ] Analytical Size fail\n",__func__,__LINE__);
		return fail;
	}
	return success;
}

int AnalyticalEthDiDoRS485(PNParameter *PnParameter ,PNAnalyze *PnAnalyze )
{
	if(strcmp(PnAnalyze->EthDiDoRS485,"1") == 0)
	{
		PnParameter->EthDiDoRS485= Eth1Di10Do0RS4850;
		printf("[%s -%d ] 1X Eth 10X DI \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->EthDiDoRS485,"2") == 0)
	{
		PnParameter->EthDiDoRS485= Eth2Di10Do2RS4850;
		printf("[%s -%d ] 2X Eth 10X DI 2X DO\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->EthDiDoRS485,"3") == 0)
	{
		PnParameter->EthDiDoRS485= Eth2Di10Do2RS4852;
		printf("[%s -%d ] 2X Eth 10X DI 2X DO 2X RS485 \n",__func__,__LINE__);
	}else	
	{
		printf("[%s -%d ] Analytical EthDiDoRS485 fail\n",__func__,__LINE__);
		return fail;
	}
	return success;
}


int AnalyticalLanguage(PNParameter *PnParameter ,PNAnalyze *PnAnalyze )
{
	if(strcmp(PnAnalyze->language,"00") == 0)
	{
		PnParameter->language= languageChinese;
		printf("[%s -%d ]  language - Chinese \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->language,"01") == 0)
	{
		PnParameter->language= languageEnglish;
		printf("[%s -%d ] language - English \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->language,"02") == 0)
	{
		PnParameter->language= languageHybrew;
		printf("[%s -%d ] language - Hybrew \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->language,"03") == 0)
	{
		PnParameter->language= languageReserved;
		printf("[%s -%d ] language - Reserved \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->language,"04") == 0)
	{
		PnParameter->language= languageThai;
		printf("[%s -%d ] language - Thai \n",__func__,__LINE__);
	}else
	{
		printf("[%s -%d ] Analytical language fail\n",__func__,__LINE__);
		return fail;
	}
	return success;
}


int AnalyticalProduct(PNParameter *PnParameter ,PNAnalyze *PnAnalyze )
{
	if(strcmp(PnAnalyze->Product,"1") == 0)
	{
		PnParameter->Product= ProductCLT;
		printf("[%s -%d ] Product - CLT\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->Product,"2") == 0)
	{
		PnParameter->Product= ProductLE;
		printf("[%s -%d ]Product -  LE \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->Product,"3") == 0)
	{
		PnParameter->Product= ProductHV;
		printf("[%s -%d ]Product -  HV \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->Product,"4") == 0)
	{
		PnParameter->Product= ProductLT;
		printf("[%s -%d ]Product -  LT \n",__func__,__LINE__);
	}else
	{
		printf("[%s -%d ] Analytical Product fail\n",__func__,__LINE__);
		return fail;
	}
	return success;
}

int AnalyticalConfigure(PNParameter *PnParameter ,PNAnalyze *PnAnalyze )
{
	if(strcmp(PnAnalyze->configure,"000") == 0)
	{
		PnParameter->configure= configureBasice;
		printf("[%s -%d ] configure -  BAsice\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->configure,"001") == 0)
	{
		PnParameter->configure= configureAPP;
		printf("[%s -%d ] configure -  App\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->configure,"002") == 0)
	{
		PnParameter->configure= configureLC;
		printf("[%s -%d ] configure -  LC\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->configure,"004") == 0)
	{
		PnParameter->configure= configureIPCamera;
		printf("[%s -%d ] configure -  IP Camera \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->configure,"008") == 0)
	{
		PnParameter->configure= configureAC;
		printf("[%s -%d ] configure -  AC\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->configure,"016") == 0)
	{
		PnParameter->configure= configureThirdPartyProtocol;
		printf("[%s -%d ] configure -  Third Party Protocol\n",__func__,__LINE__);
	}else
	{
		printf("[%s -%d ] Analytical configure fail\n",__func__,__LINE__);
		return fail;
	}
	return success;
}


int Analytical_PN(PNParameter *PnParameter ,PNAnalyze *PnAnalyze)
{
	if(PnParameter == NULL && PnAnalyze == NULL)
	{
		return fail;
	}
	//Analytical Size ; 
	if(AnalyticalSize(PnParameter , PnAnalyze) == fail)
	{
		return fail;
	}
	//Analytical EthDiDoRS485 ; 
	if(AnalyticalEthDiDoRS485(PnParameter , PnAnalyze) == fail)
	{
		return fail;
	}
	//Analytical language ; 
	if(AnalyticalLanguage(PnParameter , PnAnalyze) == fail)
	{
		return fail;
	}
	//Analytical Product ; 
	if(AnalyticalProduct(PnParameter , PnAnalyze) == fail)
	{
		return fail;
	}
	//Analytical Configure ; 
	if(AnalyticalConfigure(PnParameter , PnAnalyze) == fail)
	{
		return fail;
	}
	
	return success;
}

int openHardware(char *hardwareAddr)
{
    int fd,size;
	char FileAddr[500] ="";//address 
    char Content[200] = "";//file content
	strcat(FileAddr,hardwareAddr);
	strcat(FileAddr,HARDWARE);
	printf("%s\n",FileAddr);
	fd = open(FileAddr,O_RDONLY);	
    int num =  read(fd,Content,sizeof(Content));
    close(fd);
    if( num > 0 )
	{
		printf("%s",Content);
	}
    
	return success;
}



int getPN( void )
{
	return success;
}


int main(int argc, char *argv[])
{
	PNParameter PnParameter;
	memset(&PnParameter,0,sizeof(PNParameter));
	PNAnalyze pnAAnalyze;
	memset(&pnAAnalyze,0,sizeof(PNAnalyze));
	strcpy(PnParameter.PN, PN_test);
    // step 1.  pn 
    // add code ......
    openHardware(addr_test);
	
    printfPN(PnParameter.PN,&pnAAnalyze);
    //step 2. Analytical pn  
    Analytical_PN(&PnParameter,&pnAAnalyze);
//	printf("[%s -%d ]PnParameter.configure =%d,PnParameter.EthDiDoRS485=%d,PnParameter.language=%d,PnParameter.Product=%d,PnParameter.ScreenSize=%d \n",__func__,__LINE__,PnParameter.configure,PnParameter.EthDiDoRS485,PnParameter.language,PnParameter.Product,PnParameter.ScreenSize);
	
    return 0;
}
