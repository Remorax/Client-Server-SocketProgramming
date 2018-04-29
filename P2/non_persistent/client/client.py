import socket                   


port = 60001
while (1):
	s = socket.socket()        #Creating a new socket every iteration
	host = ""
	s.connect((host, port))       #Connecting to remote socket at (host, port)
	filename = input('Enter filename: (Press q to quit) ')	#Asking user to enter filename
	if(filename=='q'):
		s.send(b'EXIT')
		break
	s.send(filename.encode('ASCII'))		#Send filename to server
	data = s.recv(1024)						#Receive buffer 1024 bits at a time
	if(data==b'ERROR'):						#Error handling in case file does not exist
		print ('Error: file does not exist')
		port+=1                          
		continue
	with open(filename, 'wb') as f:			#Opening file
	    print ('File %s opened'% filename)
	    while True:
	        print('receiving data...')
	        
	        print('data=%s' % data.decode('ASCII'))
	        if not data:
	            break
	        # write data to a file
	        f.write(data)
	        data = s.recv(1024)		#Receiving the next 1024 bits of data

	f.close()	#Close connection
	print('Successfully downloaded the file')
	s.close()	#Close socket
	print('Socket closed')
	port += 1

print ('All files transferred successfully: exiting')
