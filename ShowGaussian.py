import numpy as np   
from matplotlib import pyplot as plt   
from matplotlib import animation

data = np.loadtxt("gaussian.log")

x = range(6042,7427)
y = data[6042:7427]
plt.plot(x, y, "b", lw=3)
plt.show()