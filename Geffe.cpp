#include <iostream>
#include <bitset>
#include "Geffe.h"

using namespace std;

string LFSR1key, LFSR2key, LFSR3key, Geffe_key;

string LFSR1encryption(string buf)
{
	bitset<23> initBits(buf.substr(0, 23));
	for (size_t i = 0; i < buf.length(); i++) {
		if (initBits[22] == 1) LFSR1key += "1";
		else LFSR1key += "0";
		initBits = (((initBits >> 18) ^ (initBits)) << 22) | (initBits >> 1); //m=x^23+x^5+1
	}
	string encrypt_buf;
	for (size_t i = 0; i < buf.length(); i++)
		if (buf[i] == LFSR1key[i]) encrypt_buf += "0";
		else encrypt_buf += "1";
	return encrypt_buf;
}

string LFSR2encryption(string buf)
{
	bitset<31> initBits(buf.substr(0, 31));
	for (size_t i = 0; i < buf.length(); i++) {
		if (initBits[30] == 1) LFSR2key += "1";
		else LFSR2key += "0";
		initBits = (((initBits >> 28) ^ (initBits)) << 30) | (initBits >> 1); //m=x^31+x^3+1
	}
	string encrypt_buf;
	for (size_t i = 0; i < buf.length(); i++)
		if (buf[i] == LFSR2key[i]) encrypt_buf += "0";
		else encrypt_buf += "1";
	return encrypt_buf;
}

string LFSR3encryption(string buf)
{
	bitset<39> initBits(buf.substr(0, 39));
	for (size_t i = 0; i < buf.length(); i++) {
		if (initBits[38] == 1) LFSR3key += "1";
		else LFSR3key += "0";
		initBits = (((initBits >> 35) ^ (initBits)) << 38) | (initBits >> 1); //m=x^39+x^4+1
	}
	string encrypt_buf;
	for (size_t i = 0; i < buf.length(); i++)
		if (buf[i] == LFSR3key[i]) encrypt_buf += "0";
		else encrypt_buf += "1";
	return encrypt_buf;
}

string Geffe_encryption(string buf) {
	if(LFSR1key == "") LFSR1encryption(buf);
	LFSR2encryption(buf);
	LFSR3encryption(buf);
	for (size_t i = 0; i < buf.length(); i++) {
		bool x1, x2, x3;
		if (LFSR1key[i] == '0') x1 = 0; else x1 = 1;
		if (LFSR2key[i] == '0') x2 = 0; else x2 = 1;
		if (LFSR3key[i] == '0') x3 = 0; else x3 = 1;
		if (((x1 & x2) | ((!x1) & x3))) Geffe_key += "1";
		else Geffe_key += "0";
	}
	string encrypt_buf;
	for (size_t i = 0; i < buf.length(); i++)
		if (buf[i] == Geffe_key[i]) encrypt_buf += "0";
		else encrypt_buf += "1";
	return encrypt_buf;
}