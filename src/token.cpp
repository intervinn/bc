#include <cctype>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "token.hpp"
#include "fmt/format.h"

namespace std {
    std::string to_string(bc::TokenKind kind) {
        switch (kind) {
            case bc::BAD:
                return "<bad>";
            case bc::IDENT:
                return "<ident>";
            case bc::STRING:
                return "<string>";
            case bc::INT:
                return "<int>";
            case bc::ADD:
                return "<add>";
            case bc::SUB:
                return "<sub>";
            case bc::DIV:
                return "<div>";
            case bc::MUL:
                return "<mul>";
            case bc::REM:
                return "<rem>";
            case bc::ADD_ASSIGN:
                return "<add_assign>";
            case bc::SUB_ASSIGN:
                return "<sub_assign>";
            case bc::DIV_ASSIGN:
                return "<div_assign>";
            case bc::MUL_ASSIGN:
                return "<mul_assign>";
            case bc::REM_ASSIGN:
                return "<rem_assign>";
            case bc::EQL:
                return "<eql>";
            case bc::GTR:
                return "<gtr>";
            case bc::LSS:
                return "<lss>";
            case bc::NEQ:
                return "<neq>";
            case bc::NOT:
                return "<not>";
            case bc::ASSIGN:
                return "<assign>";
            case bc::GEQ:
                return "<geq>";
            case bc::LEQ:
                return "<leq>";
            case bc::LBR:
                return "<lbr>";
            case bc::RBR:
                return "<rbr>";
            case bc::LSQ:
                return "<lsq>";
            case bc::RSQ:
                return "<rsq>";
            case bc::LPR:
                return "<lpr>";
            case bc::RPR:
                return "<rpr>";
            case bc::NLINE:
                return "<nline>";
            case bc::END:
                return "<end>";
            case bc::IF:
                return "<if>";
            case bc::ELSE:
                return "<else>";
            case bc::PROC:
                return "<proc>";
            case bc::FOR:
                return "<for>";
            case bc::PROTO:
                return "<proto>";
            case bc::SET:
                return "<set>";
        }
        return "<unknown>";
    }
}

namespace bc {
    Token::Token() noexcept {}

    Token::Token(std::size_t pos, std::size_t end, TokenKind kind)
    : pos(pos), end(end), kind(kind) {}

    class Source {
        private:
            std::string& _str;
            std::size_t cursor;

        public:
            Source(std::string& str) : _str(str) {
                cursor = 0;
            }

            Source(std::string& str, std::size_t cursor) 
            : _str(str), cursor(cursor) {}

            std::size_t at() {
                return cursor;
            }

            std::size_t at(std::size_t index) {
                return _str.at(index);
            }

            std::size_t inc() {
                return ++cursor;
            }

            std::size_t add(std::size_t c) {
                //std::cout << "prev: " << cursor << "| new: " << cursor+c << std::endl;
                cursor += c;
                return c;
            }

            std::size_t set(size_t val) {
                cursor = val;
                return val; 
            }

            char current() {
                return at(cursor);
            }

            char next() {
                return at(cursor+1);
            }

            std::string sub(size_t pos, size_t end) {
                return _str.substr(pos, end-pos);
            }

            std::string& str() {
                return _str;
            }

            bool eof() {
                return cursor > _str.size()-1;
            }
    };

    // looks horrible, there must be a better alternative
    void parse_ops(std::vector<Token>& tok, Source& src) {
        if (src.eof()) return;
        auto pos = src.at();
        
        auto two = src.sub(pos, pos+1);

        if (two == ">=") { tok.emplace_back(pos, pos+1, GEQ); src.add(2); return; }
        if (two == "<=") { tok.emplace_back(pos, pos+1, LEQ); src.add(2); return; }

        if (two == "+=") { tok.emplace_back(pos, pos+1, ADD_ASSIGN); src.add(2); return; }
        if (two == "-=") { tok.emplace_back(pos, pos+1, SUB_ASSIGN); src.add(2); return; }
        if (two == "/=") { tok.emplace_back(pos, pos+1, DIV_ASSIGN); src.add(2); return; }
        if (two == "*=") { tok.emplace_back(pos, pos+1, MUL_ASSIGN); src.add(2); return; }

        switch (src.current()) {
            case '+':
                tok.emplace_back(pos, pos, ADD);
                src.add(1);
                break;
            case '-':
                tok.emplace_back(pos, pos, SUB);
                src.add(1);
                break;
            case '/':
                tok.emplace_back(pos, pos, DIV);
                src.add(1);
                break;
            case '*':
                tok.emplace_back(pos, pos, MUL);
                src.add(1);
                break;
            case '%':
                tok.emplace_back(pos, pos, REM);
                src.add(1);
                break;
            case '=':
                tok.emplace_back(pos, pos, ASSIGN);
                src.add(1);
                break;
            case '>':
                tok.emplace_back(pos, pos, GTR);
                src.add(1);
                break;
            case '<':
                tok.emplace_back(pos, pos, LSS);
                src.add(1);
                break;;
            case '!':
                tok.emplace_back(pos, pos, NOT);
                src.add(1);
                break;
            case '(':
                tok.emplace_back(pos, pos, LPR);
                src.add(1);
                break;
            case ')':
                tok.emplace_back(pos, pos, RPR);
                src.add(1);
                break;
            case '[':
                tok.emplace_back(pos, pos, LSQ);
                src.add(1);
                break;
            case ']':
                tok.emplace_back(pos, pos, RSQ);
                src.add(1);
                break;
            case '{':
                tok.emplace_back(pos, pos, LBR);
                src.add(1);
                break;
            case '}':
                tok.emplace_back(pos, pos, RBR);
                src.add(1);
                break;
            case '\n':
                tok.emplace_back(pos, pos, NLINE);
                src.add(1);
                break;
        }
    }

    void parse_str(std::vector<Token>& tok, Source& src) {
        if (src.eof()) return;
        if (src.current() != '"') return;
        auto pos = src.at();
        auto end = src.str().find_first_of("\"", pos+1);

        if (end == std::string::npos) {
            throw std::out_of_range(fmt::format("{}:{} - failed to capture string", pos, end));
        }

        tok.emplace_back(pos, end, STRING);
        src.set(end+1);
    }

    void parse_num(std::vector<Token>& tok, Source& src) {
        if (src.eof()) return;
        if (!std::isdigit(src.current())) return;

        auto pos = src.at();
        auto end = src.str().find_first_not_of("1234567890", pos+1);

        if (end == std::string::npos) {
            throw std::out_of_range(fmt::format("{}:{} - failed to capture int", pos, end));
        }

        tok.emplace_back(pos, end-1, INT);
        src.set(end);
    }

    std::vector<Token> parse(std::string src) {
        std::vector<Token> tokens = {};
        Source source = Source(src);

        while (true) {
            parse_ops(tokens, source);
            parse_str(tokens, source);
            parse_num(tokens, source);

            if (source.eof()) break;
        }
        
        return tokens;
    }
}