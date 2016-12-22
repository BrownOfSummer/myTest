##10.3 traversing a list
a = [1, 2, 3]
b = [4, 5, 6]
for element in a:
    pass
for i in range(len(a)):
    pass

##10.4 list operations
c = a + b #[1, 2, 3, 4, 5, 6]
c = a * 2 #[1, 2, 3, 1, 2, 3]

##10.5 list slices
t = ['a', 'b', 'c', 'd', 'e', 'f']
t[1:3] #['b', 'c']
t[:4] #['a','b','c','d']
t[3:] #['d', e,f]
t[:] #all
t[1:3] = ['x', 'y']

#list methods
#append element
#extent list
#sort ascend
t.append('1')
t.extend((['1','2']))
t.sort()
t.pop(1) #delet element for list, index is 1
t.pop() #without index, pop the last one
# del the element if you know the index
#del t[1]

#remove th element if you know the value, while do not know the index
#t.remove(value)
#the return value of remove function is none
Sum = sum([1,2,3])

# List and strings
s = 'Spam is handsome !'
t = list(s)
print s 
t = s.split()
s = 'spam-spam1-spam2'
delimiter = '_'
s.split(delimiter)

#join is the inverse of split, need to figure the delimiter
t = ['hello', 'world', '!']
delimiter = ' '
delimiter.join(t)


def bad_del_head(t):
    t = t[1:] #cannot delete the head of the t list
def good_del_head(t):
    return t[1:] #return a new list, the list t doesnot modified
test = ['a','b','c','d']
result = good_del_head(test)
print result
print test
