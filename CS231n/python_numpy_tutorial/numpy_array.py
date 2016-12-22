import numpy as np
"""We can initialize numpy arrays from nested Python lists, 
and access elements using square brackets:"""
a = np.array( [1, 2, 3] ) # create a rank 1 array
print type(a)
print a.shape               # prints "(3,)"
print a[0], a[1], a[2]
a[0] = 5                    # change the element of the array
print a

b = np.array( [ [1,2,3], [4,5,6] ] )
print b.shape
print b[0, 0], b[0, 1], b[1, 0]

"""Numpy also provides many functions to create arrays:"""
a = np.zeros( (2, 2) )
print a
b = np.ones( (1, 2) )
print b
c = np.full( (2,2), 7 )
print c
d = np.eye(2)
print d
e = np.random.random( (2,2) )
print 2
