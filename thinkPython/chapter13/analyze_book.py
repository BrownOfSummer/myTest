import string
import random

def process_file(filename, skip_header):
    """Makes a histogram that contains the words from a file
    filename: sting
    skip_header: boolean, whether to skip the Gutenberg head
    
    Returns: map from each word to the number of times it appears"""
    hist = dict()
    fp = open(filename)
    if skip_header:
        skip_gutenberg_header(fp)

    for line in fp:
        process_line(line, hist)
    return hist

def skip_gutenberg_header(fp):
    """Reads from fp untils it finds the line that ends the header .
    fp: open file object
    """
    for line in fp:
        """*END*THE SMALL PRINT! in line 241 in file"""
        if line.startswith( '*END*THE SMALL PRINT!' ):
            break


def process_line(line, hist):
    """Adds the words in the line to the histogram.
    
    Modifines hist.
    hist: histogram( map from word to frequency )
    """
    # replace hyphens with space before splitting
    line = line.replace('-', ' ')

    for word in line.split():
        # remove punctuation and convert to lowercase
        word = word.strip(string.punctuation + string.whitespace)
        word = word.lower()

        # update the histogram
        hist[word] = hist.get(word, 0) + 1


def total_words(hist):
    """Returns the total of the frequencies in a histogram."""
    return sum( hist.values() )

def different_words(hist):
    """Returns the number of different words in a histogram"""
    return len(hist)

def most_common(hist):
    """Makes a list of key-value pairs from a histogram and
    sorts them in descending order by frequency."""
    t = list()
    for key, value in hist.items():
        t.append( (value, key) )

    #t.sort(reverse=True)
    t.sort()
    t.reverse()
    return t

def print_most_common(hist, num=10):
    """Prints the most commons words in a histgram and their frequencies.
    hist: histogram ( maps from word to frequency )
    num: number of words to print
    """
    t = most_common(hist)
    print 'the most common words are:'
    for freq, word in t[:num]:
        print word, '\t', freq

"""Word subtract"""
def subtract(d1, d2):
    """Returns a dictionary with all keys that appear in d1 but not in d2
    d1, d2: dictionaries
    """
    """Find keys in d1, but not in d2
    since, we do not care about the values, set the value None"""
    res = dict()
    for key in d1:
        if key not in d2:
            res[key] = None
    return res

def random_word(hist):
    """Choose a random word from a histogram.
    The probability of each word is proportional to its frequency.
    """
    t = []
    for word ,freq in hist.items():
        t.extend( [word] * freq )
    return random.choice(t)


if __name__ == '__main__':
    hist = process_file('emma.txt', skip_header=True)
    print 'Total number of words: ', total_words(hist)
    print 'Number of different words: ', different_words(hist)
    t = most_common(hist)
    print_most_common(hist, 10)

    words = process_file('../words.txt', skip_header=False)

    diff = subtract(hist, words)
    print "The words in the book that aren't in word list are:"
    for word in diff.keys():
        print word,

    print "\n\nHere are some random words from the book"
    for i in range(30):
        print random_word(hist),
