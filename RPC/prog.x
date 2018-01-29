struct intpair {
    char a[50];
};

program MATHPROG { 
    version MATHVERS {
        string ANS(intpair) = 1; /*client calls it as add_1*/
        /*string SUB(intpair) = 2;*/
    } = 1; /*Verison of RPC being used -> used to name functions*/
} = 0x20000008; /*Unique identification of the server*/
