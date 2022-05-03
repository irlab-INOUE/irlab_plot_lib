import math
import matplotlib.pyplot as plt

t = []
x = []

dt = 0.01


for i in range(0, 5000):
    tt = i * dt
    xx = math.sin(tt)
    x.append(xx)
    t.append(tt)

#plt.plot(t, x)
plt.plot([-2.0, 2.0], [-2.0, 1.8])
plt.grid()
plt.title('test-plot')
plt.show()
