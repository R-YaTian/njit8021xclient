// OI/ACM style hash table in C
// This is UNSAFE!!!
//
#ifndef _NAIVEHASH_H
#define _NAIVEHASH_H

#define DATA_T uint8_t* 
#define INDEX_T uint32_t

void naivehash_add(INDEX_T index, DATA_T data);
DATA_T naivehash_query(const INDEX_T index);

void naivehash_init();
#undef DATA_T
#undef INDEX_T

#endif // _NAIVEHASH_H
