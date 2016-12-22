import numpy as np

x = np.array([ [1, 2], [3, 4] ], dtype=np.float64)
y = np.array([ [5, 6], [7, 8] ], dtype=np.float64)
print x + y
print np.add(x, y)

print x - y
print np.subtract(x, y)

print x * y
print np.multiply(x, y)

print x / y
print np.divide(x, y)

print np.sqrt(x)

v = np.array([9, 10])
w = np.array([11, 12])

#Inner product of vectors; both produce 219
print v.dot(w)
print np.dot(v, w)

# Matrix/vector product; both produce the rank 1 array [29 67]
print 'x.dot(v) = ', x.dot(v)
print 'np.dot(x, v) = ', np.dot(x, v)

# Matrix/matrix product; both produce the rank 2 array
print 'x.dot(y) = ', x.dot(y)
print 'np.dot(x, y) = ', np.dot(x, y)

"""Useful functions for performing computattions on arrays"""
print 'np.sum(x) = ',np.sum(x) #compute sum of all elements; 10
print 'np.sum(x, axis=0) = ', np.sum(x, axis=0) # sum of each column
print 'np.sum(x, axis=1) = ', np.sum(x, axis=1) # sum of each row

"""reshape or manipulate data, such as T"""
print "x = "
print x
print "x.T ="
print x.T
v = np.array([1, 2, 3])
print "v = ", v
print "v.T = ", v.T

