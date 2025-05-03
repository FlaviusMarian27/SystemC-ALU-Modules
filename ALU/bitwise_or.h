#ifndef BITWISE_OR_H
#define BITWISE_OR_H

#include <systemc.h>

template<int WIDTH>
SC_MODULE(BitwiseOr) {
    sc_in<sc_uint<WIDTH>> A, B;
    sc_out<sc_uint<WIDTH>> Y;

    void compute() { 
        Y.write( A.read() | B.read() ); 
    }

    SC_CTOR(BitwiseOr) {
        SC_METHOD(compute);
        sensitive << A << B;
    }
};

#endif
