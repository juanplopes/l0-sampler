import math

def exp(x):
    try:
        return math.exp(x)
    except:
        return float('inf')

def f(q, m):
    return reduce(lambda a,b: a+b, (math.log(1 - 2**(i+q) * math.exp(-2**(i+q))) for i in range(-m, m+1)))
   
def flog(q, m):
    return reduce(lambda a,b: a+b, ((2**(2*(q+i)) - 2**(q+i))/(exp(2**(q+i)) - 2**(q+i)) for i in range(-m, m+1)))

x = 0
while x < 4:
    print x, '\t', f(x, 30), '\t', flog(x, 30)
    x += 0.01
