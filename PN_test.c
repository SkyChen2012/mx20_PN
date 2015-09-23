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

#define printf(...) {char printfBuf[MAX_PRINTF_BUF_SIZE];sprintf(printfBuf,__VA_ARGS__);ATTPrintf( printfBuf);}
#define nprintf(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG,__VA_ARGS__)
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
#define HARDWARE_VERSION_LEN 19


extern char** environ;




#define    functionOptionBasice 				0b00000000			//Basice
#define    functionOptionAPP 					0b00000001			//APP
#define    functionOptionLC 					0b00000010				//LC
#define    functionOptionIPCamera 				0b00000100			//IP Camera
#define    functionOptionAC 					0b00001000				//AC
#define    functionOptionThirdPartyProtocol 	0b00010000	//
#define    functionOptionReserved32 			0b00100000
#define    functionOptionReserved64 			0b01000000
#define    functionOptionReserved128 			0b10000000

typedef struct ENV_Parameter 
{	
	char PN[HARDWARE_PN_LEN+3];
	unsigned int  	ScreenSize;   /* 1: 7 LCD 1024*600 CTP ;2: 10 LCD 1024*600 CTP;3: Reserved */
	unsigned int  	language; /* 00:Chinese 01:English 02:Hybrew 03 :Reserved 04:Thai*/
	unsigned int  	EthDiDoRS485; 
	unsigned int 	Product;
	unsigned int  	mac[6];
	unsigned int	FunctionOptionBasiceClent; 	//
	unsigned int	FunctionOptionVideoIntercom; 	//
	unsigned int	FunctionOptionAlarm;
	unsigned int	FunctionOptionAPP;
	unsigned int	FunctionOptionLiftControl;
	unsigned int	FunctionOptionIpCamera;
	unsigned int	FunctionOptionAccessDB;
	unsigned int	FunctionOptionAccessRecordQuery;
	unsigned int	FunctionOptionMiniSCASA;
	unsigned int	FunctionOptionCustomizedRS485;
	unsigned int	FunctionOptionReservedCLT;
	unsigned int	FunctionOptionReservedLE;
	unsigned int	FunctionOptionReservedHV;
	unsigned int	FunctionOptionReservedLT;
	char Version[HARDWARE_VERSION_LEN+1];
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
    ProductLT,			// Product LT
    ProductReserved
};


enum FunctionOption
{
	FunctionOptionBasiceClent = 0,	//
	FunctionOptionVideoIntercom, 	//
	FunctionOptionAlarm,
	FunctionOptionAPP,
	FunctionOptionLiftControl,
	FunctionOptionIpCamera,
	FunctionOptionAccessDB,
	FunctionOptionAccessRecordQuery,
	FunctionOptionMiniSCASA,
	FunctionOptionCustomizedRS485,
	FunctionOptionReservedCLT,
	FunctionOptionReservedLE,
	FunctionOptionReservedHV,
	FunctionOptionReservedLT
	
};


enum Language
{
    languageChinese = 0, 	// Chinese
    languageEnglish,		// English
    languageHybrew,		// Hybrew
    languageReserved,		// ReserVed
    languageThai,       // Thai
    languageNewLanguage
};







#define dug() PRINTF_N("[%s -%d ]\n",__func__,__LINE__)
/********** Implement 
****************************************************************/
/**
 *  PN 转换
 *  
 *  @param pn        PN字符串
 *  @param PnAnalyze PN转化参数
 *
 *  @return     
 */
static int printfPN(char pn[],PNAnalyze *PnAnalyze)
{   
    if (PnAnalyze == NULL) {
        
        PRINTF_E("[%s-%d] printfPN fail",__func__,__LINE__);
        return fail;
    }
    
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
 *  @return true or false
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
/**
 *  解析 以太网 DI DO RS485
 *
 *  @param EnvParameter env 
 *  @param PnAnalyze    
 *
 *  @return true or false
 */
static int AnalyticalEthDiDoRS485(ENVParameter *EnvParameter ,PNAnalyze *
PnAnalyze )
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

/**
 *  <#Description#>
 *
 *  @param EnvParameter <#EnvParameter description#>
 *  @param PnAnalyze    <#PnAnalyze description#>
 *
 *  @return <#return value description#>
 */
static int AnalyticalLanguage(ENVParameter *EnvParameter ,PNAnalyze *
PnAnalyze )
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

/**
 *  <#Description#>
 *
 *  @param EnvParameter <#EnvParameter description#>
 *  @param PnAnalyze    <#PnAnalyze description#>
 *
 *  @return <#return value description#>
 */
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
/**
 *  功能码解析
 *
 *  @param EnvParameter <#EnvParameter description#>
 *  @param PnAnalyze    <#PnAnalyze description#>
 *
 *  @return <#return value description#>
 */
static int AnalyticalConfigure(ENVParameter *EnvParameter ,PNAnalyze *
PnAnalyze )
{

	PRINTF_N("PnAnalyze %d \n" ,atoi(PnAnalyze->functionOption));
	switch(EnvParameter->Product)
	{
	case ProductCLT:{
			EnvParameter->FunctionOptionBasiceClent = 1;
			PRINTF_N("[%s -%d ] Product	CLT \n",__func__,__LINE__);
			return success;
			break;
		}
	case ProductLE :{
			EnvParameter->FunctionOptionVideoIntercom = 1;
			EnvParameter->FunctionOptionAlarm = 1;
			break;
		}
	case ProductHV:{
			EnvParameter->FunctionOptionVideoIntercom = 1;
			EnvParameter->FunctionOptionAlarm = 1;
			EnvParameter->FunctionOptionAPP = 1;
			break;
		}
	case ProductLT:
		{	
			EnvParameter->FunctionOptionVideoIntercom = 1;
			EnvParameter->FunctionOptionAlarm = 1;
			EnvParameter->FunctionOptionLiftControl = 1;
			EnvParameter->FunctionOptionAPP = 1;
			EnvParameter->FunctionOptionIpCamera = 1;
			EnvParameter->FunctionOptionAccessDB = 1;
			EnvParameter->FunctionOptionAccessRecordQuery = 1;
			EnvParameter->FunctionOptionMiniSCASA = 1;
			break;
		}
	case ProductReserved:{
		
			PRINTF_N("[%s -%d ] Product	Reserved \n",__func__,__LINE__); 
			break;
		}
	default:PRINTF_N("Product other !!!!!!! \n");
	
	}

	if(atoi(PnAnalyze->functionOption) & functionOptionAPP )
	{
			switch(EnvParameter->Product)
		{
		case ProductCLT:{
				PRINTF_N("[%s -%d ] Product	CLT \n",__func__,__LINE__);
				return success;
				break;
			}
		case ProductLE :{
				EnvParameter->FunctionOptionAPP= 1;
				break;
			}
		case ProductHV:{
				break;
			}
		case ProductLT:
			{	
				break;
			}
		case ProductReserved:{
			
				PRINTF_N("[%s -%d ] Product	Reserved \n",__func__,__LINE__); 
				break;
			}
		default:PRINTF_N("Product other !!!!!!! \n");
		
		}
	}

	if(atoi(PnAnalyze->functionOption) & functionOptionLC )
	{
		switch(EnvParameter->Product)
		{
		case ProductCLT:{
				PRINTF_N("[%s -%d ] Product	CLT \n",__func__,__LINE__);
				return success;
				break;
			}
		case ProductLE :{
				EnvParameter->FunctionOptionLiftControl = 1;
				break;
			}
		case ProductHV:{
				EnvParameter->FunctionOptionLiftControl = 1;
				break;
			}
		case ProductLT:
			{	
				break;
			}
		case ProductReserved:{
			
				PRINTF_N("[%s -%d ] Product	Reserved \n",__func__,__LINE__); 
				break;
			}
		default:PRINTF_N("Product other !!!!!!! \n");
		
		}
	}

	if(atoi(PnAnalyze->functionOption) & functionOptionIPCamera )
	{
		switch(EnvParameter->Product)
		{
		case ProductCLT:{
				PRINTF_N("[%s -%d ] Product	CLT \n",__func__,__LINE__);
				return success;
				break;
			}
		case ProductLE :{
				break;
			}
		case ProductHV:{
				EnvParameter->FunctionOptionIpCamera = 1;
				break;
			}
		case ProductLT:
			{	
				break;
			}
		case ProductReserved:{
			
				PRINTF_N("[%s -%d ] Product	Reserved \n",__func__,__LINE__); 
				break;
			}
		default:PRINTF_N("Product other !!!!!!! \n");
		
		}
	}

	if(atoi(PnAnalyze->functionOption) & functionOptionAC )
	{
		switch(EnvParameter->Product)
		{
		case ProductCLT:{
				PRINTF_N("[%s -%d ] Product	CLT \n",__func__,__LINE__);
				return success;
				break;
			}
		case ProductLE :{
				break;
			}
		case ProductHV:{
				EnvParameter->FunctionOptionAccessDB = 1;
				EnvParameter->FunctionOptionAccessRecordQuery = 1;
				break;
			}
		case ProductLT:
			{	
				break;
			}
		case ProductReserved:{
			
				PRINTF_N("[%s -%d ] Product	Reserved \n",__func__,__LINE__); 
				break;
			}
		default:PRINTF_N("Product other !!!!!!! \n");
		
		}
	}

	if(atoi(PnAnalyze->functionOption) & functionOptionThirdPartyProtocol )
	{
			switch(EnvParameter->Product)
		{
		case ProductCLT:{
				PRINTF_N("[%s -%d ] Product	CLT \n",__func__,__LINE__);
				return success;
				break;
			}
		case ProductLE :{
				break;
			}
		case ProductHV:{
				break;
			}
		case ProductLT:
			{	
				EnvParameter->FunctionOptionCustomizedRS485 = 1;
				break;
			}
		case ProductReserved:{
			
				PRINTF_N("[%s -%d ] Product	Reserved \n",__func__,__LINE__); 
				break;
			}
		default:PRINTF_N("Product other !!!!!!! \n");
		
		}
	}
	return success;
}

/**
 *  <#Description#>
 *
 *  @param EnvParameter <#EnvParameter description#>
 *
 *  @return <#return value description#>
 */
int AnalyticalPn(ENVParameter * EnvParameter)
{
	if(EnvParameter == NULL)
	{
        PRINTF_E("[%s-%d] AnalyticalPn fail ",__func__,__LINE__);
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
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////

/**
 *  <#Description#>
 *
 *  @param hardwareAddr <#hardwareAddr description#>
 *  @param fp           <#fp description#>
 *  @param envParameter <#envParameter description#>
 *  @param fileContent  <#fileContent description#>
 *
 *  @return <#return value description#>
 */
static int getVersion(char *hardwareAddr,int *fp,ENVParameter * envParameter,
char *fileContent)
{
	char * str,*head,*tail;
	int nread,i;

	if(hardwareAddr==NULL || fp==NULL || envParameter==NULL || fileContent==NULL)
	{
        PRINTF_E("[%s - %d] getVersion fail",__func__,__LINE__);
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
		PRINTF_E("checkVersion:can not find '=' after \"Version\" in %s.\n",
hardwareAddr);
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
	PRINTF_N(" [%s--%d] checkVersion:envParameter->Version = %s.\n",__func__,
__LINE__,envParameter->Version);
	return success;
}

/**
 *  <#Description#>
 *
 *  @param hardwareAddr <#hardwareAddr description#>
 *  @param fp           <#fp description#>
 *  @param envParameter <#envParameter description#>
 *  @param fileContent  <#fileContent description#>
 *
 *  @return <#return value description#>
 */
static int getPN(char *hardwareAddr,int *fp,ENVParameter * envParameter,char *
fileContent)
{
	char * str,*head,*tail;
	int nread,i;

	if(hardwareAddr==NULL || fp==NULL || envParameter==NULL || fileContent==NULL)
	{
		PRINTF_E("[%s-%d]getPN fail \n",__func__,__LINE__);
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
	PRINTF_N("[%s--%d] checkPN:envParameter->PN = %s.\n",__func__,__LINE__,
envParameter->PN);
	return success;
}
/**
 *  <#Description#>
 *
 *  @param hardwareAddr <#hardwareAddr description#>
 *  @param envParameter <#envParameter description#>
 *
 *  @return <#return value description#>
 */
static int openHardware(char *hardwareAddr ,ENVParameter * envParameter)
{
    int fp;
	int	size;
    char fileContent[200] = "";//file content
	fp = open(hardwareAddr,O_RDONLY);	
	if(fp == -1)
	{
		PRINTF_E("[%s--%d] open  hardware Address fail %s \n",__func__,__LINE__,
hardwareAddr);
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


/**
 *  <#Description#>
 *
 *  @param macAddr      <#macAddr description#>
 *  @param fp           <#fp description#>
 *  @param envParameter <#envParameter description#>
 *  @param fileContent  <#fileContent description#>
 *
 *  @return <#return value description#>
 */
static int getMacAddr(char *macAddr,int *fp,ENVParameter * envParameter,char *
fileContent)
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
	PRINTF_N("[%s--%d] checkMacAddr:  MACaddress = %s.\n",__func__,__LINE__,
MACaddress);
	unsigned int mac[6];
	sscanf (MACaddress, "%02x:%02x:%02x:%02x:%02x:%02x",&mac[0],&mac[1],&mac[2],&
mac[3],&mac[4],&mac[5]);
	
	PRINTF_N("EnvParameter = %d-%d-%d-%d-%d-%d\n",mac[0],mac[1],mac[2],mac[3],mac
[4],mac[5]);
	for(i = 0; i < 6 ;i++)
	{	
		envParameter->mac[i] = mac[i];
	}
	return success;
}
/**
 *  <#Description#>
 *
 *  @param macAddr      <#macAddr description#>
 *  @param envParameter <#envParameter description#>
 *
 *  @return <#return value description#>
 */
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
/**
 *  <#Description#>
 *
 *  @param envParameter <#envParameter description#>
 *  @param AddrHardware <#AddrHardware description#>
 *  @param AddrMac      <#AddrMac description#>
 *
 *  @return <#return value description#>
 */
int openGetPnMacVersion(ENVParameter * envParameter,char * AddrHardware, char 
* AddrMac)
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

/**
 *  <#Description#>
 *
 *  @param envParameter <#envParameter description#>
 *
 *  @return <#return value description#>
 */
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
			
		if((mac[0] == 0xff && mac[1] == 0xff && mac[2] == 0xff && mac[3] == 0xff && 
mac[4] == 0xff && mac[5] == 0xff)
			||(mac[0] == 0x00 && mac[1] == 0x00 && mac[2] == 0x00 && mac[3] == 0x00 && 
mac[4] == 0x00 && mac[5] == 0x00) )
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

/**
 *  <#Description#>
 *
 *  @param envParameter <#envParameter description#>
 *
 *  @return <#return value description#>
 */
static int setEnvEth(ENVParameter * envParameter)
{

	char MACaddress[50];
	memset(MACaddress,0,sizeof(MACaddress));
	sprintf(MACaddress,"fw_setenv eth0 %02x:%02x:%02x:%02x:%02x:%02x",
	envParameter->mac[0],envParameter->mac[1],envParameter->mac[2],envParameter->mac[3],envParameter->mac[4],envParameter->mac[5]);
	system(MACaddress);

	PRINTF_N("MACaddress = %s \n",MACaddress);
	if(envParameter->EthDiDoRS485 >1)
		{
		updateMacAddress(envParameter);
		memset(MACaddress,0,sizeof(MACaddress));
		sprintf(MACaddress,"fw_setenv eth0 %02x:%02x:%02x:%02x:%02x:%02x",
		envParameter->mac[0],envParameter->mac[1],envParameter->mac[2],envParameter->mac[3],envParameter->mac[4],envParameter->mac[5]);
		system(MACaddress);
		PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,MACaddress);
		}
	return success;
}


/**
 *  <#Description#>
 *
 *  @param envParameter <#envParameter description#>
 *
 *  @return <#return value description#>
 */
static int setEnvFunctionOption(ENVParameter * envParameter)
{
	if(envParameter==NULL)
		{
			PRINTF_E("[%s-%d]set Env Parameter fail",__func__,__LINE__);
			return fail;
		}

	char tmp[50];
	
	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv FunctionOptionAccessDB %d",envParameter->FunctionOptionAccessDB);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv FunctionOptionAccessRecordQuery %d",envParameter->FunctionOptionAccessRecordQuery);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv FunctionOptionAlarm %d",envParameter->FunctionOptionAlarm);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv FunctionOptionAPP %d",envParameter->FunctionOptionAPP);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv FunctionOptionBasiceClent %d",envParameter->FunctionOptionBasiceClent);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv FunctionOptionCustomizedRS485 %d",envParameter->FunctionOptionCustomizedRS485);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv FunctionOptionIpCamera %d",envParameter->FunctionOptionIpCamera);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv FunctionOptionLiftControl %d",envParameter->FunctionOptionLiftControl);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv FunctionOptionMiniSCASA %d",envParameter->FunctionOptionMiniSCASA);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"fw_setenv FunctionOptionVideoIntercom %d",envParameter->FunctionOptionVideoIntercom);
	PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
	system(tmp);

	return success;
}

/**
 *  <#Description#>
 *
 *  @param envParameter <#envParameter description#>
 *
 *  @return <#return value description#>
 */
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

	setEnvFunctionOption(envParameter);

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
///////////////////////////////////////////////////////////////////////////////
///////////////////////

/**
 *  <#Description#>
 *
 *  @param AddrMac      <#AddrMac description#>
 *  @param fp           <#fp description#>
 *  @param envParameter <#envParameter description#>
 *
 *  @return <#return value description#>
 */
static  int  writeMacAddr(char *AddrMac,int *fp,ENVParameter * envParameter)
{
	char MACaddress[50];
	memset(MACaddress,0,sizeof(MACaddress));
	if(AddrMac==NULL || fp==NULL || envParameter==NULL)
	{
		return fail;
	}
	updateMacAddress(envParameter);
	sprintf(MACaddress,"[MAC]\nADDRESS=%02x:%02x:%02x:%02x:%02x:%02x\n",
envParameter->mac[0],envParameter->mac[1],envParameter->mac[2],envParameter->
mac[3],envParameter->mac[4],envParameter->mac[5]);
	write(*fp,MACaddress,strlen(MACaddress));
	return success;	
}
/**
 *  <#Description#>
 *
 *  @param envParameter <#envParameter description#>
 *  @param AddrMac      <#AddrMac description#>
 *
 *  @return <#return value description#>
 */
static int updateMac(ENVParameter * envParameter, char * AddrMac)
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

int AnalyzePNMAC(void)
{
		ENVParameter EnvParameter;
		memset(&EnvParameter,0,sizeof(ENVParameter));
		
		// step 1.	pn 
		if(fail == openGetPnMacVersion(&EnvParameter,addrhardware_test,addrmac_test))
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
		
		PRINTF_N("[%s -%d ]EnvParameter.EthDiDoRS485=%d,EnvParameter.language=%d,EnvParameter.Product=%d,EnvParameter.ScreenSize=%d,EnvParameter.PN = %s,EnvParameter.Version=%s\n",__func__,__LINE__,EnvParameter.EthDiDoRS485,EnvParameter.language,EnvParameter.Product,EnvParameter.ScreenSize,EnvParameter.PN,EnvParameter.Version);
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
		if(fail == updateMac(&EnvParameter,addrmac_test))
		{
			PRINTF_E("[%s-%d]updateMac fail",__func__,__LINE__);
			return -5;
		}
		
		return 0;
}


static char str[][40] = { 	"FunctionOptionBasiceClent",
						   	"FunctionOptionVideoIntercom",
						   	"FunctionOptionAlarm",
						   	"FunctionOptionAPP",
						   	"FunctionOptionLiftControl",
						   	"FunctionOptionIpCamera",
						   	"FunctionOptionAccessRecordQuery",
						   	"FunctionOptionMiniSCASA",
						   	"FunctionOptionCustomizedRS485"};
int propSet(void)
{
	char** e;   
	char* v;   
	int i;     
	char tmp[50];  
	PRINTF_N("[%s-%d] \n",__func__,__LINE__);


	for(i = 0; i < sizeof(str)/40 ;i ++)
		{
		v = getenv(str[i]); 
		PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,v);
		if (v) {         		
			memset(tmp,0,sizeof(tmp));
			sprintf(tmp,"setprop %s %s",str[i],v);
			PRINTF_N("[%s-%d] %s \n",__func__,__LINE__,tmp);
			system(tmp);
			}    
		}  	  
	return 0;
}


/**
 *  <#Description#>
 *
 *  @param argc <#argc description#>
 *  @param argv <#argv description#>
 *
 *  @return <#return value description#>
 */
int main(int argc, char *argv[])
{


	return propSet();

	
	/* Check for existence */
	if( (access( addrmac_test, 0 )) != -1 )
	{
	
		return  AnalyzePNMAC();
		
	}else
	{
	
	

	}


	return 0;
	
	
	
}
