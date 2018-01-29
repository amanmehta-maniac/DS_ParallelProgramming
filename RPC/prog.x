struct intpair {
    char a[50];
};

program MATHPROG { 
    version MATHVERS {
        string ANS(intpair) = 1; 
    } = 1; 
} = 0x20000008; 