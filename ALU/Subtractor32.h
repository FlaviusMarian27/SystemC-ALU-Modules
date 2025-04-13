#ifndef SUBTRACTOR32_H
#define SUBTRACTOR32_H
#include <systemc.h>
#include "TwosComplement.h"
#include "rca32.h"

SC_MODULE(Subtractor32) {
    sc_in<sc_int<32>> A, B;
    sc_out<sc_int<32>> S;
    sc_out<bool> Cout;

    sc_signal<sc_int<32>> B_c2;
    sc_signal<bool> zero; // carry-in = 0

    TwosComplement* tc;
    RCA32* adder;

    SC_CTOR(Subtractor32) {
        zero.write(0);

        tc = new TwosComplement("twos_complement");
        tc->A(B);
        tc->A_C2(B_c2);

        adder = new RCA32("rca_sub");
        adder->A(A);
        adder->B(B_c2);
        adder->Cin(zero);
        adder->S(S);
        adder->Cout(Cout);
    }
};

#endif
