import string
row = list()
dic = dict()
f = open('../data.txt', 'r')
for line in f:
    line = line.strip()
    row = line.split()
    if row[2] not in dic:
        dic[row[2]] = []
        dic[row[2]].append((row[0], row[1]))
    else:
        dic[row[2]].append((row[0], row[1]))
print dic
dic2 = dict()
