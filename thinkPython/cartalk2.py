"""Exercise 9.8 of thinkpython"""
def has_palindrome(i, start, length):
    """ Returns true if the integer i, when written as a string,
    contains a palindrome with length(len), starting at index(start)"""
    s = str(i)[start:start+lenght]
    return s[::-1] == s

def check(i):
    """checks whether the integer(i) has the properties described in the puzzler"""
    return( has_palindrome(i, 2, 4) and
            has_palindrome(i+1, 1, 5) and
            has_palindrome(i+2, 1, 4) and
            has_palindrome(i+3, 0, 6))

def check_all():
    """Enumerates the six-digit numbers and prints any that satisfy the requirements of the puzzler"""
    i = 100000
    while i <= 999996:
        if check(i):
            print i
        i = i + 1

print 'the following are the possible odometer readings:'
check_all()
