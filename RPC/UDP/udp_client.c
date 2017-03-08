/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "udp.h"
#include"errno.h"
#include"rpc/rpc.h"
#include"stdio.h"
#include"stdlib.h"

void
file_server_1(char *host,char *name)
{
	CLIENT *clnt;
	output  *result_1;
	input  fileserverproc_1_arg;
	char buffer[2100];
#ifndef	DEBUG
	clnt = clnt_create (host, FILE_SERVER, FILE_VERS, "udp");// Specifing the procedure name, version number and protocol name
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
		strcpy(fileserverproc_1_arg.arg1,name);// inserting it to the structure.
#endif	/* DEBUG */ 

	result_1 = fileserverproc_1(&fileserverproc_1_arg, clnt);//calling the main function
	if (result_1 == (output *) NULL) {
		clnt_perror (clnt, "call failed");
	}

printf("\n\nresult is : %s\n",result_1->res1);
strcpy(buffer,result_1->res1);
if (strlen(buffer) == 0 )
{
printf("file not found\n");
exit(0);
}

//Creating a new file in order to store the content of the required file
FILE *iterativec = fopen("clientfile.txt","w+");
if(iterativec==NULL)
{
printf("File not found\n");
}
printf("File found\n");
fprintf(iterativec,"%s\n",buffer);


#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host,*name;

	if (argc!=3) {
           printf("Arguments insufficient\n");
           exit(-1);
     }

	host = argv[1];
	name= argv[2];
	file_server_1 (host,name);// calling the fuction where in it would store the required file in a structure.
exit (0);
}
