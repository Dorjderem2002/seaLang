#include <iostream>
#include <iomanip>

using namespace std;

int DisassembleOp8080(unsigned char *codebuffer, int pc)
{
    unsigned char *code = &codebuffer[pc];
    int opbytes = 1;
    cout << pc << " ";
    switch (*code)
    {
    case 0x00:
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
        cout<<"MVI B,#$"<<code[1];  
        opbytes = 2;
        break;
    case 0x07:
        printf("RLC");
        break;
    case 0x08:
        printf("NOP");
        break;
    default:
        break;
    }
    cout<<"\n";
    return opbytes;
}

int main()
{
    cout << "Hello 8080" << endl;
    return 0;
}