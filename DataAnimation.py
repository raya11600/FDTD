import numpy as np   
from matplotlib import pyplot as plt   
from matplotlib import animation

data = np.loadtxt("data.log")

fig = plt.figure()
plt.xlim(0, 100)
plt.ylim(-1, 1)
images = []
for i in range(500):
	x = data[0, :]
	y = data[i, :]
	im = plt.plot(x, y, "b", lw=3)
	images.append(im)



ani = animation.ArtistAnimation(fig, images, interval=50, 
							blit=True, repeat_delay=2000)
#ani.save('dynamic_images.mp4')

plt.show()