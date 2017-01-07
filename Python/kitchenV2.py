import httplib

def light_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV2_IP'])
    conn.request("GET", "/kitchen/light/1")
    r1 = conn.getresponse()
    print r1.read()

def light_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV2_IP'])
    conn.request("GET", "/kitchen/light/0")
    r1 = conn.getresponse()
    print r1.read()

def vibration_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV2_IP'])
    conn.request("GET", "/kitchen/vibration/1")
    r1 = conn.getresponse()
    print r1.read()

def vibration_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV2_IP'])
    conn.request("GET", "/kitchen/vibration/0")
    r1 = conn.getresponse()
    print r1.read()

def door_lock():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV2_IP'])
    conn.request("GET", "/kitchen/door/0")
    r1 = conn.getresponse()
    print r1.read()
    
def door_unlock():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV2_IP'])
    conn.request("GET", "/kitchen/door/1")
    r1 = conn.getresponse()
    print r1.read()

def door_check():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV2_IP'])
    conn.request("GET", "/kitchen/door/check/1")
    r1 = conn.getresponse()
    print r1.read()

def smoke_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV2_IP'])
    conn.request("GET", "/kitchen/smoke/1")
    r1 = conn.getresponse()
    print r1.read()

def smoke_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV2_IP'])
    conn.request("GET", "/kitchen/smoke/0")
    r1 = conn.getresponse()
    print r1.read()

def leak_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV2_IP'])
    conn.request("GET", "/kitchen/leak/1")
    r1 = conn.getresponse()
    print r1.read()

def leak_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV2_IP'])
    conn.request("GET", "/kitchen/leak/0")
    r1 = conn.getresponse()
    print r1.read()

def notification():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV2_IP'])
    conn.request("GET", "/kitchen/notification")
    r1 = conn.getresponse()
    r1=r1.read()
    conn = httplib.HTTPConnection(dataList['gardenV1_part2_IP'])
    conn.request("GET", "/kitchen/notification")
    r2 = conn.getresponse()
    r2=r2.read()
    print r1+"&"+r2
    
