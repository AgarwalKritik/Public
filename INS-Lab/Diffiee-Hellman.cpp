// Author: Kritik Agarwal <https://github.com/Kritik007>

// Implementation of Diffie-Hellman Algorithm in C++

#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

void heading()
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "|                           DIFFIE HELLMAN KEY EXCHANGE ALGORITHM                         |" << endl;
	cout << "|                                KRITIK AGARWAL 19BBTCS067                                |" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
}

// Power function to return value of a ^ b mod P
lli power(lli a, lli b, lli P)
{
	if (b == 1)
		return a;
	else
		return (((lli)pow(a, b)) % P);
}

// Main Function
int main()
{
	heading();
	lli P, G, x, a, y, b, ka, kb;
	cout << "-> Enter a prime number: ";
	cin >> P;
	cout << "-> Enter a primitive root for G: ";
	cin >> G;

	cout << "-> The value of P : " << P << endl;
	cout << "-> The value of G : " << G << endl;

	// Karan will choose the private key a
	a = 4; // a is the chosen private key
	cout << "\n-> The private key a for Karan : " << a << endl;
	x = power(G, a, P); // gets the generated key

	// Kritik will choose the private key b
	b = 3; // b is the chosen private key
	cout << "-> The private key b for Kritik : " << b << endl;
	y = power(G, b, P); // gets the generated key

	// Generating the secret key after the exchange of keys
	ka = power(y, a, P); // Secret key for Karan
	kb = power(x, b, P); // Secret key for Kritik

	cout << "\n-> Secret key for the Karan is : " << ka << endl;
	cout << "-> Secret Key for the Kritik is : " << kb << endl;

	if (ka == kb)
	{
		cout << "\n>>> The Key Exhange is successful!!" << endl;
	}
	else
	{
		cout << "\n>>> The Key Exchange is unsuccessful!!" << endl;
	}

	return 0;
}
