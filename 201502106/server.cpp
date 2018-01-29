#include <iostream>
#include <bits/stdc++.h>
#include <rpc/rpc.h>
#include "prog.h"

using namespace std;

int each = 1000;
int num_chunk;
string OUT;

int *num_chunks_1_svc(intpair *pair, struct svc_req *X){
    string ss = "apropos ";
    static int x;
    for(int i=0;pair->a[i]!='\0';i++) ss+=pair->a[i];
    int i;
    ss+=" > output.txt";
    const char *s = ss.c_str();
    cout<<"command to run:" << ss<<"\n";
    system(s);
    string line, ret = "";
    std::ifstream inFile;
    inFile.open("output.txt");
    while (getline(inFile,line)) {
        ret = ret + line + "\n";
    }
    inFile.close();
    cout << ret << endl;
    if(ret.size()==0){
        num_chunk = -1;
        return(&num_chunk);
    }
    OUT = ret;
    num_chunk = ret.size()/each;
    if((ret.size())%each) num_chunk++;
    return (&num_chunk);
}

String *get_chunk_1_svc(int *num, struct svc_req *X){
    string this_chunk = OUT.substr((*num)*each,each);
    String *tosend;
    tosend = (String *)malloc(sizeof(String));
    tosend->String_val = (char *)malloc(sizeof(char) * (each+1));
    strncpy(tosend->String_val, (char *)(this_chunk.c_str()), sizeof(char)*(each+1)); 
    cout << tosend->String_val << endl;
    tosend->String_len = (this_chunk.size()) * sizeof(char);
    // system("rm output.txt");
    return tosend;
}





