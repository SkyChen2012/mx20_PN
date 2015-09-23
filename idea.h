#ifndef HEADER_IDEA_H
#define HEADER_IDEA_H

#ifdef  __cplusplus
extern "C" {
#endif

#define IDEA_ENCRYPT	1
#define IDEA_DECRYPT	0

#define IDEA_INT unsigned int
#define IDEA_BLOCK	8
#define IDEA_KEY_LENGTH	16

typedef struct idea_key_st
	{
	IDEA_INT data[9][6];
	} IDEA_KEY_SCHEDULE;

#ifndef NOPROTO
char *idea_options(void);
void idea_ecb_encrypt(unsigned char *in, unsigned char *out,
	IDEA_KEY_SCHEDULE *ks);
void idea_set_encrypt_key(unsigned char *key, IDEA_KEY_SCHEDULE *ks);
void idea_set_decrypt_key(IDEA_KEY_SCHEDULE *ek, IDEA_KEY_SCHEDULE *dk);
void idea_cbc_encrypt(unsigned char *in, unsigned char *out,
	long length, IDEA_KEY_SCHEDULE *ks, unsigned char *iv,int enc);
void idea_cfb64_encrypt(unsigned char *in, unsigned char *out,
	long length, IDEA_KEY_SCHEDULE *ks, unsigned char *iv,
	int *num,int enc);
void idea_ofb64_encrypt(unsigned char *in, unsigned char *out,
	long length, IDEA_KEY_SCHEDULE *ks, unsigned char *iv, int *num);
void idea_encrypt(unsigned long *in, IDEA_KEY_SCHEDULE *ks);
#else
char *idea_options();
void idea_ecb_encrypt();
void idea_set_encrypt_key();
void idea_set_decrypt_key();
void idea_cbc_encrypt();
void idea_cfb64_encrypt();
void idea_ofb64_encrypt();
void idea_encrypt();
#endif

#ifdef  __cplusplus
}
#endif

#endif
