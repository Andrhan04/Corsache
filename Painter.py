import numpy as np
import seaborn as sns
import matplotlib.pylab as plt

F = open('startPoints.txt','r+')
x = 0
data = [[0,0]]
buf = F.readline()
buf = F.readline()
while(x < 1000):
    buf = F.readline()
    res = buf.split()
    print(res[1])
    data.append([int(res[0]), int(res[1])])
    x+=1


ax = sns.heatmap(data, linewidth=0)
plt.show()