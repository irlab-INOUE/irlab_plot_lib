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

plt.plot(t, x)
plt.grid()
plt.xlim(-2, 0.5)
plt.ylim(-2, 3)
plt.title('test-plot')
plt.show()
