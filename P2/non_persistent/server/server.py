import socket

print ('Started the server...\n Waiting for filename from client')

port = 60001

while (1):
    s = socket.socket()       #Creating a new socket every iteration
    host = ""
    s.bind((host, port))        #binds socket to address
    s.listen(1)			#Listen for connections made to the socket
    conn, addr = s.accept()
    filename = conn.recv(1024).decode('ASCII')   #Receive filename from client
    print('Requested file: %s', filename)
    if(filename=='EXIT'):                   #When q is pressed in client script
        break
    try:
        filename = "Data/" + filename
        f = open(filename,'rb')    #opening file
        l = f.read(1024)
        while (l):
           conn.send(l)                         #send 1024 bits at a time
           print('Sent ',l.decode('ASCII'))
           l = f.read(1024)   #Read 1024 bits from file
        f.close()
    except:
        print ('Wrong file requested, informing client...')
        conn.send(b'ERROR')
        port+=1
        continue
    print('Done sending')
    conn.close() #Close connection
    s.close() #Close socket
    port += 1

print ('Server closed')
