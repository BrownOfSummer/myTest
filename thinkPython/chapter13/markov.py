import sys
import string
import random

# global variables
suffix_map = {} # map from prefixes to a list of suddixes
prefix = ()     # current tuple of words

def process_file(filename, order = 2):
    """Reads a file and performs Markov analysis.
    filename: string
    order: integer number of words in the prefix
    Returns: map from prefix to list of possible suffixes.
    """
    fp = open(filename)
    skip_gutenberg_header(fp)

    for line in fp:
        for word in line.rstrip().split():
            process_word(word, order)

def skip_gutenberg_header(fp):
    """Reads from fp until it finds the line that ends the heander
    fp: open file object"""
    for line in fp:
        if line.startswith('*END*THE SMALL PRINT!'):
            break

def process_word(word, order):
    """Process each word.
    word: string
    order: integer
    During the first few interations, all we do is store up the words;
    after that we start adding entries to the dictionary."""
    global prefix
    if len(prefix) < order:
        prefix += (word,)
        return

    try:
        suffix_map[prefix].append(word)
    except KeyError:
        # if there is no entry for this prefix, make one
        suffix_map[prefix] = [word]

    prefix = shift(prefix, word)

def shift(t, word):
    """Forms a new tuple by removing the head and adding word to the tail.
    t: tuple of strings
    word: string
    Returns: tuple of strings
    """
    return t[1:] + (word,)

def random_text(n=100):
    """Generates random words from the analyzed text.
    Starts with a random prefix from the dictionary.
    n: number of words to generate
    """
    # choose a random prefix(not weighted by frequency)
    start = random.choice(suffix_map.keys())
    for i in range(n):
        suffixes = suffix_map.get(start, None)
        if suffixes == None:
            # if the start isn't in map, we got to the end of the 
            # original text, so we have to start again
            random_text(n-i)
            return
        # choose a random suffix
        word = random.choice(suffixes)
        print word,
        start = shift(start, word)

def main(name, filename='', n=100, order=2, *args):
    try:
        n = int(n)
        order = int(order)
    except:
        print 'Usage: randomtext.py filename [# of words] [prefix length]'
    else:
        process_file(filename, order)
        random_text(n)

if __name__=='__main__':
    main(*sys.argv)
