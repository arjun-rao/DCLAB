#!/bin/bash
gcc -g -DRPC_SVC_FG -c -o hexstr_clnt.o hexstr_clnt.c;
gcc -g -DRPC_SVC_FG -c -o hexstr_client.o hexstr_client.c;
gcc -g -DRPC_SVC_FG -o hexstr_client hexstr_clnt.o hexstr_client.o;
gcc -g -DRPC_SVC_FG -c -o hexstr_svc.o hexstr_svc.c;
gcc -g -DRPC_SVC_FG -c -o hexstr_server.o hexstr_server.c;
gcc -g -DRPC_SVC_FG -o hexstr_server hexstr_svc.o hexstr_server.o;