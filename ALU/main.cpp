#include <systemc.h>
#include "ALU_mux.h"

int sc_main(int argc, char* argv[]) {
     sc_signal<sc_int<32>> A, B, result, rem;
     sc_signal<sc_uint<3>> opcode;
     sc_signal<bool> Cin, CoutAdd, CoutSub;

     ALU alu("alu");
     alu.A(A);          alu.B(B);
     alu.opcode(opcode);
     alu.Cin(Cin);
     alu.result(result);
     alu.CoutAdd(CoutAdd);
     alu.CoutSub(CoutSub);
     alu.Remainder(rem);

     //=== ADD ===
     cout << "\n=== ADD ===" << endl;
     A.write(648); B.write(4); Cin.write(false); opcode.write(0);
     sc_start(1, SC_NS);
     cout << "A=" << A.read() << " B=" << B.read()
          << " Cin=" << Cin.read()
          << " => S=" << result.read()
          << " Cout=" << CoutAdd.read()
          << endl;
     A.write(5); B.write(6); Cin.write(true); opcode.write(0);
     sc_start(1, SC_NS);
     cout << "A=" << A.read() << " B=" << B.read()
          << " Cin=" << Cin.read()
          << " => S=" << result.read()
          << " Cout=" << CoutAdd.read()
          << endl;

     //=== SUBTRACT ===
     cout << "\n=== SUBTRACT ===" << endl;
     A.write(20); B.write(5); Cin.write(false); opcode.write(1);
     sc_start(1, SC_NS);
     cout << "A=" << A.read() << " B=" << B.read()
          << " => S=" << result.read()
          << " Cout=" << CoutSub.read()
          << endl;
     A.write(45); B.write(15); Cin.write(false); opcode.write(1);
     sc_start(1, SC_NS);
     cout << "A=" << A.read() << " B=" << B.read()
          << " => S=" << result.read()
          << " Cout=" << CoutSub.read()
          << endl;

     //=== MULTIPLY ===
     cout << "\n=== MULTIPLY (Booth) ===" << endl;
     A.write(7); B.write(-3); opcode.write(2);
     sc_start(1, SC_NS);
     cout << "A=" << A.read() << " * B=" << B.read()
          << " => S=" << result.read() << endl;
     A.write(-8); B.write(-4); opcode.write(2);
     sc_start(1, SC_NS);
     cout << "A=" << A.read() << " * B=" << B.read()
          << " => S=" << result.read() << endl;
     A.write(7); B.write(8); opcode.write(2);
     sc_start(1, SC_NS);
     cout << "A=" << A.read() << " * B=" << B.read()
          << " => S=" << result.read() << endl;

     //=== DIVIDE ===
     cout << "\n=== DIVIDE ===" << endl;
     A.write(1234); B.write(56); opcode.write(3);
     sc_start(1, SC_NS);
     cout << "Dividend=" << A.read() << " Divisor=" << B.read()
          << " => Quotient=" << result.read()
          << " Remainder=" << rem.read() << endl;
     A.write(-500); B.write(13); opcode.write(3);
     sc_start(1, SC_NS);
     cout << "Dividend=" << A.read() << " Divisor=" << B.read()
          << " => Quotient=" << result.read()
          << " Remainder=" << rem.read() << endl;

     //=== BITWISE AND ===
     cout << "\n=== BITWISE AND ===" << endl;
     A.write(13); B.write(10); opcode.write(4);
     sc_start(1, SC_NS);
     cout << "A=" << A.read() << " B=" << B.read()
          << " => S=" << result.read() << endl;

     //=== BITWISE OR ===
     cout << "\n=== BITWISE OR ===" << endl;
     A.write(13); B.write(10); opcode.write(5);
     sc_start(1, SC_NS);
     cout << "A=" << A.read() << " B=" << B.read()
          << " => S=" << result.read() << endl;

     //=== BITWISE XOR ===
     cout << "\n=== BITWISE XOR ===" << endl;
     A.write(13); B.write(10); opcode.write(6);
     sc_start(1, SC_NS);
     cout << "A=" << A.read() << " B=" << B.read()
          << " => S=" << result.read() << endl;

     //=== BITWISE NOT ===
     cout << "\n=== BITWISE NOT ===" << endl;
     A.write(13); B.write(0); opcode.write(7);
     sc_start(1, SC_NS);
     cout << "A=" << A.read()
          << " => S=" << result.read() << endl;

     return 0;
}
