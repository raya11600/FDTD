import matplotlib.pyplot as plt
import numpy as np
from matplotlib import animation


name = "Phasor_Ex"
Phasor_Ex = np.loadtxt( name + ".log" )
x = np.arange(len(Phasor_Ex[0])+1)
y = np.arange(len(Phasor_Ex)+1)
X, Y = np.meshgrid(x, y)
plt.figure(1)
#plt.subplot(231)
plt.pcolormesh(X,Y,Phasor_Ex)

name = "Phasor_Ey"
Phasor_Ey = np.loadtxt( name + ".log" )
x = np.arange(len(Phasor_Ey[0])+1)
y = np.arange(len(Phasor_Ey)+1)
X, Y = np.meshgrid(x, y)
plt.figure(2)
#plt.subplot(232)
plt.pcolormesh(X,Y,Phasor_Ey)

name = "Phasor_Ez"
Phasor_Ez = np.loadtxt( name + ".log" )
x = np.arange(len(Phasor_Ez[0])+1)
y = np.arange(len(Phasor_Ez)+1)
X, Y = np.meshgrid(x, y)
plt.figure(3)
#plt.subplot(233)
plt.pcolormesh(X,Y,Phasor_Ez)

name = "Phasor_Hx"
Phasor_Hx = np.loadtxt( name + ".log" )
x = np.arange(len(Phasor_Hx[0])+1)
y = np.arange(len(Phasor_Hx)+1)
X, Y = np.meshgrid(x, y)
plt.figure(4)
#plt.subplot(234)
plt.pcolormesh(X,Y,Phasor_Hx)

name = "Phasor_Hy"
Phasor_Hy = np.loadtxt( name + ".log" )
x = np.arange(len(Phasor_Hy[0])+1)
y = np.arange(len(Phasor_Hy)+1)
X, Y = np.meshgrid(x, y)
plt.figure(5)
#plt.subplot(235)
plt.pcolormesh(X,Y,Phasor_Hy)

name = "Phasor_Hz"
Phasor_Hz = np.loadtxt( name + ".log" )
x = np.arange(len(Phasor_Hz[0])+1)
y = np.arange(len(Phasor_Hz)+1)
X, Y = np.meshgrid(x, y)
plt.figure(6)
#plt.subplot(236)
plt.pcolormesh(X,Y,Phasor_Hz)

plt.show()