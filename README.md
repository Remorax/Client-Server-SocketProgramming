# Socket Programming

This repository contains a sample code to basic client-server connections, done as part of Assignment 1 of the Computer Networks course at IIIT, Hyderabad.

For Problem 1:

1. Go to folder P1
2. Open one Terminal tab in client folder and the other in server folder
3. Run gcc -o client client.c in client tab and gcc -o server server.c in server tab
4. Run ./server followed by ./client
5. It shows an error for rp.txt because it does not exist but successfully downloads file1.txt, file2.txt and file3.txt

For Problem 2:
1. Go to folder P2
2. The Persistent folder contains the code for the persistent connection and vice versa.
3. Open one Terminal tab in client folder and the other in server folder
4. Run python3 client.c in client tab and python3 server.c in server tab
5. Enter the names of the input files. They're downloaded successfully and for random non existant file, it gives an error.
6. It shows an error for rp.txt because it does not exist but successfully downloads file1.txt, file2.txt and file3.txt
7. Follow the same procedure for non persistent connections. It prints the time at the end.

Non persistent connection takes slightly more time than persistent connections, this could be due to the opening of a new socket for every file.
