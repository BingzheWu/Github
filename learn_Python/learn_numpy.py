from scipy.optimize import fsolve 
from scipy.integrate import odeint 
import numpy as np 
from mpl_toolkits.mplot3d import Axes3D  
def f2(w,t):
    y1,y2,y3=w
    return np.array([-0.013*y1-1000.0*y1*y2,-2500.0*y2*y3,-0.013*y1-1000.0*y1*y2-2500.0*y2*y3])
if __name__=='__main__':
    t = np.arange(0, 10, 0.001)  
    track1 = odeint(f2, (1.0, 1.0, 0.0), t) 
    from mpl_toolkits.mplot3d import Axes3D
    import matplotlib.pyplot as plt 
    fig = plt.figure()
    ax = Axes3D(fig)
    ax.plot(track1[:,0], track1[:,1], track1[:,2])
    plt.show()
