import httplib

def light_on():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/light/1")
    r1 = conn.getresponse()
    print r1.read()

def light_off():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/light/0")
    r1 = conn.getresponse()
    print r1.read()

def fan_on():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/fan/1")
    r1 = conn.getresponse()
    print r1.read()

def fan_off():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/light/0")
    r1 = conn.getresponse()
    print r1.read()

def door_lock():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/door/1")
    r1 = conn.getresponse()
    print r1.read()
    
def door_unlock():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/door/0")
    r1 = conn.getresponse()
    print r1.read()

def door_check():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/door/check/1")
    r1 = conn.getresponse()
    print r1.read()

def temp_check():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/temp/check/1")
    r1 = conn.getresponse()
    print r1.read()

def humid_check():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/humid/check/1")
    r1 = conn.getresponse()
    print r1.read()

def pir_on():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/pir/1")
    r1 = conn.getresponse()
    print r1.read()

def pir_off():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/pir/0")
    r1 = conn.getresponse()
    print r1.read()

def temp_on():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/temp/1")
    r1 = conn.getresponse()
    print r1.read()

def temp_off():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/temp/0")
    r1 = conn.getresponse()
    print r1.read()

def notification():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/notification")
    r1 = conn.getresponse()
    print r1.read()
    
