struct intpair {
    int a;
    int b;
};

program MATHPROG { 
    version MATHVERS {
        int ADD(intpair) = 1; /*client calls it as add_1*/
        int SUB(intpair) = 2;
    } = 1; /*Verison of RPC being used -> used to name functions*/
} = 0x20000008; /*Unique identification of the server*/
