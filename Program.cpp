#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <cmath>
#include "EichenauerLehn.hpp"
#include "Geffe.hpp"

using namespace std;

string readFromFile(string name);
void writeInFile(string name, string buf);
string convertToBits(string name);
void userInterface();
void decryption(string buf, string key);
string print_binary(char c);

int main()
{
	userInterface();
	system("pause");
	return EXIT_SUCCESS;
}

string print_binary(char c) {
	int k = 128;
	string res;
	while (k > 0) {
		if (bool(c&k) == 1) res += "1";
		else res += "0";
		k = k >> 1;
	}
	return res;
};

string readFromFile(string name)
{
	string buf;
	ifstream fin(name);
	if (!fin.is_open())
	{
		cout << "File opening error: " << strerror(errno) << endl;
		system("pause");
		exit(1);
	}
	else getline(fin, buf);
	fin.close();
	return buf;
}

void writeInFile(string name, string buf)
{
	ofstream fout(name);
	if (!fout.is_open())
	{
		cout << "File opening error: " << strerror(errno) << endl;
		system("pause");
		exit(1);
	}
	else fout << buf;
	fout.close();
}

string convertToBits(string buf)
{	
	string buf_bits;
	for (size_t i = 0; i < buf.length(); i++)
		buf_bits += print_binary(buf[i]);
	return buf_bits;
}

void decryption(string buf, string key)
{
	string resBits;
	for (size_t i = 0; i < buf.length(); i++)
		if (buf[i] == key[i]) resBits += "0";
		else resBits += "1";
	string out;
	for (size_t i = 0; i < resBits.length(); i += 8) {
		string str = resBits.substr(i, 8);
		bitset<8> bits(str);
		unsigned long num = bits.to_ulong();
		out += (char)num;
	}
	writeInFile("output.txt", out);
}

void userInterface()
{
	bool flag = false;
	int direction = 0;
	while (!flag)
	{
		cout << "1 - LFSR1 encryption\n"
			<< "2 - Geffe encryption\n"
			<< "3 - Eichenauer, Lehn encryption\n"
			<< "4 - LFSR1 decryption\n"
			<< "5 - Geffe decryption\n"
			<< "6 - Eichenauer, Lehn decryption\n"
			<< "0 - Exit\n"
			<< "> ";
		cin >> direction;
		switch (direction)
		{
		case 1:
			writeInFile("lfsr1.txt", LFSR1encryption(convertToBits(readFromFile("input.txt"))));
			writeInFile("lfsr1_key.txt", LFSR1key);
			system("pause");
			break;
		case 2:
			writeInFile("Geffe.txt", Geffe_encryption(convertToBits(readFromFile("input.txt"))));
			writeInFile("Geffe_key.txt", Geffe_key);
			system("pause");
			break;
		case 3:
			writeInFile("eichenauer_lehn.txt", ELencryption(convertToBits(readFromFile("input.txt"))));
			writeInFile("eichenauer_lehn_key.txt", ELkey);
			system("pause");
			break;
		case 4:
			if (LFSR1key == "") LFSR1key = readFromFile("lfsr1_key.txt");
			decryption((readFromFile("lfsr1.txt")), LFSR1key);
			system("pause");
			break;
		case 5:
			if (Geffe_key == "") Geffe_key = readFromFile("Geffe_key.txt");
			decryption((readFromFile("Geffe.txt")), Geffe_key);
			system("pause");
			break;
		case 6:
			if (ELkey == "") ELkey = readFromFile("eichenauer_lehn_key.txt");
			decryption((readFromFile("eichenauer_lehn.txt")), ELkey);
			system("pause");
			break;
		case 0: 
			flag = true;
			break;
		default: 
			cout << "Error! Try again..." << endl;
			system("pause");
			break;
		}
	}
}
