#include "crypto.h"

int main()
{
    Crypto crypt;

    //The test cases provided
    string str1 = "1c0111001f010100061a024b53535009181c";
    string str2 = "686974207468652062756c6c277320657965";

    cout << crypt.fixedXOR(str1, str2) << endl;
    return 0;
}