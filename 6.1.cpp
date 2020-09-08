#include "crypto.h"

int main()
{
    Crypto crypt;
    string str = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    cout << crypt.con_hex_2_b64(str) << endl;
    return 0;
}