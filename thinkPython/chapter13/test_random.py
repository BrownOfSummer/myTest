import random
for i in range(10):
    x = random.random()
    print x

print "random integer between >=5 and <= 10:",random.randint(5,10)
print "random integer between >=5 and <= 10:",random.randint(5,10)

t = [1, 2, 3, 4]
print "random element in list:",random.choice(t)

def histogram(t):
    res = dict()
    for i in t:
        if i not in res:
            res[i] = 1
        else:
            res[i] += 1
    return res

def choose_from_hist(d):
    res = list()
    for key in d:
        value = d[key]
        for i in range(value):
            res.append(key)
    return res
t = ['a', 'a', 'b']
hist = histogram(t)
print hist
res = choose_from_hist(hist)
print res
print "choice with probability:",random.choice(res)

