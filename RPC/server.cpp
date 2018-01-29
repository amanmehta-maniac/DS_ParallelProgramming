#include <iostream>
#include <bits/stdc++.h>
#include <rpc/rpc.h>
#include "prog.h"

using namespace std;
char *sx;

char **ans_1_svc(intpair *pair, struct svc_req *X){
	string ss="apropos ";
    static int x;
	for(int i=0;pair->a[i]!='\0';i++) ss+=pair->a[i];
    int i;
    ss+=" > output.txt";
	const char *s = ss.c_str();
    cout<<"command to run:" << ss<<"\n";
	system(s);
	string line, ret;
    std::ifstream inFile;
    inFile.open("output.txt");
    while (inFile >> line) {
        ret = ret + line;
    }
    inFile.close();
    cout << ret << endl;
    cout << ret.size() << endl;
    sx = (char*)(ret.c_str());
    cout<<sx<<"\n";
	return (&sx);
}