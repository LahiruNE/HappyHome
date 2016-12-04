import httplib

def light_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
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
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
    conn.request("GET", "/kitchen/light/0")
    r1 = conn.getresponse()
    print r1.read()

def fan_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
    conn.request("GET", "/kitchen/fan/1")
    r1 = conn.getresponse()
    print r1.read()

def fan_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
    conn.request("GET", "/kitchen/fan/0")
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
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
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
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
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
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
    conn.request("GET", "/kitchen/door/check/1")
    r1 = conn.getresponse()
    print r1.read()

def temp_check():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
    conn.request("GET", "/kitchen/temp/check/1")
    r1 = conn.getresponse()
    print r1.read()

def humid_check():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
    conn.request("GET", "/kitchen/humid/check/1")
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
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
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
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
    conn.request("GET", "/kitchen/smoke/0")
    r1 = conn.getresponse()
    print r1.read()

def temp_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
    conn.request("GET", "/kitchen/temp/1")
    r1 = conn.getresponse()
    print r1.read()

def temp_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
    conn.request("GET", "/kitchen/temp/0")
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
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
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
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
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
    
    conn = httplib.HTTPConnection(dataList['KitchenV1_IP'])
    conn.request("GET", "/kitchen/notification")
    r1 = conn.getresponse()
    print r1.read()
    
