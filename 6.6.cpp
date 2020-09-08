#include "crypto.h"

int main()
{
	Crypto crypt;
	string message;
	string ascii_mess;
	string key;

	ifstream infile;


	infile.open("C:\\Users\\Äìèòðèé\\Desktop\\text6.6.txt");
	getline(infile, message, '\0');
	infile.close();

	
	ascii_mess = crypt.con_hex_2_ascii(crypt.con_b64_2_hex(message));

	
	int keyLength = crypt.guess_key_length(ascii_mess);

	
	int blocks = ascii_mess.size() / keyLength;

	for (int i = 0; i < keyLength; ++i)
	{
		string block;
		char indexKey = '\0';

		
		for (int j = 0; j < blocks; j++) {
			block += ascii_mess.substr((j * keyLength) + i, 1);
		}

		
		key += crypt.single_byte_xor(block);
	}

	cout << "KEY: " << key << endl;
	cout << "DECODED: " << crypt.con_hex_2_ascii(crypt.repeatingKeyXOR(ascii_mess, key)) << endl;

	return 0;
}
