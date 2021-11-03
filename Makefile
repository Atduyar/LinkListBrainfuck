GCC = gcc 
GFLAGS = 

build: clean brainfuck

brainfuck:
  $(GCC)  bf.c -o bf $(GFLAGS)
  
clean:
	rm -f bf || true
