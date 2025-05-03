#ifndef SRT_DIVIDER_H
#define SRT_DIVIDER_H

#include <systemc.h>

SC_MODULE(SRTDivider) {
    // intrări
    sc_in<sc_int<32>> dividend;
    sc_in<sc_int<32>> divisor;
    sc_in<bool>        start;
    // ieșiri
    sc_out<sc_int<32>> quotient;
    sc_out<sc_int<32>> remainder;
    sc_out<bool>       done;

    
};

#endif // SRT_DIVIDER_H
