import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.cm as mplcm
import matplotlib.colors as colors
import pylab
from matplotlib2tikz import save as tikz_save
import sys


colors = pylab.cm.nipy_spectral(np.linspace(0,1,9))




r_list = []
for i in range(7):
	r_list.append(np.loadtxt('output/ev%d.txt' %i, skiprows = 1, unpack=True))

exact = np.loadtxt('output/exact_ev.txt', skiprows = 1, unpack=True)


n = 10

for i in range(7):
	plt.plot(r_list[i][3][::n], r_list[i][4][::n], color=colors[i+1], alpha=0.5)

plt.plot(r_list[0][0], r_list[0][1], marker='o', color='gold', label='_nolegend_')
plt.plot(exact[3][::n], exact[4][::n], '--', color='black')
plt.grid()
plt.xlabel('x-position [AU]')
plt.ylabel('y-position [AU]')
plt.axis("equal")
plt.legend([r'$v_0 = 2.5 \pi$', r'$v_0 = 2.6 \pi$', r'$v_0 = 2.7 \pi$', r'$v_0 = 2.8 \pi$',\
r'$v_0 = 2.85 \pi$', r'$v_0 = 2.9 \pi$', r'$v_0 = 3 \pi$', r'$v_0 = \sqrt{8} \pi$ (exact)'])
tikz_save("Figures/escape_velocity.tex", figureheight='\\figureheight', figurewidth='\\figureheight')
plt.show()
