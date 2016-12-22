import numpy as np

a = np.array( [ [1,2,3,4], [5,6,7,8], [9,10,11,12] ] )
b = a[:2, 1:3]
print a
print b

"""(1) Slicing:"""
"""A slice of an array is a view into the same data,
so modify it will modify the original array."""
print a[0, 1]
b[0, 0] = 77
print a[0, 1]

# Two ways of accessing the data in the middle row of the array.
# Mixing integer indexing with slices yields an array of lower rank,
# while using only slices yields an array of the same rank as the
# original array: a
row_r1 = a[1, :] # Rank 1 view of the second row of a
row_r2 = a[1:2, :] # Rank 2 view of the second row of a
print row_r1, row_r1.shape
print row_r2, row_r2.shape

# We can make the same distinction when accessing columns of an array:
col_r1 = a[:, 1]
col_r2 = a[:, 1:2]
print col_r1, col_r1.shape
print col_r2, col_r2.shape

"""(2) Integer array indexing: """
"""In contrast, integer array indexing allows you to construct arbitrary arrays using the data from another array."""
a = np.array([[1,2], [3, 4], [5, 6]])
# An example of integer array indexing.
# The returned array will have shape (3,) and 
print a[ [0, 1, 2], [0, 1, 0] ] #[1 4 5]
# The above example of integer array indexing is equivalent to this:
print np.array([a[0, 0], a[1, 1], a[2, 0]])  # Prints "[1 4 5]"

# When using integer array indexing, you can reuse the same
# element from the source array:
print a[[0, 0], [1, 1]]  # Prints "[2 2]"
# Equivalent to the previous integer array indexing example
print np.array([a[0, 1], a[0, 1]])  # Prints "[2 2]"
"""One useful trick with integer array indexing is selecting or mutating one element from each row of a matrix:"""
a = np.array([[1,2,3], [4,5,6], [7,8,9], [10, 11, 12]])
# Create an array of indices
b = np.array([0, 2, 0, 1])
# Select one element from each row of a using the indices in b
print a[np.arange(4), b]  # Prints "[ 1  6  7 11 ]"

"""(3) Boolean array indexing:"""
"""Boolean array indexing lets you pick out arbitrary elements of an array. 
Frequently this type of indexing is used to select the elements of an array that satisfy some condition. """
a = np.array([[1,2], [3, 4], [5, 6]])
bool_index = ( a > 2 )
print bool_index
print a[bool_index]
# We can do all of the above in a single concise statement:
print a[a > 2]     # Prints "[3 4 5 6]"


"""Datatypes"""
x = np.array([1, 2])
print x.dtype
x = np.array([1.0, 2])
print x.dtype
x = np.array([1.6, 2], dtype=np.int64)
print x.dtype
print x
