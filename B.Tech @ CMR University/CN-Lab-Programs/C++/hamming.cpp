// Copyright (C) 2021 Kritik Agarwal <https://github.com/Kritik007>

// Write a program for Hamming code/CRC.

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a, b, c[30], d, r = 0, d1;
    cout << " Enter the No of Data Bits you want to Enter : ";
    cin >> a;
    while (a + r + 1 > pow(2, r))
    {
        r++;
    }
    cout << "No of data bits to be added " << r << " : Total Bits :" << a + r << endl;
    cout << " Enter the Data Bits One by One :" << endl;
    for (int i = 1; i <= a; ++i)
        cin >> c[i];
    cout << endl
         << " Data bits entered : ";
    for (int i = 1; i <= a; ++i)
        cout << c[i] << " ";
    cout << endl;
    int data[a + r];
    d = 0;
    d1 = 1;
    for (int i = 1; i <= a + r; ++i)
    {
        if ((i) == pow(2, d))
        {
            data[i] = 0;
            ++d;
        }
        else
        {
            data[i] = c[d1];
            ++d1;
        }
    }
    cout << " Data Bits are Encoded with Parity bits(0): ";
    for (int i = 1; i <= a + r; ++i)
        cout << data[i] << " ";
    d1 = 0;
    int min, max = 0, parity, s, j;
    for (int i = 1; i <= a + r; i = pow(2, d1))
    {
        ++d1;
        parity = 0;
        j = i;
        s = i;
        min = 1;
        max = i;
        for (j; j <= a + r;)
        {
            for (s = j; max >= min && s <= a + r; ++min, ++s)
            {
                if (data[s] == 1)
                    parity++;
            }
            j = s + i;
            min = 1;
        }
        if (parity % 2 == 0)
            data[i] = 0;
        else
            data[i] = 1;
    }
    cout << endl << " Hamming codeword bits for even parity are : ";
    for (int i = 1; i <= a + r; ++i)
        cout << data[i] << " ";
    cout << endl << endl;
}
