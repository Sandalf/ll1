#ifndef scanner_hpp
#define scanner_hpp

typedef enum { _id, _nat, _real, _num, _lpar, _rpar, _sum, _mult, _min, _eof, _err } token;

extern void open(const char *fname);
extern void close();
extern token next();

#endif