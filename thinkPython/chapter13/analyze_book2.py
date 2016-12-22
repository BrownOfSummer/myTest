"""Python provides a data structure called set that provides many common set 
operations. Write a program the uses set subtration to find words in the book
that are not in the word list

return set(d1) - set(d2)
"""

import string
import random

from analyze_book import *

def subtract(d1, d2):
    """Returns a set of all keys the appear in d1 but not in d2.
    d1, d2: dictionaries"""
    return set(d1) - set(d2)

if __name__ == '__main__':
    hist = process_file('emma.txt', skip_header=True)
    print 'Total number of words: ', total_words(hist)
    print 'Number of different words: ', different_words(hist)
    t = most_common(hist)
    print_most_common(hist, 10)

    words = process_file('../words.txt', skip_header=False)

    diff = subtract(hist, words)
    print "The words in the book that aren't in word list are:"
    for word in diff:
        print word,

    print "\n\nHere are some random words from the book"
    for i in range(30):
        print random_word(hist),
