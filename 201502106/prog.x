struct intpair {
    char a[50];
};

typedef char String<10000>;


program MATHPROG { 
    version MATHVERS {
        int num_chunks(intpair) = 1;
        String get_chunk(int) = 2;
    } = 1; 
} = 0x20000008; 
