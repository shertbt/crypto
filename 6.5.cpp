#include "crypto.h"

int main()
{
    Crypto crypt;

    
    string str = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal";
    string key = "ICE";

    cout << "ENCODED: " << crypt.repeatingKeyXOR(str, key) << endl;
    return 0;
}