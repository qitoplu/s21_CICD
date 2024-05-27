#include "s21_cat.h"

int main(int argc, char **argv) {
  struct flags flag[8] = {
      {'b', "-number-nonblank"},
      {'e', ""},
      {'n', "-number"},
      {'s', "-squeeze-blank"},
      {'t', ""},
      {'v', "-show-nonprinting"},
      {'T', "-show-tabs"},
      {'E', "-show-ends"},
  };
  int mass[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  parser(mass, argv, argc, flag);
  printik("temp.txt");
  remove("temp.txt");

  return 0;
}

void printik(char *filename) {
  FILE *f = fopen(filename, "rt");
  if (f == NULL) {
    exit(1);
  }
  int c = fgetc(f);
  while (c != EOF) {
    putc(c, stdout);
    c = fgetc(f);
  }
  fclose(f);
}

void parser(int mass[], char **argv, int argc, struct flags *flag) {
  for (int j = 1; j < argc; j++) {
    if (argv[j][0] != '-') {
      switchFunc(argv[j], mass);
    } else {
      ++argv[j];
      int fl = 0;
      while (*argv[j]) {
        if (fl) break;
        for (int i = 0; i < 8; i++) {
          if (*argv[j] == flag[i].sho || strcmp(argv[j], flag[i].lo) == 0) {
            mass[i] = 1;
            fl = 1;
            break;
          }
        }
        ++argv[j];
      }
    }
  }
}

void switchFunc(char *filename, int mass[]) {
  int count = 0;
  for (int i = 0; i < 8; i++) {
    if ((mass[i] == 1) && (i == 0)) {
      bfunc(filename);
    }
    if ((mass[i] == 1) && (i == 1)) {
      esmfunc(filename);
    }
    if ((mass[i] == 1) && (i == 2)) {
      nfunc(filename);
    }
    if ((mass[i] == 1) && (i == 3)) {
      sfunc(filename);
    }
    if ((mass[i] == 1) && (i == 4)) {
      tsmfunc(filename);
    }
    if ((mass[i] == 1) && (i == 5)) {
      vfunc(filename);
    }
    if ((mass[i] == 1) && (i == 6)) {
      tbigfunc(filename);
    }
    if ((mass[i] == 1) && (i == 7)) {
      ebigfunc(filename);
    }
    if (mass[i] == 0) {
      count++;
    }
  }
  if (count == 8) {
    printTemp(filename);
  }
}

void sfunc(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    exit(1);
  }
  FILE *temp = fopen("temp.txt", "a+");
  if (temp == NULL) {
    exit(1);
  }
  char line[4096];
  int isEmpty = 0;
  while (fgets(line, sizeof(line), f)) {
    for (int i = 0; line[i]; i++) {
      if (!isspace(line[i])) {
        isEmpty = 0;
        break;
      } else {
        isEmpty++;
      }
    }
    if (isEmpty == 1 || isEmpty == 0) {
      fputs(line, temp);
    }
  }
  fclose(f);
  fclose(temp);
}

void nfunc(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    exit(1);
  }
  FILE *temp = fopen("temp.txt", "a+");
  if (temp == NULL) {
    exit(1);
  }
  int count = 1;
  char line[4096];
  while (fgets(line, sizeof(line), f)) {
    fprintf(temp, "%6d", count);
    fputc('\t', temp);
    fputs(line, temp);
    count++;
  }
  fclose(f);
  fclose(temp);
}

void bfunc(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    exit(1);
  }
  FILE *temp = fopen("temp.txt", "a+");
  if (temp == NULL) {
    exit(1);
  }
  int count = 1;
  char line[4096];
  while (fgets(line, sizeof(line), f)) {
    int isEmpty = 1;
    for (int i = 0; line[i]; i++) {
      if (line[i] != '\n') {
        isEmpty = 0;
        break;
      }
    }
    if (!isEmpty) {
      fprintf(temp, "%6d", count);
      fputc('\t', temp);
      count++;
    }
    fputs(line, temp);
  }
  fclose(f);
  fclose(temp);
}

void ebigfunc(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    exit(1);
  }
  FILE *temp = fopen("temp.txt", "a+");
  if (temp == NULL) {
    exit(1);
  }
  char line[4096];
  while (fgets(line, sizeof(line), f)) {
    for (int i = 0; i < (int)strlen(line); i++) {
      if (line[i] == '\n') {
        line[i] = '$';
      }
    }
    fputs(line, temp);
    fputc('\n', temp);
  }
  fclose(f);
  fclose(temp);
}

void tbigfunc(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    exit(1);
  }
  FILE *temp = fopen("temp.txt", "a+");
  if (temp == NULL) {
    exit(1);
  }
  char line[4096];
  while (fgets(line, sizeof(line), f)) {
    for (int i = 0; i < (int)strlen(line); i++) {
      if ((line[i]) == 9) {
        fputc('^', temp);
        fputc('I', temp);
      } else {
        fputc(line[i], temp);
      }
    }
  }
  fclose(f);
  fclose(temp);
}

void printTemp(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    exit(1);
  }
  FILE *temp = fopen("temp.txt", "a+");
  if (temp == NULL) {
    exit(1);
  }
  char line[4096];
  while (fgets(line, sizeof(line), f)) {
    fputs(line, temp);
  }
  fclose(f);
  fclose(temp);
}

void vfunc(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    exit(1);
  }
  FILE *temp = fopen("temp.txt", "a+");
  if (temp == NULL) {
    exit(1);
  }
  char line[4096];
  while (fgets(line, sizeof(line), f)) {
    for (int i = 0; i < (int)strlen(line); i++) {
      if ((line[i] < 32 && line[i] >= 0 && line[i] != '\n' &&
           line[i] != '\t') ||
          line[i] == 9) {
        fprintf(temp, "^%c", line[i] + 64);
      } else if ((unsigned char)line[i] >= 128 &&
                 (unsigned char)line[i] < 255) {
        fprintf(temp, "M^%c", line[i] + 64);
      } else {
        fputc(line[i], temp);
      }
    }
  }
  fclose(f);
  fclose(temp);
}

void tsmfunc(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    exit(1);
  }
  FILE *temp = fopen("temp.txt", "a+");
  if (temp == NULL) {
    exit(1);
  }
  char line[4096];
  while (fgets(line, sizeof(line), f)) {
    for (int i = 0; i < (int)strlen(line); i++) {
      if ((line[i] < 32 && line[i] >= 0 && line[i] != '\n' &&
           line[i] != '\t') ||
          line[i] == 9) {
        fprintf(temp, "^%c", line[i] + 64);
      } else if ((unsigned char)line[i] >= 128 &&
                 (unsigned char)line[i] < 255) {
        fprintf(temp, "M^%c", line[i] + 64);
      } else {
        fputc(line[i], temp);
      }
    }
  }
  fclose(f);
  fclose(temp);
}

void esmfunc(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    exit(1);
  }
  FILE *temp = fopen("temp.txt", "a+");
  if (temp == NULL) {
    exit(1);
  }
  char line[4096];
  while (fgets(line, sizeof(line), f)) {
    for (int i = 0; i < (int)strlen(line); i++) {
      if (line[i] == '\n') {
        fputc('$', temp);
      } else if ((line[i] < 32 && line[i] >= 0 && line[i] != '\n' &&
                  line[i] != '\t') ||
                 line[i] == 9) {
        fprintf(temp, "^%c", line[i] + 64);
      } else if ((unsigned char)line[i] >= 128 &&
                 (unsigned char)line[i] < 255) {
        fprintf(temp, "M^%c", line[i] + 64);
      } else {
        fputc(line[i], temp);
      }
    }
    if (!feof(f)) {
      fputc('\n', temp);
    }
  }
  fclose(f);
  fclose(temp);
}
