,fork: fork.c process.c process.h
	gcc -o fork fork.c process.c process.h

clean:
	rm -f fork
