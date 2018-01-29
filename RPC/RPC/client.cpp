#include <iostream>
#include <rpc/rpc.h>
#include <unistd.h>
#include "prog.h"

using namespace std;

int main(int argc, char *argv[])
{
    CLIENT *Client;
    intpair Pair;
    int *result;
    char host[256];

    if (argc != 3) {
        fprintf(stderr, "usage:./client_prog num1 num2\n");
        exit(1);
    }
    gethostname(host, 256);

    Client = clnt_create(host, MATHPROG, MATHVERS, "udp"); //Create a handle for Client
    
    if(Client == NULL)
    {
        cout << "Error: Client not formed" << endl;
        exit(-1);
    }

    Pair.a = atoi(argv[1]);
    Pair.b = atoi(argv[2]);

    result = add_1(&Pair, Client);
    cout << "Result of addition is " << *result << endl;
    result = sub_1(&Pair, Client);
    cout << "Result of addition is " << *result << endl;

    String * print = sendstring_1(&Pair, Client);
    cout << "String: " << print->String_val << endl;
    return 0;
}
