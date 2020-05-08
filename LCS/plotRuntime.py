import matplotlib.pyplot as plt
import numpy as np
nrows=1
ncolumn =3
fig, multi = plt.subplots(nrows,ncolumn)



x,y,z = np.loadtxt('run_time.txt',delimiter=',',unpack=True,dtype=np.float)
multi[0].plot(x,z,label="without memory(recursively)")
multi[0].plot(x,y,label="with memory(memonic)")



x,y = np.loadtxt('run_time_memonic_with_para.txt',delimiter=',',unpack=True,dtype=np.float)
temp={}
for i,j in zip(x,y):
    temp[i]= j
newy=[]
newx=[]
for ij in sorted(temp.keys()):
    newy.append(temp[ij])
    newx.append(ij) 


multi[1].plot(newx,newy,label="with memory(parallization)")
multi[1].set_title("Memonic with parallelization")


x,y = np.loadtxt('run_time1.txt',delimiter=',',unpack=True,dtype=np.float)
multi[2].plot(x,y,label="with memory(memonic)")
multi[2].set_title("Memonic with out parallelization")
plt.legend()
plt.show()

