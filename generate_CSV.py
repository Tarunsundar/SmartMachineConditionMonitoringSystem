import serial
from datetime import datetime
import csv

arduino_port = "COM4" #serial port of Arduino on windows
baud = 115200 #arduino nicla sense me runs at 115200 baud
fileName="sensor_readings.csv" #name of the CSV file generated


now = datetime.now() #finding time now using a python class
issueTimeStamp = now.strftime("%d") #converting the time object to a string
fileName="sensor_readings_" +issueTimeStamp+ ".csv" #name of the CSV file generated

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)


file = open(fileName, "w")

print("Created file")

getData= ser.readline()
dataString = getData.decode('utf-8')
data=dataString[0:][:-2]
print(data)

readings = data.split(",")
print(readings)

samples = 100 #how many samples to collect
print_labels = False
line = 0 #start at 0 because our header is 0 (not real data)
sensor_data = [] #store data

# collect the samples
while line <= samples:
    now = datetime.now()
    timeStamp = now.strftime("%m/%d/%Y,%H:%M:%S")
    print(timeStamp)
    sensor_data.append(timeStamp)
    getData=ser.readline()
    dataString = getData.decode('utf-8')
    data=dataString[0:][:-2]
    print(data)

    readings = data.split(",")
    print(readings)

    sensor_data.append(readings)
    print(sensor_data)

    line = line+1

# create the CSV
with open(fileName, 'w', encoding='UTF8', newline='') as f:
    writer = csv.writer(f)
    writer.writerows(sensor_data)

print("Data collection complete!")
file.close()