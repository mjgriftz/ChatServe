Welcome to chatclient/chatserve CS372 Project1
Created by Marcus Griffiths

addrinfo structure used in client code courtesy of Beej's Network Programming Guide
For testing, chatserve was run on flip3.engr.oregonstate.edu with port#: 11113


*** Description ***

This set of programs will run a chat server where 'chatserve' is run. A client may connect to this server by running 'chatclient'. Once connected, the server and client become peers that may send text messages back and forth between one another.



*** Instructions for Execution ***

In order to create the chatclient executable, please compile only the main.c file contained in this directory.

Example:
	gcc -o chatclient main.c

To run the 'chatclient', provide both the hostname of the chatserver and the port number.

Example:
	./chatclient flip3.engr.oregonstate.edu 11113

To run the 'chatserve', simply run chatserve with the desired port number as an argument.

Example:
	./chatserve 11113



*** Instructions for Use ***

The chatserve must already be running on the designated port when chatclient attempts to connect. When chatclient first begins, it will prompt user for a handle. This handle will be retained by the client until the connection is terminated. 

The client will have the first chance to send a message. Text messages between server and client must alternate. Either the client or the server may terminate the connection with the command '/quit' on their respective turn. After the connection is terminated, chatserve will continue to listen for additioinal connections. 

The chatserve must terminate its process in order completely finish.

