from serial import Serial

import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style

import time

fig = plt.figure()

sensors = ["torque", "RPM", "current", "voltage"]
yss = []
xs = []
axs = []

colours = ["red", "green", "blue", "pink"]

logFile = "logs/log.csv"

window = 30
startTime = time.time()

with open(logFile, "w") as log:
    log.write("time")

    for i, sensor in enumerate(sensors):
        log.write(f",{sensor}")
        yss.append([])
        ax = fig.add_subplot(1, len(sensors), i + 1)
        ax.set_title(sensor)
        axs.append(ax)

    log.write("\n")
    log.flush()

    def animate(i):
        data = None
        dataLine = None
        try:
            dataLine = serial.readline().decode().strip()
            data = [float(i) for i in dataLine.split(",")]
        except:
            pass

        if data is not None:
            newTime = time.time() - startTime                   
            xs.append(newTime)

            log.write(f"{newTime},{dataLine}\n")
            log.flush()

            windowStart = 0
            while xs[windowStart] < newTime - window:
                windowStart += 1

            # print(windowStart)

            newXs = xs[windowStart:]

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