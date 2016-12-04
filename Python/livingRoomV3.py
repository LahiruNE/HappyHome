import httplib

def light1_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV3_IP'])
    conn.request("GET", "/living/light1/1")
    r1 = conn.getresponse()
    print r1.read()

def light1_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV3_IP'])
    conn.request("GET", "/living/light1/0")
    r1 = conn.getresponse()
    print r1.read()

def light2_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV3_IP'])
    conn.request("GET", "/living/light2/1")
    r1 = conn.getresponse()
    print r1.read()

def light2_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV3_IP'])
    conn.request("GET", "/living/light2/0")
    r1 = conn.getresponse()
    print r1.read()

def light3_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV3_IP'])
    conn.request("GET", "/living/light3/1")
    r1 = conn.getresponse()
    print r1.read()

def light3_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV3_IP'])
    conn.request("GET", "/living/light3/0")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV3_IP'])
    conn.request("GET", "/living/fan/1")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV3_IP'])
    conn.request("GET", "/living/fan/0")
    r1 = conn.getresponse()
    print r1.read()

