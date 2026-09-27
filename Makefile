extract: extract.c
	gcc extract.c -o extract -Wall -Wextra

.PHONY: clean run test

clean:
	rm -f extract

run: extract
	./extract

test: extract
	cat test.in | ./extract > test.tmp
	diff test.tmp test.out
	rm test.tmp
