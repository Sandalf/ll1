#include <iostream>
#include <stack>
#include <typeinfo>
#include "scanner.hpp"

using namespace std;

enum generator
{
    exp,
    exp_,
    term,
    term_,
    fact,
    err
};

struct Production
{
    token terminal;
    generator generator;
};

void pgenerator(generator g)
{
    printf("generator: ");
    switch (g)
    {
    case exp:
        printf("exp\n");
        break;
    case exp_:
        printf("exp_\n");
        break;
    case term:
        printf("term\n");
        break;
    case term_:
        printf("term_\n");
        break;
    case fact:
        printf("fact\n");
        break;
    case err:
        printf("err\n");
        break;
    default:
        break;
    }
}

extern bool ll1(const char *fname)
{

    open(fname);

    generator table[5][7] = {
                /* (     -    num   +       )      *      $ */
    /* exp   */ { exp,  exp,  exp,  err,   err,   err,   err},
    /* exp'  */ { err,  err,  err,  exp_,  exp_,  err,   exp_},
    /* term  */ { term, term, term, err,   err,   err,   err},
    /* term' */ { err,  err,  err,  term_, term_, term_, term_},
    /* fact  */ { fact, fact, fact, err,   err,   err,   err}
    };

    token t = next();
    stack<generator> s;
    generator initSymbol;

    s.push(exp);

    generator x = s.top();
    generator pi = table[x][t];

    pgenerator(pi);

    if (x == err) {
        close();
        return false;
    }

    close();

    return t != _eof;
}
