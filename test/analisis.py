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
colaB  = np.zeros(data_inv.size)
colaC  = np.zeros(data_inv.size)
encargos = np.zeros(data_inv.size)

for i,t in enumerate(data_inv):
  #print(t[1].split(':'))  
  tiempo[i]   = strpdelta_np(t[1].decode("utf-8"))
  cola[i]     = t[2]
  colaA[i]    = t[3]
  colaB[i]    = t[4]
  colaC[i]    = t[5]
  encargos[i] = t[6]
  
plt.figure()
plt.plot(tiempo,cola)
plt.title("Evolucion del tamano de la cola de productos")
plt.xlabel("tiempo")
plt.ylabel("size(cola)")

plt.figure()
plt.plot(tiempo,colaA,'g--')
plt.title("Evolucion de la cola del insumo A")
plt.xlabel("tiempo")
plt.ylabel("size(cola A)")

plt.figure()
plt.plot(tiempo,colaB,'g--')
plt.title("Evolucion de la cola del insumo B")
plt.xlabel("tiempo")
plt.ylabel("size(cola B)")

plt.figure()
plt.plot(tiempo,colaC,'g--')
plt.title("Evolucion de la cola del insumo C")
plt.xlabel("tiempo")
plt.ylabel("size(cola C)")

plt.figure()
plt.plot(tiempo,encargos,'r-')
plt.title("Evolucion de la # encargos")
plt.xlabel("tiempo")
plt.ylabel("encargos")

dt =[('nombre','S15'),('tiempo','S25'),('vencidas','int')]
data_inv = np.genfromtxt('controldecalidad.out', delimiter=',' ,dtype =dt)

tiempo = np.zeros(data_inv.size, dtype='timedelta64[ms]')
vencidas   = np.zeros(data_inv.size)

for i,t in enumerate(data_inv):
  #print(t[1].split(':'))  
  tiempo[i]   = strpdelta_np(t[1].decode("utf-8"))
  vencidas[i] = t[2]
  
plt.figure()
plt.plot(tiempo,vencidas)
plt.title("Evolucion de la cantidad de unidades vencidas")
plt.xlabel("tiempo")
plt.ylabel("vencidas")

dt =[('nombre','S15'),('tiempo','S25'),('costo','int')]
data_inv = np.genfromtxt('controldeinventario.out', delimiter=',' ,dtype =dt)

tiempo = np.zeros(data_inv.size, dtype='timedelta64[ms]')
costo   = np.zeros(data_inv.size)

for i,t in enumerate(data_inv):
  #print(t[1].split(':'))  
  tiempo[i]   = strpdelta_np(t[1].decode("utf-8"))
  costo[i] = t[2]
  
plt.figure()
plt.plot(tiempo,costo)
plt.title("Evolucion del costo de reposicion de inventario")
plt.xlabel("tiempo")
plt.ylabel("costo [$]")