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


#define success 1
#define fail 	0



#ifdef __ANDROID_LOG__
#include <android/log.h>

#define LOG_TAG "PN_test"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR ,LOG_TAG, __VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__)

#define printf(...) {char printfBuf[MAX_PRINTF_BUF_SIZE];sprintf(printfBuf, __VA_ARGS__);ATTPrintf( printfBuf);}
#define nprintf(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#else
#define LOGD(...)  printf(__VA_ARGS__)
#define LOGI(...)  printf(__VA_ARGS__)
#define LOGW(...)  printf(__VA_ARGS__)
#define LOGE(...)  printf(__VA_ARGS__)
#define LOGF(...)  printf(__VA_ARGS__)
#define nprintf(...) printf(__VA_ARGS__)
#endif 


#define PRINTF_N	LOGI
#define PRINTF_E	LOGE


#define addrhardware_test "/work/bensonchen/mx20/trunk/source/platform/android/hardware/mx20/libPN/test/hardware.ini"
#define addrmac_test "/work/bensonchen/mx20/trunk/source/platform/android/hardware/mx20/libPN/test/mac.ini"
#define PN_test "704-4511-1011-1000-00"


#define addrhardware "/sdcard/hardware.ini"
#define addrmac "/sdcard/mac.ini"

#define HARDWARE 	"/hardware.ini"
#define MAC 		"/mac.ini"


#define Inch_7 "1"
#define Inch_10 "2"

#define HARDWARE_PN_LEN 21
#define HARDWARE_VERSION_LEN 20

typedef struct ENV_Parameter 
{	
	char PN[HARDWARE_PN_LEN+3];
	unsigned int  ScreenSize;   /* 1: 7 LCD 1024*600 CTP ;2: 10 LCD 1024*600 CTP ;3: Reserved */
	unsigned int  language; /* 00:Chinese 01:English 02:Hybrew 03 :Reserved 04:Thai*/
	unsigned int  EthDiDoRS485; 
	unsigned int  Product;
	unsigned int  mac[6];
	unsigned int  functionOption;
	char Version[HARDWARE_VERSION_LEN];
}ENVParameter;



typedef struct PN_Analyze   
{	
	//Example 704-45ab-cdde-wxxx-yy
	char type[2+2];//45
	char material[1+3];//a
	char CTPSize[1+3];//b
	char EthDiDoRS485[1+3];//c
	char Appearance[2+2];//dd
	char mounting[1+3];//e
	char Product[1+3];//w
	char functionOption[3+1];//xxx
	char language[2+2];//yy
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
	CTPSize7Inch = 1,// 7 LCD 1024*600 CTP
	CTPSize10Inch  // 10 LCD 1024*600 CTP
};


enum EthDiDoRS485
{
	Eth1Di10Do0RS4850 = 1, // 1XEth 10XDi
	Eth2Di10Do2RS4850,	// 2XEth 10XDi 2X Do
	Eth2Di10Do2RS4852 // 2XEth 10XDi 2X Do 2XRS485
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
    ProductCLT = 1, 	// Product CLT
    ProductLE, 			// Product LE
    ProductHV,			// Product HV
    ProductLT			// Product LT
};


enum FunctionOption
{
    functionOptionBasice = 0,			//Basice
    functionOptionAPP = 1,				//APP
    functionOptionLC = 2,				//LC
    functionOptionIPCamera = 4,			//IP Camera
    functionOptionAC = 8,				//AC
    functionOptionThirdPartyProtocol = 16	//
};


enum Language
{
    languageChinese = 0, 	// Chinese
    languageEnglish,		// English
    languageHybrew,		// Hybrew
    languageReserved,		// ReserVed
    languageThai			// Thai
};


#define dug() PRINTF_N("[%s -%d ]\n",__func__,__LINE__)
/********** Implement ****************************************************************/
/**
 *  PN 转换
 *  
 *  @param pn        <#pn description#>
 *  @param PnAnalyze 转化后的结构体
 *
 *  @return     
 */
static int printfPN(char pn[],PNAnalyze *PnAnalyze)
{   
    PRINTF_N("PN = %s \n",pn);
	memcpy(PnAnalyze->type,pn+4,2);	
	memcpy(PnAnalyze->material,pn+6,1);	
	memcpy(PnAnalyze->CTPSize,pn+7,1);
	memcpy(PnAnalyze->EthDiDoRS485,pn+9,1);	
	memcpy(PnAnalyze->Appearance,pn+10,2);
	memcpy(PnAnalyze->mounting,pn+12,1);	
	memcpy(PnAnalyze->Product,pn+14,1);	
	memcpy(PnAnalyze->functionOption,pn+15,3);	
	memcpy(PnAnalyze->language,pn+19,2);
	PRINTF_N("PnAnalyze->type = %s\n",PnAnalyze->type);
	PRINTF_N("PnAnalyze->material = %s\n",PnAnalyze->material);
	PRINTF_N("PnAnalyze->CTPSize = %s\n",PnAnalyze->CTPSize);
	PRINTF_N("PnAnalyze->EthDiDoRS485 = %s\n",PnAnalyze->EthDiDoRS485);
	PRINTF_N("PnAnalyze->Appearance = %s\n",PnAnalyze->Appearance);
	PRINTF_N("PnAnalyze->mounting = %s\n",PnAnalyze->mounting);
	PRINTF_N("PnAnalyze->Product = %s\n",PnAnalyze->Product);
	PRINTF_N("PnAnalyze->functionOption = %s\n",PnAnalyze->functionOption);
	PRINTF_N("PnAnalyze->language = %s\n",PnAnalyze->language);
    return success;
}
/**
 *  解析屏幕大小
 *
 *  @param EnvParameter 解析后的参数
 *  @param PnAnalyze    pn转化结构体
 *
 *  @return 成功or失败
 */
static int AnalyticalSize(ENVParameter *EnvParameter ,PNAnalyze *PnAnalyze )
{
	if(strcmp(PnAnalyze->CTPSize,Inch_7) == 0)
	{
		EnvParameter->ScreenSize = CTPSize7Inch;
		PRINTF_N("[%s -%d ] 7 Inch LCD 1024*600 CTP\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->CTPSize,Inch_10) == 0)
	{
		EnvParameter->ScreenSize = CTPSize10Inch;
		PRINTF_N("[%s -%d ] 10 Inch LCD 1024*600 CTP\n",__func__,__LINE__);
	}else
	{
		PRINTF_E("[%s -%d ] Analytical Size fail\n",__func__,__LINE__);
		return fail;
	}
	return success;
}

static int AnalyticalEthDiDoRS485(ENVParameter *EnvParameter ,PNAnalyze *PnAnalyze )
{
	if(strcmp(PnAnalyze->EthDiDoRS485,"1") == 0)
	{
		EnvParameter->EthDiDoRS485= Eth1Di10Do0RS4850;
		PRINTF_N("[%s -%d ] 1X Eth 10X DI \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->EthDiDoRS485,"2") == 0)
	{
		EnvParameter->EthDiDoRS485= Eth2Di10Do2RS4850;
		PRINTF_N("[%s -%d ] 2X Eth 10X DI 2X DO\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->EthDiDoRS485,"3") == 0)
	{
		EnvParameter->EthDiDoRS485= Eth2Di10Do2RS4852;
		PRINTF_N("[%s -%d ] 2X Eth 10X DI 2X DO 2X RS485 \n",__func__,__LINE__);
	}else	
	{
		PRINTF_E("[%s -%d ] Analytical EthDiDoRS485 fail\n",__func__,__LINE__);
		return fail;
	}
	return success;
}


static int AnalyticalLanguage(ENVParameter *EnvParameter ,PNAnalyze *PnAnalyze )
{
	if(strcmp(PnAnalyze->language,"00") == 0)
	{
		EnvParameter->language= languageChinese;
		PRINTF_N("[%s -%d ]  language - Chinese \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->language,"01") == 0)
	{
		EnvParameter->language= languageEnglish;
		PRINTF_N("[%s -%d ] language - English \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->language,"02") == 0)
	{
		EnvParameter->language= languageHybrew;
		PRINTF_N("[%s -%d ] language - Hybrew \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->language,"03") == 0)
	{
		EnvParameter->language= languageReserved;
		PRINTF_N("[%s -%d ] language - Reserved \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->language,"04") == 0)
	{
		EnvParameter->language= languageThai;
		PRINTF_N("[%s -%d ] language - Thai \n",__func__,__LINE__);
	}else
	{
		PRINTF_E("[%s -%d ] Analytical language fail\n",__func__,__LINE__);
		return fail;
	}
	return success;
}


static int AnalyticalProduct(ENVParameter *EnvParameter ,PNAnalyze *PnAnalyze )
{
	if(strcmp(PnAnalyze->Product,"1") == 0)
	{
		EnvParameter->Product= ProductCLT;
		PRINTF_N("[%s -%d ] Product - CLT\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->Product,"2") == 0)
	{
		EnvParameter->Product= ProductLE;
		PRINTF_N("[%s -%d ]Product -  LE \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->Product,"3") == 0)
	{
		EnvParameter->Product= ProductHV;
		PRINTF_N("[%s -%d ]Product -  HV \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->Product,"4") == 0)
	{
		EnvParameter->Product= ProductLT;
		PRINTF_N("[%s -%d ]Product -  LT \n",__func__,__LINE__);
	}else
	{
		PRINTF_E("[%s -%d ] Analytical Product fail\n",__func__,__LINE__);
		return fail;
	}
	return success;
}

static int AnalyticalConfigure(ENVParameter *EnvParameter ,PNAnalyze *PnAnalyze )
{
	if(strcmp(PnAnalyze->functionOption,"000") == 0)
	{
		EnvParameter->functionOption= functionOptionBasice;
		PRINTF_N("[%s -%d ] functionOption -  BAsice\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->functionOption,"001") == 0)
	{
		EnvParameter->functionOption= functionOptionAPP;
		PRINTF_N("[%s -%d ] functionOption -  App\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->functionOption,"002") == 0)
	{
		EnvParameter->functionOption= functionOptionLC;
		PRINTF_N("[%s -%d ] functionOption -  LC\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->functionOption,"004") == 0)
	{
		EnvParameter->functionOption= functionOptionIPCamera;
		PRINTF_N("[%s -%d ] functionOption -  IP Camera \n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->functionOption,"008") == 0)
	{
		EnvParameter->functionOption= functionOptionAC;
		PRINTF_N("[%s -%d ] functionOption -  AC\n",__func__,__LINE__);
	}else if(strcmp(PnAnalyze->functionOption,"016") == 0)
	{
		EnvParameter->functionOption= functionOptionThirdPartyProtocol;
		PRINTF_N("[%s -%d ] functionOption -  Third Party Protocol\n",__func__,__LINE__);
	}else
	{
		PRINTF_E("[%s -%d ] Analytical functionOption fail\n",__func__,__LINE__);
		return fail;
	}
	return success;
}

int AnalyticalPn(ENVParameter * EnvParameter)
{
//int AnalyticalPN(ENVParameter *EnvParameter ,PNAnalyze *PnAnalyze)
//{
	if(EnvParameter == NULL)
	{
		return fail;
	}
	
	PNAnalyze pnAAnalyze;
	memset(&pnAAnalyze,0,sizeof(PNAnalyze));
	
	printfPN(EnvParameter->PN,&pnAAnalyze);

	//Analytical Size ; 
	if(AnalyticalSize(EnvParameter , &pnAAnalyze) == fail)
	{
		return fail;
	}
	//Analytical EthDiDoRS485 ; 
	if(AnalyticalEthDiDoRS485(EnvParameter , &pnAAnalyze) == fail)
	{
		return fail;
	}
	//Analytical language ; 
	if(AnalyticalLanguage(EnvParameter , &pnAAnalyze) == fail)
	{
		return fail;
	}
	//Analytical Product ; 
	if(AnalyticalProduct(EnvParameter , &pnAAnalyze) == fail)
	{
		return fail;
	}
	//Analytical Configure ; 
	if(AnalyticalConfigure(EnvParameter , &pnAAnalyze) == fail)
	{
		return fail;
	}
	
	return success;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


static int getVersion(char *hardwareAddr,int *fp,ENVParameter * envParameter,char *fileContent)
{
	char * str,*head,*tail;
	int nread,i;

	if(hardwareAddr==NULL || fp==NULL || envParameter==NULL || fileContent==NULL)
	{
		return fail;
	}

	head = strstr(fileContent,"Version");
	if(head==NULL){
		PRINTF_E("checkVersion:can not find Version number in %s.\n",hardwareAddr);
		close(*fp);
		return fail;
	}
	head +=7;
	str = strstr(head,"=");
	if(str==NULL){
		PRINTF_E("checkVersion:can not find '=' after \"Version\" in %s.\n",hardwareAddr);
		close(*fp);
		return fail;
	}
	head = str+1;
	tail = strstr(head+1,"\n");
	if(tail==NULL){
		PRINTF_E("checkVersion:can not find Version tail in %s.\n",hardwareAddr);
		close(*fp);
		return fail;
	}
	nread = tail-head;
	for(i=0;i<nread;i++){
		if(*(head+i)!=' ' && *(head+i)!='\t'){
			break;
		}
	}
	head += i;
	nread = tail-head;
	for(i=0;i<nread;i++){
		if(*(head+i)==' ' || *(head+i)=='\t'){
			break;
		}
	}
	tail = head + i;
	strncpy(envParameter->Version,head,tail-head);
	PRINTF_N(" [%s--%d] checkVersion:envParameter->Version = %s.\n",__func__,__LINE__,envParameter->Version);
	return success;
}


static int getPN(char *hardwareAddr,int *fp,ENVParameter * envParameter,char *fileContent)
{
	char * str,*head,*tail;
	int nread,i;

	if(hardwareAddr==NULL || fp==NULL || envParameter==NULL || fileContent==NULL)
	{
		PRINTF_E("[%s-%d]getPN parameter NULL \n",__func__,__LINE__);
		return fail;
	}
	head = strstr(fileContent,"PN");
	if(head==NULL){
		head = strstr(fileContent,"pn");
		if(head==NULL){
			PRINTF_E("checkPN:can not find PN number in %s.\n",hardwareAddr);
			close(*fp);
		return fail;
		}
	}
	head +=2;
	str = strstr(head,"=");
	if(str==NULL){
		PRINTF_E("checkPN:can not find '=' after \"Version\" in %s.\n",hardwareAddr);
		close(*fp);
		return fail;
	}
	head = str+1;
	tail = strstr(head+1,"\n");
	if(tail==NULL){
		PRINTF_E("checkPN:can not find Version tail in %s.\n",hardwareAddr);
		close(*fp);
		return fail;
	}
	nread = tail-head;
	for(i=0;i<nread;i++){
		if(*(head+i)!=' ' && *(head+i)!='\t'){
			break;
		}
	}
	head += i;
	nread = tail-head;
	for(i=0;i<nread;i++){
		if(*(head+i)==' ' || *(head+i)=='\t'){
			break;
		}
	}
	tail = head + i;
	strncpy(envParameter->PN,head,tail-head);
	PRINTF_N("[%s--%d] checkPN:envParameter->PN = %s.\n",__func__,__LINE__,envParameter->PN);
	return success;
}

static int openHardware(char *hardwareAddr ,ENVParameter * envParameter)
{
    int fp;
	int	size;
    char fileContent[200] = "";//file content
	fp = open(hardwareAddr,O_RDONLY);	
	if(fp == -1)
	{
		PRINTF_E("[%s--%d] open  hardware Address fail %s \n",__func__,__LINE__,hardwareAddr);
		return  fail;	
	}
	if(read(fp,fileContent,sizeof(fileContent))<= 0 )
	{	
		PRINTF_E("[%s--%d] read %s fail\n",__func__,__LINE__,hardwareAddr);
		return fail;
	}
	
	if(fail == getVersion(hardwareAddr,&fp,envParameter, fileContent))
  	{
  		PRINTF_E("[%s--%d] getVersion fail \n",__func__,__LINE__);
		return 	fail;		
	}   
	
	if(fail == getPN(hardwareAddr,&fp,envParameter, fileContent))
  	{
  		PRINTF_E("[%s--%d] getPN fail \n",__func__,__LINE__);
		return 	fail;		
	}   
   
	close(fp);	
	return success;
}



static int getMacAddr(char *macAddr,int *fp,ENVParameter * envParameter,char *fileContent)
{	
	char * str,*head,*tail;
	int nread,i;
	char MACaddress[50];
	memset(MACaddress,0,sizeof(MACaddress));

	if(macAddr==NULL || fp==NULL || envParameter==NULL || fileContent==NULL)
	{
		return fail;
	}
	head = strstr(fileContent,"ADDRESS");
	if(head==NULL){
		PRINTF_E("checkMAC:can not find MAC in %s.\n",macAddr);
		close(*fp);
		return fail;
		
	}
	head +=7;
	str = strstr(head,"=");
	if(str==NULL){
		PRINTF_E("checkMAC:can not find '=' after \"Version\" in %s.\n",macAddr);
		close(*fp);
		return fail;
	}
	head = str+1;
	tail = strstr(head+1,"\n");
	if(tail==NULL){
		PRINTF_E("checkMAC:can not find MAC Address tail in %s.\n",macAddr);
		close(*fp);
		return fail;
	}
	nread = tail-head;
	for(i=0;i<nread;i++){
		if(*(head+i)!=' ' && *(head+i)!='\t'){
			break;
		}
	}
	head += i;
	nread = tail-head;
	for(i=0;i<nread;i++){
		if(*(head+i)==' ' || *(head+i)=='\t'){
			break;
		}
	}
	tail = head + i;
	strncpy(MACaddress,head,tail-head);
	PRINTF_N("[%s--%d] checkMacAddr:  MACaddress = %s.\n",__func__,__LINE__,MACaddress);
	unsigned int mac[6];
	sscanf (MACaddress, "%02x:%02x:%02x:%02x:%02x:%02x",&mac[0],&mac[1],&mac[2],&mac[3],&mac[4],&mac[5]);
	
	PRINTF_N("EnvParameter = %d-%d-%d-%d-%d-%d\n",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
	for(i = 0; i < 6 ;i++)
	{	
		envParameter->mac[i] = mac[i];
	}
	return success;
}

static int openMac(char *macAddr,ENVParameter * envParameter)
{
    int fp;
    char fileContent[200] = "";//file content
	//PRINTF_N("%s\n",macAddr);
	fp = open(macAddr,O_RDONLY);	
	if(fp == -1)
	{
		PRINTF_E("[%s--%d] open  Mac Address fail %s \n",__func__,__LINE__,macAddr);
		return  fail;	
	}
    if(read(fp,fileContent,sizeof(fileContent))<= 0 )
	{
	   return fail;
	}

	if(fail == getMacAddr(macAddr,&fp,envParameter, fileContent))
	{
		PRINTF_E("[%s--%d] get Mac Address fail \n",__func__,__LINE__);
		return	fail;		
	}	


	
    close(fp);
	//PRINTF_N("%s",fileContent);
	return success;
}

int openGetPnMacVersion(ENVParameter * envParameter,char * AddrHardware, char * AddrMac)
{

	if(fail == openHardware(AddrHardware,envParameter))
	{
		PRINTF_E("[%s--%d] open Hardware Address fail \n",__func__,__LINE__);
		return	fail;
	}

	if(fail == openMac(AddrMac,envParameter))
	{
		PRINTF_E("[%s--%d] open Hardware Address fail \n",__func__,__LINE__);
		return	fail;
	}


	return success;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

static int updateMacAddress(ENVParameter * envParameter )
{
		unsigned int mac[6];
		int i;
		
		for(i = 0; i < 6 ;i++)
		{	
			 mac[i] = envParameter->mac[i] ;
		}

		if(mac[5] != 0xff)
		{
			mac[5] += 1;
		}else if(mac[4] != 0xff)
		{
			mac[5] = 0x01;
			mac[4] += 1;
		}else if(mac[3] != 0xff)
		{
			mac[4] = 0x01;
			mac[3] += 1;
		}else if(mac[2] != 0xff)
		{
			mac[3] = 0x01;
			mac[2] += 1;
		}else if(mac[1] != 0xff)
		{
			mac[2] = 0x01;
			mac[1] += 1;
		}else if(mac[0] != 0xff)
		{
			mac[1] = 0x01;
			mac[0] += 1;
		}else
		{
			for(i = 0; i < 6 ;i++)
			{	
				 mac[i] = 0x01;
			}
		}	
			
		if((mac[0] == 0xff && mac[1] == 0xff && mac[2] == 0xff && mac[3] == 0xff && mac[4] == 0xff && mac[5] == 0xff)
			||(mac[0] == 0x00 && mac[1] == 0x00 && mac[2] == 0x00 && mac[3] == 0x00 && mac[4] == 0x00 && mac[5] == 0x00) )
		{
			
			for(i = 0; i < 6 ;i++)
			{	
				 mac[i] = 0x01;
			}
		}

		for(i = 0; i < 6 ;i++)
		{	
			envParameter->mac[i] = mac[i];
		}
		
		return success;
}


static int setEnvEth(ENVParameter * envParameter)
{

	char MACaddress[50];
	memset(MACaddress,0,sizeof(MACaddress));
	sprintf(MACaddress,"fw_setenv eth0 %02x:%02x:%02x:%02x:%02x:%02x",envParameter->mac[0],envParameter->mac[1],envParameter->mac[2],envParameter->mac[3],envParameter->mac[4],envParameter->mac[5]);
	system(MACaddress);

	PRINTF_N("MACaddress = %s \n",MACaddress);
	if(envParameter->EthDiDoRS485 >1)
		{
		updateMacAddress(envParameter);
		memset(MACaddress,0,sizeof(MACaddress));
		sprintf(MACaddress,"fw_setenv eth0 %02x:%02x:%02x:%02x:%02x:%02x",envParameter->mac[0],envParameter->mac[1],envParameter->mac[2],envParameter->mac[3],envParameter->mac[4],envParameter->mac[5]);
		system(MACaddress);
		PRINTF_N("MACaddress = %s \n",MACaddress );
		}
	return success;
}


int setEnvParameter(ENVParameter * envParameter)
{
	PRINTF_N("[%s - %d] \n",__func__,__LINE__);

	if(envParameter==NULL)
	{
		PRINTF_E("[%s-%d]set Env Parameter fail",__func__,__LINE__);
		return fail;
	}
	int i,ETHs;
	char tmp[50];
	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv PN %s",envParameter->PN);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv Version %s",envParameter->Version);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv Product %d",envParameter->Product);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);
	
	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv ScreenSize %d",envParameter->ScreenSize);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv functionOption %d",envParameter->functionOption);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv EthDiDoRS485 %d",envParameter->EthDiDoRS485);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv language %d",envParameter->language);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);
	
	setEnvEth(envParameter);

	return success;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

static  int  writeMacAddr(char *AddrMac,int *fp,ENVParameter * envParameter)
{
	char MACaddress[50];
	memset(MACaddress,0,sizeof(MACaddress));
	if(AddrMac==NULL || fp==NULL || envParameter==NULL)
	{
		return fail;
	}
	updateMacAddress(envParameter);
	sprintf(MACaddress,"[MAC]\nADDRESS=%02x:%02x:%02x:%02x:%02x:%02x\n",envParameter->mac[0],envParameter->mac[1],envParameter->mac[2],envParameter->mac[3],envParameter->mac[4],envParameter->mac[5]);
	write(*fp,MACaddress,strlen(MACaddress));
	return success;	
}

int updateMac(ENVParameter * envParameter, char * AddrMac)
{
	
	int fp;
	char fileContent[200] = "";//file content
	//PRINTF_N("%s\n",macAddr);
	
	fp = open(AddrMac,O_RDWR);    
	if(fp == -1)
	{
		PRINTF_E("[%s--%d] open  Mac Address fail %s \n",__func__,__LINE__,AddrMac);
		return  fail;	
	}

	if(fail == writeMacAddr(AddrMac,&fp,envParameter))
	{
		PRINTF_E("[%s--%d] update  Mac Address fail \n",__func__,__LINE__);
		return  fail;	   
	}   
	close(fp);
	return success;
}



int main(int argc, char *argv[])
{
	ENVParameter EnvParameter;
	memset(&EnvParameter,0,sizeof(ENVParameter));
	
    // step 1.  pn 
    if(fail == openGetPnMacVersion(&EnvParameter,addrhardware,addrmac))
    	{
    	PRINTF_E("[%s-%d]openGetPnMacVersion fail",__func__,__LINE__);
		return -1;
	}
	
    //step 2. Analytical pn  
    //strcpy(EnvParameter.PN, PN_test);
    if(fail == AnalyticalPn(&EnvParameter))
    {
    	PRINTF_E("[%s-%d]AnalyticalPn fail",__func__,__LINE__);
 	   return -2;
   	}
	
	PRINTF_N("[%s -%d ]EnvParameter.functionOption =%d,EnvParameter.EthDiDoRS485=%d,EnvParameter.language=%d,EnvParameter.Product=%d,EnvParameter.ScreenSize=%d,EnvParameter.PN = %s,EnvParameter.Version=%s\n",__func__,__LINE__,EnvParameter.functionOption,EnvParameter.EthDiDoRS485,EnvParameter.language,EnvParameter.Product,EnvParameter.ScreenSize,EnvParameter.PN,EnvParameter.Version);
	PRINTF_N("EnvParameter = %d-%d-%d-%d-%d-%d\n",EnvParameter.mac[0],EnvParameter.mac[1],EnvParameter.mac[2],EnvParameter.mac[3],EnvParameter.mac[4],EnvParameter.mac[5]);

	//step 3. Encrypted 
	/*
	code ......
	.............
	*/
	
	//step 4.  Set ENV 
	if(fail == setEnvParameter(&EnvParameter))
	{
		PRINTF_E("[%s-%d]setEnvParameter fail",__func__,__LINE__);
		return -4;
	}
	
	//step 5. 
	if(fail == updateMac(&EnvParameter,addrmac))
	{
		PRINTF_E("[%s-%d]updateMac fail",__func__,__LINE__);
		return -5;
	}
	
    return 0;
}