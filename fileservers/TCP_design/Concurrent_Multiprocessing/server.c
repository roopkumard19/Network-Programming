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

int sock,new_sock;
int join,list;
struct sockaddr_in server;
struct sockaddr_in client;
int length,number;
signed int count;
int data_read,data_write;
int receive;
char data_client[1024]; 
char buffer[2096];
char dat[255];
FILE *iterative;

if (argc<4)
{
printf("port or filename not provided\n");
}



printf("filename 1 is : %s\n", argv[2]);
printf("filename 2 is : %s\n", argv[3]);

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
server.sin_port=htons(atoi(argv[1]));			// Assigning the port number for the server 
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
struct dirent *ent;


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
if (new_sock==-1)
{
printf("Unable to accept the connection");			// Error when connection is not established.
exit(-1);
}

printf("\naccepted %d\n",new_sock);

int i;
int pid;
pid=fork();
printf("the child pid is %d\n",pid);




if(pid<0)
{
printf("Error in fork %d\n",pid);
close(new_sock);
exit(-1);
}
if(pid>0)
{
printf("\nthe parent pid is %d \n", getpid());
close(new_sock);
}

//for(i=0;i<=3;i++){
if(pid==0)
{

close(sock);

if(write(new_sock,argv[2],sizeof(argv[2]))<0)
{
printf("File cannot be written\n");
}

if(read(new_sock,buffer,2096)<0)
{
printf("name cannot be read\n");
}

if(write(new_sock,argv[3],sizeof(argv[3]))<0)
{
printf("File cannot be written\n");
}

printf("\nboth the files have been sent\n");



/* Reading the data from the client */

printf("the pid is %d\n", pid);
receive= read(new_sock, data_client, 1024);
printf("The file asked by the client:%s\n",data_client);
strcpy(dat,data_client);


/* Calling of the file and opening */

if(strcmp(dat,argv[2])>0)
{
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

else if(strcmp(dat,argv[2])<0)
{
printf("File not with server\n");
}
/* Reading the data from the file */

data_read= fread(buffer,1,sizeof(buffer),iterative);
if(data_read<0)
{
printf("File Cannot be read\n");
}
while(data_read>0)
{


/* Sending data back to client */

data_write=write(new_sock,buffer,data_read);
if(data_write<=0)
{
printf("File cannot be written\n");
}
data_read=data_read-data_write;

}
close(new_sock);

printf("The process is complete.\n ");
}
close(new_sock);
bzero(data_client,1024);
printf("\nEnter next file\n ");
}
printf("No file entered\n");
return 0;

}
