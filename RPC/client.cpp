#include <iostream>
#include <rpc/rpc.h>
#include <unistd.h>
#include "prog.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
    CLIENT *Client;
    intpair Pair;
    char *result;
    char host[256];
    gethostname(host, 256);
    Client = clnt_create(host, MATHPROG, MATHVERS, "udp"); 
    if(Client == NULL)
    {
        cout << "Error: Client not formed" << endl;
        exit(-1);
    }
    for(int j=1;j<argc;j++){
        int i=0;
        for(i=0;argv[j][i]!='\0';i++) Pair.a[i] = argv[j][i];
        Pair.a[i]='\0';
        cout << "Command >> " << Pair.a << endl;
        cout << (*ans_1(&Pair, Client)) << endl;
    }
    return 0;
}
