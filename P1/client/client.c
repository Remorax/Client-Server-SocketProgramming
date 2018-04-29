// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

void requestFile(int sock, char* filename)
{
    char* buffer = (char*)malloc(sizeof(char)*1025);
    printf("Requesting %s...\n", filename);
    send(sock, filename, strlen(filename), 0);  // send filename.
    
    int valread = read( sock , buffer, 1024); // receive message back from server, into the buffer
    buffer[valread] = '\0';
    if(valread<0)
        free(buffer),perror("Read failed"),exit(1);  // error handling for read failure
    if(strcmp(buffer,"ERROR")==0){
        printf("Requested wrong file. Make request for another file\n"); //error handling for wrong file requested
        free(buffer);
        return;
    }
    int f = open(filename, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IXUSR); //opens the file
    while(1){
        write(f,buffer,valread); //writes buffer to file
        if(valread<1024){
            break;
        }
        valread = read( sock , buffer, 1024);   //reads contents into buffer
        buffer[valread] = '\0';
        if(valread<0)
            free(buffer),close(f),perror("Read failed"),exit(1);
    }
    close(f);   //close file descriptor
    free(buffer);
    printf("File downloaded\n");
    return;
}

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) //socket creation error
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr)); // to make sure the struct is empty. Essentially sets sin_zero as 0
                                                // which is meant to be, and rest is defined below

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Converts an IP address in numbers-and-dots notation into either a 
    // struct in_addr or a struct in6_addr depending on whether you specify AF_INET or AF_INET6.
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)  // connect to the server address
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    requestFile(sock, "file1.txt");   //requesting files
    requestFile(sock, "file2.txt");
    requestFile(sock, "assignment1.pdf");

    /* Request a non existant file */
    requestFile(sock, "rp.txt");

    requestFile(sock, "file3.txt");

    send(sock, "EXIT", 4, 0);
    return 0;
}
