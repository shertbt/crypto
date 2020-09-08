#pragma once
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

class Crypto
{
public:
	Crypto();


	map<char, string> gen_hex_table();
	string con_hex_2_bin(string hexStr);
	string add_spaces(string str, int spaces);
	vector<int> con_bin_2_dec(string str, double power);
	string con_hex_2_b64(string str);
	string con_ascii_2_hex(string str);
	string single_byte_xor(string str);
	string fixedXOR(string str1, string str2);
	float get_score(string input);
	std::pair<string, float> detectSingleByteXOR(vector<int> maxV);
	string repeatingKeyXOR(string str, string key);
	int hamming_distance(string str1, string str2);
	int guess_key_length(string cipherText);
	string con_b64_2_hex(string str);
	string con_dec_2_bin(int decimal);
	char single_byte_xor_2(string str);
	string con_hex_2_ascii(string str);
};