""" Exercise 9.7 of think python"""
def is_triple_double(word):
    #Test if a word contains three consecutive double letters#
    i = 0
    count = 0
    while i < len(word) - 1:
        if word[i] == word[i+1]:
            count += 1
            if count == 3:
                return True
            i = i + 2
        else:
            count = 0
            i = i + 1
    return False

def find_triple_double():
    """Read a word list and prints words with triple double letters. """
    fin = open('words.txt')
    for line in fin:
        word = line.strip()
        if is_triple_double(word):
            print word

print 'Here are all the words in the list that have'
print 'three consecutive double letters.'
find_triple_double()
