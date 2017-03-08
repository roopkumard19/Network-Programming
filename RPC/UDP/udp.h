/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _UDP_H_RPCGEN
#define _UDP_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct input {
	char arg1[2100];
};
typedef struct input input;

struct output {
	char res1[2100];
};
typedef struct output output;

#define FILE_SERVER 0x12345678
#define FILE_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define FILESERVERPROC 1
extern  output * fileserverproc_1(input *, CLIENT *);
extern  output * fileserverproc_1_svc(input *, struct svc_req *);
extern int file_server_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define FILESERVERPROC 1
extern  output * fileserverproc_1();
extern  output * fileserverproc_1_svc();
extern int file_server_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_input (XDR *, input*);
extern  bool_t xdr_output (XDR *, output*);

#else /* K&R C */
extern bool_t xdr_input ();
extern bool_t xdr_output ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_UDP_H_RPCGEN */
