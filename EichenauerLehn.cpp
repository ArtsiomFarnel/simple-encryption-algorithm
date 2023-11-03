#include <iostream>
#include "EichenauerLehn.hpp"

using namespace std;

string ELkey;

string ELencryption(string buf)
{
	int seed = 1, n = 5, a = 2, c = 3;
	string encrypt_buf;
	for (size_t i = 0; i < buf.length(); i++)
	{
		if (seed == 0) ELkey += "0";
		else ELkey += "1";
		seed = isg(n, a, c, seed);
	}
	for (size_t i = 0; i < buf.length(); i++)
		if (buf[i] == ELkey[i]) encrypt_buf += "0";
		else encrypt_buf += "1";
	return encrypt_buf;
}

int isg(int n, int a, int c, int seed)
{
	if (seed == 0) return c;
	return (a * mod_inv(seed, n) + c) % n;
}

int mod_inv(int a, int n)
{
	int b0 = n, t, q;
	int x0 = 0, x1 = 1;
	if (n == 1) return 1;
	while (a > 1)
	{
		q = a / n;
		t = n, n = a % n, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}
