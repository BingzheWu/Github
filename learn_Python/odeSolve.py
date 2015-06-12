#-coding-:-utf8-
from scipy.integrate import odeint 
import numpy as np 
from scipy.integrate import odeint 
import numpy as np 

def lorenz(w, t, p, r, b): 
    x, y, z = w 
    return np.array([p*(y-x), x*(r-z)-y, x*y-b*z]) 
t = np.arange(0, 30, 0.01) 
track1 = odeint(lorenz, (1, 1, 1), t, args=(10.0, 28.0, 8/3.0)) 
track2 = odeint(lorenz, (0.0, 1.1, 0.0), t, args=(10.0, 28.0, 3.0)) 
def plot2d():
    from pylab import *
    plot(t,track1[:,0],'r',label=u'x(t)')
    plot(t,track1[:,1],label=u'y(t)')
    plot(t,track1[:,2],label=u'z(t)')
    legend()
    xlabel('t')
    title('(1,1,1)')
    show()
def plot3d():
    from mpl_toolkits.mplot3d import Axes3D
    import matplotlib.pyplot as plt 
    print track1
    fig = plt.figure()
    ax = Axes3D(fig)
    ax.plot(track1[:,0], track1[:,1], track1[:,2])
    ax.plot(track2[:,0], track2[:,1], track2[:,2])
    plt.show()
if __name__=='__main__':
    plot3d()
    plot2d()
