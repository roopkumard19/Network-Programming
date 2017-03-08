/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "udp.h"
#include"rpc/rpc.h"
#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
output *
fileserverproc_1_svc(input *argp, struct svc_req *rqstp)
{
	static output  result;

char file_name[2100];
strcpy(file_name,argp->arg1);// copying the intended file name 
printf("received file_name is : %s\n",file_name);

FILE *iterative;
int data_read;
char buffer[2100];
char small[2100]="small.txt";
char large[2100]="large.txt";
char err[2100]= "\0";  //"File not found";
int flag = 0;

//searching for the file
if(strcmp(small,file_name)==0)
{
iterative = fopen("small.txt","r+");
flag = 1;
if(iterative==NULL)
{
printf("File not found\n");
return(0);
}
printf("File found\n");
}

if(strcmp(large,file_name)==0)
{
flag =1;
iterative = fopen("large.txt","r+");
if(iterative==NULL)
{
printf("File not found\n");
return(0);
}
printf("File found\n");
}

//error handling if the intended file is not present
if(flag == 0)
{
strcpy(buffer,err);
strcpy(result.res1,buffer);
return (&result);
}


/* Reading the data from the file */

data_read= fread(buffer,sizeof(buffer),1,iterative);
if(data_read<0)
{
printf("File Cannot be read\n");
}

strcpy(result.res1,buffer);
printf("server result ");


return (&result);
}