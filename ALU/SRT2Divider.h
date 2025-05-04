#ifndef SRT2_DIVIDER_H
#define SRT2_DIVIDER_H

#include <systemc.h>

SC_MODULE(SRT2Divider) {
    sc_in<sc_int<16>> dividend;
    sc_in<sc_int<16>> divisor;
    sc_out<sc_int<16>> quotient;
    sc_out<sc_int<16>> remainder;

    void compute() {
        // === Detectare semn intrari ===
        bool dividend_neg = dividend.read() < 0;
        bool divisor_neg  = divisor.read() < 0;

        //Convertim in valorile absolute folosind complement de 2
        sc_int<16> A;
        if (dividend_neg) {
            A = ~dividend.read() + 1;
        } else {
            A = dividend.read();
        }

        sc_int<16> raw_divisor;
        if (divisor_neg) {
            raw_divisor = ~divisor.read() + 1;
        } else {
            raw_divisor = divisor.read();
        }
        sc_uint<16> B = raw_divisor.to_uint();  // conversie explicita

        // === SRT2 core logic ===
        sc_int<17> P = 0;

        // Numara zerourile de la inceput pentru normalizare
        int K = 0;
        for (int j = 15; j >= 0; --j) {
            if ((B >> j) & 1) break;
            K++;
        }

        sc_bigint<49> PAB = (sc_bigint<49>(P), A, B);
        PAB = PAB << K;

        P = sc_int<17>(PAB.range(48, 32));
        A = PAB.range(31, 16);
        B = PAB.range(15, 0);

        sc_int<16> Q = 0;

        for (int i = 0; i < 16; ++i) {
            sc_int<3> top3 = (P >> 14) & 0x7;

            if (top3 == 0 || top3 == 7) {
                sc_bigint<33> PA = (sc_bigint<33>(P), A);
                PA = PA << 1;
                P = sc_int<17>(PA.range(32, 16));
                A = PA.range(15, 0);
                Q = Q << 1;
                Q[0] = 0;
                A[0] = 0;
            }
            else if (P > 0) {
                sc_bigint<33> PA = (sc_bigint<33>(P), A);
                PA = PA << 1;
                P = sc_int<17>(PA.range(32, 16));
                A = PA.range(15, 0);
                Q = Q << 1;
                Q[0] = 0;
                A[0] = 1;
                P = P - B;
            }
            else if (P < 0) {
                sc_bigint<33> PA = (sc_bigint<33>(P), A);
                PA = PA << 1;
                P = sc_int<17>(PA.range(32, 16));
                A = PA.range(15, 0);
                Q = Q << 1;
                Q[0] = 1;
                A[0] = 0;
                P = P + B;
            }
        }

        if (P < 0) {
            P = P + (sc_int<32>(B) << K);
            A = A - 1;
        }

        if (K != 0) {
            P = P >> K;
        }

        // === Aplicare semne finale ===
        bool quotient_neg = dividend_neg ^ divisor_neg;
        bool remainder_neg = dividend_neg;

        sc_int<16> q_out;
        if (quotient_neg) {
            q_out = ~(A - Q) + 1;
        } else {
            q_out = A - Q;
        }

        sc_int<16> r_out;
        if (remainder_neg) {
            r_out = ~P.range(15, 0) + 1;
        } else {
            r_out = P.range(15, 0);
        }

        quotient.write(q_out);
        remainder.write(r_out);
    }

    SC_CTOR(SRT2Divider) {
        SC_METHOD(compute);
        sensitive << dividend << divisor;
    }
};

#endif
