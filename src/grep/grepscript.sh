#!/bin/sh

EXPECTED=expected.txt
GOT=got.txt

while IFS= read -r line; do
    egrep $line > "$EXPECTED" 2> /dev/null < /dev/null
    ./s21_grep $line > "$GOT" 2> /dev/null < /dev/null
    if cmp -s "$EXPECTED" "$GOT"; then
        echo "PASSED TEST grep $line"
    else
        echo "FAILED TEST grep $line"
    fi
done <<END
struct s21_grep.c
-i CHAR s21_grep.c
-v char s21_grep.c
-c char s21_grep.c
-l char s21_grep.c
-n char s21_grep.c
-h char s21_grep.c
-s char s21_grep.c
-f not_exists.txt s21_grep.c
-e char s21_grep.c
-echar s21_grep.c
-i char s21_grep.c ../cat/s21_cat.c
-v char s21_grep.c ../cat/s21_cat.c
-c char s21_grep.c ../cat/s21_cat.c
-l char s21_grep.c ../cat/s21_cat.c
-n char s21_grep.c ../cat/s21_cat.c
-h char s21_grep.c ../cat/s21_cat.c
-s char s21_grep.c ../cat/s21_cat.c
-e char s21_grep.c ../cat/s21_cat.c
-echar s21_grep.c ../cat/s21_cat.c
-iv Char s21_grep.c ../cat/s21_cat.c
-ic CHAR s21_grep.c ../cat/s21_cat.c
-il CHAR s21_grep.c ../cat/s21_cat.c
-ivc CHAR s21_grep.c ../cat/s21_cat.c
-ice CHAR s21_grep.c ../cat/s21_cat.c
-vc char s21_grep.c ../cat/s21_cat.c
-vl char s21_grep.c ../cat/s21_cat.c
-cn char s21_grep.c ../cat/s21_cat.c
int
-e int
int not_exists.txt
-e int not_exists.txt
-f not_exists.txt
main s21_grep.c Makefile
-e '\)' s21_grep.c
-f
END
