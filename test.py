from fractions import Fraction

import operator as op
def ncr(n, r):
    r = min(r, n-r)
    if r == 0: return 1
    numer = reduce(op.mul, xrange(n, n-r, -1))
    denom = reduce(op.mul, xrange(1, r+1))
    return numer//denom

def probsingle(n, m, d, i):
    f = Fraction(1, 1)
    for j in range(i):
        f = f * Fraction(m-j, m)
    for j in range(i, n):
        f = f * Fraction(m-i, m)
    return (1 - f) ** d

def prob2(n, m, d):
    f = Fraction
    print float((1-f(1, m))**(n-1)), float(f(m-1, m)*(1 - f(2, m))**(n-2))
    return ((2*(1-f(1, m))**(n-1) - f(m-1, m)*(1 - f(2, m))**(n-2)))

def prob(n, m, d):
    total = Fraction(0, 1)
    for i in range(1, n+1):
        print i, float(total)
        total += (-1)**(i) * ncr(n, i) * probsingle(n, m, d, i)
    return total
        
print float(prob2(10, 20, 1)), float(probsingle(10, 20, 1, 2))
