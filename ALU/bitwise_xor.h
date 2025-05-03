#ifndef BITWISE_XOR_H
#define BITWISE_XOR_H

#include <systemc.h>

template<int WIDTH>
SC_MODULE(BitwiseXor) {
    sc_in<sc_uint<WIDTH>> A, B;
    sc_out<sc_uint<WIDTH>> Y;

    void compute() { 
        Y.write( A.read() ^ B.read() ); 
    }

    SC_CTOR(BitwiseXor) {
        SC_METHOD(compute);
        sensitive << A << B;
    }
};

#endif