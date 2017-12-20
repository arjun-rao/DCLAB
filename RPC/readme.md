##
* rpcinfo to check if its there
* create hexoct.x
* rpcgen -aC hexoct.x
* make -f Makefile.hexoct
* sudo ./server
* ./client localhost


## MacOS Instructions

Run the following commands to setup rpcgen:

	brew install rpcgen

	sudo nfsd enable
	sudo touch /etc/exports
	sudo nfsd checkexports
	sudo nfsd start

Run `sudo nfsd status` until it shows running. Now run `rpcinfo`

If you don't get any errors, it should work now.


## Miscellenous Info:

Important!
Before we compile, we will make a change to the makefile. We will make sure that the server is compiled so that the symbol `RPC_SVC_FG` is defined. This will cause our server to run in the foreground. For testing purposes, this is convenient since we'll be less likely to forget about it and it will be easier to kill (we don't have to look up its process ID).

Edit the makefile and find the line that defines `CFLAGS`:


	CFLAGS += -g

and change it to:


	CFLAGS += -g -DRPC_SVC_FG

Secondly, we want to make sure that rpcgen generates code that conforms to ANSI C, so we'll add a -C (capital C) parameter to the rpcgen command. Change the line in the makefile that defines:


	RPCGENFLAGS =

to:


	RPCGENFLAGS = -C

Now compile your program by running make. You'll see output similar to:

	cc -g -DRPC_SVC_FG -c -o hexoct_clnt.o hexoct_clnt.c
	cc -g -DRPC_SVC_FG -c -o hexoct_client.o hexoct_client.c
	cc -g -DRPC_SVC_FG -c -o hexoct_xdr.o hexoct_xdr.c
	cc -g -DRPC_SVC_FG -o hexoct_client hexoct_clnt.o hexoct_client.o hexoct_xdr.o -lnsl
	cc -g -DRPC_SVC_FG -c -o hexoct_svc.o hexoct_svc.c
	cc -g -DRPC_SVC_FG -c -o hexoct_server.o hexoct_server.c
	cc -g -DRPC_SVC_FG -o hexoct_server hexoct_svc.o hexoct_server.o hexoct_xdr.o -lnsl

Note that the -lnsl argument is not needed when linking under Linux, *BSD, or OS X.

If you're running OS X, Linux, or BSD and don't have a makefile, run the above commands using gcc as the compiler and omitting -lnsl:


	gcc -g -DRPC_SVC_FG -c -o hexoct_clnt.o hexoct_clnt.c
	gcc -g -DRPC_SVC_FG -c -o hexoct_client.o hexoct_client.c
	gcc -g -DRPC_SVC_FG -c -o hexoct_xdr.o hexoct_xdr.c
	gcc -g -DRPC_SVC_FG -o hexoct_client hexoct_clnt.o hexoct_client.o hexoct_xdr.o
	gcc -g -DRPC_SVC_FG -c -o hexoct_svc.o hexoct_svc.c
	gcc -g -DRPC_SVC_FG -c -o hexoct_server.o hexoct_server.c
	gcc -g -DRPC_SVC_FG -o hexoct_server hexoct_svc.o hexoct_server.o hexoct_xdr.o

Unfortunately, the compilation produces a number of warnings but you can ignore them.

The result is that you have two executables: hexoct_client and hexoct_server. You can move hexoct_server to another machine or run it locally, giving hexoct_client your local machine's name or the name localhost.

If you're running this on a non-SunOS machine, you may need to start the RPC port mapper first. Chances are you won't and you should try running the server first. If it does not exit immediately with an unable to register error, you're probably good to go. If you do need to start the portmapper then here are the commands that you'll need to run on several popular operating systems:

OS	command
Mac OS X

 	launchctl start com.apple.portmap

Linux

	/sbin/portmap
*BSD

	/usr/sbin/rpcbind

In one window, run:


	./hexoct_server

If you're on OS X Leopard, you'll need to be root to start the server. Either su and get a root shell or run:


	sudo ./hexoct_server

In another window, run:


	./hexoct_client localhost

In the server window, you should see the following text appear:


	add function called

This confirms that the client and server are communicating. If your client just seems to be hanging, chances are you have not started the portmapper.

