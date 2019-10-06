#include <cstdio>
#include "parser.hpp"

bool exp(), exp_(), term(), term_(), fact();

token t;

void printtoken(token t) {
    switch (t)
    {
        case _num: printf("_num\n"); break;
        case _lpar: printf("_lpar\n"); break;
        case _rpar: printf("_rpar\n"); break;
        case _sum: printf("_sum\n"); break;
        case _mult: printf("_mult\n"); break;
        case _min: printf("_min\n"); break;
        case _eof: printf("_eof\n"); break;
        case _err: printf("_err\n"); break;
        default: break;
    }
}

bool match(token k) {
    printtoken(k);
    if (k == t) {
        t = next();
        return true;
    }
    return false;
}

bool fact() {
    // printf("fact\n");
    // printtoken(t);
    if (t == _lpar) return match(_lpar) and exp() and match(_rpar);
    if (t == _min) return match(_min) and fact();
    if (t == _num) return match(_num);
    return false;
}

bool term_() {
    // printf("term_\n");
    // printtoken(t);
    if (t == _mult) return match(_mult) and fact() and term_();
    if (t == _sum || t == _eof || t == _rpar) return true;
    return false;
}

bool term() {
    // printf("term\n");
    // printtoken(t);
    if (t == _lpar || t == _min || t == _num) return fact() && term_();
    return false;
}

bool exp_() {
    // printf("exp_\n");
    // printtoken(t);
    if (t == _sum) return match(_sum) and term() and exp_();
    if (t == _eof || t == _rpar) return true;
    return false;
}

bool exp() {
    // printf("exp\n");
    // printtoken(t);
    if (t == _lpar || t == _min || t == _num) return term() && exp_();
    return false;
}

extern bool parse(const char *fname) {
    open(fname);

    t = next();
    // printf("t: %d\n", t);    

    bool r = exp() and t == _eof;
    printtoken(t);

    close();

    return r;
}
