GCC = gcc 
GFLAGS = 

rebuild: clean install

install:
  $(GCC)  bf.c -o bf $(GFLAGS)
  
clean:
	rm -f bf || true
