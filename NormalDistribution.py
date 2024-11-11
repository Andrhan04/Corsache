'''
11.11.24 start to do
'''
from scipy.stats import shapiro
from scipy.stats import normaltest
import numpy as np
#Получаем данные
file = "C:/Coursace/Coursace/log/pole_100x100/full_result/0/Alive/Alive_0.txt"
fInput=open(file,"r")
labelForParam=fInput.readline().rstrip('\r\n')
firstFileString=fInput.readline().rstrip('\r\n')
data=[]
bufer = fInput.readlines()
for s in bufer:
    buf = s.split()
    data.append(int(float(buf[1])))

#-- класс для неприменимости метода
from collections import namedtuple
MethodNotAllowed = namedtuple('MethodNotAllowed', ['statistic', 'pvalue'])
methodNotAllowed=MethodNotAllowed("D'Agostino not works!","D'Agostino not works!")


if len(data)!=0:
    #считаем нормальность распределения
    label="None"
    if len(data)>=3:
        ResShapiro=shapiro(data)
    else:
        ResDAgostino=methodNotAllowed
    if len(data)>=20:
        ResDAgostino=normaltest(data)
    else:
        ResDAgostino=methodNotAllowed
    line=str(len(data))+";"+str(label)+";"+str(ResShapiro.statistic)+";"+str(ResShapiro.pvalue)+";"+str(ResDAgostino.statistic)+";"+str(ResDAgostino.pvalue)
    #считаем дисперсию и стандартное отклонение
    line=line+";"+str(np.var(data))+";"+str(np.std(data))+";"+str(max(data)-min(data))
    line=line+'\n'

print("ResShapiro.statistic    = " + str(ResShapiro.statistic))
print("ResShapiro.pvalue       = " + str(ResShapiro.pvalue))
print("ResDAgostino.statistic  = " + str(ResDAgostino.statistic))
print("ResDAgostino.pvalue     = "+str(ResDAgostino.pvalue))
