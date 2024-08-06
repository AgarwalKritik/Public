// Author: Kritik Agarwal <https://github.com/Kritik007>

// Implementation of Caesar Cipher Algorithm in C++

#include <bits/stdc++.h>

using namespace std;

void heading()
{
    system("cls");
    cout << "-------------------------------------------------------------------------------------------" << endl;
    cout << "|                                KRITIK AGARWAL 19BBTCS067                                |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
}

// Function to receive text and shift and return the encrypted text
static string cipher(string input, int key)
{
    string result = "";
    char ch;
    // Traverse text
    for (int i = 0; i < input.length(); i++)
    {
        ch = input[i];
        // Apply transformation to each char
        // Encrypt Uppercase letters
        if (isupper(input[i]))
        {
            if (ch >= 'A' && ch <= 'Z')
                result += char(int(input[i] + key - 65 + 26) % 26 + 65);
        }
        // Encrypt Lowercase letters
        else
        {
            if (ch >= 'a' && ch <= 'z')
                result += char(int(input[i] + key - 97 + 26) % 26 + 97);
        }
    }

    // Return the resulting string
    return result;
}

static string decipher(string input, int key)
{
    string result = "";
    char ch;
    for (int i = 0; i < input.length(); i++)
    {
        ch = input[i];
        // Apply transformation to each char
        // Decrypt Uppercase letters
        if (isupper(input[i]))
        {
            if (ch >= 'A' && ch <= 'Z')
                result += char(int(input[i] - key - 65) % 26 + 65);
        }
        // Decrypt Lowercase letters
        else
        {
            if (ch >= 'a' && ch <= 'z')
                result += char(int(input[i] - key - 97) % 26 + 97);
        }
    }
    return result;
}

// Main Function
int main()
{
    heading();
    string text;
    int s;
    cout << ">> Enter Plain Text Value: ";
    cin >> text;
    cout << ">> Enter Value between 0-25 to Shift PlainText by: ";
    cin >> s;
    string cipher_res = cipher(text, s);
    string decipher_res = decipher(cipher_res, s);
    cout << "\n>> Encrypted Caesar-Cipher Text: " << cipher_res << endl;
    cout << "\n>> Decrypted Caesar-Cipher Text: " << decipher_res << endl;
    return 0;
}