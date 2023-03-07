from serial import Serial

import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style

import time

fig = plt.figure()

sensors = ["torque", "RPM", "current"]
yss = []
xs = []
axs = []

colours = ["red", "green", "blue"]

window = 30
startTime = time.time()

for i, sensor in enumerate(sensors):
    yss.append([])
    ax = fig.add_subplot(1, len(sensors), i + 1)
    ax.set_title(sensor)
    axs.append(ax)

def animate(i):
    data = None
    try:
        data = [float(i) for i in serial.readline().decode().strip().split(",")]
    except:
        pass

    if data is not None:
        newTime = time.time() - startTime
        xs.append(newTime)

        windowStart = 0
        while xs[windowStart] < newTime - window:
            windowStart += 1

        # print(windowStart)

        newXs = xs[windowStart:]
        print(len(xs))
        print(len(newXs))
        print()

        xs.clear()
        xs.extend(newXs)
        
        for i, val in enumerate(data):
            yss[i].append(val)
            newYs = yss[i][windowStart:]
            yss[i].clear()
            yss[i].extend(newYs)

        for i, ys in enumerate(yss):
            axs[i].clear()
            axs[i].set_title(sensors[i])
            axs[i].plot(xs, ys, color=colours[i])
            axs[i].set_xlim(newTime - window, newTime)


serial = Serial("/dev/ttyUSB0", 57600)

ani = animation.FuncAnimation(fig, animate, interval = 100)
plt.show()