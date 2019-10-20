#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "md5.h"
#include "aes.h"
#include "h3c_dict.h"
#include "naivehash.h"
#include "h3c_AES_MD5.h"

/* 大小端问题 */
//大小端检测，如果 ENDIANNESS=='l' 则为小端
static union { char c[4]; unsigned long mylong; } endian_test = {{ 'l', '?', '?', 'b' } }; 
static int initialized = 0;
#define ENDIANNESS ((char)endian_test.mylong)
//大小端转换
#define BigLittleSwap32(A) ((((uint32_t)(A)&0xff000000)>>24)|\
	(((uint32_t)(A)&0x00ff0000)>>8)|\
	(((uint32_t)(A)&0x0000ff00)<<8)|\
	(((uint32_t)(A)&0x000000ff)<<24))
//void main()
//{
//	test();
//}

int test() {
	unsigned char encrypt_data[32] = { 0xcf, 0xfe, 0x64, 0x73, 0xd5, 0x73, 0x3b, 0x1f, 0x9e, 0x9a, 0xee, 0x1a, 0x6b, 0x76, 0x47, 0xc8, 0x9e, 0x27, 0xc8, 0x92, 0x25, 0x78, 0xc4, 0xc8, 0x27, 0x03, 0x34, 0x50, 0xb6, 0x10, 0xb8, 0x35 };
	unsigned char decrypt_data[32];
	unsigned char i;

	// decrypt
	h3c_AES_MD5_decryption(decrypt_data, encrypt_data);

	// print
	printf("encrypted string = ");
	for (i = 0; i<32; ++i) {
		printf("%x%x", ((int)encrypt_data[i] >> 4) & 0xf,
			(int)encrypt_data[i] & 0xf);
	}
	printf("\n");
	printf("decrypted string = ");
	for (i = 0; i<32; ++i) {
		printf("%x%x", ((int)decrypt_data[i] >> 4) & 0xf,
			(int)decrypt_data[i] & 0xf);
	}
	// the decrypt_data should be 8719362833108a6e16b08e33943601542511372d8d1fb1ab31aa17059118a6ba
	getchar();
	return 0;
}

//参考 h3c_AES_MD5.md 文档中对算法的说明
int h3c_AES_MD5_decryption(unsigned char *decrypt_data, unsigned char *encrypt_data)
{
	const unsigned char key[16] = { 0xEC, 0xD4, 0x4F, 0x7B, 0xC6, 0xDD, 0x7D, 0xDE, 0x2B, 0x7B, 0x51, 0xAB, 0x4A, 0x6F, 0x5A, 0x22 };        // AES_BLOCK_SIZE = 16
	unsigned char iv1[16] = { 'a', '@', '4', 'd', 'e', '%', '#', '1', 'a', 's', 'd', 'f', 's', 'd', '2', '4' };        // init vector
	unsigned char iv2[16] = { 'a', '@', '4', 'd', 'e', '%', '#', '1', 'a', 's', 'd', 'f', 's', 'd', '2', '4' }; //每次加密、解密后，IV会被改变！因此需要两组IV完成两次“独立的”解密
	unsigned int length_1;
	unsigned int length_2;
	unsigned char tmp0[32];
	unsigned char sig[255];
	unsigned char tmp2[16];
	unsigned char tmp3[16];
	// decrypt
	AES128_CBC_decrypt_buffer(tmp0, encrypt_data, 32, key, iv1);
	memcpy(decrypt_data, tmp0, 16);
	length_1 = *(tmp0 + 5);
	get_sig(*(uint32_t *)tmp0, *(tmp0 + 4), length_1, sig);
	MD5(sig, length_1, tmp2);

	AES128_CBC_decrypt_buffer(tmp3, tmp0+16, 16, tmp2, iv2);

	memcpy(decrypt_data + 16, tmp3, 16);

	length_2 = *(tmp3 + 15);
	get_sig(*(uint32_t *)(tmp3 + 10), *(tmp3 + 14), length_2, sig + length_1);
	if (length_1 + length_2>32)
	{
		memcpy(decrypt_data, sig, 32);
	}
	else
	{
		memcpy(decrypt_data, sig, length_1 + length_2);
	}
	MD5(decrypt_data, 32, decrypt_data);//获取MD5摘要数据，将结果存到前16位中
	MD5(decrypt_data, 16, decrypt_data + 16);//将前一MD5的结果再做一次MD5，存到后16位
	return 0;
}


// 查找表函数，根据索引值、偏移量以及长度查找序列
char* get_sig(uint32_t index, int offset, int length, unsigned char* dst)
{
	uint32_t index_tmp;
	const unsigned char *base_address;
	// printf("index = %x\n" ,index);
	
	if (ENDIANNESS == 'l')
	{
		index_tmp = BigLittleSwap32(index); // 小端情况，如PC架构
	}
	else
	{
		index_tmp = index; // 大端序，如MIPS架构
	}
	switch (index_tmp) // this line works in mips.
	{
    // E0310
    case 0x03CDF437: base_address=x03CDF437; break;
    case 0x06ADBF60: base_address=x06ADBF60; break;
    case 0x12544A15: base_address=x12544A15; break;
    case 0x130C9ADA: base_address=x130C9ADA; break;
    case 0x17B15B39: base_address=x17B15B39; break;
    case 0x19A6C03B: base_address=x19A6C03B; break;
    case 0x1BCF48C5: base_address=x1BCF48C5; break;
    case 0x1C04B737: base_address=x1C04B737; break;
    case 0x1CBD7B39: base_address=x1CBD7B39; break;
    case 0x212E9B02: base_address=x212E9B02; break;
    case 0x2137957E: base_address=x2137957E; break;
    case 0x2F24C371: base_address=x2F24C371; break;
    case 0x35CF3ED4: base_address=x35CF3ED4; break;
    case 0x377B7FA2: base_address=x377B7FA2; break;
    case 0x3F363676: base_address=x3F363676; break;
    case 0x40ACD79D: base_address=x40ACD79D; break;
    case 0x436F74E0: base_address=x436F74E0; break;
    case 0x4D1667CB: base_address=x4D1667CB; break;
    case 0x518A8E61: base_address=x518A8E61; break;
    case 0x56DBA188: base_address=x56DBA188; break;
    case 0x65E0B689: base_address=x65E0B689; break;
    case 0x6D19EB05: base_address=x6D19EB05; break;
    case 0x842DF988: base_address=x842DF988; break;
    case 0x89ABEB9C: base_address=x89ABEB9C; break;
    case 0x8AA4989B: base_address=x8AA4989B; break;
    case 0x9A9C4F26: base_address=x9A9C4F26; break;
    case 0x9E8A427F: base_address=x9E8A427F; break;
    case 0xA49F9D56: base_address=xA49F9D56; break;
    case 0xADA4E115: base_address=xADA4E115; break;
    case 0xAEC910AE: base_address=xAEC910AE; break;
    case 0xBA58E3C3: base_address=xBA58E3C3; break;
    case 0xBB701B4C: base_address=xBB701B4C; break;
    case 0xBFBAB666: base_address=xBFBAB666; break;
    case 0xC424E9EA: base_address=xC424E9EA; break;
    case 0xCAC2E8AF: base_address=xCAC2E8AF; break;
    case 0xCAE3687C: base_address=xCAE3687C; break;
    case 0xE7CABFD3: base_address=xE7CABFD3; break;
    case 0xE933C673: base_address=xE933C673; break;
    case 0xEC439434: base_address=xEC439434; break;
    case 0xEED0A89C: base_address=xEED0A89C; break;
	default:
		printf("lookup dict failed.\n"); // 查表失败
        printf("attempted to lookup 0x%08x\n", index_tmp);
		base_address = xBFBAB666;
		break;
	}
	memcpy(dst, base_address + offset, length);
	return dst;
}
