import numpy
from scipy.optimize import fsolve 
import math

def f1(x):
	return math.cos(x)+1.0/(1+math.exp(-2*x))
if __name__=='__main__':
	result=fsolve(f1,3.0)
	print result

