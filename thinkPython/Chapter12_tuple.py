t1 = ('a', 'b', 'c', 'd')
t = tuple('lupins')
print t[0]

##list and tuple
s = 'abc'
t = [0, 1, 2]
zip(s, t)

zip('Anne', 'Elk')

t = [('a', 0), ('b',1), ('c', 2)]
for letter, number in t:
    print number, letter

def has_match(t1, t2):
    for x, y in zip(t1, t2):
        if x == y:
            return True
        return False

for index, element in enumerate('abc'):
    print index, element



###########dict and tuples
#each tuple is a key-value pair
d = {'a':0, 'b':1, 'c':2}
t = d.items()
print t

t = [ ('a', 0), ('c', 2), ('b', 1) ]
d = dict(t)
print d

directory = dict()
last = 'green'
first = 'jim'
directory[last,first] = 1234
for last, first in directory:
    print first, last, directory[last, first]

def sort_by_length(words):
    t = []
    for word in words:
        t.append( (len(word), word) )

        t.sort(reverse=True)
        res = []
        for length, word in t:
            res.append(word)
        return res















