#include "crypto.h"

int main()
{
    Crypto crypt;

    string str = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    cout << crypt.single_byte_xor(str) << endl;
    return 0;
}