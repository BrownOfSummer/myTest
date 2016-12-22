fin = open( 'words.txt' )
"""
for line in fin:
    word = line.strip()
    if len(word) > 20:
        print word
"""
"""
def has_no_e(word):
    for char in word:
        if char in 'Ee':
            return False
        else:
            return True
count_no_e = 0
count = 0
for line in fin:
    count += 1
    if has_no_e(line):
        count_no_e += 1
print 1.0*count_no_e / count
"""
##### Exercise 9.3
"""
def avoids(word, forbidden):
    for char in word:
        if char in forbidden:
            return False
        return True
letter = raw_input('What letters to exclude ?\n')
count_no_forbidden = 0
count = 0
for line in fin:
    word = line.strip()
    if avoids(word, letter):
        count_no_forbidden += 1
    count += 1
percent = (1.0 * count_no_forbidden / count) * 100
print str(percent) + "% of the words don't have " + letter + "."
"""

##### Exercise 9.4
"""
def uses_only(word, letters):
    for char in word:
        if char in letters:
            continue
        else:
            return False
    return True
for line in fin:
    word = line.strip()
    if uses_only(word, 'acefhlo'):
        print word
    else:
        continue
"""
### Exercise 9.5
"""
def uses_all(word, letters):
    for char in letters:
        if char in word:
            continue
        else:
            return False
    return True
for line in fin:
    word = line.strip()
    if uses_all(word, 'vowels'):
        print word
"""

### Exercise 9.6
"""
def is_abecedarian(word):
    length = len(word)
    for i in range(length - 1):
        if word[i] < word[i+1]:
            continue
        else:
            return False
    return True

for line in fin:
    word = line.strip()
    if is_abecedarian(word):
        print word
"""
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
