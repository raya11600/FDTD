import matplotlib.pyplot as plt
import numpy as np
from matplotlib import animation


#plt.subplot(2,1,1)
""" subplot(a, b, c): size = a * b, c = current figure
	if a = 2, b = 3, then a * b is
		1, 2, 3
		4, 5, 6
"""
#fig = plt.figure()
plt.figure()
for i in range(500):
	if i > 1 and i % 50 == 0:
		name = "Ex_" + str(i) 
		data = np.loadtxt( name + ".log" )
		x = np.arange(len(data[0])+1)
		y = np.arange(len(data)+1)
		X, Y = np.meshgrid(x, y)
		plt.pcolormesh(X,Y,data)
		plt.pause(0.5)
		#plt.colorbar()
		#plt.title( name )	

#ani = animation.ArtistAnimation(fig, images, interval=50, 
#							blit=True, repeat_delay=2000)
#ani.save('dynamic_images.mp4')


plt.show()