/* Declaring header files*/

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/time.h>

int main(int argc, char *argv[]) 			// The argc and argv are used to get the command line arguments.
{

/* Declaration of variables */

int sock,new_sock;
int join,list;
struct sockaddr_in server;
struct sockaddr_in client;
int length,number;
signed int count;
int data_read,data_write;
int receive;
char data_client[1024];
char req_file[1024]; 
char buffer[1024];
char dat[255];
char get[3],http[9];
char file[1024], header[1024];
char newfile[1024];
char host[1024]; 
char dummy[1024];
char send_response[1024];
char get_response[1024];
FILE *iterative;
DIR *directory;
struct timeval t1, t2;
if (argc<3)
{
printf("port not provided\n");
}

if((directory = opendir(argv[1]))==NULL)
{
printf("Unable to open directory\n");
exit(0);
}
else {printf("Directory opened is : %s\n",argv[1]);}

/*Socket creation*/

sock=socket(AF_INET, SOCK_STREAM, 0);			// creating a socket with arguments such as domain,connection type (TCP), protocol
if(sock==-1)
{
printf("Socket is not created");		 	// Error when socket not created
exit(-1);
}

printf("Socket created\n");

/* Defining the value for the server structure*/

server.sin_family= AF_INET;                             // Assigning the Family name AF_INET 
server.sin_port=htons(8080);			// Assigning the port number for the server 
server.sin_addr.s_addr=INADDR_ANY;			// IP address is not assigned to any specific socket.
bzero(&server.sin_zero, 8);


/* Binding of socket*/

length=sizeof(struct sockaddr_in);
join=bind(sock, (struct sockaddr *)&server, length);// passing arguments such as sd, server struct & length of struct to the bind function 
if (join==-1)
{
printf("Bind has not happened");			// error when bind does not happend
exit(-1);
}

printf("bind done\n");

for(;;)
{

/*Placing the socket in listening mode */ 

list=listen(sock,5);					// passing arguments sd, and queue to the listen function
if (list==-1)
{
printf("Listen has not happened");			// Error when listen function fails
exit(-1);
}

printf("listening..\n");

/* Accepting a connection and creation of new socket */


new_sock=accept(sock,(struct sockaddr *)&client, &length);	 // Connection establishment and creation if new socket.
gettimeofday(&t1,NULL);
if (new_sock==-1)
{
printf("Unable to accept the connection");			// Error when connection is not established.
exit(-1);
}

printf("accepted\n");
if(read(new_sock,buffer,1024)<0)
{
printf("name cannot be read\n");
}
printf("buffer: %s\n",buffer);
sscanf(buffer, "%s %s %s \n%s %s",get,file,http,dummy,host); //storing the values into the buffer that will send/receive data from client
printf("host: %s\n",host);
strcpy(newfile,file+1);
sprintf(req_file,"%s/%s",argv[1],newfile);
printf("Req file is %s\n",req_file);

if((iterative = fopen(req_file,"r"))==NULL)			// open the file
{
printf("Unable to fetch the file\n");

/*Error handling */

sprintf(send_response, "HTTP/1.1 404 Not Found\r\nContent-length: 85\r\nContent-Type: text/html\r\n\r\n<html><header><title>404 File not Found</title></header><body>404 File not Found</body></html>");
printf("send response %s\n",send_response);
if(write(new_sock,send_response, sizeof(send_response))<0)	// send back error data to the client when the file is not present with the server
{ 
printf("can't send s.\n");
exit(0);
}

}
else 
{
printf("file found\n");


bzero(buffer,1024);

data_read= fread(buffer,1,sizeof(buffer),iterative);		// Read the data from the file
if(data_read<0)
{
printf("File Cannot be read\n");
}
printf("data in file: %s\n",buffer);

fseek(iterative,0,SEEK_END);					// Know the size of the file
int file_size = ftell(iterative);
fseek(iterative,0,SEEK_SET);
printf("file size: %d\n",file_size);

/* Sending data back to client */
sprintf(get_response, "HTTP/1.1 200 OK\r\nContent-length: %d\r\nContent-Type: text/html\r\n\r\n",file_size);// HTML header is put in the buffer
     
printf("get response1: \n%s", get_response);
strcat(get_response, buffer);
printf("get response2: \n%s", get_response);
if(write(new_sock,get_response, sizeof(get_response))<0)			// The data in the file is sent to the client

{ 
printf("can't send s.\n");
}

else {printf("sent http header...\n");}
gettimeofday(&t2,NULL);
printf("The time taken to record and display data is ' %lu' microseconds\n",t2.tv_usec-t1.tv_usec);	// Calculate the time taken to respond.
}
close(new_sock);
printf("The process is complete.\n ");
bzero(data_client,1024);
printf("Enter next file\n ");

}
}
