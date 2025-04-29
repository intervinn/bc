#include "tok.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

size_t findfirstof(char* src, char* goal, size_t bgn, size_t end) {
    for (size_t i = bgn; i <= end; i++) {
        uint8_t j = 0;
        while (goal[j] != '\0') {
            if (goal[j] == src[j]) return i;
            j++;
        }
    }
    return -1;
}

size_t append(struct token* src, size_t len, struct token item) {
    src = realloc(src, sizeof(item)*len+1);
    src[len] = item;
    return len+1;
}

struct token* tparse(char* src) {  
    struct token* tok = malloc(0);
    const size_t srclen = strlen(src);
    size_t len = 0;

    size_t csr = 0;
    int c;

    while (1) {
        c = src[csr];
        if (c == EOF || c == '\0') {
            break;
        }

        switch (c) {
            case '[':
            len = append(tok, len, (struct token){
                .end = csr,
                .pos = csr,
                .kind = lsq
            });
            break;
            case ']':
            len = append(tok, len, (struct token){
                .end = csr,
                .pos = csr,
                .kind = rsq
            });
            break;
            case '{':
            len = append(tok, len, (struct token){
                .end = csr,
                .pos = csr,
                .kind = lbr
            });
            break;
            case '}':
            len = append(tok, len, (struct token){
                .end = csr,
                .pos = csr,
                .kind = rbr
            });
            break;
            case '(':
            len = append(tok, len, (struct token){
                .end = csr,
                .pos = csr,
                .kind = lpr
            });
            break;
            case ')':
            len = append(tok, len, (struct token){
                .end = csr,
                .pos = csr,
                .kind = rpr
            });
            break;
        }

        if (c == '"') {
            size_t pos = csr;
            size_t end = findfirstof(src, "\"", pos+1, srclen);

            len = append(tok, len, (struct token){
                .pos = pos,
                .end = end,
                .kind = string
            });
        }
    }

    return tok;
}