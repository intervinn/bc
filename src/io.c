#include "io.h"
#include <stdio.h>
#include <stdlib.h>

size_t rline(char* buf, FILE* fp) {
    size_t size = 0;
    size_t pos = 0;

    int c;

    while (1) {
        c = fgetc(fp);

        if (c == EOF || c == '\n') {
            break;
        }

        if (pos+1 >= size) {
            size = size+1;
            buf = realloc(buf, size);
            if (buf == NULL) {
                return -1;
            }
        }
        buf[pos++] = c;
    }
    
    buf = realloc(buf, pos+1);
    buf[pos] = '\0';

    return size;
}

