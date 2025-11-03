/* microprintf */
#include <unistd.h>
#undef strlen

char *wrap_char(const char c) {
  static char buf[2];

  buf[0] = c;
  buf[1] = '\0';
  return buf;
}

unsigned int strlen(const char *str) {
  unsigned int n;
  const char *p = str;

  if (!*p) return 0;

  while (*p) {
    p++;
    n++;
  }

  return n;
}

int puts(const char *str) {
   unsigned int n;
   n = strlen(str);

  if (n < 1) {
    return -1;
  }

  return write(1, str, n);
}

int main() {
  puts ("test\n");

  return 0;
}
