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
#include <math.h>

int main(int argc, char *argv[])
{
/*declare variables*/

int sockfd, portnum;
char buffer[2096];



struct sockaddr_in serv_addr;
struct hostent *server;
if (argc<3)
{
printf("port or hostname not provided\n");
}


/*create socket*/
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd<0)
{
printf("cant open a socket.\n");
exit(1);
}
printf("socket created.\n");


/*set the address in the sockaddr_in*/

bzero((char*)&serv_addr, sizeof(serv_addr));
portnum = atoi(argv[2]);
server = gethostbyname (argv[1]);
if (portnum==0)
{
printf("no such host.\n");
exit(1);
}

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


bzero(buffer, 2096);
if(read(sockfd,buffer,2096)<0)
{
printf("name cannot be read\n");
}

printf("File1 = %s\n",buffer);

bzero(buffer, 2096);
if(send(sockfd, buffer, sizeof(buffer), 0)<0)
{
printf("can't send s.\n");
}

bzero(buffer, 2096);
if(read(sockfd,buffer,2096)<0)
{
printf("name cannot be read\n");
}

printf("File2 = %s\n",buffer);

/*write*/

printf("enter the file name:");
bzero(buffer, 2096);
fgets(buffer, sizeof(buffer), stdin);
if(send(sockfd, buffer, sizeof(buffer), 0)<0)
{
printf("can't send the integer.\n");
}


/*read*/

bzero(buffer,2096);

if(read(sockfd, buffer, 2096)<0)
{
printf("cant read the msg\n");
exit(1);
}


/* Calling of the file and writing */

FILE *iterativec = fopen("clientfile1.txt","w+");
if(iterativec==NULL)
{
printf("File not found\n");
return(0);
}
printf("File found\n");
fprintf(iterativec,"%s\n",buffer);

printf("%s\n",buffer);

return 0;
}
