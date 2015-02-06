build:
	$(CC) -I/usr/local/include -c captcha.c -o captcha.o
	$(CC) -I/usr/local/include -c libcaptcha.c -o libcaptcha.o
	$(AR) rc libcaptcha.a libcaptcha.o
	ranlib libcaptcha.a
	$(CC) -I/usr/local/include -o captcha captcha.o -L/usr/local/lib -lgd -L. -lcaptcha -Wl,--format=binary -Wl,captcha.ttf -Wl,--format=default

clean:
	rm -f captcha *.a *.o
