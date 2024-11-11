'''
31.07.2024 Программа проходит по данным в папке, получает параметры из JSON файла и проверяет их на нормальность критериями Шапиро-Уилка и Д'Агостино
По результатам формируется файл-таблица с данными вида:
Число элементов (в выборке);Метка;Результат Шапиро;P-значение Шапиро;Результат Д'Агостино;P-значение Д'Агостино;Дисперсия;Стандартное отклонение;Размах

В папке должны находится файлы с JSON заголовком. 
В заголовке в качестве параметров есть:
1. Метка для идентификации файлов (например число ловушек)
2. Параметр с массивом данных для проверки на нормальность
https://habr.com/ru/companies/otus/articles/671322/
Критерий Шапиро-Уилка. URL: https://studfile.net/preview/4241954/page:7/#17
Критерий Д’Агостино. URL: https://studfile.net/preview/16712870/page:25/
-------------------------------------------------------
@param folderName - папка с данными
@param folderSaveName - папка в которую нужно сохранить изображение
@param fileSaveName - имя файла для сохранения
@param jsonParamName - какой параметр из JSON брать для проверки
@param paramFalseValue - значение параметра при котором показание не рассматривается (NULL - отсутствие)
@param labelForParam - метка для именования результатов (название переменной в JSON, например число ловушек)
@param firstFileString - первая строка для записи в файл (Заголовок)
'''
from scipy.stats import shapiro
from scipy.stats import normaltest
import math
import os
import json
import numpy as np
#Получаем данные
fInput=open("input.txt","r")
folderName=fInput.readline().rstrip('\r\n')
folderSaveName=fInput.readline().rstrip('\r\n')
fileSaveName=fInput.readline().rstrip('\r\n')
jsonParamName=fInput.readline().rstrip('\r\n')
paramFalseValue=fInput.readline().rstrip('\r\n')
jsonParamFalse=-1
if paramFalseValue!="NULL":
    jsonParamFalse=float(paramFalseValue)
labelForParam=fInput.readline().rstrip('\r\n')
firstFileString=fInput.readline().rstrip('\r\n')
#-- класс для неприменимости метода
from collections import namedtuple
MethodNotAllowed = namedtuple('MethodNotAllowed', ['statistic', 'pvalue'])
methodNotAllowed=MethodNotAllowed("D'Agostino not works!","D'Agostino not works!")

fout=open(folderSaveName+fileSaveName,"w")
fout.write(firstFileString+'\n')
for root, dirs, files in os.walk(folderName):
    for filename in files:
        f=open(folderName+filename)
        jsonData=json.loads(f.readline())
        if jsonParamName in jsonData:
            data=[]
            if paramFalseValue=="NULL":
                data=jsonData[jsonParamName]
            else:
                for x in jsonData[jsonParamName]:
                    if x!=jsonParamFalse:
                        data.append(x)
            line=""
            if len(data)!=0:
                #считаем нормальность распределения
                label="None"
                if labelForParam in jsonData:
                    label=jsonData[labelForParam]
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
            fout.write(line)
        f.close()
fout.close()


