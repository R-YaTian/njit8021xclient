// OI/ACM style hash table in C
// This is UNSAFE!!!
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include "naivehash.h"
#define MAX_ENTRIES 64 // enough for h3c_AES_MD5
#define MODN 107
#define DATA_T uint8_t* 
#define INDEX_T uint32_t

static size_t head[MODN], njmp[MAX_ENTRIES];
static DATA_T obj[MAX_ENTRIES];
static INDEX_T orig_index[MAX_ENTRIES];
static size_t top;

static int initialized = 0;

void naivehash_add(INDEX_T index, DATA_T data)
{
    top++;
    size_t hashindex = index % MODN;
    njmp[top] = head[hashindex];
    orig_index[top] = index;
    obj[top] = data;
    head[hashindex] = top;
}

DATA_T naivehash_query(const INDEX_T index)
{
    printf("naivehash_query(%x)\n", index);
    // return NULL if not found
    for (size_t i=head[index%MODN];i;i=njmp[i])
    {
        if (index == orig_index[i])
            return obj[i];
    }
    return NULL;
}

void naivehash_init()
{
#include "h3c_dict.h"
    naivehash_add(0x03CDF437, x03CDF437);
    naivehash_add(0x06ADBF60, x06ADBF60);
    naivehash_add(0x12544A15, x12544A15);
    naivehash_add(0x130C9ADA, x130C9ADA);
    naivehash_add(0x17B15B39, x17B15B39);
    naivehash_add(0x19A6C03B, x19A6C03B);
    naivehash_add(0x1BCF48C5, x1BCF48C5);
    naivehash_add(0x1C04B737, x1C04B737);
    naivehash_add(0x1CBD7B39, x1CBD7B39);
    naivehash_add(0x212E9B02, x212E9B02);
    naivehash_add(0x2137957E, x2137957E);
    naivehash_add(0x2F24C371, x2F24C371);
    naivehash_add(0x35CF3ED4, x35CF3ED4);
    naivehash_add(0x377B7FA2, x377B7FA2);
    naivehash_add(0x3F363676, x3F363676);
    naivehash_add(0x40ACD79D, x40ACD79D);
    naivehash_add(0x436F74E0, x436F74E0);
    naivehash_add(0x4D1667CB, x4D1667CB);
    naivehash_add(0x518A8E61, x518A8E61);
    naivehash_add(0x56DBA188, x56DBA188);
    naivehash_add(0x65E0B689, x65E0B689);
    naivehash_add(0x6D19EB05, x6D19EB05);
    naivehash_add(0x842DF988, x842DF988);
    naivehash_add(0x89ABEB9C, x89ABEB9C);
    naivehash_add(0x8AA4989B, x8AA4989B);
    naivehash_add(0x9A9C4F26, x9A9C4F26);
    naivehash_add(0x9E8A427F, x9E8A427F);
    naivehash_add(0xA49F9D56, xA49F9D56);
    naivehash_add(0xADA4E115, xADA4E115);
    naivehash_add(0xAEC910AE, xAEC910AE);
    naivehash_add(0xBA58E3C3, xBA58E3C3);
    naivehash_add(0xBB701B4C, xBB701B4C);
    naivehash_add(0xBFBAB666, xBFBAB666);
    naivehash_add(0xC424E9EA, xC424E9EA);
    naivehash_add(0xCAC2E8AF, xCAC2E8AF);
    naivehash_add(0xCAE3687C, xCAE3687C);
    naivehash_add(0xE7CABFD3, xE7CABFD3);
    naivehash_add(0xE933C673, xE933C673);
    naivehash_add(0xEC439434, xEC439434);
    naivehash_add(0xEED0A89C, xEED0A89C);
}
