all: test.c pool.c
	gcc --std=gnu99 test.c pool.c -O3 -o test
	
clean:
	rm ./test