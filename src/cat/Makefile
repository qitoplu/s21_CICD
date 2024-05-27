W= -Wall -Wextra -Werror -std=c11
clean:
	rm -rf *.o

s21_cat.o: s21_cat.c
	gcc $(W) -c s21_cat.c -o s21_cat.o

s21_cat: s21_cat.o
	gcc $(W) s21_cat.o -lm -o s21_cat