#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;  // sockaddr_in - references elements of the socket address. "in" for internet
    int opt = 1, fp;
    int addrlen = sizeof(address);
    char buffer[1025] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)  // creates socket, SOCK_STREAM is for TCP. SOCK_DGRAM for UDP
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // This is to lose the pesky "Address already in use" error message
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                                                  &opt, sizeof(opt))) // SOL_SOCKET is the socket layer itself
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;  // Address family. For IPv6, it's AF_INET6. 29 others exist like AF_UNIX etc. 
    address.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP address - listens from all interfaces.
    address.sin_port = htons( PORT );    // Server port to open. Htons converts to Big Endian - Left to Right. RTL is Little Endian

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Port bind is done. You want to wait for incoming connections and handle them in some way.
    // The process is two step: first you listen(), then you accept()
    if (listen(server_fd, 3) < 0) // 3 is the maximum size of queue - connections you haven't accepted
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // returns a brand new socket file descriptor to use for this single accepted connection. Once done, use send and recv
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    char* filename = (char*)calloc(1024, sizeof(char));   //dynamically allocating memory
    valread = read(new_socket, filename, 1024);        //reads filename
    while(strcmp(filename,"EXIT")!=0){
        int fp=open(filename,O_RDONLY);			//opens file in read-only format								 
        if(fp<0){            //error handling
            perror("An error was encountered");
            send(new_socket, "ERROR", 5, 0);
            valread = read(new_socket, filename, 1024);
            continue;
        }
        valread = read(fp, buffer, 1024);      //reading contents of file
        buffer[valread] = '\0';
        if(valread<0)
            close(fp),perror("Read failed"),exit(1);

        printf("Sending file %s\n", filename);
        while(1){                                    //Read and send contents of file 1024 bits at a time
            send(new_socket, buffer, strlen(buffer), 0);          
            valread = read(fp, buffer, 1024);                
            buffer[valread] = '\0';
            if(valread<0)
                close(fp),perror("Read failed"),exit(1);
            if(valread==0)
                break;
        }
        // use sendto() and recvfrom() for DGRAM
        printf("File sent\n");

        filename = (char*)calloc(1024, sizeof(char));
        valread = read(new_socket, filename, 1024);
        close(fp);					//Close the file pointer
    }


    return 0;
}
