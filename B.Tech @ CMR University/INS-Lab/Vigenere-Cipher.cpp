// Author: Kritik Agarwal <https://github.com/Kritik007>

// Implementation of Vignere Cipher Algorithm in C++

#include <bits/stdc++.h>

using namespace std;

void heading()
{
    system("cls");
    cout << "-------------------------------------------------------------------------------------------" << endl;
    cout << "|                                KRITIK AGARWAL 19BBTCS067                                |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
}

// Function to generate the key in a cyclic manner until it's length isn't equal to the length of original text
static string generateKey(string str, string key)
{
    int x = str.size();

    for (int i = 0;; i++)
    {
        if (x == i)
            i = 0;
        if (key.size() == str.size())
            break;
        key.push_back(key[i]);
    }
    return key;
}

// Function to return the encrypted text generated with the help of the key
static string cipherText(string str, string key)
{
    string cipher_text;

    for (int i = 0; i < str.size(); i++)
    {
        // converting in range 0-25
        char x = (str[i] + key[i]) % 26;

        // convert into alphabets(ASCII)
        x += 'A';

        cipher_text.push_back(x);
    }
    return cipher_text;
}

// Function to decrypt the encrypted text and return the original text
static string originalText(string cipher_text, string key)
{
    string orig_text;

    for (int i = 0; i < cipher_text.size(); i++)
    {
        // converting in range 0-25
        char x = (cipher_text[i] - key[i] + 26) % 26;

        // convert into alphabets(ASCII)
        x += 'A';
        orig_text.push_back(x);
    }
    return orig_text;
}

// Main Function
int main()
{
    heading();
    string str, keyword;
    cout << ">> Enter a string value: ";
    cin >> str;
    cout << ">> Enter a keyword value: ";
    cin >> keyword;
    string key = generateKey(str, keyword);
    string cipher_text = cipherText(str, key);
    cout << "\n>> Encrypted/Cipher Text : "
         << cipher_text << "\n";
    cout << "\n>> Original/Decrypted Text : "
         << originalText(cipher_text, key) << endl;
    return 0;
}
