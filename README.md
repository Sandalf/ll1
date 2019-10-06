# C++ Parser

## Original Grammar

```
exp -> exp + term | term
term -> term * fact | fact
fact -> (exp) | -fact | num
```

## Final Grammar
In this version of the grammar, left-recursion was removed.

```
exp -> term exp'
exp' -> + term exp' | λ
term -> fact term'
term' -> * fact term | λ
fact -> (exp) | -fact | num
```
