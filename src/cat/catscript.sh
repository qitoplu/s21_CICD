#!/bin/sh
EXPECTED=expected.txt
GOT=got.txt

while IFS= read -r line; do
    cat $line > "$EXPECTED" 2> /dev/null < /dev/null
    ./s21_cat $line > "$GOT" 2> /dev/null < /dev/null
    if cmp -s "$EXPECTED" "$GOT"; then
        echo "TEST s21_cat $line PASSED"
    else
        echo "TEST s21_cat $line FAILED"

    fi
done <<END
s21_cat.c
-b s21_cat.c
-e s21_cat.c
-n s21_cat.c
-s s21_cat.c
-t s21_cat.c
-v s21_cat.c
-s s21_cat.c s21_cat.h
-bbbbb s21_cat.c
not_exists.txt
END
