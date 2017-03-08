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
char data_client1[1024];
//int* client1;
struct sockaddr_in client1;
int len;


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
pthread_t tid[10];
socklen_t clilen;
int *thread_soc;
struct thread thread1;


if (argc<5)
{
printf("port or filename not provided\n");
}



printf("filename 1 is : %s\n", argv[2]);
printf("filename 2 is : %s\n", argv[3]);
printf("Number of threads %s\n", argv[4]);
/*Socket creation*/

sock=socket(AF_INET, SOCK_DGRAM, 0);			// creating a socket with arguments such as domain,connection type (TCP), protocol
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






for(;;)
{
/* Reading the data from the client */

if(recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&client, &length)<0)

{
printf("File cannot be written\n");
}
printf("Client: %s\n",buffer);

if((sendto(sock,argv[2],sizeof(argv[2]),0,(struct sockaddr *)&client, length))<0)
{
printf("File cannot be written\n");
}

bzero(buffer, 1024);

int e_buffer=recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&client, &length);


if((sendto(sock,argv[3],sizeof(argv[3]),0,(struct sockaddr *)&client, length))<0)
{
printf("File cannot be written\n");

}

receive= recvfrom(sock, data_client, 1024, 0, (struct sockaddr *)&client, &length);
printf("The file asked by the client: '%s'\n",data_client);

printf("checking \n");

if(receive>0)
{
strcpy(obj.data_client1,data_client);

/*COPYING ALL THE VALUES INTO THE STRUCTURE */
strcpy(obj.arg2,argv[2]);
strcpy(obj.arg3,argv[3]);
obj.sock_new = sock;
obj.len = length;
obj.client1 = client;

int *sock1 = malloc(sizeof(int));
*sock1 = sock;


/*CALLING PTHREAD CREATE */
int i,Number_of_threads;
Number_of_threads = atoi(argv[4]);
for(i=0;i<Number_of_threads;i++)
{

pthread_create(&tid[i], NULL, &doit,(void *)sock1);
printf("Calling doit function\n");
printf("data_client %s\n",data_client);
}

//------------------------------------------------------------------------------------//
}

}
printf("No file entered");
return 0;

}



/*Doit Function */


void* doit (void * sock2)
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

client = obj.client1;
strcpy(a2,obj.arg2);
strcpy(a3,obj.arg3);
new_sock=obj.sock_new;
strcpy(data_client,obj.data_client1);

//printf("test\n");
printf("dataclient %s\n",data_client);
strcpy(dat,data_client);
length = obj.len;
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
bzero(buffer,1024);
data_read= fread(buffer,1,sizeof(buffer),iterative);
if(data_read<0)
{
printf("File Cannot be read\n");
}
while(data_read>0)
{


/* Sending data back to client */
printf("sock_id is %d",new_sock);
data_write=sendto(new_sock,buffer,1024,0,(struct sockaddr *)&client, length);

//printf("data_written is%d\n", data_write);
//printf("File written in buffer \n%s\n",buffer);
if(data_write<=0)
{
printf("File cannot be written\n");
}
data_read=data_read-data_write;
exit(0);
}
close(new_sock);
printf("The process is complete.\n ");
//bzero(data_client,1024);

close((int) sock2);

}







