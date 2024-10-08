fork: fork.c pattern1.h pattern2.h pattern1.c pattern2.c
	gcc -o fork fork.c pattern1.c pattern2.c

results: 
	(echo "Pattern 1:" 1>&2; ./fork 1 $$(echo "$$((RANDOM % 15 + 5))"); \
	echo 1>&2; \
	echo "Pattern 2:" 1>&2; ./fork 2 $$(echo "$$((RANDOM % 15 + 5))")) 2> results.txt

clean:
	rm -f fork
