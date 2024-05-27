W=-Wall -Wextra -Werror -std=c11

clean:
	rm -rf *.o

s21_grep.o: s21_grep.c
	gcc $(W) -c s21_grep.c -o s21_grep.o

s21_grep: s21_grep.o
	gcc $(W) s21_grep.o -lm -o s21_grep