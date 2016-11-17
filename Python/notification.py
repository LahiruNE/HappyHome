import httplib

def living_pir():
    conn = httplib.HTTPConnection("192.168.43.231")
    conn.request("GET", "/living/notification")
    r1 = conn.getresponse()
    print r1.read()
