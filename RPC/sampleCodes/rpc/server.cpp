#include <iostream>
#include <rpc/rpc.h>
#include "prog.h"

using namespace std;

int *add_1_svc(intpair *pair, struct svc_req *X) //Function name is defined by FnNameinSmall_RPCVersion_svc
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
