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

        // Left shift
        shiftedLeft.write(value << shift);

        // Arithmetic right shift (preserve sign)
        shiftedRight.write(value >> shift);
    }

    SC_CTOR(ShiftUnit) {
        SC_METHOD(compute_shift);
        sensitive << numberToBeShifted << positionsToShift;
    }
};

#endif
