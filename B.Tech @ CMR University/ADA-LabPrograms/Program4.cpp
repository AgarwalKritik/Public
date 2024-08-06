#include <bits/stdc++.h>

using namespace std;

class knapsack
{
    int n, m, v[100][100], p[100], w[100];

public:
    void read_data();
    void opt_sol();
    void write_data();
};

int max(int a, int b)
{
    return a > b ? a : b;
}

void KHeader()
{
    system("cls");
    cout << "\x1B[34m-------------------------------------------------------------------------------------------" << endl;
    cout << "|                                KRITIK AGARWAL 19BBTCS067                                |" << endl;
    cout << "-------------------------------------------------------------------------------------------\033[0m" << endl;
}

void knapsack::read_data()
{
    KHeader();
    cout << ">>> Enter The Number of Elements: ";
    cin >> n;
    cout << ">>> Enter The Profits & Weight of The Elements" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << "    >>> For Item Number [ " << i << " ] : ";
        cin >> p[i] >> w[i];
    }
    cout << ">>> Enter The Capacity of Knapsack: ";
    cin >> m;
}
void knapsack::write_data()
{
    int i, j, x[10], count = 0;
    for (i = 0; i <= n; i++)
        x[i] = 0;
    i = n;
    j = m;
    while (i != 0 && j != 0)
    {
        if (v[i][j] != v[i - 1][j])
        {
            x[i] = 1;
            j = j - w[i];
        }
        i--;
    }
    for (i = 1; i <= n; i++)
    {
        if (x[i])
        {
            cout << "\tSl. No.\tWeight\tProfit" << endl;
            cout << "\t  " << ++count << "\t  " << w[i] << "\t  " << p[i] << endl;
        }
    }
    cout << ">>> The Total Profit = " << v[n][m] << endl;
}
void knapsack::opt_sol()
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (i == 0 || j == 0)
                v[i][j] = 0;
            else if (j < w[i])
                v[i][j] = v[i - 1][j];
            else
                v[i][j] = max(v[i - 1][j], v[i - 1][(j - w[i])] + p[i]);
        }
    }
}

int main()
{
    knapsack a;
    int ans = 1;
    do
    {
        a.read_data();
        a.opt_sol();
        a.write_data();
        cout << "\n\n\x1B[35mEnter Any Number To Perform Again\nEnter 0 to Exit\n>>> \033[0m";
        cin >> ans;
    } while (ans != 0);
}