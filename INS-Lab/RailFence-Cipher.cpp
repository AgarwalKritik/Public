// Author: Kritik Agarwal <https://github.com/Kritik007>

// Implementation of Rail Fence Cipher Algorithm in C++

#include <bits/stdc++.h>

using namespace std;

void heading()
{
    system("cls");
    cout << "-------------------------------------------------------------------------------------------" << endl;
    cout << "|                                KRITIK AGARWAL 19BBTCS067                                |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
}

// Function to encrypt a message
static string encRF(string input, int key)
{
    // Creating the matrix to cipher plain text, where key = rows , length(text) = columns
    char rail[key][(input.length())];

    // Filling the rail matrix to distinguish filled spaces from blank ones
    for (int i = 0; i < key; i++)
        for (int j = 0; j < input.length(); j++)
            rail[i][j] = '\n';

    // Finding the direction
    bool dir_down = false;
    int row = 0, col = 0;

    for (int i = 0; i < input.length(); i++)
    {
        // Checking the direction of flow reverse the direction if we've just filled the top or bottom rail
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;

        // Filling the corresponding alphabet
        rail[row][col++] = input[i];

        // Finding the next row using direction flag
        dir_down ? row++ : row--;
    }

    // Constructing the cipher using the rail matrix
    string result;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < input.length(); j++)
            if (rail[i][j] != '\n')
                result.push_back(rail[i][j]);

    return result;
}

// Function to decrypt the message
static string decRF(string cipher, int key)
{
    // Creating the matrix to cipher plain text || key = rows , length(text) = columns
    char rail[key][cipher.length()];

    // Filling the rail matrix to distinguish filled spaces from blank ones
    for (int i = 0; i < key; i++)
        for (int j = 0; j < cipher.length(); j++)
            rail[i][j] = '\n';

    // Finding the direction
    bool dir_down;

    int row = 0, col = 0;

    // Marking the places with '*'
    for (int i = 0; i < cipher.length(); i++)
    {
        // Checking the direction of flow
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;

        // Placing the marker
        rail[row][col++] = '*';

        // Finding the next row using direction flag
        dir_down ? row++ : row--;
    }

    // Constructing to fill the rail matrix
    int index = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < cipher.length(); j++)
            if (rail[i][j] == '*' && index < cipher.length())
                rail[i][j] = cipher[index++];

    // Reading the matrix in zig-zag manner to construct the resultant text
    string result;
    row = 0, col = 0;
    for (int i = 0; i < cipher.length(); i++)
    {
        // Checking the direction of flow
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;

        // Placing the marker
        if (rail[row][col] != '*')
            result.push_back(rail[row][col++]);

        // Finding the next row using direction flag
        dir_down ? row++ : row--;
    }
    return result;
}

//  Main Function
int main()
{
    heading();
    string str;
    int n;
    cout << ">> Enter Some String Value: ";
    getline(cin, str);
    cout << ">> Enter a key integer value: ";
    cin >> n;
    // Encrypt the msg and display
    string enc = encRF(str, n);
    cout << "\n>> Encrypted Text: " << enc << endl;

    // Decrypt the msg
    cout << "\n>> Decrypted Text: " << decRF(enc, n) << endl;
    return 0;
}
