#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "md5.h"

void FillMD5Area(uint8_t digest[], uint8_t id, const char passwd[], const uint8_t srcMD5[])
{
	uint8_t	msgbuf[128]; // msgbuf = ‘id‘ + ‘passwd’ + ‘srcMD5’
	size_t	msglen;
	size_t	passlen;

	passlen = strlen(passwd);
	msglen = 1 + passlen + 16;
	assert(sizeof(msgbuf) >= msglen);

	msgbuf[0] = id;
	memcpy(msgbuf+1,	 passwd, passlen);
	memcpy(msgbuf+1+passlen, srcMD5, 16);

	md5_state_t state;
	md5_init(&state);
	md5_append(&state, (const md5_byte_t *)msgbuf, msglen);
	md5_finish(&state, digest);
}
