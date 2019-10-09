#include <iostream>
#include <stack>
#include <typeinfo>
#include <map>
#include "scanner.hpp"

using namespace std;

token tok;

enum generator
{
    exp,
    exp_,
    term,
    term_,
    fact,
    err
};

struct Symbol
{
    token terminal;
    generator generator;
    bool isTerminal;
    bool isGenerator;
};

typedef stack<Symbol> production;

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

bool matchtoken(token k) {
    if (k == tok) {
        tok = next();
        return true;
    }
    return false;
}

extern bool ll1(const char *fname)
{

    open(fname);

    // generator table[5][7] = {
    //             /* (     -    num   +       )      *      $ */
    // /* exp   */ { exp,  exp,  exp,  err,   err,   err,   err},
    // /* exp'  */ { err,  err,  err,  exp_,  exp_,  err,   exp_},
    // /* term  */ { term, term, term, err,   err,   err,   err},
    // /* term' */ { err,  err,  err,  term_, term_, term_, term_},
    // /* fact  */ { fact, fact, fact, err,   err,   err,   err}
    // };

    production p1;
    p1.push((Symbol){ .generator = term, .isGenerator = true });
    p1.push((Symbol){ .generator = exp, .isGenerator = true });

    production p2;
    p2.push((Symbol){ .terminal = _sum, .isTerminal = true });
    p2.push((Symbol){ .generator = term, .isGenerator = true });
    p2.push((Symbol){ .generator = exp, .isGenerator = true });

    production p3;

    production p4;
    p4.push((Symbol){ .generator = fact, .isGenerator = true });
    p4.push((Symbol){ .generator = term_, .isGenerator = true });

    production p5;
    p5.push((Symbol){ .terminal = _mult, .isTerminal = true });
    p5.push((Symbol){ .generator = fact, .isGenerator = true });
    p5.push((Symbol){ .generator = term_, .isGenerator = true });

    production p6;

    production p7;
    p7.push((Symbol){ .terminal = _lpar, .isTerminal = true });
    p7.push((Symbol){ .generator = exp, .isGenerator = true });
    p7.push((Symbol){ .terminal = _rpar, .isTerminal = true });

    production p8;
    p8.push((Symbol){ .terminal = _min, .isTerminal = true });
    p8.push((Symbol){ .generator = fact, .isGenerator = true });

    production p9;
    p9.push((Symbol){ .terminal = _num, .isTerminal = true });

    /* Error Production */
    production pE;
    pE.push((Symbol){ .terminal = _err, .isTerminal = true });

    production table[5][7] = {
                /* (  -   num  +   )   *  $ */
    /* exp   */ { p1, p1, p1, pE, pE, pE, pE },
    /* exp'  */ { pE, pE, pE, p2, p3, pE, p3 },
    /* term  */ { p4, p4, p4, pE, pE, pE, pE },
    /* term' */ { pE, pE, pE, p6, p6, p5, p6 },
    /* fact  */ { p7, p8, p9, pE, pE, pE, pE }
    };

    tok = next();
    stack<Symbol> s;
    Symbol initSymbol;
    initSymbol.generator = exp;
    initSymbol.isGenerator = true;

    s.push(initSymbol);

    Symbol x = s.top();
    if (x.isTerminal) {
        if (matchtoken(x.terminal));
        else return false;
    } else {
        production pi = table[x.generator][tok];
        Symbol sim = pi.top();
        if (sim.isTerminal && sim.terminal == _err) return false;
        else {
            production piInverted;
            while (!pi.empty())
            {
                piInverted.push(p1.top());
                pi.pop();
            }            
        }
    }
    // production pi = table[x][t];

    // pgenerator(pi);

    // if (x == err) {
    //     close();
    //     return false;
    // }    

    close();

    return tok != _eof;
}
