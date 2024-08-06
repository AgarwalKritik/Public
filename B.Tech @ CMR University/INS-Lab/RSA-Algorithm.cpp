// Author: Kritik Agarwal <https://github.com/Kritik007>

// Implementation of RSA Algorithm in C++ to enCrypt and deCrypt plaintext

#include <bits/stdc++.h>

using namespace std;

void heading()
{
    system("cls");
    cout << "-------------------------------------------------------------------------------------------" << endl;
    cout << "|                                KRITIK AGARWAL 19BBTCS067                                |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
}

// Function to find Greatest Common Divisor
long int GCD(long int a, long int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    return GCD(b, a % b);
}

// Function to check whether the number is prime or not
long int isPrime(long int a)
{
    int i;
    for (i = 2; i < a; i++)
    {
        if ((a % i) == 0)
            return 0;
    }
    return 1;
}

// Function to encrypt the plaintext message
long int enCrypt(char ch, long int n, long int e)
{
    int i;
    long int temp = ch;
    for (i = 1; i < e; i++)
        temp = (temp * ch) % n;
    return temp;
}

// Function to decrypt the plaintext message
char deCrypt(long int ch, long int n, long int d)
{
    int i;
    long int temp = ch;
    for (i = 1; i < d; i++)
        ch = (temp * ch) % n;
    return ch;
}

// Main Function
int main()
{
    heading();
    long int i, len;
    long int p, q, n, fy, e, d, cipher[50];
    char text[50];

    // Get input of plaintext here
    cout << ">> Enter the text to be encrypted: ";
    cin.getline(text, sizeof(text));
    len = strlen(text);

    // Generate Two Random Prime Numbers for encryption and decryption
    do
    {
        p = rand() % 30;
    } while (!isPrime(p));

    do
    {
        q = rand() % 30;
    } while (!isPrime(q));

    // Calculation of value of n and ɸ[fy]
    n = p * q;
    fy = (p - 1) * (q - 1);

    // Generate Value of e (encryption) and d (decryption) such that it satifies the condition gcd(ɸ,e)=1
    do
    {
        e = rand() % fy;
    } while (GCD(fy, e) != 1);

    do
    {
        d = rand() % fy;
    } while (((d * e) % fy) != 1);

    // Display the generated prime numbers
    cout << "\n>> Two prime numbers (p and q) are: " << p << " and " << q << endl;

    // Display the generated public and private keys
    cout << "\n>> Public Key (n, e): (" << n << ", " << e << ")\n";
    cout << ">> Private key (n, d): (" << n << ", " << d << ")\n";

    // Encrypt the message through loop
    for (i = 0; i < len; i++)
        cipher[i] = enCrypt(text[i], n, e);

    // Display the encrypted message
    cout << "\n>> Encrypted message: ";
    for (i = 0; i < len; i++)
        cout << cipher[i];

    // Decrypt the message through loop
    for (i = 0; i < len; i++)
        text[i] = deCrypt(cipher[i], n, d);

    // Display the decrypted message
    cout << "\n>> Decrypted message: ";
    for (i = 0; i < len; i++)
        cout << text[i];

    cout << endl;
    return 0;
}