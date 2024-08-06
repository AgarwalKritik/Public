// Author: Kritik Agarwal <https://github.com/Kritik007>

// Implementation of Hill Cipher Algorithm in C++

#include <bits/stdc++.h>

using namespace std;

long double encrypt[3][1], decrypt[3][1], a[3][3], b[3][3], mes[3][1], c[3][3];

void heading()
{
    system("cls");
    cout << "-------------------------------------------------------------------------------------------" << endl;
    cout << "|                                KRITIK AGARWAL 19BBTCS067                                |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
}

// Function to get key and message from user
void getKeyMessage()
{
    int i, j;
    char msg[3];
    cout << ">> Enter 3x3 matrix for key (It should be inversible):\n";
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            cin >> a[i][j];
            c[i][j] = a[i][j];
        }
    cout << "\n>> Enter a 3 letter string: ";
    cin >> msg;
    for (i = 0; i < 3; i++)
        mes[i][0] = msg[i] - 97;
}

// Function to find inverse of key matrix
void inverse()
{
    int i, j, k;
    float p, q;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            if (i == j)
                b[i][j] = 1;
            else
                b[i][j] = 0;
        }
    for (k = 0; k < 3; k++)
    {
        for (i = 0; i < 3; i++)
        {
            p = c[i][k];
            q = c[k][k];
            for (j = 0; j < 3; j++)
            {
                if (i != k)
                {
                    c[i][j] = c[i][j] * q - p * c[k][j];
                    b[i][j] = b[i][j] * q - p * b[k][j];
                }
            }
        }
    }
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            b[i][j] = b[i][j] / c[i][i];
    cout << "\n\n>> Inverse Matrix is:\n";
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            cout << b[i][j] << " ";
        cout << "\n";
    }
}

// Function to Encrypt The Message
void encryption()
{
    int i, j, k;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 1; j++)
            for (k = 0; k < 3; k++)
                encrypt[i][j] = encrypt[i][j] + a[i][k] * mes[k][j];
    cout << "\n>> Encrypted string is: ";
    for (i = 0; i < 3; i++)
        cout << (char)(fmod(encrypt[i][0], 26) + 97);
}

// Function to Decrypt The Message
void decryption()
{
    int i, j, k;
    inverse();
    for (i = 0; i < 3; i++)
        for (j = 0; j < 1; j++)
            for (k = 0; k < 3; k++)
                decrypt[i][j] = decrypt[i][j] + b[i][k] * encrypt[k][j];
    cout << "\n>> Decrypted string is: ";
    for (i = 0; i < 3; i++)
        cout << (char)(fmod(decrypt[i][0], 26) + 97);
    cout << "\n";
}

// Main Function
int main()
{
    heading();
    getKeyMessage();
    encryption();
    decryption();
}