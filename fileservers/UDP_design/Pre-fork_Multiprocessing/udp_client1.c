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

int sockfd, portnum,length,receive;
char buffer[2096];
struct sockaddr_in serv_addr;
struct hostent *server;
if (argc<3)
{
printf("port or hostname not provided\n");
}


/*create socket*/

sockfd = socket(AF_INET, SOCK_DGRAM, 0);
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
bzero(buffer, 2096);



/*write*/
length=sizeof(serv_addr);
strcpy(buffer, "I am client1..What files u have?");
if(sendto(sockfd, buffer,2096,0,(struct sockaddr *)&serv_addr, length)<0)
{
printf("can't send the data.\n");
}


/*read*/

bzero(buffer,2096);
if((receive=recvfrom(sockfd, buffer, 2096,0,(struct sockaddr *)&serv_addr, &length))<0)
{
printf("File cannot be written\n");
}

printf("File1 = %s\n",buffer);

bzero(buffer, 2096);
if(sendto(sockfd, buffer,2096,0,(struct sockaddr *)&serv_addr, length)<0)
{
printf("can't send the integer.\n");
}

bzero(buffer,2096);
if((receive=recvfrom(sockfd, buffer, 2096,0,(struct sockaddr *)&serv_addr, &length))<0)
{
printf("File cannot be written\n");
}

printf("File2 = %s\n",buffer);

printf("enter the file name:");
bzero(buffer, 2096);
fgets(buffer, sizeof(buffer), stdin);
if(sendto(sockfd, buffer,2096,0,(struct sockaddr *)&serv_addr, length)<0)
{
printf("can't send.\n");
}

bzero(buffer,2096);
if((receive=recvfrom(sockfd, buffer, 2096,0,(struct sockaddr *)&serv_addr, &length))<0)
{
printf("File cannot be written\n");
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
return 0;
}
