njit8021xclient: clients fillmd5 mainclient etc
	$(CC) $(CFLAGS) $(LDFLAGS) -o client client-main.o client-auth.o client-ip.o client-fillmd5-libcrypto.o client-njit8021xclient.o md5-buildin/client-md5_one.o md5-buildin/client-md5_dgst.o md5-buildin/client-mem_clr.o client-aes.o client-h3c_AES_MD5.o -lpcap

clients:
	$(CC) $(CFLAGS)  -c -o client-main.o `test -f 'main.c' || echo './'`main.c
	$(CC) $(CFLAGS)  -c -o client-auth.o `test -f 'auth.c' || echo './'`auth.c
	$(CC) $(CFLAGS)  -c -o client-ip.o `test -f 'ip.c' || echo './'`ip.c

fillmd5:
	$(CC) $(CFLAGS)  -c -o client-fillmd5-libcrypto.o `test -f 'fillmd5-libcrypto.c' || echo './'`fillmd5-libcrypto.c

mainclient:
	$(CC) $(CFLAGS)  -c -o client-njit8021xclient.o `test -f 'njit8021xclient.c' || echo './'`njit8021xclient.c

etc:
	$(CC) $(CFLAGS)  -c -o md5-buildin/client-md5_one.o `test -f 'md5-buildin/md5_one.c' || echo './'`md5-buildin/md5_one.c
	$(CC) $(CFLAGS)  -c -o md5-buildin/client-md5_dgst.o `test -f 'md5-buildin/md5_dgst.c' || echo './'`md5-buildin/md5_dgst.c
	$(CC) $(CFLAGS)  -c -o md5-buildin/client-mem_clr.o `test -f 'md5-buildin/mem_clr.c' || echo './'`md5-buildin/mem_clr.c
	$(CC) $(CFLAGS)  -c -o client-aes.o `test -f 'aes.c' || echo './'`aes.c
	$(CC) $(CFLAGS)  -c -o client-h3c_AES_MD5.o `test -f 'h3c_AES_MD5.c' || echo './'`h3c_AES_MD5.c


clean:
	rm *.o md5-buildin/*.o client
