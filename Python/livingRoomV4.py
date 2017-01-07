import httplib

def light_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/light/1")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/light/0")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/fan/0")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/door/0")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/door/1")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/door/check/1")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/temp/check/1")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/humid/check/1")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/temp/1")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/temp/0")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/smoke/1")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/smoke/0")
    r1 = conn.getresponse()
    print r1.read()

def pir_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part2_IP'])
    conn.request("GET", "/living/pir/1")
    r1 = conn.getresponse()
    print r1.read()

def pir_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part2_IP'])
    conn.request("GET", "/living/pir/0")
    r1 = conn.getresponse()
    print r1.read()

def sound_on():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part2_IP'])
    conn.request("GET", "/living/sound/1")
    r1 = conn.getresponse()
    print r1.read()

def sound_off():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part2_IP'])
    conn.request("GET", "/living/sound/0")
    r1 = conn.getresponse()
    print r1.read()

def window_lock():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part2_IP'])
    conn.request("GET", "/living/window/0")
    r1 = conn.getresponse()
    print r1.read()
    
def window_unlock():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part2_IP'])
    conn.request("GET", "/living/window/1")
    r1 = conn.getresponse()
    print r1.read()

def window_check():
    dataList={}

    with open("../log/log.txt") as log:
        for line in log:
            if line!="":
                value=line.split("=")[1].split('\n')[0].split("'")[1]
                key=line.split("=")[0]
                dataList[key]=value
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part2_IP'])
    conn.request("GET", "/living/window/check/1")
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
    
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part1_IP'])
    conn.request("GET", "/living/notification")
    r1 = conn.getresponse()
    r1=r1.read()
    conn = httplib.HTTPConnection(dataList['LivingRoomV4_part2_IP'])
    conn.request("GET", "/living/notification")
    r2 = conn.getresponse()
    r2=r2.read()
    print r1+"&"+r2
