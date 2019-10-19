njit8021xclient: clients fillmd5 mainclient h3c-aes-md5
	$(CC) $(CFLAGS) $(LDFLAGS) -o client client-main.o client-auth.o client-ip.o client-fillmd5.o client-njit8021xclient.o client-aes.o client-h3c_AES_MD5.o md5.o naivehash.o -lpcap

clients:
	$(CC) $(CFLAGS)  -c -o client-main.o `test -f 'main.c' || echo './'`main.c
	$(CC) $(CFLAGS)  -c -o client-auth.o `test -f 'auth.c' || echo './'`auth.c
	$(CC) $(CFLAGS)  -c -o client-ip.o `test -f 'ip.c' || echo './'`ip.c

fillmd5:
	$(CC) $(CFLAGS)  -c -o md5.o `test -f 'md5.c' || echo './'`md5.c
	$(CC) $(CFLAGS)  -c -o client-fillmd5.o `test -f 'fillmd5-standalone.c' || echo './'`fillmd5-standalone.c

mainclient:
	$(CC) $(CFLAGS)  -c -o client-njit8021xclient.o `test -f 'njit8021xclient.c' || echo './'`njit8021xclient.c

h3c-aes-md5:
	$(CC) $(CFLAGS)  -c -o client-aes.o `test -f 'aes.c' || echo './'`aes.c
	$(CC) $(CFLAGS)  -c -o client-h3c_AES_MD5.o `test -f 'h3c_AES_MD5.c' || echo './'`h3c_AES_MD5.c
	$(CC) $(CFLAGS)  -c -o naivehash.o `test -f 'naivehash.c' || echo './'`naivehash.c


clean:
	rm *.o client
