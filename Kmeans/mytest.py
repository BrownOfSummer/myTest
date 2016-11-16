from matplotlib import pyplot as plt
from numpy import *

def read_data(filename):
    """input: a file path and name
    return: a list of [(x1,y1),(x2,y2),...]"""
    dataMat = list()
    fr = open(filename)
    for line in fr.readlines():
        curLine = line.strip().split()
        dataMat.append( ( float(curLine[0]), float(curLine[1]) ) )
    return dataMat

def distEclud(vecA, vecB):
    """input: truple/list A B containing 2 elements
    return: float num stands for variation"""
    return sqrt( (vecA[0] - vecB[0])**2 + (vecA[1]-vecB[1])**2 )

def init_centroids(data, k):
    """Select k diffent coordinate as centroids
    input:  list of data, and indicate how many centroids
    return: a list of k centroids: [ (x1, y1), (x2, y2),... ]"""
    import random
    t = list()
    while( len(set(t)) != k ):
        t = random.sample(data, k)
    return t

def calc_classify( dataMat, centroids ):
    """input: data, and the centroids this time
    return: the classification based on this centroids"""
    classify = dict()
    for i in range( len(dataMat) ):
        minDist = inf
        minIndex = -1
        for j in range( len(centroids) ):
            dist = distEclud( dataMat[i], centroids[j] )
            if dist < minDist:
                minDist = dist; minIndex = j
        if minIndex not in classify:
            classify[minIndex] = [ dataMat[i] ]
        else:
            classify[minIndex].append( dataMat[i] )
    return classify

def kmeans( dataMat, centroids):
    """input: data, and the centroids this time
    return: new_centroids is the update centroids
    """
    """        
    classify = dict()
    for i in range( len(dataMat) ):
        minDist = inf
        minIndex = -1
        for j in range(len(centroids)):
            dist = distEclud( dataMat[i], centroids[j] )
            if dist < minDist:
                minDist = dist; minIndex = j
        if minIndex not in classify:
            classify[minIndex] = [ dataMat[i] ]
        else:
            classify[minIndex].append( dataMat[i] )
    """
    classify = calc_classify(dataMat, centroids)
    new_centroids = []
    for i in range( len(centroids) ):
        tmp = classify[i]
        length = len(tmp)
        xmean = 0; ymean = 0
        for j in range(length):
            xmean += float(tmp[j][0]) / length
            ymean += float(tmp[j][1]) / length
        new_centroids.append( (xmean, ymean) )
    return new_centroids

def show( origin_cent, centroids, classify, K):
    point_mark = ['or', 'ob', 'og', 'ok', '^r', '+r', 'sr', 'dr', '<r', 'pr']
    centro_mark = ['Dr', 'Db', 'Dg', 'Dk', '^b', '+b', 'sb', 'db', '<b', 'pb']
    if len(point_mark) < K:
        print("Two many centroids for plot !")
        return -1
    for i in range(K):
        tmp = classify[i]
        plt.plot(origin_cent[i][0], origin_cent[i][1], centro_mark[i], markersize = 6)
        plt.plot(centroids[i][0], centroids[i][1], centro_mark[i], markersize = 12)
        for j in range(len(tmp)):
            plt.plot( tmp[j][0], tmp[j][1], point_mark[i], markersize = 6 )
    plt.show()

def main():
    K = 4
    dataMat = read_data('coor.txt')
    centroids = init_centroids(dataMat, K)
    origin_cent = centroids
    inter_num = 0
    while(inter_num < 50):
        inter_num += 1
        Dist = 0;
        new_centroids = kmeans( dataMat, centroids )
        for i in range(K):
            Dist += distEclud(new_centroids[i], centroids[i])
        if Dist < 0.01:
            break
        else:
            centroids = new_centroids
    print("totally iterates %d times" %(inter_num) )
    classify = calc_classify(dataMat, new_centroids)
    show( origin_cent, new_centroids, classify, K )

if __name__ == '__main__':
    main()
