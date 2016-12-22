import math
def square_root( a ):
    """Calc square root of a using NewTon methods"""
    epsilon = 0.00001
    x = 3.0
    while True:
        y = ( x + a / x ) / 2
        if abs(y - x) < epsilon:
            break;
        else:
            x = y
    #print y
    return y

#square_root(5)

data = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0]
for x in data:
    print x,
    print square_root( x ),
    print math.sqrt( x ),
    print square_root( x ) - math.sqrt( x )

#### calc the 1/pi using loop
k = 0
constant = 2.0 * math.sqrt(2) / 9801
Sum = 0.0
while True:
    Num = math.factorial(4*k) * (1103 + 26390 * k)
    Den = math.factorial(k)**4 * 396**(4*k)
    tmp = 1.0 * Num / Den
    if tmp < 1e-15:
        break
    Sum += tmp
    k += 1
print 1.0 / (constant * Sum)

