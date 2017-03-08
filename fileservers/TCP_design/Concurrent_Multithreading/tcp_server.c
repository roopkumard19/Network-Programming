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
#include <pthread.h>
#include <stdint.h>



struct thread{

unsigned int sock_new;
char arg2[1024];
char arg3[1024];


}obj;

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
void sig_int(int);
void *doit(void *);
pthread_t tid;
socklen_t clilen;
int *thread_soc;
struct thread thread1;


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



/*Placing the socket in listening mode */ 

list=listen(sock,5);					// passing arguments sd, and queue to the listen function
if (list==-1)
{
printf("Listen has not happened");			// Error when listen function fails
exit(-1);
}

printf("listening..\n");

/* Accepting a connection and creation of new socket */


for(;;)
{
new_sock=accept(sock,(struct sockaddr *)&client, &length);	 // Connection establishment and creation if new socket.
if (new_sock==-1)
{
printf("Unable to accept the connection");			// Error when connection is not established.
exit(-1);
}

printf("accepted\n");

/*COPYING ALL THE VALUES INTO THE STRUCTURE */
strcpy(obj.arg2,argv[2]);
strcpy(obj.arg3,argv[3]);
obj.sock_new = new_sock;
uintptr_t *sock1 = malloc(sizeof(uintptr_t));
*sock1 = new_sock;


/*CALLING PTHREAD CREATE */
pthread_create(&tid, NULL, doit,sock1);
printf("Calling doit function\n");



//------------------------------------------------------------------------------------//


}
printf("No file entered");
return 0;

}



/*Doit Function */


void* doit (void *sock2)
{


int new_sock = *(int *) sock2;
int sock;
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
void sig_int(int);
pthread_t tid;
socklen_t clilen;
char a2[1024];
char a3[1024];
int wr,len;


strcpy(a2,obj.arg2);
strcpy(a3,obj.arg3);



if(write(new_sock,a2,sizeof(a2))<0)
{
printf("File cannot be written\n");
}

if(read(new_sock,buffer,2096)<0)
{
printf("name cannot be read\n");
}

if(write(new_sock,a3,sizeof(a3))<0)
{
printf("File cannot be written\n");
}

printf("both the files are sent\n");

/* Reading the data from the client */

receive = read(new_sock, data_client, 1024);
printf("File asked by the client '%s'\n", data_client);
strcpy(dat,data_client);



// Calling of the file and opening 

if(strcmp(dat,a2)>0)
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

else if(strcmp(dat,a3)>0)
{
iterative = fopen("Fil2.txt","r+");
if(iterative==NULL)
{
printf("File not found\n");
return(0);
}
printf("File found\n");
}
/* Opening and Reading the data from the file */

data_read= fread(buffer,1,sizeof(buffer),iterative);
if(data_read<0)
{
printf("File Cannot be read\n");
}
while(data_read>0)
{


/* Sending data back to client */

data_write=write(new_sock,buffer,data_read);
printf("File written  \n%s\n",buffer);
if(data_write<=0)
{
printf("File cannot be written\n");
}
data_read=data_read-data_write;

}
close(new_sock);
printf("The process is complete.\n ");
bzero(data_client,1024);

close((int) sock2);

}







