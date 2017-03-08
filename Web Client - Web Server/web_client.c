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
#include <sys/time.h>

int main(int argc, char *argv[])
{
/*declare variables*/

int sockfd, portnum;
char buffer[1024000];
char arg1[1024];
char server_name[1024];
char file[1024];
char get_request[1024];
struct sockaddr_in serv_addr;
struct hostent *server;
struct timeval t1, t2;

if (argc<3)
{
printf("port or hostname not provided\n");
}
/* Loop to get the server name from the command line arguments */

strcpy(arg1, argv[1]);
int j;
for(j = 0; j < strlen(arg1); j++)
{
if (arg1[j] == '/')
{
strncpy(server_name, arg1, j);
server_name[j] = '\0';
break;
} 
}
/* Loop to get the file name from the command line arguments */  
  
for (j; j < strlen(arg1); j++)
{
strcat(file, &arg1[j]);
break;
}

printf("server_name is : %s\n", server_name);
printf("file is : %s\n", file);

/*create socket*/

sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd<0)
{
printf("cant open a socket.\n ");
exit(1);
}
printf("socket created.\n");


/*set the address in the sockaddr_in*/

bzero((char*)&serv_addr, sizeof(serv_addr));
portnum = atoi(argv[2]);
server = gethostbyname (server_name);
if (portnum==0)
{
printf("no such host.\n");
exit(1);
}
printf("ok here1\n");
serv_addr.sin_family = AF_INET;
bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
serv_addr.sin_port = htons(portnum);

printf("address set.\n");

/*connect*/

int len= sizeof(serv_addr);
if(connect(sockfd,(struct sockaddr *) &serv_addr,len)<0)
{
printf("can't connect to socket.\n");
exit(1);
}
printf("connected to socket.\n");

gettimeofday(&t1,NULL);

bzero(get_request, 1024);
sprintf(get_request, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", file, server_name);	// Storing the server and file name into the buffer
     
printf("\n%s", get_request);

if(send(sockfd, get_request, sizeof(get_request), 0)<0)		// send request to client
{
printf("can't send s.\n");
}
printf("sent http req...\n");

bzero(buffer,1024000);

if(read(sockfd, buffer, 1024000)<0)				//Reda reply from client.
{
printf("cant read the msg\n");
}
printf("buffer: %s\n",buffer);


FILE *iterativec = fopen("clientfile.html","w+");	// Open file to write in the file.
if(iterativec==NULL)
{
printf("File not found\n");
return(0);
}
printf("File found\n");
fprintf(iterativec,"%s\n",buffer);
gettimeofday(&t2,NULL);
printf("The time taken to record and display data is ' %lu' microseconds\n",t2.tv_usec-t1.tv_usec);	// Calculate the time taken to respond.


printf("%s\n",buffer);
}
