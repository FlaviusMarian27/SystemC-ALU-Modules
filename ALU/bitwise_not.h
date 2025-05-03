#ifndef BITWISE_NOT_H
#define BITWISE_NOT_H

#include <systemc.h>

template<int WIDTH>
SC_MODULE(BitwiseNot) {
    sc_in<sc_uint<WIDTH>> A;
    sc_out<sc_uint<WIDTH>> Y;

    void compute() { 
        Y.write( ~A.read() ); 
    }

    SC_CTOR(BitwiseNot) {
        SC_METHOD(compute);
        sensitive << A;
    }
};

#endif