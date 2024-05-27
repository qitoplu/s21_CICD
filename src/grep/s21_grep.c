#include "s21_grep.h"

int match(char *string, char *pattern, struct flags *flag, int *print_v) {
  int vflag = REG_EXTENDED;
  if (flag->i) vflag = REG_ICASE;
  int status;
  regex_t re;
  if ((status = regcomp(&re, pattern, vflag)) == 0) {
    status = regexec(&re, string, 0, NULL, 0);
    regfree(&re);
  }
  if (status == 0) *print_v = 0;
  return status;
}

int main(int argc, char **argv) {
  int majflag = 0;
  struct flags flag = {0};
  int opt;
  char *patterns[4096] = {0};
  int pattern_count = 0;

  while ((opt = getopt(argc, argv, "e:ivclnhsfo:?")) != -1) {
    switch (opt) {
      case 'e':
        flag.e = 1;
        patterns[pattern_count++] = optarg;
        break;
      case 'i':
        flag.i = 1;
        break;
      case 'v':
        flag.v = 1;
        break;
      case 'c':
        flag.c = 1;
        break;
      case 'l':
        flag.l = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 'h':
        flag.h = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 'f':
        flag.f = 1;
        break;
      case 'o':
        flag.o = 1;
        break;
      case '?':
        printf("error\n");
        break;
    }
  }
  if (flag.e != 1 && argv[optind] != NULL) {
    patterns[pattern_count] = argv[optind++];
    flag.e = 1;
  }
  if (argc - optind >= 2) {
    majflag = 1;
  }
  for (int i = optind; i < argc; i++) {
    print(&flag, argv[i], patterns, majflag);
  }
  return 0;
}

void print(struct flags *flag, char *filename, char *patterns[], int majflag) {
  char buffer[4096];
  int lflag = 0;
  int line_counter = 0;
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    if (!flag->s) perror("error");
    return;
  }

  int i;
  int cnt = 0;
  while (fgets(buffer, sizeof(buffer), file)) {
    int nflag = 0;
    line_counter++;
    int print_v = 1;
    int add = 0;
    for (i = 0; patterns[i] != NULL; i++) {
      if (match(buffer, patterns[i], flag, &print_v) == 0) {
        lflag = 1;
        nflag = 1;
        if (!flag->v && !flag->c && !flag->l && !flag->n && !flag->h && majflag)
          printf("%s:%s", filename, buffer);
        if (!flag->v && !flag->c && !flag->l && !flag->n && !flag->h &&
            !majflag)
          printf("%s", buffer);
        add = 1;
      }
    }
    if (flag->v)
      cnt += print_v;
    else
      cnt += add;
    if (flag->v && print_v && majflag && !flag->c && !flag->l)
      printf("%s:%s", filename, buffer);
    if (flag->v && print_v && !majflag && !flag->c && !flag->l)
      printf("%s", buffer);
    if (flag->n && nflag && !flag->c && !flag->l && !majflag)
      printf("%d:%s", line_counter, buffer);
    if (flag->n && nflag && !flag->c && !flag->l && majflag)
      printf("%s:%d:%s", filename, line_counter, buffer);
    if (flag->h && nflag && !flag->l && !flag->c) printf("%s", buffer);
  }
  if (flag->c && !flag->l && majflag) printf("%s:%d\n", filename, cnt);
  if (flag->c && !flag->l && !majflag) printf("%d\n", cnt);
  if (flag->l && lflag) printf("%s\n", filename);
  fclose(file);
}
