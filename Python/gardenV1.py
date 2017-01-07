import httplib

def light_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part1_IP'])
    conn.request("GET", "/garden/light/1")
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
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part1_IP'])
    conn.request("GET", "/garden/light/0")
    r1 = conn.getresponse()
    print r1.read()

def waterlevel_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part1_IP'])
    conn.request("GET", "/garden/waterlevel/1")
    r1 = conn.getresponse()
    print r1.read()

def waterlevel_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part1_IP'])
    conn.request("GET", "/garden/waterlevel/0")
    r1 = conn.getresponse()
    print r1.read()

def waterlevel_check():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part1_IP'])
    conn.request("GET", "/garden/waterlevel/check/1")
    r1 = conn.getresponse()
    print r1.read()

def rain_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part1_IP'])
    conn.request("GET", "/garden/rain/1")
    r1 = conn.getresponse()
    print r1.read()

def rain_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part1_IP'])
    conn.request("GET", "/garden/rain/0")
    r1 = conn.getresponse()
    print r1.read()

def tankvalve_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part1_IP'])
    conn.request("GET", "/garden/tankvalve/1")
    r1 = conn.getresponse()
    print r1.read()

def tankvalve_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part1_IP'])
    conn.request("GET", "/garden/tankvalve/0")
    r1 = conn.getresponse()
    print r1.read()

def tankvalve_check():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part1_IP'])
    conn.request("GET", "/garden/tankvalve/check/1")
    r1 = conn.getresponse()
    print r1.read()

def soilvalve_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part2_IP'])
    conn.request("GET", "/garden/soilvalve/1")
    r1 = conn.getresponse()
    print r1.read()

def soilvalve_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part2_IP'])
    conn.request("GET", "/garden/soilvalve/0")
    r1 = conn.getresponse()
    print r1.read()

def soilvalve_check():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part2_IP'])
    conn.request("GET", "/garden/soilvalve/check/1")
    r1 = conn.getresponse()
    print r1.read()

def soil_activate():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part2_IP'])
    conn.request("GET", "/garden/soil/1")
    r1 = conn.getresponse()
    print r1.read()

def soil_deactivate():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part2_IP'])
    conn.request("GET", "/garden/soil/0")
    r1 = conn.getresponse()
    print r1.read()

def moisture_check():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part2_IP'])
    conn.request("GET", "/garden/soil/check/1")
    r1 = conn.getresponse()
    print r1.read()

def photo_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part2_IP'])
    conn.request("GET", "/garden/photocell/1")
    r1 = conn.getresponse()
    print r1.read()

def photo_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part2_IP'])
    conn.request("GET", "/garden/photocell/0")
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
    
    conn = httplib.HTTPConnection(dataList['gardenV1_part1_IP'])
    conn.request("GET", "/garden/notification")
    r1 = conn.getresponse()
    r1=r1.read()
    conn = httplib.HTTPConnection(dataList['gardenV1_part2_IP'])
    conn.request("GET", "/garden/notification")
    r2 = conn.getresponse()
    r2=r2.read()
    print r1+"&"+r2
