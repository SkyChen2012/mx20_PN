#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "idea.h"

unsigned char k[16]={
	0x00,0x01,0x00,0x06,0x00,0x03,0x00,0x04,
	0x00,0x05,0x00,0x06,0x00,0x07,0x00,0x08};

unsigned char *in="kjhkhlkjhljkkij";

unsigned char  c[8]={0x11,0xFB,0xED,0x2B,0x01,0x98,0x6D,0xE5};

unsigned char out[80];

char *text="Hello to all people out there";

static unsigned char cfb_key[16]={
	0xe1,0xf0,0xc3,0xd2,0xa5,0xb4,0x87,0x96,
	0x69,0x78,0x4b,0x5a,0x2d,0x3c,0x0f,0x1e,
	};
static unsigned char cfb_iv[80]={0x34,0x12,0x78,0x56,0xab,0x90,0xef,0xcd};
static unsigned char cfb_buf1[40],cfb_buf2[40],cfb_tmp[8];
#define CFB_TEST_SIZE 24
static unsigned char plain[CFB_TEST_SIZE]=
	        {
        0x4e,0x6f,0x77,0x20,0x69,0x73,
        0x20,0x74,0x68,0x65,0x20,0x74,
        0x69,0x6d,0x65,0x20,0x66,0x6f,
        0x72,0x20,0x61,0x6c,0x6c,0x20
        };
static unsigned char cfb_cipher64[CFB_TEST_SIZE]={
	0x59,0xD8,0xE2,0x65,0x00,0x58,0x6C,0x3F,
	0x2C,0x17,0x25,0xD0,0x1A,0x38,0xB7,0x2A,
	0x39,0x61,0x37,0xDC,0x79,0xFB,0x9F,0x45

/*	0xF9,0x78,0x32,0xB5,0x42,0x1A,0x6B,0x38,
	0x9A,0x44,0xD6,0x04,0x19,0x43,0xC4,0xD9,
	0x3D,0x1E,0xAE,0x47,0xFC,0xCF,0x29,0x0B,*/
	}; 
/*
#ifndef NOPROTO
static int cfb64_test(unsigned char *cfb_cipher);
static char *pt(unsigned char *p);
#else
static int cfb64_test();
static char *pt();
#endif

int main(argc,argv)
int argc;
char *argv[];
	{
	int i,err=0;
	IDEA_KEY_SCHEDULE key,dkey; 
	unsigned char iv[8];

	idea_set_encrypt_key(k,&key);
	idea_ecb_encrypt(in,out,&key);
	printf("in=%ld     :",sizeof(in));
	
	for (i=0; i<15; i++)
		printf("%02X ",in[i]);
	printf("\n");
	printf("got     :");
	for (i=0; i<15; i++)
		printf("%02X ",out[i]);
	printf("\n");
	printf("expected:");
	for (i=0; i<8; i++)
		printf("%02X ",c[i]);
	printf("\n");
	

	idea_set_decrypt_key(&key,&dkey);
	idea_ecb_encrypt(c,out,&dkey);


	if (err == 0) printf("ecb idea ok\n");



	memcpy(iv,k,8);
	idea_cbc_encrypt((unsigned char *)text,out,strlen(text)+1,&key,iv,1);
	memcpy(iv,k,8);
	idea_cbc_encrypt(out,out,8,&dkey,iv,0);
	idea_cbc_encrypt(&(out[8]),&(out[8]),strlen(text)+1-8,&dkey,iv,0);
	if (memcmp(text,out,strlen(text)+1) != 0)
		{
		printf("cbc idea bad\n");
		err=4;
		}
	else
		printf("cbc idea ok\n");

	printf("cfb64 idea ");
	if (cfb64_test(cfb_cipher64))
		{
		printf("bad\n");
		err=5;
		}
	else
		printf("ok\n");

	exit(err);
	return(err);
	}

static int cfb64_test(cfb_cipher)
unsigned char *cfb_cipher;
        {
        IDEA_KEY_SCHEDULE eks,dks;
        int err=0,i,n;

        idea_set_encrypt_key(cfb_key,&eks);
        idea_set_decrypt_key(&eks,&dks);
        memcpy(cfb_tmp,cfb_iv,8);
        n=0;
        idea_cfb64_encrypt(plain,cfb_buf1,(long)12,&eks,
                cfb_tmp,&n,IDEA_ENCRYPT);
        idea_cfb64_encrypt(&(plain[12]),&(cfb_buf1[12]),
                (long)CFB_TEST_SIZE-12,&eks,
                cfb_tmp,&n,IDEA_ENCRYPT);
        if (memcmp(cfb_cipher,cfb_buf1,CFB_TEST_SIZE) != 0)
                {
                err=1;
                printf("idea_cfb64_encrypt encrypt error\n");
                for (i=0; i<CFB_TEST_SIZE; i+=8)
                        printf("%s\n",pt(&(cfb_buf1[i])));
                }
        memcpy(cfb_tmp,cfb_iv,8);
        n=0;
        idea_cfb64_encrypt(cfb_buf1,cfb_buf2,(long)17,&eks,
                cfb_tmp,&n,IDEA_DECRYPT);
        idea_cfb64_encrypt(&(cfb_buf1[17]),&(cfb_buf2[17]),
                (long)CFB_TEST_SIZE-17,&dks,
                cfb_tmp,&n,IDEA_DECRYPT);
        if (memcmp(plain,cfb_buf2,CFB_TEST_SIZE) != 0)
                {
                err=1;
                printf("idea_cfb_encrypt decrypt error\n");
                for (i=0; i<24; i+=8)
                        printf("%s\n",pt(&(cfb_buf2[i])));
                }
        return(err);
        }

static char *pt(p)
unsigned char *p;
	{
	static char bufs[10][20];
	static int bnum=0;
	char *ret;
	int i;
	static char *f="0123456789ABCDEF";

	ret= &(bufs[bnum++][0]);
	bnum%=10;
	for (i=0; i<8; i++)
		{
		ret[i*2]=f[(p[i]>>4)&0xf];
		ret[i*2+1]=f[p[i]&0xf];
		}
	ret[16]='\0';
	return(ret);
	}
*/	