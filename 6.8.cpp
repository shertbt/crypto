#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>

using namespace std;


string detectAESinECB(string file) {
    ifstream input_file;
    input_file.open(file);
    string str;
    int maxcounter = 0;
    string result;
    while (!input_file.eof())
    {
        getline(input_file, str);
        int block_size = 16;

        int blocks = str.size() / block_size;
        int count = 0;
        for (int i = 0; i < blocks; i++)
        {
            //Take a substring of x number of bytes
            string strA = str.substr(i * block_size, block_size);

            for (int j = i + 1; j < blocks; j++)
            {
                //Take another substring of x number of bytes
                string strB = str.substr(j * block_size, block_size);
                if (strA == strB)
                {
                    count++;

                }
            }
        }
        if (maxcounter < count)
        {
            maxcounter = count;
            result = str;
        }
    }
    return result;
}

int main()
{
    cout << detectAESinECB("C:\\Users\\ִלטענטי\\Desktop\\text6.8.txt") << endl;
    return 0;
}