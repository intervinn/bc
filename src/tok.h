#ifndef _BC_TOK_H
#define _BC_TOK_H

#include <stddef.h>
#include <stdio.h>

enum kind {
    bad,
    ident,

    string,
    number,

    add,
    sub,
    diw,
    mod,
    rem,

    
    add_assign,
    sub_assign,
    div_assign,
    mod_assign,
    rem_assign,

    eql, // ==
    gtr, // >
    lss, // <
    neq, // !=
    not, // !
    assign, // =

    geq, // >=
    leq, // <=

    lbr, // {}
    rbr, 
    lsq, // []
    rsq,

    lpr, // ()
    rpr,

    nline
};

struct token {
    size_t pos;
    size_t end;

    enum kind kind;
};

struct token* tparse(char* src);

#endif