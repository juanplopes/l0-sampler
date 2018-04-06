import math

def f(q):
    m = 64
    return reduce(lambda a,b: a*b, (1 - q*2**i * math.exp(-q*2**i) for i in range(-m, m+1)))

V = [(f(1+x/1e5), 1+x/1e5) for x in range(int(1e5+1))]
answer1 = (min(V)[0]+max(V)[0])/2


    
answer2 = filter(lambda (y, x): (abs(y-answer1) < 5e-11), V)[0][1]
answer2 = math.pi * 2 * math.log(answer2, 2)



answer3 = (V[0][0]-answer1)/math.sin(2*math.pi*math.log(1, 2)-answer2)

print '%.12f' % answer1
print '%.12f' % answer3
print '%.12f' % answer2

