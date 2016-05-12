"""
   Convex Hull Assignment: COSC262 (2016)
   Student Name: Cecilia Villatoro
   id: 67486777
"""
#global representing the number of points in data list
n = 0
def readDataPts(filename):
    """Reads data from an input file and returns a list of tuples
       [(x0,y0), (x1, y1), ...]
    """
    listPts = []
    f = open(filename, 'r')
    numPoints = int(f.readline())
    global n 
    n = numPoints
    for i in range(numPoints):
        line = [int(x) for x in f.readline().strip('\n\r').split(' ')]
        if len(line) > 0:
            tup = (line[0], line[1])
        listPts.append(tup)

    return listPts

def findMinPt(listPts):
    """
    returns the index of the point of minimum y value. Selects right-most point
    if 2 points of identical y-value exist
    """
    minIndex = 0
    maxX = 0
    minY = float('inf')
    i = 0
    for x, y in listPts:
        #found a point of equal y value to the current y minimum
        if y == minY:
            if x > maxX:
                minY = y
                maxX = x
                minIndex = i 

        if y < minY:
            minY = y
            minIndex = i

        i += 1

    return minIndex


def swap(list, i, k):
    """
    swaps a pair of points in a list
    """
    tmp = list[i]
    list[i] = list[k]
    list[k] = tmp

import math
def theta(pointA, pointB):
     ''' Computes an approximation of the angle between
     the line AB and a horizontal line through A.
     '''
     #report:modiified
     dx = pointB[0] - pointA[0]
     dy = pointB[1] - pointA[1]
     if abs(dx) < 1.e-6 and abs(dy) < 1.e-6:
        t = 0
        return t
     else:
        t = float(dy)/float((abs(dx) + abs(dy)))

     if dx < 0:
        t = 2 - t
     elif dy < 0:
        t = 4 + t
     angle = t * 90

     if angle == 0.0:
        return 360
     else: 
        return angle

def giftwrap(listPts):
    """Returns the indices of hull vertices computed using giftwrap algorithm
    """
    k = findMinPt(listPts)
    chull  = list(range(0,n+1))
    i = 0
    v = 0
    initialPt = listPts[k]
    #add the last point to the end of the list to stop the iteration 
    listCopy = listPts[0:]
    listCopy.append(initialPt)

    while (k != n):
        #swap points list
        swap(listCopy, i, k)
        #swap indeces
        swap(chull, i, k)
        minAngle = 361
        for j in range(i+1, n+1):
            angle = theta(listCopy[i], listCopy[j])
            if angle < minAngle and angle > v and listCopy[i] != listCopy[j]:
                minAngle = angle
                k = j
        i += 1
        v = minAngle
        
    #report:useful
    chull = [str(x) for x in chull]

    return ' '.join(chull[0:i]).strip()

#report: use of merge sort, modification
def merge_sort(list, p0):
    """
    merge sort algorithm for sorting based on angle
    """

    if len(list) < 2:
        return list
    else:
        middle = len(list) / 2 
        left = merge_sort(list[:middle], p0)
        right = merge_sort(list[middle:], p0)
        return merge(left, right, theta, p0)

def merge(left, right, key, p0):
    
    result = []
    lenLeft = len(left) 

    lenRight = len(right) 
    j = 0
    k = 0
    while j < lenLeft and k < lenRight:
        if key(p0, (left[j][0], left[j][1])) <= key(p0,(right[k][0], right[k][1])):
            result.append(left[j])
            j+=1
        else:
            result.append(right[k] )
            k+=1
        
    while(j < lenLeft):
        result.append(left[j])
        j+=1
        
    while(k < lenRight):
        result.append(right[k])
        k+=1
    

    return result

def lineFn(ptA, ptB, ptC):
 
 return ((ptB[0]-ptA[0])*(ptC[1]-ptA[1]) -
 (ptB[1]-ptA[1])*(ptC[0]-ptA[0]) )

def isCCW(ptA, ptB, ptC):
 """
 determines if 3 points form a counter-clockwise line
 """
 return lineFn(ptA, ptB, ptC) > 0

#report, used this function
def addIndex(listPts):
    """
    add index of each point as a third parameter to the tuple to perserve order of indeces
    """
    result = []
    for i in range(len(listPts)):
        result.append( listPts[i]+(i,))
    return result

def grahamscan(listPts):
    """Returns the indices of hull vertices computed using grahamscan algorithm
    """

    indexP0 = findMinPt(listPts)
    p0 = listPts[indexP0]

    #add index to tuples
    listCp = addIndex(listPts)

    #sort pts by angle from p0
    sortedPts = merge_sort(listCp, p0)

    stack = []
    chull = []
    #initialize stack with first 3 points of the sorted list
    for i in range(0,3):
        stack.append( (sortedPts[i][0], sortedPts[i][1]))
        chull.append(sortedPts[i][2])
     #loop through remaining points on sorted list to find sets of 3 points that for a counter-clowckwise line
    for i in range(3, n):
        pt =  (sortedPts[i][0],sortedPts[i][1])

        while not isCCW(stack[-2], stack[-1], pt):
            stack.pop()
            chull.pop()
        stack.append(pt)
        chull.append(sortedPts[i][2])

    chull = [str(x) for x in chull]
    return  ' '.join(chull).strip()


def distance(ptA, ptB, ptC):
    """computes the distance between line segment AB to a point C
    """
    deltaABx = ptB[0]-ptA[0];
    deltaABy = ptB[1]-ptA[1];
    num = deltaABx*(ptA[1]-ptC[1])-deltaABy*(ptA[0]-ptC[0]);
    if (num < 0) :
        num = -num;
    return num;
   
def findMinX(listPts):
    minX= float('inf')
    i = 0
    xindex = -1
    for x, y in listPts:
        if x < minX:
            minX = x
            xindex = i
        i += 1
    return xindex

def findMaxX(listPts):
    maxX = 0
    i = 0
    xIndex = -1
    for x, y in listPts:
        if x > maxX:
            maxX = x
            xIndex = i
        i += 1
    return xIndex

def quickhull(ptA, ptB, set, rightIndexSet, chull):
    """computes the furthest point to the right of A and B and adds its to the convex hull
    """
    i = 0
    furthestPtIn = -1
    if len(set) > 0:
        furthestPt = ptA
        maxDistance = 0
        #find the furthest point from A and B in the set
        for ptC in set:
            dist = distance(ptA, ptB, ptC)
            if  dist > maxDistance:
                maxDistance = dist
                furthestPt = ptC
                furthestPtIn = rightIndexSet[i]
            i += 1
       
        chull.append(furthestPtIn)
        #partition set into points on the right side of line A to C
        rightSet1 = []
        rightSet1IndexSet = []
        i = 0
        for pt in set:
            res = lineFn(ptA, furthestPt, pt)
            if (abs(res) < 1.e-6):
                i += 1
                continue
            if res < 0:
                rightSet1.append(pt)
                rightSet1IndexSet.append(rightIndexSet[i])
            i += 1
        i = 0
        #partition set into points on the right side of line C to B
        rightSet2 =  []
        rightSet2IndexSet  = []
        for pt in set:
            res = lineFn(furthestPt, ptB, pt)
            if (abs(res) < 1.e-6):
                i += 1
                continue
            if res < 0:
                rightSet2.append(pt)
                rightSet2IndexSet.append(rightIndexSet[i])
            i += 1
        quickhull(ptA, furthestPt, rightSet1, rightSet1IndexSet, chull)
        quickhull(furthestPt, ptB, rightSet2, rightSet2IndexSet, chull)




def amethod(listPts):
    """Returns the indices of hull vertices computed using a third algorithm
       implementation of quickhull algorithm
    """ 
    #find the right most and left most points of the hull
    indexMinX = findMinX(listPts)
    
    indexMaxX = findMaxX(listPts)
    #create  line segment between the min and max pts
    ptA = listPts[indexMinX]

    ptB = listPts[indexMaxX]

    #create two sets at left and right of the min max line segment
    leftSet = []
    leftIndexSet = []
    rightSet = []
    rightIndexSet = []
    i = 0
    for ptC in listPts:
       
        res = lineFn(ptA, ptB, ptC)
        if (abs(res) < 1.e-6):
            i += 1
            continue
        #C is to the left of AB
        if res > 0:
            leftSet.append(ptC)
            leftIndexSet.append(i)
        #C is to the right of AB
        if res < 0:
            rightSet.append(ptC)
            rightIndexSet.append(i)
        i += 1
    chull = [indexMinX, indexMaxX]    

    quickhull(ptA, ptB, rightSet, rightIndexSet, chull)
    quickhull(ptB, ptA, leftSet, leftIndexSet, chull)
    chull = [str(x) for x in chull]
    return ' '.join(chull).strip()
import os
def main():
    #verifying all input files in set A and set B algorithm output against .out file data
    directories = ['./Set_A/', './Set_B/']
    data = True

    for dir in directories:
        for fn in os.listdir(dir):
            if data:
                print(dir + fn)
                listPts = readDataPts(dir + fn)  
                data = False
            else:
                filename = dir + fn
                sol1  =  (sorted([int(x) for x in giftwrap(listPts).split(' ')]) )      
                sol2  =  (sorted([int(x) for x in grahamscan(listPts).split(' ')]) )      
                sol3  =  (sorted([int(x) for x in amethod(listPts).split(' ')]) )      

                f = open(filename, 'r')
                l = f.read().strip('\r\n ').split(' ')
                # print(l)

                l = ([int(x) for x in l]) 
                l = sorted(l)
                if l == sol1:
                    print True
                else:
                    print False
                if l == sol2:
                    print True
                else:
                    print False

                if l == sol3:
                    print True
                else:
                    print False            # providedrint(sorted(l))
                data = True
if __name__  ==  "__main__":
    main()
  