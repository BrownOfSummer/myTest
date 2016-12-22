"""Write a program that uses this algorithm to choose an random book word from the book"""
"""
Modify the algorithm of analyze_book.py to accelarate:
(1) Use keys to get a list of words in the book.
(2) Build a list that contains the cumulatives sum of word frequency.
    The last item in this list is the total number of words in the bool, n.
(3) Choose a random number from 1 to n. Use a bisection to find the index
    where the random number would be inserted in the cumulative sum.
(4) Use the index to find the correspoding word in the word list.
"""

import string
import random
from analyze_book import *
from bisect import bisect

def random_word(hist):
    """Choose a random word from a histogram.
    The probability of each word is proportional to its frequency.
    This couble be made faster by computing the cumulative frequencies
    once and reusing them"""
    words = []
    freqs = []
    total_freq = 0

    # make a list of words and a list of cumulative frequencies
    for word, freq in hist.items():
        total_freq += freq
        words.append(word)
        freqs.append(total_freq)

    # choose a random value and find its location in the cumulative list
    x = random.randint(0, total_freq-1) # 0 <= x <= total_freq-1
    index = bisect(freqs, x)
    return words[index]

if __name__=='__main__':
    hist = process_file('emma.txt', skip_header=True)
    for i in range(30):
        print random_word(hist),
