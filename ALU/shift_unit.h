#ifndef SHIFT_UNIT_H
#define SHIFT_UNIT_H

#include <systemc.h>

template<int nrBits, int positionsToShiftBits>
SC_MODULE(ShiftUnit) {
    sc_in<sc_int<nrBits>> numberToBeShifted;
    sc_in<sc_uint<positionsToShiftBits>> positionsToShift;
    sc_out<sc_int<nrBits>> shiftedLeft;
    sc_out<sc_int<nrBits>> shiftedRight;

    void compute_shift() {
        sc_int<nrBits> value = numberToBeShifted.read();
        sc_uint<positionsToShiftBits> shift = positionsToShift.read();

        sc_int<nrBits> leftResult = 0;
        sc_int<nrBits> rightResult = 0;

        //pentru shiftarea la stanga
        for( int i = nrBits - 1 ; i >= 0 ; i-- ){
            if( i >= shift ){
                leftResult[i] = value[i - shift];
            }else{
                leftResult[i] = 0;
            }
        }

        //shiftare la dreapta
        for( int i = 0 ; i < nrBits ; i++ ){
            if( i + shift < nrBits ){
                rightResult[i] = value[i + shift];
            }else{
                rightResult[i] = value[nrBits - 1];//bit de semn
            }
        }

        //scriem rezultatul iesirilor
        shiftedLeft.write(leftResult);
        shiftedRight.write(rightResult);
    }

    SC_CTOR(ShiftUnit) {
        SC_METHOD(compute_shift);
        sensitive << numberToBeShifted << positionsToShift;
    }
};

#endif