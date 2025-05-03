#include <systemc.h>
#include "rca32.h"
#include "Subtractor32.h"
#include "booth_multiplier.h"
#include "shift_unit.h"
#include "bitwise_and.h"
#include "bitwise_or.h"
#include "bitwise_xor.h"
#include "bitwise_not.h"

int sc_main(int argc, char* argv[]) {
    // Semnale pentru adunare și scădere (signed)
    sc_signal<sc_int<32>> A, B;
    sc_signal<bool> Cin;
    sc_signal<sc_int<32>> S_add;
    sc_signal<bool> Cout_add;

    // Instanțiere adder
    RCA32 rca("rca");
    rca.A(A); rca.B(B); rca.Cin(Cin);
    rca.S(S_add); rca.Cout(Cout_add);

    // Semnale pentru scădere
    sc_signal<sc_int<32>> S_sub;
    sc_signal<bool> Cout_sub;
    Subtractor32 sub("subtractor");
    sub.A(A); sub.B(B);
    sub.S(S_sub); sub.Cout(Cout_sub);

    // Înmultire Booth (signed)
    sc_signal<sc_int<32>> multiplicand, multiplier;
    sc_signal<sc_int<64>> product;
    BoothMultiplier<32> mul("booth");
    mul.multiplicand(multiplicand);
    mul.multiplier(multiplier);
    mul.product(product);

    // Shift unit (signed)
    sc_signal<sc_int<32>> shift_in;
    sc_signal<sc_uint<5>> shift_amt;
    sc_signal<sc_int<32>> shl_res, shr_res;
    ShiftUnit<32,5> shift("shift_unit");
    shift.numberToBeShifted(shift_in);
    shift.positionsToShift(shift_amt);
    shift.shiftedLeft(shl_res);
    shift.shiftedRight(shr_res);

    // --- Bitwise (unsigned) ---
    sc_signal<sc_uint<32>> A_u, B_u;
    sc_signal<sc_uint<32>> y_and, y_or, y_xor, y_not;

    BitwiseAnd<32> bw_and("bw_and");
    bw_and.A(A_u); bw_and.B(B_u); bw_and.Y(y_and);

    BitwiseOr<32> bw_or("bw_or");
    bw_or.A(A_u);  bw_or.B(B_u);  bw_or.Y(y_or);

    BitwiseXor<32> bw_xor("bw_xor");
    bw_xor.A(A_u); bw_xor.B(B_u); bw_xor.Y(y_xor);

    BitwiseNot<32> bw_not("bw_not");
    bw_not.A(A_u); bw_not.Y(y_not);

    //============================== ADD ==============================
    cout << "=== ADD ===" << endl;
    A.write(648); B.write(4); Cin.write(0);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " B=" << B.read()
         << " Cin=" << Cin.read()
         << " S=" << S_add.read()
         << " Cout=" << Cout_add.read()
         << endl;

    A.write(5); B.write(6); Cin.write(1);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " B=" << B.read()
         << " Cin=" << Cin.read()
         << " S=" << S_add.read()
         << " Cout=" << Cout_add.read()
         << endl;

    //============================= SUB ================================
    cout << "\n=== SUBTRACT ===" << endl;
    A.write(20); B.write(5);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " B=" << B.read()
         << " S=" << S_sub.read()
         << " Cout=" << Cout_sub.read()
         << endl;

    A.write(45); B.write(15);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " B=" << B.read()
         << " S=" << S_sub.read()
         << " Cout=" << Cout_sub.read()
         << endl;

    //========================== MULTIPLY =============================
    cout << "\n=== MULTIPLY (Booth) ===" << endl;
    multiplicand.write(7); multiplier.write(-3);
    sc_start(1, SC_NS);
    cout << "M='" << multiplicand.read()
         << "' * '" << multiplier.read()
         << "' = " << product.read()
         << endl;

    //=========================== SHIFT ===============================
    cout << "\n=== SHIFT ===" << endl;
    shift_in.write(8); shift_amt.write(2);
    sc_start(1, SC_NS);
    cout << "8 << 2 = " << shl_res.read() << endl;

    shift_in.write(-32); shift_amt.write(3);
    sc_start(1, SC_NS);
    cout << "-32 >> 3 = " << shr_res.read() << endl;

    //========================= BITWISE ===============================
    cout << "\n=== BITWISE ===" << endl;
    A_u.write(13);
    B_u.write(10);
    sc_start(1, SC_NS);

    cout << "A=13 B=10" << endl;
    cout << "A & B = " << y_and.read() << endl;  // should be 8
    cout << "A | B = " << y_or.read()  << endl;  // should be 15
    cout << "A ^ B = " << y_xor.read() << endl;  // should be 7
    cout << "~A    = " << y_not.read() << endl;  // 4294967282

    return 0;
}
