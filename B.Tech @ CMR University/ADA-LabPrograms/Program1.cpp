#include <bits/stdc++.h>

using namespace std;

class Sort
{
    int A[30], N;

public:
    void Qsort();
    void msort();
    void isort();
    void choice();
};

void Second()
{
    system("cls");
    cout << "-------------------------------------------------------------------------------------------" << endl;
    cout << "|                                KRITIK AGARWAL 19BBTCS067                                |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
}

void Sort::choice()
{
    int k = 4;
    Second();
    cout << "\n\n\t\t\t\tWELCOME TO SORTING METHODS WINDOW." << endl;
    cout << "\n\t\t\t\tWhich operation you want to perform?" << endl;
    while (k > 0)
    {
        cout << "\n\n\t\t\t\t-------------------------------------" << endl;
        cout << "\t\t\t\t\t      Main Menu" << endl;
        cout << "\t\t\t\t-------------------------------------" << endl;
        cout << "\n\t\t\t\t1) Insertion Sort\n\t\t\t\t2) Merge Sort\n\t\t\t\t3) Quick Sort\n\t\t\t\tPress \"0\" to EXIT" << endl;
        cout << "\n\t\t\t\t-------------------------------------" << endl;
        cout << "\n\t\t\t\tEnter your choice: ";
        cin >> k;
        switch (k)
        {
        case 1:
            isort();
            return;
        case 2:
            msort();
            return;
        case 3:
            Qsort();
            return;
        case 0:
            exit(0);
        default:
            cout << "Wrong Input!!";
        }
    }
}

void Sort::isort()
{
    int A[1000], a, b, c, tmp;
    Second();
    cout << "\n\n\t\t\t\t-------------------------------------" << endl;
    cout << "\t\t\t\t  WELCOME TO INSERTION SORT WINDOW.\n";
    cout << "\t\t\t\t-------------------------------------" << endl;
    cout << "\n\t\t\t\tEnter size of array: ";
    cin >> a;
    cout << "\n\t\t\t\tEnter array elements: ";
    for (b = 0; b < a; b++)
        cin >> A[b];
    for (b = 1; b <= a - 1; b++)
    {
        for (c = b; c > 0 && A[c - 1] > A[c]; c--)
        {
            tmp = A[c];
            A[c] = A[c - 1];
            A[c - 1] = tmp;
        }
    }
    cout << "\n\t\t\t\tResult: ";
    for (b = 0; b <= a - 1; b++)
    {
        cout << A[b];
        if (b < a - 1)
            cout << " , ";
    }
    cout << "\n\t\t\t\t-------------------------------------";
}

void merge(int a[], int i1, int j1, int i2, int j2)
{
    int temp[50];
    int i, j, k;
    i = i1;
    j = i2;
    k = 0;
    while (i <= j1 && j <= j2)
    {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    while (i <= j1)
        temp[k++] = a[i++];
    while (j <= j2)
        temp[k++] = a[j++];
    for (i = i1, j = 0; i <= j2; i++, j++)
        a[i] = temp[j];
}
void mergesort(int a[], int i, int j)
{
    int mid;
    if (i < j)
    {
        mid = (i + j) / 2;
        mergesort(a, i, mid);
        mergesort(a, mid + 1, j);
        merge(a, i, mid, mid + 1, j);
    }
}
void Sort::msort()
{
    int a[30], n, i;
    Second();
    cout << "\n\n\t\t\t\t-------------------------------------" << endl;
    cout << "\t\t\t\t    WELCOME TO MERGE SORT WINDOW.\n";
    cout << "\t\t\t\t-------------------------------------" << endl;
    cout << "\n\t\t\t\tEnter size of array: ";
    cin >> n;
    cout << "\n\t\t\t\tEnter array elements: ";
    for (i = 0; i < n; i++)
        cin >> a[i];
    mergesort(a, 0, n - 1);
    cout << "\n\t\t\t\tResult: ";
    for (i = 0; i < n; i++)
    {
        cout << a[i];
        if (i < n - 1)
            cout << " , ";
    }
    cout << "\n\t\t\t\t-------------------------------------";
}

void quicksort(int x[10], int ft, int lt)
{
    int pvt, j, temp, i;
    if (ft < lt)
    {
        pvt = ft;
        i = ft;
        j = lt;
        while (i < j)
        {
            while (x[i] <= x[pvt] && i < lt)
                i++;
            while (x[j] > x[pvt])
                j--;
            if (i < j)
            {
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
        temp = x[pvt];
        x[pvt] = x[j];
        x[j] = temp;
        quicksort(x, ft, j - 1);
        quicksort(x, j + 1, lt);
    }
}
void Sort::Qsort()
{
    Second();
    cout << "\n\n\t\t\t\t-------------------------------------" << endl;
    cout << "\t\t\t\t    WELCOME TO QUICK SORT WINDOW.\n";
    cout << "\t\t\t\t-------------------------------------" << endl;
    int x[20], size, i;
    cout << "\n\t\t\t\tEnter size of array: ";
    cin >> size;
    cout << "\n\t\t\t\tEnter array elements: ";
    for (i = 0; i < size; i++)
        cin >> x[i];
    quicksort(x, 0, size - 1);
    cout << "\n\t\t\t\tResult: ";
    for (i = 0; i < size; i++)
    {
        cout << x[i];
        if (i < size - 1)
            cout << " , ";
    }
    cout << "\n\t\t\t\t-------------------------------------";
}

int main()
{
    Sort s;
    int a = 1;
    do
    {
        s.choice();
        cout << "\n\n\t\t\t\tEnter Any Number To Perform Sorting Again\n\t\t\t\tEnter 0 to Exit\n\t\t\t\t>>> ";
        cin >> a;
    } while (a != 0);
}