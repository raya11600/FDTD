import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("data.log")

x = data[0, :]

y1 = data[25,:]
y2 = data[50,:]
y3 = data[100,:]
y4 = data[150,:]
y5 = data[200,:]
y6 = data[400,:]

plt.subplot(231)
plt.plot(x, y1, lw=3)
plt.xlim(0, 100)
plt.ylim(-1, 1)

plt.subplot(232)
plt.plot(x, y2, lw=3)
plt.xlim(0, 100)
plt.ylim(-1, 1)

plt.subplot(233)
plt.plot(x, y3, lw=3)
plt.xlim(0, 100)
plt.ylim(-1, 1)

plt.subplot(234)
plt.plot(x, y4, lw=3)
plt.xlim(0, 100)
plt.ylim(-1, 1)

plt.subplot(235)
plt.plot(x, y5, lw=3)
plt.xlim(0, 100)
plt.ylim(-1, 1)

plt.subplot(236)
plt.plot(x, y6, lw=3)
plt.xlim(0, 100)
plt.ylim(-1, 1)

plt.show()