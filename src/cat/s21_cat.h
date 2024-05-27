#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flags {
  char sho;
  char lo[50];
};

void printik(char *filename);
void parser(int mass[], char **argv, int argc, struct flags *flag);
void sfunc(char *filename);
void tbigfunc(char *filename);
void ebigfunc(char *filename);
void bfunc(char *filename);
void nfunc(char *filename);
void vfunc(char *filename);
void tsmfunc(char *filename);
void esmfunc(char *filename);
void printTemp(char *filename);
void switchFunc(char *filename, int mass[]);