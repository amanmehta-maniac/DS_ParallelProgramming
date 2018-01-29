
struct intpair {
    int a;
    int b;
};

typedef char String<100>;

program MATHPROG {
    version MATHVERS {
        int ADD(intpair) = 1;
        int SUB(intpair) = 2;
        String SENDSTRING(void) = 3;
    } = 1;
} = 0x20000008;
