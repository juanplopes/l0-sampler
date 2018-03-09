from fractions import Fraction

import operator as op
def ncr(n, r):
    r = min(r, n-r)
    if r == 0: return 1
    numer = reduce(op.mul, xrange(n, n-r, -1))
    denom = reduce(op.mul, xrange(1, r+1))
    return numer//denom

def probsingle(n, m, i):
    f = Fraction(1, 1)
    for j in range(i):
        f = f * Fraction(m-j, m)
    for j in range(i, n):
        f = f * Fraction(m-i, m)
    return f

def probi(n, m, d, i):
    f = Fraction(0, 1)
    for j in range(1, i+1):
        f += (-1)**(j+1) * ncr(i, j) * probsingle(n, m, j)
    return (1 - f) ** d

def prob(n, m, d):
    f = Fraction(0, 1)
    for j in range(1, n+1):
        f += (-1)**(j+1) * ncr(n, j) * probi(n, m, d, j)
    return f
        
print float(prob(100, 140, 8))

#\begin{align*}
#\sum_{i=1}^n (-1)^{j+1} {n \choose i} \left(1 - \sum_{j=1}^i (-1)^{j+1} {i \choose j} \frac{m}{m} \times \frac{m-1}{m} \times  \ldots \times \frac{m-j+1}{m} \times \left(\frac{m-j}{m}\right)^{n-j} \right)^d
#\end{align*}
