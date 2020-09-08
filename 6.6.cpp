#include "crypto.h"

int main()
{
	Crypto crypt;
	string message;
	string ascii_mess;
	string key;

	ifstream infile;


	infile.open("C:\\Users\\ִלטענטי\\Desktop\\text6.6.txt");
	getline(infile, message, '\0');
	infile.close();

	//Convert the hexadecimal string to ASCII
	ascii_mess = crypt.con_hex_2_ascii(crypt.con_b64_2_hex(message));

	//Guess the length of the key
	int keyLength = crypt.guess_key_length(ascii_mess);

	//Transpose the message based on keysize length
	int blocks = ascii_mess.size() / keyLength;

	for (int i = 0; i < keyLength; ++i)
	{
		string block;
		char indexKey = '\0';

		/*
			Transpose the message into blocks
			based on keysize and concatenate it
			into one string
		*/
		for (int j = 0; j < blocks; j++) {
			block += ascii_mess.substr((j * keyLength) + i, 1);
		}

		//Concatenate the selected characters, which will become the predicted key
		key += crypt.single_byte_xor(block);
	}

	cout << "KEY: " << key << endl;
	cout << "DECODED: " << crypt.con_hex_2_ascii(crypt.repeatingKeyXOR(ascii_mess, key)) << endl;

	return 0;
}