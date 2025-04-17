#include <systemc.h>
#include "rca32.h"
#include "Subtractor32.h"
#include "booth_multiplier.h"
#include "shift_unit.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<sc_int<32>> A;
    sc_signal<sc_int<32>> B;
    sc_signal<bool> Cin;
    sc_signal<sc_int<32>> S;
    sc_signal<bool> Cout;

    // Instantiem adder-ul
    RCA32 rca("rca");
    rca.A(A);
    rca.B(B);
    rca.Cin(Cin);
    rca.S(S);
    rca.Cout(Cout);

    sc_signal<sc_int<32>> S_sub;
    sc_signal<bool> Cout_sub;
    
    Subtractor32 sub("subtractor");
    sub.A(A);
    sub.B(B);
    sub.S(S_sub);
    sub.Cout(Cout_sub);

    // === Booth Multiplier ===
    sc_signal<sc_int<32>> multiplicand, multiplier;
    sc_signal<sc_int<64>> product;
    BoothMultiplier<32> mul("booth");
    mul.multiplicand(multiplicand);
    mul.multiplier(multiplier);
    mul.product(product);

    // Semnale pentru Shift Unit
    sc_signal<sc_int<32>> shift_input;
    sc_signal<sc_uint<5>> shift_amount;
    sc_signal<sc_int<32>> shift_left_result, shift_right_result;

    // Instantiere Shift Unit
    ShiftUnit<32, 5> shift("shift_unit");
    shift.numberToBeShifted(shift_input);
    shift.positionsToShift(shift_amount);
    shift.shiftedLeft(shift_left_result);
    shift.shiftedRight(shift_right_result);

    //==============================ADD================================
    cout << "Adunare:" << endl;
    A.write(648);
    B.write(4);
    Cin.write(0);

    sc_start(1, SC_NS); // rulam simularea

    // Afisam rezultatul
    cout << "A = " << A.read() << "\t" 
    << "B = " << B.read() << "\t"
    << "Cin = " << Cin.read() << "\t"
    << "S = " << S.read() << "\t"
    << "Cout = " << Cout.read() << endl;

    A.write(5);
    B.write(6);
    Cin.write(1);

    sc_start(1, SC_NS); 

    cout << "A = " << A.read() << "\t" 
    << "B = " << B.read() << "\t"
    << "Cin = " << Cin.read() << "\t"
    << "S = " << S.read() << "\t"
    << "Cout = " << Cout.read() << endl;   

    A.write(4294967295);
    B.write(1);
    Cin.write(1);

    sc_start(1, SC_NS); 

    cout << "A = " << A.read() << "\t" 
    << "B = " << B.read() << "\t"
    << "Cin = " << Cin.read() << "\t"
    << "S = " << S.read() << "\t"
    << "Cout = " << Cout.read() << endl;    
    
    //=============================SUB======================================
    cout << endl;
    cout << "Scadere:" << endl;

    A.write(20);
    B.write(5);

    sc_start(1, SC_NS);
    cout << "A = " << A.read()
         << ", B = " << B.read()
         << ", S = " << S_sub.read()
         << ", Cout = " << Cout_sub.read() << endl;

    A.write(45);
    B.write(15);

    sc_start(1, SC_NS);
    cout << "A = " << A.read()
         << ", B = " << B.read()
         << ", S = " << S_sub.read()
         << ", Cout = " << Cout_sub.read() << endl;

    // ========== Inmultire ==========
    cout << "\n=== Inmultire (BoothMultiplier): ===" << endl;
    multiplicand.write(7);
    multiplier.write(-3);

    sc_start(1, SC_NS);
    cout << "Multiplicand = " << multiplicand.read()
        << ", Multiplier = " << multiplier.read()
        << ", Product = " << product.read() << endl;

    multiplicand.write(-20);
    multiplier.write(-11);

    sc_start(1, SC_NS);
    cout << "Multiplicand = " << multiplicand.read()
        << ", Multiplier = " << multiplier.read()
        << ", Product = " << product.read() << endl;


    // ========== Shiftare ==========
    cout << "\n=== Shiftare Stanga si Dreapta ===" << endl;
    shift_input.write(8); 
    shift_amount.write(2);
    sc_start(1, SC_NS);
    cout << "8 << 2 = " << shift_left_result.read() << endl;
    //1000 -> 100000

    shift_input.write(-32); // 111...0000
    shift_amount.write(3); 

    sc_start(1, SC_NS);
    cout << "-32 >> 3 = " << shift_right_result.read() << endl;

    return 0;
}
