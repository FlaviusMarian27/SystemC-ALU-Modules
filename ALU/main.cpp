#include <systemc.h>
#include "ALU_mux.h"

int sc_main(int argc, char* argv[]) {
     // Semnale pentru intrări și ieșire
    sc_signal<sc_int<32>> A, B, result;
    sc_signal<sc_uint<3>> opcode;

    // Instanțiem ALU
    ALU alu("alu");
    alu.A(A);
    alu.B(B);
    alu.opcode(opcode);
    alu.result(result);

    //=== ADD ===
    cout << "\n=== ADD ===" << endl;
    A.write(648); B.write(4); opcode.write(0);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " B=" << B.read()
         << " => Result=" << result.read()
         << endl;

    A.write(5); B.write(6); opcode.write(0);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " B=" << B.read()
         << " => Result=" << result.read()
         << endl;

    //=== SUBTRACT ===
    cout << "\n=== SUBTRACT ===" << endl;
    A.write(20); B.write(5); opcode.write(1);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " B=" << B.read()
         << " => Result=" << result.read()
         << endl;

    A.write(45); B.write(15); opcode.write(1);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " B=" << B.read()
         << " => Result=" << result.read()
         << endl;

    //=== MULTIPLY ===
    cout << "\n=== MULTIPLY (Booth) ===" << endl;
    A.write(7); B.write(-3); opcode.write(2);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " * B=" << B.read()
         << " => Result=" << result.read()
         << endl;

    //=== DIVIDE ===
    cout << "\n=== DIVIDE (SRT2) ===" << endl;
    A.write(1234); B.write(56); opcode.write(3);
    sc_start(1, SC_NS);
    cout << "Dividend=" << A.read()
         << " Divisor="  << B.read()
         << " => Quotient=" << result.read()
         << endl;

    A.write(-500); B.write(13); opcode.write(3);
    sc_start(1, SC_NS);
    cout << "Dividend=" << A.read()
         << " Divisor="  << B.read()
         << " => Quotient=" << result.read()
         << endl;

    //=== AND ===
    cout << "\n=== BITWISE AND ===" << endl;
    A.write(13); B.write(10); opcode.write(4);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " B=" << B.read()
         << " => Result=" << result.read()
         << endl;

    //=== OR ===
    cout << "\n=== BITWISE OR ===" << endl;
    A.write(13); B.write(10); opcode.write(5);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " B=" << B.read()
         << " => Result=" << result.read()
         << endl;

    //=== XOR ===
    cout << "\n=== BITWISE XOR ===" << endl;
    A.write(13); B.write(10); opcode.write(6);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " B=" << B.read()
         << " => Result=" << result.read()
         << endl;

    //=== NOT ===
    cout << "\n=== BITWISE NOT ===" << endl;
    A.write(13); B.write(0); opcode.write(7);
    sc_start(1, SC_NS);
    cout << "A=" << A.read()
         << " => Result=" << result.read()
         << endl;

    return 0;
}
