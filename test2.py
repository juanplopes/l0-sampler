import math

def f(q):
    m = 5
    return reduce(lambda a,b: a*b, (1 - q*2**i * math.exp(-q*2**i) for i in range(-m, m+1)))
    
x = 1
while x < 2:
    print x, '\t', f(x)
    x += 0.01
