# --coding--=utf8
from pylab import *
import math
import sys
reload(sys)
def initData(r):
    FFTtime=[]
    PCGtime=[]
    size=[]
    for Info in r:
        Info=Info.split(',')
        size.append(float(Info[0]))
        FFTtime.append(float(Info[1]))
        PCGtime.append(float(Info[2]))
    return size,FFTtime,PCGtime
def plotTime(r):
    size,FFTtime,PCGtime=initData(r)
    plot(size,FFTtime,'r',label=u'FFT')
    plot(size,PCGtime,'b',label=u'Normal')
    legend()
    xlabel('MatrixSize')
    ylabel('time')
    show()
if __name__=='__main__':
    fileName=sys.argv[1]
    r=open(fileName,'r')
    plotTime(r)

