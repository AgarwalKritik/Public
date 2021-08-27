// KMP Algorithm

#include <bits/stdc++.h>

using namespace std;

void Second()
{
    system("cls");
    cout << "\x1B[34m-------------------------------------------------------------------------------------------" << endl;
    cout << "|                                KRITIK AGARWAL 19BBTCS067                                |" << endl;
    cout << "-------------------------------------------------------------------------------------------\033[0m" << endl;
}

void ComputePrefixSuffix(char *pattern, int M, int *computePrefixSuffix)
{
    int length = 0, i = 1;
    computePrefixSuffix[0] = 0;
    while (i < M)
    {
        if (pattern[i] == pattern[length])
        {
            length++;
            computePrefixSuffix[i] = length;
            i++;
        }
        else
        {
            if (length != 0)
                length = computePrefixSuffix[length - 1];
            else
            {
                computePrefixSuffix[i] = 0;
                i++;
            }
        }
    }
}

void Search(char *pattern, char *givenstring)
{
    int i = 0, j = 0, count = 0, M = strlen(pattern), N = strlen(givenstring), computePrefixSuffix[M];
    ComputePrefixSuffix(pattern, M, computePrefixSuffix);
    while (i < N)
    {
        if (pattern[j] == givenstring[i])
        {
            j++;
            i++;
        }
        if (j == M)
        {
            cout << "\n\t\t\t\x1B[32m    >>> Found pattern match at index [ " << (i - j) << " ] <<< \033[0m" << endl;
            j = computePrefixSuffix[j - 1];
            count++;
        }
        else if (i < N && pattern[j] != givenstring[i])
        {
            if (j != 0)
                j = computePrefixSuffix[j - 1];
            else
                i = i + 1;
        }
    }
    if (count == 0)
    {
        cout << "\n\t\t\t\t\x1B[31m>>> No pattern match found!! <<< \033[0m" << endl;
    }
}

int main()
{
    char givenstring[100], pattern[100];
    int ans = 1;
    do
    {
        Second();
        cout << "\n\t\t\t\x1B[33m String Matching Algorithm Demonstration in C++\033[0m" << endl;
        cout << "\n\t\t\t\tEnter String: ";
        cin >> givenstring;
        cout << "\n\t\t\t\tEnter Pattern To Search: ";
        cin >> pattern;
        Search(pattern, givenstring);
        cout << "\n\n\t\t\t\t\x1B[35mEnter Any Number To Perform Search Again\n\t\t\t\tEnter 0 to Exit\n\t\t\t\t>>> \033[0m";
        cin >> ans;
    } while (ans != 0);
    return 0;
}
