import socket

print ('Started the server...\nWaiting for filename from client')

s = socket.socket()            #Creating socket
host = ""
port = 60001

s.bind((host, port))		#Binding socket to (host,port)
s.listen(5)

conn, addr = s.accept()
while (1):				
    filename = conn.recv(1024).decode('ASCII')       #Receive the data from socket
    if(filename=='EXIT'):			#Exit if q is pressed
        print ('Exiting...')
        break
    print('Requested file: %s' % filename)
    try:
        filename = "Data/" + filename
        f = open(filename,'rb')		#opening file
        l = f.read(1024)
        while (l):
           conn.send(l)             #Send after read
           l = f.read(1024)         #Read the next 1024 bits
        conn.send(b"EOF")
        f.close()
    except:
        print ('Wrong file requested, informing client...')       #if random file was requested (error handling)
        conn.send(b'ERROR')
        continue
    print('Done sending')
conn.close() #Close connection
s.close() #Close socket
print ('Server closed')
