import matplotlib.pyplot as plt
j=10000
for i in range(60):
    
    import subprocess
    subprocess.call(["g++", "kruskal_avl.cpp"])
    tmp=subprocess.call(["./a.out", str(j)])
    j+=10000

f1 = open('edges_avl.txt', 'r')
f2 = open('time_avl.txt', 'r')
list1=[]
list2=[]

for x in f1:
    list1.append(x)
f1.close()

for x in f2:
    list2.append(x)
f2.close()

for i in list1:
    data1 = i.split(" ")
for i in list2:
    data2 = i.split(" ")

data1.pop()
data2.pop()
data3=[]
data4=[]

for i in data1:
    data3.append(float(i))

for i in data2:
    data4.append(float(i))

    
    

print(data3)
print(data4)

plt.plot(data3,data4,'r',label='AVL')




j=10000
for i in range(60):
    
    import subprocess
    subprocess.call(["g++", "kruskal_veb.cpp"])
    tmp=subprocess.call(["./a.out", str(j)])
    j+=10000

f1 = open('edges_veb.txt', 'r')
f2 = open('time_veb.txt', 'r')
list1=[]
list2=[]

for x in f1:
    list1.append(x)
f1.close()

for x in f2:
    list2.append(x)
f2.close()

for i in list1:
    data1 = i.split(" ")
for i in list2:
    data2 = i.split(" ")

data1.pop()
data2.pop()
data3=[]
data4=[]

for i in data1:
    data3.append(float(i))

for i in data2:
    data4.append(float(i))

    
    

print(data3)
print(data4)

plt.plot(data3,data4,'b', label='van Emde Boas')
plt.xlabel('NUMBER OF EDGES')
plt.ylabel('TIME OF EXECUTION (MILLISECONDS)')
legend = plt.legend(loc='upper center')



plt.show()



