GCC = gcc
GFLAGS = -Wall

rebuild: clean install

install:
	$(GCC) bf.c -o bf $(GFLAGS)


clean:
	rm -f bf || true
