#-coding-:utf8
from pylab import *
import sys
reload(sys)

def InitData(fileName):
    r=open(fileName,'r')
    plotInfo={}
    for info in r:
        info = info.split(',')
        length=len(info)
        for i in range(length):
            if i in plotInfo:
                plotInfo[i].append(info[i])
            else:
                plotInfo[i]=[info[i]]
    return plotInfo

def plot2D(fileName,ImageName):
    plotInfo=InitData(fileName)
    for i in plotInfo:
        print i
        if i==0:
            continue
        else:
            plot(plotInfo[0],plotInfo[i])
    show()
def curecySolution(x):
    return 1.0/x*tan(-pi/4.0-log(x))

def NormalPlot(fileName,ImageName,n):
    plotInfo=InitData(fileName)
    Z=[]
    h=1.0/float(n);
    for t in range(n+1):
        Z.append(curecySolution(1+t*h))
    plot(plotInfo[0],plotInfo[1],'r*',label=u"Euler Result")
    plot(plotInfo[0],plotInfo[2],label=u"Improve Euler Result")
    plot(plotInfo[0],Z,label=u"Curreny Solution")
    legend()
    xlabel('x')
    ylabel('y')
    grid('on')
    title(ImageName)
    show()
if __name__=='__main__':
    ImageName=sys.argv[1]
    fileName=sys.argv[2]
    n=10
    NormalPlot(fileName,ImageName,n)

