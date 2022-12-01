test: common_test.o
	cc *.o -o common_test

common_test.o:
	cc -c common.c -o common.o
	cc -c common_test.c -o common_test.o

clean:
	rm -f *.o
	rm -f common_test
