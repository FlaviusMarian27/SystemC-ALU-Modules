#ifndef ALU_MUX_H
#define ALU_MUX_H

#include <systemc.h>
#include "rca32.h"
#include "Subtractor32.h"
#include "booth_multiplier.h"
#include "SRT2Divider.h"
#include "bitwise_and.h"
#include "bitwise_or.h"
#include "bitwise_xor.h"
#include "bitwise_not.h"
#include "Mux8_32.h"

SC_MODULE(ALU) {
    // Port-uri externe
    sc_in<sc_int<32>>   A, B;
    sc_in<sc_uint<3>>   opcode;
    sc_out<sc_int<32>>  result;

    // Semnale interne pe 32 biți
    sc_signal<sc_int<32>>   res_add, res_sub, res_mul, res_div;
    sc_signal<sc_int<32>>   res_and, res_or, res_xor, res_not;

    // Semnale dummy pentru carry/borrow
    sc_signal<bool>         dummy_cin;
    sc_signal<bool>         dummy_cout_add;
    sc_signal<bool>         dummy_cout_sub;

    // Semnale intermediare pentru adaptări
    sc_signal<sc_int<64>>   full_mul;                // produs 64 biți
    sc_signal<sc_int<16>>   A16, B16, div_q16, div_r16; // div inputs/outputs 16 biți
    sc_signal<sc_uint<32>>  A_u, B_u;                // A, B pentru bitwise
    sc_signal<sc_uint<32>>  and_u, or_u, xor_u, not_u; // rezultate bitwise unsigned

    // Module interne
    RCA32                   adder;
    Subtractor32            subtractor;
    BoothMultiplier<32>     multiplier;
    SRT2Divider             divider;  // modul original, pe 16 biți
    BitwiseAnd<32>          and_mod;
    BitwiseOr<32>           or_mod;
    BitwiseXor<32>          xor_mod;
    BitwiseNot<32>          not_mod;
    Mux8_32<sc_int<32>>     mux;

    SC_CTOR(ALU)
      : adder("adder"), subtractor("subtractor"), multiplier("multiplier"),
        divider("divider"), and_mod("and_mod"), or_mod("or_mod"),
        xor_mod("xor_mod"), not_mod("not_mod"), mux("mux")
    {
        // Adaptări intermediare
        SC_METHOD(slice_mul);         sensitive << full_mul;
        SC_METHOD(slice_div_inputs);  sensitive << A << B;
        SC_METHOD(extend_div);        sensitive << div_q16;
        SC_METHOD(cast_bitwise_inputs); sensitive << A << B;
        SC_METHOD(extend_bitwise);    sensitive << and_u << or_u << xor_u << not_u;

        // ADD
        adder.A(A);
        adder.B(B);
        adder.Cin(dummy_cin);
        adder.S(res_add);
        adder.Cout(dummy_cout_add);

        // SUB
        subtractor.A(A);
        subtractor.B(B);
        subtractor.S(res_sub);
        subtractor.Cout(dummy_cout_sub);

        // MUL
        multiplier.multiplicand(A);
        multiplier.multiplier(B);
        multiplier.product(full_mul);

        // DIV
        divider.dividend(A16);
        divider.divisor(B16);
        divider.quotient(div_q16);
        divider.remainder(div_r16);

        // BITWISE
        and_mod.A(A_u);
        and_mod.B(B_u);
        and_mod.Y(and_u);
        or_mod.A(A_u);
        or_mod.B(B_u);
        or_mod.Y(or_u);
        xor_mod.A(A_u);
        xor_mod.B(B_u);
        xor_mod.Y(xor_u);
        not_mod.A(A_u);
        not_mod.Y(not_u);

        // MUX 8:1
        mux.d0(res_add);
        mux.d1(res_sub);
        mux.d2(res_mul);
        mux.d3(res_div);
        mux.d4(res_and);
        mux.d5(res_or);
        mux.d6(res_xor);
        mux.d7(res_not);
        mux.sel(opcode);
        mux.y(result);
    }

    void slice_mul() {
        res_mul.write(full_mul.read().range(31, 0));
    }

    void slice_div_inputs() {
        A16.write(A.read().range(15, 0));
        B16.write(B.read().range(15, 0));
    }

    void extend_div() {
        res_div.write((sc_int<32>)div_q16.read());
    }

    void cast_bitwise_inputs() {
        A_u.write((sc_uint<32>)A.read());
        B_u.write((sc_uint<32>)B.read());
    }

    void extend_bitwise() {
        res_and.write((sc_int<32>)and_u.read());
        res_or.write((sc_int<32>)or_u.read());
        res_xor.write((sc_int<32>)xor_u.read());
        res_not.write((sc_int<32>)not_u.read());
    }
};

#endif // ALU_MUX_H