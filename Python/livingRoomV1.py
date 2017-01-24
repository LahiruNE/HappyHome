import urllib
 
def sendSMS(uname, hashCode, numbers, sender, message):
    data =  urllib.parse.urlencode({'username': uname, 'hash': hashCode, 'numbers': numbers,
        'message' : message, 'sender': sender})
    data = data.encode('utf-8')
    request = urllib.request.Request("http://api.txtlocal.com/send/?")
    f = urllib.request.urlopen(request, data)
    fr = f.read()
    return(fr)
 
resp =  sendSMS('hirunikegalle@gmail.com', 'ede8a6b83f7afcffe0828ce3b40e0943a3c298a9', '+946482041',
    'Jims Autos', 'This is your message')
print (resp)

#ede8a6b83f7afcffe0828ce3b40e0943a3c298a9 
