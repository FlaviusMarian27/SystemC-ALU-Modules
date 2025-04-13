#ifndef TWOS_COMPLEMENT_H
#define TWOS_COMPLEMENT_H
#include<systemc.h>

SC_MODULE(TwosComplement){
    sc_in<sc_int<32>> A;
    sc_out<sc_int<32>> A_C2;

    void compute(){
        sc_int<32> c2 = (~A.read() + 1); // Complementul lui B
        A_C2.write(c2);
    }

    SC_CTOR(TwosComplement){
        SC_METHOD(compute);
        sensitive << A;
    }
};

#endif

/*
5-0000 0101
-5 - 1111 1011
20 - 0001 0100
15 - 0000 1111
cout = 1
*/