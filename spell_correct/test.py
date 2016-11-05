
a = [1, 2]
b = []
c = ['a', 'b']

d = a or b or c
e = b or a or c

print d
print e
if -1:
    print c

res = max('ah', 'bf', key=lambda x: x[0])
print res

def comparator(x):
    return x[2]
print( max('ah2', 'bf1', key=comparator) )

text1 = 'abcdefg'
text2 = 'efghijkl'
res = (w for w in text1 if w in text2)
print set(res)
print res

res2 = [w for w in text1 if w in text2]
res3 = set( w for w in text1 if w in text2 )

splits = [(text1[:i], text1[i:]) for i in range(len(text1) + 1)]
print splits

