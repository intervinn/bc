#ifndef _BC_TOK_H
#define _BC_TOK_H

#include <cstddef>
#include <string>
#include <vector>

namespace bc {

    enum TokenKind {
        BAD,
        IDENT,

        STRING,
        INT,

        ADD,
        SUB,
        DIV,
        MUL,
        REM,

        ADD_ASSIGN,
        SUB_ASSIGN,
        DIV_ASSIGN,
        MUL_ASSIGN,
        REM_ASSIGN,

        EQL,
        GTR,
        LSS,
        NEQ,
        NOT,
        ASSIGN,

        GEQ,
        LEQ,

        LBR,
        RBR,
        LSQ,
        RSQ,
        LPR,
        RPR,

        NLINE,

        IF,
        ELSE,
        FOR,
        PROC,
        END,
        PROTO,
        SET
    };

    class Token {
        public:
            Token() noexcept;
            Token(std::size_t pos, std::size_t end, TokenKind kind);
        
            std::size_t pos;
            std::size_t end;
            TokenKind kind;
    };

    std::vector<Token> parse(std::string src);
}

namespace std {
    std::string to_string(bc::TokenKind kind);
}

#endif