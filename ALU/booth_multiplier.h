#ifndef BOOTH_MULTIPLIER_H
#define BOOTH_MULTIPLIER_H

#include <systemc.h>

template<int WIDTH>
SC_MODULE(BoothMultiplier) {
    sc_in<sc_int<WIDTH>> multiplicand;
    sc_in<sc_int<WIDTH>> multiplier;
    sc_out<sc_int<2 * WIDTH>> product;

    SC_CTOR(BoothMultiplier) {
        SC_METHOD(process);//era thread, cu method ruleaza mai bine si nu mai da 0 la result
        sensitive << multiplicand << multiplier;
        //dont_initialize();  // ca sa nu se activeze automat la inceput
    }

    void process() {
        sc_int<2 * WIDTH> A = 0;
        sc_int<2 * WIDTH> S = 0;
        sc_int<2 * WIDTH> P = 0;

        sc_int<WIDTH> m = multiplicand.read();
        sc_int<WIDTH> q = multiplier.read();

        A.range(2 * WIDTH - 1, WIDTH) = m;
        S.range(2 * WIDTH - 1, WIDTH) = -m;
        P.range(WIDTH - 1, 0) = q;

        int Q_1 = 0;

        for (int i = 0; i < WIDTH; ++i) {
            int Q_0 = P[0];

            if (Q_0 == 1 && Q_1 == 0)
                P = P + S;
            else if (Q_0 == 0 && Q_1 == 1)
                P = P + A;

            Q_1 = P[0];
            P = P >> 1;
            P[2 * WIDTH - 1] = P[2 * WIDTH - 2];//extindere pt semn
        }

        product.write(P);
        //wait(SC_ZERO_TIME);
        //sc_stop();
    }
};

#endif
