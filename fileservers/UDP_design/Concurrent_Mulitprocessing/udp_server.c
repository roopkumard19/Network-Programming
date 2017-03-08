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


int main(int argc, char *argv[]) 			// The argc and argv are used to get the command line arguments.
{

/* Declaration of variables */

int sock;
int join,list;
struct sockaddr_in server;
struct sockaddr_in client;
int length,number;
signed int count;
int data_read,data_write;
int receive;
char data_client[1024]; 
char buffer[1024];
char dat[255];
FILE *iterative;

if (argc<4)
{
printf("port or filename not provided\n");
}

printf("filename 1 is : %s\n", argv[2]);
printf("filename 2 is : %s\n", argv[3]);

/*Socket creation*/

sock=socket(AF_INET, SOCK_DGRAM, 0);			// creating a socket with arguments such as domain,connection type (TCP), protocol
if(sock==-1)
{
printf("Socket is not created");		 	// Error when socket not created
exit(-1);
}
printf("socket created\n");

/* Defining the value for the server structure*/

server.sin_family= AF_INET;                             // Assigning the Family name AF_INET 
server.sin_port=htons(atoi(argv[1]));			// Assigning the port number for the server 
server.sin_addr.s_addr=INADDR_ANY;			// IP address is not assigned to any specific socket.
bzero(&server.sin_zero, 8);


/* Binding of socket*/

length=sizeof(struct sockaddr_in);
join=bind(sock, (struct sockaddr *)&server, length);// passing arguments such as sd, server struct & length of struct to the bind function 
if (join==-1)
{
printf("Bind has not happened\n");			// error when bind does not happend
exit(-1);
}
printf("bind done\n");

bzero(buffer, 1024);

if((recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&client, &length))<0)
{
printf("File cannot be written\n");
}
printf("Client: %s\n",buffer);

int i;
int pid;
pid=fork();
printf("the child pid is %d\n",pid);


if(pid<0)
{
printf("Error in fork %d\n",pid);

}
if(pid>0)
{
printf("\nthe parent pid is %d \n", getpid());

}


while(pid==0)
{


if((sendto(sock,argv[2],sizeof(argv[2]),0,(struct sockaddr *)&client, length))<0)
{
printf("File cannot be written\n");
}

if((recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&client, &length))<0)
{
printf("File cannot be written\n");
}

if((sendto(sock,argv[3],sizeof(argv[3]),0,(struct sockaddr *)&client, length))<0)
{
printf("File cannot be written\n");
}

/* Receiving request from the client */

receive= recvfrom(sock, data_client, 1024, 0, (struct sockaddr *)&client, &length);
printf("The file asked by the client:%s\n",data_client);
strcpy(dat,data_client);
//printf("dat= %s\n", dat);

/* Calling of the file and opening */

if(strcmp(dat,argv[2])>0)
{
printf("ok\n");
iterative = fopen("File.txt","r+");
if(iterative==NULL)
{
printf("File not found\n");
return(0);
}
printf("File found\n");
}

else if(strcmp(dat,argv[3])>0)
{
iterative = fopen("Fil2.txt","r+");
if(iterative==NULL)
{
printf("File not found\n");
return(0);
}
printf("File found\n");
}


/* Reading the data from the file and moving to the buffer before being sent to the client */

data_read= fread(buffer,1,sizeof(buffer),iterative);
if(data_read<0)
{
printf("File Cannot be read\n");
}
while(data_read>0)
{


/* Sending data back to client */

data_write=sendto(sock,buffer,1024,0,(struct sockaddr *)&client, length);
if(data_write<=0)
{
printf("File cannot be written\n");
}
data_read=data_read-data_write;

}
printf("The process is complete.\n ");
}

bzero(data_client,1024);
return 0;

}


