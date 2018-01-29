all:
	rpcgen prog.x
	g++ -std=c++11 client.cpp prog_clnt.c prog_xdr.c -o client
	g++ -std=c++11 server.cpp prog_svc.c prog_xdr.c -o server
