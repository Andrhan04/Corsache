'''
11.11.24 start to do
'''
from scipy.stats import shapiro
from scipy.stats import normaltest
import numpy as np
#Получаем данные
file = "C:/Coursace/Coursace/log/pole_100x100/full_result/0/Alive/Alive_0.txt"
fInput=open(file,"r")
data_y=[]
data_x=[]
bufer = fInput.readlines()
for s in bufer:
    buf = s.split()
    data_x.append(int(float(buf[0])))
    data_y.append(int(float(buf[1])))

#-- класс для неприменимости метода
from collections import namedtuple
MethodNotAllowed = namedtuple('MethodNotAllowed', ['statistic', 'pvalue'])
methodNotAllowed=MethodNotAllowed("D'Agostino not works!","D'Agostino not works!")

if len(data_y)!=0:
    #считаем нормальность распределения
    label="None"
    if len(data_y)>=3:
        ResShapiro=shapiro(data_y)
    else:
        ResDAgostino=methodNotAllowed
    if len(data_y)>=20:
        ResDAgostino=normaltest(data_y)
    else:
        ResDAgostino=methodNotAllowed
    #line=str(len(data_y))+";"+str(label)+";"+str(ResShapiro.statistic)+";"+str(ResShapiro.pvalue)+";"+str(ResDAgostino.statistic)+";"+str(ResDAgostino.pvalue)
    #считаем дисперсию и стандартное отклонение
    line=str(np.var(data_y))+";"+str(np.std(data_y))+";"+str(max(data_y)-min(data_y))
    line=line+'\n'
print("FOR Y")
print("ResShapiro.statistic    = " + str(ResShapiro.statistic))     # Должно к 1 стремиться
print("ResShapiro.pvalue       = " + str(ResShapiro.pvalue))        # Значение p для проверки гипотезы
print("ResDAgostino.statistic  = " + str(ResDAgostino.statistic))   # Должно к 1 стремиться
print("ResDAgostino.pvalue     = " + str(ResDAgostino.pvalue))        # Значение p для проверки гипотезы


if len(data_x)!=0:
    #считаем нормальность распределения
    label="None"
    if len(data_x)>=3:
        ResShapiro=shapiro(data_x)
    else:
        ResDAgostino=methodNotAllowed
    if len(data_x)>=20:
        ResDAgostino=normaltest(data_x)
    else:
        ResDAgostino=methodNotAllowed
    #line=str(len(data_y))+";"+str(label)+";"+str(ResShapiro.statistic)+";"+str(ResShapiro.pvalue)+";"+str(ResDAgostino.statistic)+";"+str(ResDAgostino.pvalue)
    #считаем дисперсию и стандартное отклонение
    line=str(np.var(data_x))+";"+str(np.std(data_x))+";"+str(max(data_x)-min(data_x))
    line=line+'\n'

print("FOR X")
print("ResShapiro.statistic    = " + str(ResShapiro.statistic))     # Должно к 1 стремиться
print("ResShapiro.pvalue       = " + str(ResShapiro.pvalue))        # Значение p для проверки гипотезы
print("ResDAgostino.statistic  = " + str(ResDAgostino.statistic))   # Должно к 1 стремиться
print("ResDAgostino.pvalue     = "+str(ResDAgostino.pvalue))        # Значение p для проверки гипотезы
