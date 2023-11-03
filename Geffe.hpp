#pragma once
#include <string>

using namespace std;

extern string LFSR1key, LFSR2key, LFSR3key, Geffe_key;

string LFSR1encryption(string buf);
string LFSR2encryption(string buf);
string LFSR3encryption(string buf);
string Geffe_encryption(string buf);
