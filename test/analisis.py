#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Sep 27 19:31:28 2017

@author: marcos
"""
import datetime
import numpy as np
import matplotlib.pyplot as plt

plt.close('all')
def strpdelta(s):
    hr, minu, sec, msec, frac = map(float, s.split(':'))
    msec += frac
    return datetime.timedelta(hours=hr, minutes=minu, seconds=sec, milliseconds = msec)


strpdelta_np = np.frompyfunc(strpdelta, 1, 1)

dt =[('nombre','S10'),('tiempo','S25'),('cola','int'),
     ('colaA','int'),('colaB','int'),('colaC','int'),('encargos','int')]
data_inv = np.genfromtxt('inventario.out', delimiter=',' ,dtype =dt)

tiempo = np.zeros(data_inv.size, dtype='timedelta64[ms]')
cola   = np.zeros(data_inv.size)
colaA  = np.zeros(data_inv.size)
encargos = np.zeros(data_inv.size)

for i,t in enumerate(data_inv):
  #print(t[1].split(':'))  
  tiempo[i] = strpdelta_np(t[1].decode("utf-8"))
  cola[i]   = t[2]
  colaA[i]  = t[3]
  encargos[i] = t[6]
  
#plt.plot(tiempo/1e6,cola)
#plt.plot(tiempo/1e6,colaA,'g--')
plt.plot(tiempo,encargos,'r-')

  
 