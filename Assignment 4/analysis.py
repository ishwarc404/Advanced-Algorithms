import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


colours = [ "blue","green","red","cyan","magenta","yellow","black","white"]
df = pd.read_csv("Results.csv")
numdf = pd.DataFrame()
numdf["Numbers"] = df["Numbers"]
df = df.drop(columns=["Unnamed: 0"]) #dropping the initial indexing column
df = df.drop(columns=["Numbers"]) #dropping the initial indexing column


#for the time readings
# for i in range(400,410):
#     df[str(i)] = df[str(i)].replace(0,df.mode()[str(i)][0])
#     plt.plot(numdf["Numbers"],df[str(i)]) 

# plt.show()

#let's get the means
means = df.mean(axis=0)
# iterations = [i for i in range(400,410)]
iterations = [i for i in range(1000,1100)]
plt.plot(iterations,means)
plt.show()