import math
class Points:
    def __init__(self,X=0,Y=0):
        self.X=X
        self.Y=Y
def InitData(r):
    pointList=[]
    for point in r:
        print point
        temp=Points()
        point=point.split(',')
        temp.X=float(point[1])
        temp.Y=float(point[0])
        pointList.append(temp)
    print len(pointList)
    return pointList
def check(aLat,aLon,APoints):
    iSum=0
    if(len(APoints)<3):
        print "point isn't in Poly'"
        return 0
    else:
        iCloud=len(APoints)
        for i in range(0,iCloud):
            if i==iCloud-1:
                dLon1 = APoints[i].X
                dLat1 = APoints[i].Y
                dLon2 = APoints[0].X
                dLat2 = APoints[0].Y
            else:
                dLon1 = APoints[i].X
                dLat1 = APoints[i].Y
                dLon2 = APoints[i+1].X
                dLat2 = APoints[i+1].Y
            print dLat1
            print dLat2
            if (aLat>=dLat1 and aLat<dLat2) or (aLat<dLat1 and aLat >= dLat2):
                if math.fabs(dLat1-dLat2)>0:
                    dLon = dLon1 - ((dLon1 - dLon2) * (dLat1 - aLat)) / (dLat1 - dLat2)
                if dLon<aLon:
                    iSum=iSum+1
        print iSum
        if iSum%2 != 0:
            return 1
        else:
            return 0
if __name__=='__main__':
    r=open('test','r')
    pointList=InitData(r)
    print pointList
    print check(39.9934907590,116.3028893615,pointList)





