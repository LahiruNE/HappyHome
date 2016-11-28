import httplib


dataList={}

with open("../log/log.txt") as log:
    for line in log:
        if line!="":
            value=line.split("=")[1].split('\n')[0].split("'")[1]
            key=line.split("=")[0]
            dataList[key]=value

conn = httplib.HTTPConnection(dataList['LivingRoomV1_IP'])
conn.request("GET", "/living/notification")
r1 = conn.getresponse()
print r1.read()
