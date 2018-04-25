import math

def f(m, r):
    return reduce(lambda a,b: a*b, (1 - float(r)/2**i * (1-1.0/2**i)**(r-1) for i in range(1, m+1)))
    
def g(m, r):
    return reduce(lambda a,b: a*b, (1 - float(r)/2**i * math.exp(-float(r)/2**i) for i in range(1, m+1)))
    
for r in range(0, 2**16, 2**16/128):
    print r, '\t', f(1000, r), '\t', g(1000, r)
