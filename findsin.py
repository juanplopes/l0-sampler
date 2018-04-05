import math

def f(q):
    m = 32
    return reduce(lambda a,b: a*b, (1 - q*2**i * math.exp(-q*2**i) for i in range(-m, m+1)))

V = [(f(1+x/1e5), 1+x/1e5) for x in range(int(1e5+1))]
answer1 = (min(V)[0]+max(V)[0])/2

print min(V), max(V), answer1
    
answer2 = filter(lambda (y, x): (abs(y-answer1) < 5e-11), V)[0][1]

print answer2, math.pi * 2 * math.log(answer2, 2)

answer3 = 
