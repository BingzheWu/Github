#-coding-:utf8
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt  
import numpy as np 
from numpy import pi
import sys
reload(sys)
def InitData(fileName):
    r=open(fileName,'r')
    InfoDict={}
    for info in r:
        info = info.split(',')
        length=len(info)
        for i in range(length):
            if i not in InfoDict:
                InfoDict[i]=[float(info[i].strip())]
            else:
                InfoDict[i].append(float(info[i].strip()))
    return InfoDict
def plot3Ddata(fileName,ImageName):
    plotInfo=InitData(fileName)
    X = np.array(plotInfo[0],dtype=np.float) 
    Y = np.array(plotInfo[1],dtype=np.float)
    Z=np.array(plotInfo[2],dtype=np.float)
    X.shape=1000,1001
    Y.shape=1000,1001
    Z.shape=1000,1001
    Z1=np.sin(Y-X)
    ax=plt.subplot(111,projection='3d')
    ax.plot_surface(X,Y,Z,cmap=plt.cm.coolwarm,alpha=1)
    plt.title(ImageName)
    plt.show()
    
    '''
    for i  in plotInfo:
        ax=plt.subplot(111,projection='3d')
        if i==0 or i==1:
            continue
        else:
            Z=np.array(plotInfo[i])
            print Z
            ax.plot_surface(X,Y,Z,rstride=2,cstride=1,cmap=plt.cm.coolwarm,alpha=0.8)
            plt.show()
    '''
if __name__=='__main__':
    fileName=sys.argv[1]
    ImageName=sys.argv[2]
    plot3Ddata(fileName,ImageName)
