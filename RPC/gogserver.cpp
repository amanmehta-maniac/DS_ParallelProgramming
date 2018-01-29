#include <iostream>
#include <string>
#include <stdexcept>
#include <array>
#include <memory>
#include <cstdio>
#include <rpc/rpc.h>
#include "prog.h"

using namespace std;

string globout;
int csize = 150;
int t;
int lenou;
string run_command(const char* cmd)
{
        array<char, 128> buffer;
        string result;
        shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
        if (!pipe) throw runtime_error("popen() failed!");
        while (!feof(pipe.get())) {
            if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
                result += buffer.data();
        }
        return result;
}

String *getchunk_1_svc(int *chunknumber, struct svc_req *X)
{
    string schunk = globout.substr((*chunknumber)*csize,csize);
    int lenou = schunk.length();
    lenou++;
    // cout<<lenou<<'\n';
    String *ret;
    ret = (String *)malloc(sizeof(String));
    ret->String_val = (char *)malloc(sizeof(char) * (lenou));
    // char to[27] = "Hello from the other size";
    strncpy(ret->String_val, schunk.c_str() , sizeof(char)*(lenou));
    // cout << ret->String_val;
    ret->String_len = (lenou-1) * sizeof(char);
    return ret;
}

int *getnumchunk_1_svc(String *clr, struct svc_req *X)
{
    // cout<<clr->String_val<<'\n';
    globout = run_command((const char *)(clr->String_val));
    cout<<globout.length()<<'\n';
    lenou = globout.length();
    t= lenou/csize;
    if(lenou%csize==0) t=t;
    else t++;
    return(&t);
}
