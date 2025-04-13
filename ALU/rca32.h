#ifndef RCA32_H
#define RCA32_H
#include<systemc.h>

SC_MODULE(RCA32){
    sc_in<sc_int<32>>A;
    sc_in<sc_int<32>>B;
    sc_in<bool> Cin;
    sc_out<sc_int<32>> S;
    sc_out<bool> Cout;

    void compute(){
        sc_int<32> a = A.read();
        sc_int<32> b = B.read();
        bool c = Cin.read();
        sc_int<32> sum;

        for( int i = 0 ; i < 32 ; i++ ){
            sum[i] = a[i] ^ b[i] ^ c;
            c = (a[i] & b[i]) | (a[i] & c) | (b[i] & c);
        }

        S.write(sum);
        Cout.write(c);
    }

    SC_CTOR(RCA32){
        SC_METHOD(compute);
            sensitive << A << B << Cin;
    }
};

#endif