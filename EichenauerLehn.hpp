#pragma once
#include <string>

using namespace std;

extern string ELkey;

string ELencryption(string buf);
int isg(int n, int a, int c, int seed);
int mod_inv(int a, int n);
