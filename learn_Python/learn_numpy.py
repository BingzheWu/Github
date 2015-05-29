import numpy
from scipy.optimize import fsolve 
from math import sin,cos,exp

def f1(x):
    return cos(x)+1.0/(1+exp(-2*x))
def f2(x):
    return [-cos(x[0])/81.0+x[1]*x[1]/9.0+sin(x[2])/3.0-x[0],sin(x[0])/3.0+cos(x[2])/3.0-x[1],-cos(x[0])/9.0+x[1]/3.0+sin(x[2])/6.0-x[2]]
if __name__=='__main__':
    result=fsolve(f2,[1,1,-1])
    print result
    result1=fsolve(f1,3)
    print result1
