CC=/home/student/crosstools/arm-2010.09/bin/arm-none-linux-gnueabi-gcc

all: install

# link .o's together with correct soname and real name
libmy-utils.so.1.0 : test1.o test2.o test3.o
	$(CC) 

test1.o : test1.c # compile test1 w/ correct flags and output test1.o
	$(CC) 

test2.o : test2.c # compile test2 w/ correct flags and output test2.o
	$(CC) 

test3.o : test3.c # compile test3 w/ correct flags and output test3.o
	$(CC) 

clean:
	rm -f *.o *.so.*

install: libmy-utils.so.1.0
	cp $< /home/student/targetfs/usr/local/lib


