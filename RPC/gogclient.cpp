#include <iostream>
#include <rpc/rpc.h>
#include <unistd.h>
#include "prog.h"

using namespace std;

int main(int argc, char *argv[])
{
    CLIENT *Clnt;
    string cmd;
    char host[256];
    int numofarg = argc;
    for(int i=0;i<numofarg;i++)
    {
        if(i!=0)
            cmd += " ";

        if(i==0)
            cmd += "apropos";
        else
            cmd += string(argv[i]);

    }
    // cout<<s<<'\n';
    int lenc = cmd.length();
    lenc++;
    gethostname(host, 256);

    Clnt = clnt_create(host, APROPROG, APROVERS, "udp");

    if(Clnt == NULL)
    {
        cout << "Error: Clnt not formed" << '\n';
        exit(-1);
    }
    String *argu;
    argu = (String *)malloc(sizeof(String));
    argu->String_val = (char *)malloc(sizeof(char)*(lenc));
    strncpy(argu->String_val, cmd.c_str(), sizeof(char)*(lenc));
    // cout<< argu->String_val << '\n';
    argu->String_len = (lenc-1) * sizeof(char);
    int* numofchunk=getnumchunk_1(argu, Clnt);
    // cout<<numofchunk<<'\n';
    // cout<<(*numofchunk)<<'\n';
    string ret;
    int chunk_no;
    for(int i=0;i<(*numofchunk);i++)
    {
        // String *output;
        chunk_no = i;
        String *output = getchunk_1(&chunk_no,Clnt);
        ret += string(output->String_val) ;
        // cout<< output->String_len<<'\n';
        // cout<< output->String_val <<'\n';
    }
    cout<<ret;
    return 0;
}
