import numpy as np
import matplotlib.pyplot as plt
import os

'''
Change datacone to whatever folder you're storing your processed data in
Change dataproccone to another folder to store the procesed txt files
When saving, save as .txt file in your data folder
'''

#remove first two lines from txt files, only run once when all data is collected 
for filename in os.listdir('./SingleGanglion/datacone'):
    if filename not in os.listdir('./SingleGanglion/dataproccone') and filename[-4:]=='.txt':
        with open('./SingleGanglion/datacone/'+filename, 'r') as fin:
            data = fin.read().splitlines(True)
        with open('./SingleGanglion/dataproccone/'+filename, 'w') as fout:
            fout.writelines(data[2:])

'''
This for loop below will go through all your files and output the firing rate into rates
Currently setup for graphing stimulus strength vs firing rate
Change shape and format of rates matrix to adjust for different purposes
'''

rates = np.zeros((len(os.listdir('./SingleGanglion/dataproccone')),2))

for j, filename in enumerate(os.listdir('./SingleGanglion/dataproccone')):
    if filename[-4:]=='.txt':
        f = np.loadtxt('./SingleGanglion/dataproccone/'+filename)
        x = f[:,0]
        y = f[:,1]

        count = 0

        for i in range(len(x)):
            if x[i]>=400 and x[i]<=1200: # can adjust these values to whatever range you want to look at
                if y[i]>y[i-1] and y[i]>y[i+1] and y[i]>10:
                    count +=1
        rates[j,0]= float(filename[:-10]) #may need to change this line depending on how you name your files
        rates[j,1]= count/0.8 #make sure the denominator is (upper range-lower range)/1000
    
rates = np.sort(rates, axis=0) #makes sure they're in the correct ordering for graphing

'''
can also use np.savetxt(filename, rates) to save rates as a txt file for whatever purpose
'''

plt.plot(rates[1:,0], rates[1:,1]) # graph stimulus strength vs firing rate
plt.show()