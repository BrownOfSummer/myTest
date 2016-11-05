"""Write my spell correcting code"""
import re
from collections import Counter

"""Transform text to word list. lower, - ' is treated ad space'"""
def words(text): return re.findall(r'\w+', text.lower())

"""Return a Counter dict, word as key, count is value"""
WORDS = Counter(words( open('big.txt').read() ))
#W = words( open('tmp.txt').read() )
#print WORDS

def P(word, N=sum(WORDS.values())):
    """Probability of `word` ."""
    return 1.0 * WORDS[word] / N

def correction(word):
    """Most probable spelling correction for word.
    word: the user input string
    return: the most like corrected word"""
    return max(candidates(word), key=P) #return word that the P of it is max

def candidates(word):
    """Generate possible spelling corrections for word.
    word: the user input string
    return: a list of words"""
    return ( known([word]) or known(edits1(word)) or known(edits2(word)) or [word] )

def known(words):
    """The subset of `words` that appear int the dict of WORDS
    words: input list of word
    return: list of word that has appeared in WORDS."""
    return set(w for w in words if w in WORDS)

def edits1(word):
    """The edits that are one edit away from `word`.
    word: the user input string
    return: list of all strings that are one edit away from `word` """
    letters    = 'abcdefghijklmnopqrstuvwxyz'
    splits     = [(word[:i], word[i:])    for i in range(len(word) + 1)]
    deletes    = [L + R[1:]               for L, R in splits if len(R)]
    transposes = [L + R[1] + R[0] + R[2:] for L, R in splits if len(R) > 1]
    replaces   = [L + c + R[1:]           for L, R in splits for c in letters]
    inserts    = [L + c + R               for L, R in splits for c in letters]
    return set(deletes + transposes + replaces + inserts)

def edits2(word):
    """All edits that are two edits away from `word`.
    word: user input string
    return: list of string are two edits away form input string"""
    return (e2 for e1 in edits1(word) for e2 in edits1(e1))


print len(WORDS)
print sum(WORDS.values())
print WORDS['the'], P('the')
print WORDS['of'], P('of')
print WORDS['and'], P('and')

res = correction('speling')
print res
