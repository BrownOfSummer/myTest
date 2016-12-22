eng2sp = dict()
print eng2sp
eng2sp['one'] = 'uno'
print eng2sp

print 'one' in eng2sp
print 'uno' in eng2sp

vals = eng2sp.values()
print vals

def histogram(s):
    d = dict()
    for c in s:
        if c not in d:
            d[c] = 1
        else:
            d[c] += 1
    return d
## if c in dict, get returns the corresponding value, else returns 0
def histogram_with_get(s):
    d = dict()
    for c in s:
        d[c] = 1 + d.get(c, 0)

## print the each key and corresponding value
def print_hist(h):
    for c in h:
        print c, h[c]

## use the value to seach the key
def reverse_lookup(d, v):
    l = list()
    for k in d:
        if d[k] == v:
            l.append(k)
    return l
    #raise ValueError

## to show how to use list as the value of the dictionary
def invert_dict(d):
    inverse = dict()
    for key in d:
        val = d[key]
        if val not in inverse:
            inverse[val] = [key]
        else:
            inverse[val].append(key)
    return inverse

### fibonacci with dict
known = {0:0, 1:1}
def fibonacci(n):
    if n in known:
        return known[n]
    res = fibonacci(n-1) + fibonacci(n-2)
    known[n] = res
    return res
h = histogram('brontosaurus')
print h

