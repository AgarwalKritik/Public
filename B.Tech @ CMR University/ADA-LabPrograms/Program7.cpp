#include <bits/stdc++.h>

using namespace std;

class bfs
{
    int A[20][20], Q[20], Visited[20], n, i, j, f = 0, r = -1;

public:
    void BFS(int v);
    void BFSmain();
};

class dfs
{
    int A[20][20], Visited[20], n;

public:
    void DFS(int v);
    void DFSmain();
};

void KHeader()
{
    system("cls");
    cout << "\x1B[34m-------------------------------------------------------------------------------------------" << endl;
    cout << "|                                KRITIK AGARWAL 19BBTCS067                                |" << endl;
    cout << "-------------------------------------------------------------------------------------------\033[0m" << endl;
}

void bfs::BFS(int v)
{
    for (i = 1; i <= n; i++)
        if (A[v][i] && !Visited[i])
            Q[++r] = i;

    if (f <= r)
    {
        Visited[Q[f]] = 1;
        BFS(Q[f++]);
    }
}
void bfs::BFSmain()
{
    KHeader();
    cout << "\n------------------------------------- BFS OPERATIONS --------------------------------------\n";
    int v;
    cout << "\n>>> Enter The Number of Vertices :";
    cin >> n;
    for (i = 1; i <= n; i++)
    {
        Q[i] = 0;
        Visited[i] = 0;
    }
    cout << "\n>>> Enter Graph Data in Matrix Form :\n";
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            cin >> A[i][j];
        }
    }
    cout << "\n>>> Enter Starting Vertex:";
    cin >> v;
    BFS(v);
    for (i = 1; i <= n; i++)
    {
        if (Visited[i])
            cout << "\n>>> The Node \x1B[32m" << i << "\033[0m is Reachable. ";
        else
        {
            cout << "\n>>>\x1B[31m BFS is Not Possible!!\033[0m\n>>>\x1B[31m Not All Nodes Are Reachable!!\033[0m";
            break;
        }
    }
    cout << "\n";
}

void dfs::DFS(int v)
{
    int i;
    Visited[v] = 1;
    for (i = 1; i <= n; i++)
        if (A[v][i] && !Visited[i])
        {
            cout << "\n"
                 << v << " -> " << i;
            DFS(i);
        }
}
void dfs::DFSmain()
{
    KHeader();
    cout << "\n------------------------------------- DFS OPERATIONS --------------------------------------\n";
    int i, j, c = 0;
    cout << "\n>>> Enter The Number of Vertices :";
    cin >> n;
    for (i = 1; i <= n; i++)
    {
        Visited[i] = 0;
        for (j = 1; j <= n; j++)
            A[i][j] = 0;
    }
    cout << "\n>>> Enter The Adjacency Matrix :\n";
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            cin >> A[i][j];
    DFS(1);
    cout << "\n";
    for (i = 1; i <= n; i++)
    {
        if (Visited[i])
            c++;
    }
    if (c == n)
        cout << "\n>>> \x1B[32mGraph is Connected!!\033[0m\n";
    else
        cout << "\n>>> \x1B[31mGraph is Not Connected!!\033[0m\n";
}

int main()
{
    bfs b;
    dfs d;
    int a = 1, ch;
    do
    {
        KHeader();
        cout << "\n---------------------------------------- MAIN MENU ----------------------------------------\n";
        cout << "\n\x1B[34m [ 1 ] BFS OPERATIONS \n [ 2 ] DFS OPERATIONS \n [ 0 ] EXIT \n >>> \033[0m";
        cin >> ch;
        switch (ch)
        {
        case 1:
            b.BFSmain();
            cout << "\n\n\x1B[35mEnter Any Number To Perform Again\nEnter 0 to Exit\n>>> \033[0m";
            cin >> a;
            break;
        case 2:
            d.DFSmain();
            cout << "\n\n\x1B[35mEnter Any Number To Perform Again\nEnter 0 to Exit\n>>> \033[0m";
            cin >> a;
            break;
        case 0:
            exit(0);
        default:
            cout << "\n>>> \x1B[31mWrong Choice!!\033[0m";
        }
    } while (a != 0);
    return 0;
}