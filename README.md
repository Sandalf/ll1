# C++ Parser

## Original Grammar

```
exp -> exp + term | term
term -> term * fact | fact
fact -> (exp) | -fact | num
```

## Final Grammar
Left-recursion was removed.

```
exp -> term exp'
exp' -> + term exp' | λ
term -> fact term'
term' -> * fact term | λ
fact -> (exp) | -fact | num
```

## Predictive Sets

|        π           |   Prediction(π)    |
|--------------------|--------------------|
|exp -> term exp'    |{ (, -, num }       |
|exp' -> + term exp' |{ + }               |
|exp' -> λ           |{ $, ) }            |
|term -> fact term'  |{ (, - , num }      |
|term' -> * fact term|{ * }               |
|term' -> λ          |{ +, $, ) }         |
|fact -> (exp)       |{ ( }               |
|fact -> -fact       |{ - }               |
|fact -> num         |{ num }             |
