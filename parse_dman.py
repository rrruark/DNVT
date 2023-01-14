#Differential Manchester Parser
#Robert Ruark
#2022

import pandas as pd
import matplotlib.pyplot as plt

columns = ["time", "amplitude"]
df = pd.read_csv("both_phones.csv", usecols=columns)
#df = pd.read_csv("CSV0.csv", usecols=columns)
#df = pd.read_csv("16k_lb_start_trunk.csv", usecols=columns)
#df = pd.read_csv("lb_starts_high.csv", usecols=columns)
#df = pd.read_csv("lb_powered_cb.csv", usecols=columns)
#df = pd.read_csv("cb.csv", usecols=columns)
#df = pd.read_csv("lb_long_start.csv", usecols=columns)

plt.plot(df.time, df.amplitude)
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.title('DNVT Start Transmission')
plt.xlim(-0.0002, 0.01)
#plt.show()

y = df.amplitude
vmid=2.5
state=0
print(y[0])
if(y[0]>vmid):
    state=1
    
times = []
state_time=0

for x in y:
    temp_val=0
    if(x>vmid):
        temp_val=1
    if(temp_val==state):
        state_time = state_time + 1
    else:
        state = temp_val
        times.append(state_time)
        state_time=0
        
#print(times)
plt.cla()
plt.hist(times, bins=range(min(times), max(times) + 1, 1))
plt.yscale('log')
#plt.show()

print(times)

#if(long) -> 1
#if(short) -> 0 then skip next

data = []
error = []
tmid= 9
short_count = 0

for value in times:
    if(value > tmid):
        #print("long")
        #print("1")
        data.append(1)
        short_count = 0
        if(short_count ==1):
            print("Warning: Possible Error")
    else:
        #print("short")
        if(short_count == 0):
            data.append(0)
            #print("0")
        short_count = short_count + 1
        if(short_count==2):
            short_count = 0
print(data)

index = range(len(data))

plt.cla()
plt.scatter(index,data)
#plt.show()

#test_data = [1,1,1,1,1,1,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1]
#print(test_data)
test_byte = 0
byte_ready=0
data_bytes = []

bit_index=0

for b in data:
    test_byte = test_byte | b
    #print("bit ",bit_index, "=",b, "running byte = ", test_byte)
    if(byte_ready): 
        data_bytes.append(test_byte)
        #print("Appending",test_byte)
        test_byte=0
        bit_index=0
        byte_ready=0
    else:
        if(bit_index<7):
            test_byte = test_byte << 1
            bit_index = bit_index + 1
    if(bit_index==7):
        byte_ready=1
        
print(data_bytes)