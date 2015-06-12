#-*-coding=utf-8
from pylab import *
import math
def initData(r):
    x0_values=[]
    y0_values,y1_values=[],[]
    num=0
    for data in r:
        data=data.split(',')
        y0_values.append(data[0])
        y1_values.append(data[1])
        x0_values.append(2*num*math.pi/256)
        num=num+1
    return x0_values,y0_values,y1_values
def showData(r):
    x0_values,y0_values,y1_values=initData(r)
    plot (x0_values,y0_values,label=u"oringinal singal")
    plot(x0_values,y1_values,'r+',label=u"processed singal")
    legend()
    xlabel('t')
    ylabel('y(t)')
    grid('on')
    show()
if __name__=='__main__':
    r=open('5.3','r')
    showData(r)

