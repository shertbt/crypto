
#include "crypto.h"

Crypto::Crypto() {}
map<char, string> Crypto::gen_hex_table()
{
    map<char, string> map;

    map['0'] = "0000";
    map['1'] = "0001";
    map['2'] = "0010";
    map['3'] = "0011";
    map['4'] = "0100";
    map['5'] = "0101";
    map['6'] = "0110";
    map['7'] = "0111";
    map['8'] = "1000";
    map['9'] = "1001";
    map['a'] = "1010";
    map['b'] = "1011";
    map['c'] = "1100";
    map['d'] = "1101";
    map['e'] = "1110";
    map['f'] = "1111";

    return map;
}

string Crypto::con_hex_2_bin(string hexStr)
{
    map<char, string> m = gen_hex_table();

    string newStr = "";
    for (int i = 0; i < hexStr.size(); i++)
    {
        newStr += m.find(hexStr[i])->second;
    }
    return newStr;
}

string Crypto::add_spaces(string str, int spaces)
{
    string newStr = "";
    int count = 0;

    for (int i = 0; i < str.size(); i++)
    {


        if (count == spaces)
        {
            newStr += " ";
            i--;
            count = 0;
        }
        else
        {
            newStr += str[i];
            count++;
        }
    }

    return newStr;
}

vector<int> Crypto::con_bin_2_dec(string str, double power)
{
    vector<int> v;
    string newStr = "";
    istringstream iss(str);
    string x;

    while (iss >> x)
    {
        double p = power;
        double decimal = 0.0;

        for (int i = 0; i < x.size(); i++)
        {
            if (x[i] == '1')
            {
                decimal += pow(2.0, p);
            }
            p--;
        }
        v.push_back((int)decimal);
    }
    return v;
}
string Crypto::con_hex_2_b64(string str)
{
    string b64 = "";
    string ref = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string newStr = add_spaces(con_hex_2_bin(str), 6);

    vector<int> v = con_bin_2_dec(newStr, 5.0);

    for (int i = 0; i < v.size(); i++)
    {
        b64 += ref[v[i]];
    }

    return b64;
}

string Crypto::con_ascii_2_hex(string str)
{
    stringstream ss;
    for (int i = 0; i < str.size(); i++)
    {
        ss << std::hex << (int)str[i];
    }
    return ss.str();
}

string Crypto::fixedXOR(string str1, string str2)
{
    //Check if the length of both the strings are equal
    if (str1.size() != str2.size())
    {
        return "The strings are not of equal length.";
    }
    else
    {
        string newStr = "";

        
        str1 = add_spaces(con_hex_2_bin(str1), 8);
        str2 = add_spaces(con_hex_2_bin(str2), 8);

        
        vector<int> v1 = con_bin_2_dec(str1, 7.0);
        vector<int> v2 = con_bin_2_dec(str2, 7.0);

        
        for (int i = 0; i < v1.size(); i++)
        {
            
            unsigned char a = v1[i];

            
            unsigned char b = v2[i];

           
            unsigned char c = a ^ b;

            
            newStr += c;
        }

        
        return con_ascii_2_hex(newStr);
    }
}
string Crypto::single_byte_xor(string str)
{
    string newStr = "";
    float score = 0;
    float maxScore = 0;
   
    str = add_spaces(con_hex_2_bin(str), 8);
    string message = "";
 
    vector<int> v = con_bin_2_dec(str, 7.0);
    for (int key = 0; key < 256; key++)
    {
        for (int i = 0; i < v.size(); i++)
        {
            unsigned char b = v[i];
            unsigned char c = b ^ (char)key;
            newStr += c;

        }
        score = get_score(newStr);
        if (score > maxScore)
        {
            maxScore = score;
            message = newStr;
        }
        newStr = "";
    }
  
    return message;
}

float Crypto::get_score(string input)
{

    std::map<int, float> FREQUENCY = {
     {'a',  0.08167},
     {'b',  0.01492},
     {'c',  0.02782},
     {'d',  0.04253},
     {'e',  0.12702},
     {'f',  0.02228},
     {'g',  0.02015},
     {'h',  0.06094},
     {'i',  0.06966},
     {'j',  0.00153},
     {'k',  0.00772},
     {'l',  0.04025},
     {'m',  0.02406},
     {'n',  0.06749},
     {'o',  0.07507},
     {'p',  0.01929},
     {'q',  0.00095},
     {'r',  0.05987},
     {'s',  0.06327},
     {'t',  0.09056},
     {'u',  0.02758},
     {'v',  0.00978},
     {'w',  0.02360},
     {'x',  0.00150},
     {'y',  0.01974},
     {'z',  0.00074},
     {' ', 0.13000}
    };
    float sum = 0;
    for (int i = 0; i < input.size(); i++)
        sum = sum + FREQUENCY[tolower((int)input[i])];
    return sum;
};
std::pair<string, float> Crypto::detectSingleByteXOR(vector<int> v)
{
    std::pair<string, float> result;
    string newStr = "";
    float score = 0;
    float maxScore = 0;
    string message = "";
    for (int key = 0; key < 256; key++)
    {
        for (int i = 0; i < v.size(); i++)
        {
            unsigned char b = v[i];
            unsigned char c = b ^ (char)key;
            newStr += c;

        }
        score = get_score(newStr);
        if (score > maxScore)
        {
            maxScore = score;
            message = newStr;
        }
        newStr = "";
    }
    result = std::make_pair(message, maxScore);
    return result;
}
string Crypto::repeatingKeyXOR(string str, string key)
{
    string newStr = "";
    int count = 0;


    for (int i = 0; i < str.size(); i++)
    {
        unsigned char a = key[count];
        unsigned char b = str[i];
        unsigned char c = b ^ a;

        newStr += c;

        if (count == key.size() - 1)
        {
            count = 0;
        }
        else
        {
            count++;
        }
    }

   
    string final = "";
    final += con_ascii_2_hex(newStr);
    return final;
}
char Crypto::single_byte_xor_2(string str)
{
    string newStr = "";
    float score = 0;
    float maxScore = 0;
    char ch;
    for (int key = 0; key <= 256; key++)
    {

        for (int i = 0; i < str.size(); i++)
        {
            unsigned char b = str[i];
            unsigned char c = b ^ (char)key;
            newStr += c;

        }
        score = get_score(newStr);
        if (score > maxScore)
        {
            maxScore = score;
            ch = (char)key;
        }
        newStr = "";
    }

    return ch;
}
int Crypto::hamming_distance(string str1, string str2)
{
    int count = 0;
    for (int i = 0; i < str1.size(); i++)
    {
        int partial = (str1[i] & 0xFF) ^ (str2[i] & 0xFF);
        while (partial)
        {
            count += partial & 1;
            partial = partial >> 1;
        }
    }
    return count;
}

int Crypto::guess_key_length(string cipherText)
{
    int KEYSIZE = -1;
    double leastNormalized = INT_MAX;

    
    for (int i = 2; i < 40; i++)
    {
        double normalize = 0.0f;

        
        int bytes = cipherText.size() / i;

        for (int j = 0; j < bytes - 1; j++)
        {
            string blockA = cipherText.substr((j * i), i);
            string blockB = cipherText.substr(((j + 1) * i), i);

            
            int edit_distance = hamming_distance(blockA, blockB);

            normalize += ((double)edit_distance) / ((double)blockA.size());
        }

         
        normalize /= bytes;

       
        if (normalize > 0 && normalize < leastNormalized)
        {
            leastNormalized = normalize;
            KEYSIZE = i;
        }
    }

   
    return KEYSIZE;
}

string Crypto::con_b64_2_hex(string str)
{
    string hex = "";
    string ref = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string binary = "";

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != '\n' && str[i] != '=')
        {
            int pos = ref.find(str[i]);
            string bits = con_dec_2_bin(pos);
            binary += bits;
        }
    }
    binary = add_spaces(binary, 4);

    istringstream iss(binary);
    string x;

    map<char, string> m = gen_hex_table();
    map<char, string>::iterator it;

    while (iss >> x)
    {
        for (it = m.begin(); it != m.end(); it++)
        {
            if (it->second == x)
            {
                hex += it->first;
            }
        }
    }

    return hex;
}

string Crypto::con_dec_2_bin(int decimal)
{
    string newStr = "";
    int value = decimal;
    while (value != 0)
    {
        int rem = value % 2;
        value = value / 2;
        char c = rem + '0';
        newStr += c;
    }
    if (newStr.size() < 6)
    {
        int deficit = 6 - newStr.size();
        for (int i = 0; i < deficit; i++)
        {
            newStr += "0";
        }
    }
    reverse(newStr.begin(), newStr.end());
    return newStr;
}
string Crypto::con_hex_2_ascii(string str)
{
    string newStr = "";
    string str2 = add_spaces(con_hex_2_bin(str), 8);
    vector<int> v = con_bin_2_dec(str2, 7.0);

    for (int i = 0; i < v.size(); i++)
    {
        newStr += (char)v[i];
    }
    return newStr;
}