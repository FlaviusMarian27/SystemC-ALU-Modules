#ifndef MUX8_32_H
#define MUX8_32_H

#include <systemc.h>

template<typename T>
SC_MODULE(Mux8_32) {
    sc_in<T>         d0, d1, d2, d3, d4, d5, d6, d7;
    sc_in<sc_uint<3>> sel;
    sc_out<T>        y;

    void do_mux() {
        switch (sel.read()) {
            case 0: y.write(d0.read()); break; // ADD
            case 1: y.write(d1.read()); break; // SUB
            case 2: y.write(d2.read()); break; // MUL
            case 3: y.write(d3.read()); break; // DIV
            case 4: y.write(d4.read()); break; // AND
            case 5: y.write(d5.read()); break; // OR
            case 6: y.write(d6.read()); break; // XOR
            case 7: y.write(d7.read()); break; // NOT
            default: y.write(0); break;
        }
    }

    SC_CTOR(Mux8_32) {
        SC_METHOD(do_mux);
        sensitive << d0 << d1 << d2 << d3
                  << d4 << d5 << d6 << d7
                  << sel;
    }
};

#endif
