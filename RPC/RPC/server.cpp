#include <iostream>
#include <rpc/rpc.h>
#include "prog.h"

using namespace std;

int *add_1_svc(intpair *pair, struct svc_req *X)
{
    static int result;
    result = pair->a + pair->b;
    return(&result);
}

int *sub_1_svc(intpair *pair, struct svc_req *X)
{
    static int result;
    result = pair->a - pair->b;
    return(&result);
}


String *sendstring_1_svc(void *vd, struct svc_req *X)
{
    String *tosend;
    tosend = (String *)malloc(sizeof(String));
    tosend->String_val = (char *)malloc(sizeof(char) * 100);
    char to[27] = "Hello from the other size";
    strncpy(tosend->String_val, (char *)"hello from the other side", sizeof(char)*27); 
    cout << tosend->String_val << endl;
    tosend->String_len = 27 * sizeof(char);
    return tosend;
}
