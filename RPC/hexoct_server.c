/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "hexoct.h"

int *
tohex_1_svc(int *argp, struct svc_req *rqstp)
{

	static int  result;
	result = *argp;
	printf("Hex: %x\n",*argp);

	return(&result);
}

int *
tooct_1_svc(int *argp, struct svc_req *rqstp)
{

	static int  result;
	result = *argp;
	printf("Oct: %o\n",*argp);
	return(&result);
}