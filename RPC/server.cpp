#include <iostream>
#include <bits/stdc++.h>
#include <rpc/rpc.h>
#include "prog.h"

using namespace std;

char **ans_1_svc(intpair *pair, struct svc_req *X){
	string ss="apropos ";static int x;
	for(int i=0;pair->a[i]!='\0';i++) ss+=pair->a[i];
    int i;ss+=" > text";
	const char *s = ss.c_str();
	system(s);
	string line,ret;
    ifstream myfile ("text");
    if (myfile.is_open()){
        while ( myfile >> line ){
            ret += line;
            ret += " ";
        }
        myfile.close();
    }
    cout << ret << endl;
    cout << ret.size() << endl;
    static char *sx = (char*)(ret.c_str());
	return (&sx);
}