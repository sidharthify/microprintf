/* microprintf */
#include <unistd.h>
#include <stdarg.h>
#undef strlen

char *wrap_char(const char c) {
    static char buf[2];
    buf[0] = c;
    buf[1] = '\0';
    return buf;
}

unsigned int strlen(const char *str) {
    unsigned int n = 0;
    const char *p = str;

    if (!*p) return 0;

    while (*p) {
        p++;
        n++;
    }

    return n;
}

char *itoa(int value, char *buf) {
    int i = 0;

    if (value == 0) {
        buf[i++] = '0';
        buf[i] = '\0';
        return buf;
    }

    while (value != 0) {
        int digit = value % 10;
        buf[i++] = '0' + digit;
        value /= 10;
    }

    buf[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char tmp = buf[j];
        buf[j] = buf[i - j - 1];
        buf[i - j - 1] = tmp;
    }

    return buf;
}

int puts(const char *str) {
    unsigned int n = strlen(str);

    if (n < 1) {
        return -1;
    }

    return write(1, str, n);
}

int microprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    const char *p = fmt;
    while (*p) {
        if (*p == '%' && *(p + 1) == 'c') {
            char c = (char)va_arg(args, int);
            puts(wrap_char(c));
            p += 2;
        } else if (*p == '%' && *(p + 1) == 's') {
            char *s = va_arg(args, char *);
            puts(s);
            p += 2;
        } else if (*p == '%' && *(p + 1) == 'd') {
            int num = va_arg(args, int);
            char buf[16];
            itoa(num, buf);
            puts(buf);
            p += 2;
        } else {
            write(1, p, 1);
            p++;
        }
    }

    va_end(args);
    return 0;
}

int main() {
    microprintf("char: %c, str: %s, num: %d\n", 'X', "test", 1234);
    puts("done\n");
    return 0;
}