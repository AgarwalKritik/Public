// Author: Kritik Agarwal <https://github.com/Kritik007>

// Implementation of RSA Algorithm in C++

#include <bits/stdc++.h>

using namespace std;

// Function to Find Greatest Common Divisor
int GCD(int x, int y)
{
    int tmp;
    while (1)
    {
        tmp = x % y;
        if (tmp == 0)
            return y;
        x = y;
        y = tmp;
    }
}

int main()
{
    double p, q;
    cout << ">>>  Enter Two Co-prime Numbers:  ";
    cin >> p >> q;
    double n = p * q;
    double cnt;
    double fy = (p - 1) * (q - 1);

    // Public Key
    // enc stands for encrypt
    double enc = 2;
    while (enc < fy)
    {
        cnt = GCD(enc, fy);
        if (cnt == 1)
            break;
        else
            enc++;
    }

    // Private Key
    // dcry stands for decrypt
    double dcry;
    double k = 2; // k can be any arbitrary value

    // Choosing dcry such that it satisfies the condition dcry*enc = 1 + k * fy
    dcry = (1 + (k * fy)) / enc;
    double msg;
    cout << ">>>  Enter a message:  ";
    cin >> msg;
    double c = pow(msg, enc);
    double m = pow(c, dcry);
    c = fmod(c, n);
    m = fmod(m, n);
    cout << "\nMessage data = " << msg;
    cout << "\nEncrypted data = " << c;
    cout << "\nOriginal Message sent = " << m << endl;
    return 0;
}