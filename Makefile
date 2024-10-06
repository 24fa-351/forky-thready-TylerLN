# Targets and dependencies
fork: fork.c pattern1.h pattern2.h pattern1.c pattern2.c
	gcc -o fork fork.c pattern1.c pattern2.c

clean:
	rm -f fork
