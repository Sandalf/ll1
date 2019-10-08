#ifndef scanner_hpp
#define scanner_hpp

typedef enum { _lpar, _min, _num, _sum, _rpar, _mult, _eof,  _id, _nat, _real, _err } token;

extern void open(const char *fname);
extern void close();
extern token next();

#endif