#include <bits/stdc++.h>

using namespace std;

class topo
{
    int n, a[10][10], in[10];

public:
    void read();
    void find();
    void sort();
};

void Second()
{
    system("cls");
    cout << "\x1B[34m-------------------------------------------------------------------------------------------" << endl;
    cout << "|                                KRITIK AGARWAL 19BBTCS067                                |" << endl;
    cout << "-------------------------------------------------------------------------------------------\033[0m" << endl;
}

void topo::read()
{
    cout << "\n>>> Enter the no. of jobs: ";
    cin >> n;
    cout << "\n>>> Enter the adjacency matrix\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
}

void topo::find()
{
    for (int j = 0; j < n; j++)
    {
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum = sum + a[i][j];
        in[j] = sum;
    }
}

void topo::sort()
{
    int u, v, t[10], s[10];
    find();
    int top = -1;
    int k = 0;
    for (int i = 0; i < n; i++)
        if (in[i] == 0)
            s[++top] = i;
    while (top != -1)
    {
        u = s[top--];
        t[k++] = u;
        for (v = 0; v < n; v++)
        {
            if (a[u][v] == 1)
            {
                in[v]--;
                if (in[v] == 0)
                    s[++top] = v;
            }
        }
    }
    cout << "\n>>> Topological order sequence is ";
    for (int i = 0; i < n; i++)
        cout << "\033[3;42;30m" << t[i] << " "
             << "\033[0m";
}

int main()
{
    topo t;
    int a = 1;
    do
    {
        Second();
        t.read();
        t.sort();
        cout << "\n\n\x1B[35mEnter Any Number To Perform Again\nEnter 0 to Exit\n>>> \033[0m";
        cin >> a;
    } while (a != 0);

    return 0;
}