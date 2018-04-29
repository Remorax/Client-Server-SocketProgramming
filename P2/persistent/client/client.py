import socket                   

s = socket.socket()
host = ""
port = 60001
s.connect((host, port))
while (1):
    filename = input('Enter filename: (Press q to quit) ')      #Asking user to enter filename
    if(filename=='q'):               #Exiting if user enters q
        s.send(b'EXIT')
        break
    s.send(filename.encode('ASCII'))	#Send filename
    data = s.recv(1024)                        
    if(data==b'ERROR'):
        print ('Error: file does not exist')
        continue
    with open(filename, 'wb') as f:          #Opening file named filename
        print ('File %s opened'% filename)
        print('receiving data...')
        while True
            if "EOF" in data.decode('ASCII'):
                data = data.decode('ASCII').replace("EOF","")
                f.write(data.encode('ASCII'))
                break
            f.write(data)   # write data to a file
            data = s.recv(1024)    #Receive next 1024 bits from file
            
    f.close()       #Close file
    print('Successfully downloaded the file')

s.close()   #Close socket
print('Socket closed')

print ('All files transferred successfully: exiting')
