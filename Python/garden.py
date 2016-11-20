import httplib

def light_on():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/garden/light/1")
    r1 = conn.getresponse()
    print r1.read()

def light_off():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/garden/light/0")
    r1 = conn.getresponse()
    print r1.read()

def tankvalve_on():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/garden/tankvalve/1")
    r1 = conn.getresponse()
    print r1.read()

def tankvalve_off():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/garden/tankvalve/0")
    r1 = conn.getresponse()
    print r1.read()
