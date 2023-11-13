#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int DisassembleOp8080(vector<uint8_t> codebuffer, int pc)
{
    vector<uint8_t>::iterator code = codebuffer.begin() + pc;
    int opbytes = 1;
    cout << pc << " ";
    switch (*code)
    {
    case 0x00:
        cout << "NOP";
        break;
    case 0x01:
        cout << "LXI B,#$" << code[2] << code[1];
        opbytes = 3;
        break;
    case 0x02:
        cout << "STAX B";
        break;
    case 0x03:
        cout << "INX B";
        break;
    case 0x04:
        cout << "INR B";
        break;
    case 0x05:
        cout << "DCR B";
        break;
    case 0x06:
        cout << "MVI B,#$" << code[1];
        opbytes = 2;
        break;
    case 0x07:
        cout << "RLC";
        break;
    case 0x08:
        cout << "NOP";
        break;
    case 0x09:
        cout << "DAD B";
        break;
    case 0x0a:
        cout << "LDAX B";
        break;
    case 0x0b:
        cout << "DCX B";
        break;
    case 0x0c:
        cout << "INR C";
        break;
    case 0x0d:
        cout << "DCR C";
    case 0x0e:
        cout << "MVI " << code[1] << ",D8";
    default:
        break;
    }
    cout << "\n";
    return opbytes;
}

int main()
{
    ifstream program;
    program.open("invaders");
    string line;
    vector<uint8_t> s;
    int t;
    while (program >> hex >> t)
    {
        s.push_back((uint8_t)t);
    }
    program.close();
    int pc = 0;
    while (pc < (int)s.size())
    {
        pc += DisassembleOp8080(s, pc);
    }

    return 0;
}