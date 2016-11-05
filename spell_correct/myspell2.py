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

"""I defined correction2, for the formular: P(w|c)*P(c)"""
def correction2(word):
    """To get the P(c|w) is equal to argmax P(w|c) * P(c)
    this function is to calc the math max P(w|c)
    word: user input strings
    return: the hypothesis of the probably correct word."""
    correcte_word = word;
    if known([word]):
        return correcte_word
    hypothesis1 = known( edits1(word) )
    hypothesis2 = known( edits2(word) ) - hypothesis1 #in 2 not in 1, because 2 contains 1
    res = list()
    "calc the c for the P(w|c)*P(c)"
    if hypothesis1:
        for c in hypothesis1:
            string_set = edits1( word )
            if c in string_set:
                res.append( (P(c) * 1.0 / len(string_set) , c) )
    if hypothesis2:
        for c in hypothesis2:
            string_set = set(edits2( word ) )
            if c in string_set:
                res.append( (P(c) * 1.0 / len(string_set) , c) )

    if len(res) > 0:
        res.sort(reverse=True)
        return res[0][1]
    else:
        return correcte_word

def spelltest(tests, verbose=False):
    "Run correction(wrong) on all (right, wrong) pairs; report results."
    import time
    start = time.clock()
    good, unknown = 0, 0
    n = len(tests)
    for right, wrong in tests:
        #w = correction(wrong)
        w = correction2(wrong)
        good += (w == right)
        if w != right:
            unknown += (right not in WORDS)
            if verbose:
                print('correction({}) => {} ({}); expected {} ({})'
                        .format(wrong, w, WORDS[w], right, WORDS[right]))
    dt = time.clock() - start
    print('{:.0%} of {} correct ({:.0%} unknown) at {:.0f} words per second'
            .format(good * 1.0 / n, n, 1.0 * unknown / n, n / dt))


def Testset(lines):
    "Parse 'right: wrong1 wrong2' lines into [('right', 'wrong1'), ('right', 'wrong2')] pairs."
    return [(right, wrong)
            for (right, wrongs) in (line.split(':') for line in lines)
            for wrong in wrongs.split()]

if __name__ == '__main__':
    #print(unit_tests())
    spelltest(Testset(open('spell-testset1.txt')))
    #spelltest(Testset(open('spell-testset2.txt')))





"""
print len(WORDS)
print sum(WORDS.values())
#print WORDS['the'], P('the')
#print WORDS['of'], P('of')
#print WORDS['and'], P('and')

word = 'speling'
res = correction(word)
res2 = correction2(word)
print "correction is: ",res
print "correction2 is: ", res2
"""
