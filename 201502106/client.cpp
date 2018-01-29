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
        int * num_c = num_chunks_1(&Pair,Client);
        // String * print = sendstring_1(&Pair, Client);
        if(*(num_c)<0){
            cout<<Pair.a<<": nothing appropriate.\n";
        }
        else{
            string ans = "";
            for (int i = 0; i < *(num_c); ++i)
            {
                int ii = i;
                String *temp = get_chunk_1(&ii,Client);
                ans += string(temp->String_val);
                /* code */
            }
            cout << ans;
        }
    }
    return 0;
}
