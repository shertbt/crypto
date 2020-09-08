#include "crypto.h"

int main()
{
    Crypto crypt;

    ifstream infile;
    string str;
    int maxCount = 0;
    std::pair<string, float> mess;
    infile.open("C:\\Users\\ִלטענטי\\Desktop\\enctext.txt");
    string maxStr = "";
    //if the file is not there
    if (!infile)
    {
        cout << "Unable to open the file";
        exit(1);
    }

    while (infile >> str)
    {
        //Only look for strings with 60 char length
        if (str.size() == 60)
        {
            str = crypt.add_spaces(crypt.con_hex_2_bin(str), 8);
            vector<int> v = crypt.con_bin_2_dec(str, 7.0);
            mess = crypt.detectSingleByteXOR(v);
            if (maxCount < mess.second)
            {
                maxStr = mess.first;
                maxCount = mess.second;
            }
        }
    }

   cout <<maxStr << endl;
    return 0;
}