
njit8021xclient: clients fillmd5 mainclient etc
	$(CC) $(CFLAGS) $(LDFLAGS) -o client client-main.o client-auth.o client-ip.o client-fillmd5-libcrypto.o client-njit8021xclient.o md5-buildin/client-md5_one.o md5-buildin/client-md5_dgst.o md5-buildin/client-mem_clr.o client-aes.o client-h3c_AES_MD5.o 

clients:
	$(CC) $(CFLAGS) -MT client-main.o -MD -MP -MF .deps/client-main.Tpo -c -o client-main.o `test -f 'main.c' || echo './'`main.c
	mv -f .deps/client-main.Tpo .deps/client-main.Po
	$(CC) $(CFLAGS) -MT client-auth.o -MD -MP -MF .deps/client-auth.Tpo -c -o client-auth.o `test -f 'auth.c' || echo './'`auth.c
	mv -f .deps/client-auth.Tpo .deps/client-auth.Po
	$(CC) $(CFLAGS) -MT client-ip.o -MD -MP -MF .deps/client-ip.Tpo -c -o client-ip.o `test -f 'ip.c' || echo './'`ip.c
	mv -f .deps/client-ip.Tpo .deps/client-ip.Po

fillmd5:
	$(CC) $(CFLAGS) -MT client-fillmd5-libcrypto.o -MD -MP -MF .deps/client-fillmd5-libcrypto.Tpo -c -o client-fillmd5-libcrypto.o `test -f 'fillmd5-libcrypto.c' || echo './'`fillmd5-libcrypto.c

mainclient:
	mv -f .deps/client-fillmd5-libcrypto.Tpo .deps/client-fillmd5-libcrypto.Po
	$(CC) $(CFLAGS) -MT client-njit8021xclient.o -MD -MP -MF .deps/client-njit8021xclient.Tpo -c -o client-njit8021xclient.o `test -f 'njit8021xclient.c' || echo './'`njit8021xclient.c
	mv -f .deps/client-njit8021xclient.Tpo .deps/client-njit8021xclient.Po

etc:
	$(CC) $(CFLAGS) -MT md5-buildin/client-md5_one.o -MD -MP -MF md5-buildin/.deps/client-md5_one.Tpo -c -o md5-buildin/client-md5_one.o `test -f 'md5-buildin/md5_one.c' || echo './'`md5-buildin/md5_one.c
	mv -f md5-buildin/.deps/client-md5_one.Tpo md5-buildin/.deps/client-md5_one.Po
	$(CC) $(CFLAGS) -MT md5-buildin/client-md5_dgst.o -MD -MP -MF md5-buildin/.deps/client-md5_dgst.Tpo -c -o md5-buildin/client-md5_dgst.o `test -f 'md5-buildin/md5_dgst.c' || echo './'`md5-buildin/md5_dgst.c
	mv -f md5-buildin/.deps/client-md5_dgst.Tpo md5-buildin/.deps/client-md5_dgst.Po
	$(CC) $(CFLAGS) -MT md5-buildin/client-mem_clr.o -MD -MP -MF md5-buildin/.deps/client-mem_clr.Tpo -c -o md5-buildin/client-mem_clr.o `test -f 'md5-buildin/mem_clr.c' || echo './'`md5-buildin/mem_clr.c
	mv -f md5-buildin/.deps/client-mem_clr.Tpo md5-buildin/.deps/client-mem_clr.Po
	$(CC) $(CFLAGS) -MT client-aes.o -MD -MP -MF .deps/client-aes.Tpo -c -o client-aes.o `test -f 'aes.c' || echo './'`aes.c
	mv -f .deps/client-aes.Tpo .deps/client-aes.Po
	$(CC) $(CFLAGS) -MT client-h3c_AES_MD5.o -MD -MP -MF .deps/client-h3c_AES_MD5.Tpo -c -o client-h3c_AES_MD5.o `test -f 'h3c_AES_MD5.c' || echo './'`h3c_AES_MD5.c
	mv -f .deps/client-h3c_AES_MD5.Tpo .deps/client-h3c_AES_MD5.Po


clean:
	rm *.o md5-buildin/*.o client
