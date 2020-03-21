#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
namespace quick{
void quickSortM3(vector <ull> &ans, int st, int dr)
{
    if (st + 1 >= dr)
    {
        if (ans[st] > ans[dr])
            swap(ans[st], ans[dr]);
    }
    ull pivot, mid = (st + dr) / 2, temp;
    int p1 = st, p2 = dr;
    if (ans[st] < ans[mid]) swap(ans[st], ans[mid]);
    if (ans[st] < ans[dr]) swap (ans[st], ans[dr]);
    if (ans[mid] < ans[dr]) swap(ans[dr], ans[mid]);
    swap (ans[dr], ans[mid]);
    pivot = ans[dr];
    p1 = st - 1;
    for (p2 = st; p2 < dr; p2++)
    {
        if (ans[p2] < pivot)
        {
            p1 ++;
            temp = ans[p1];
            ans[p1] = ans[p2];
            ans[p2] = temp;
        }
    }
    p1 ++;
    temp = ans[p1];
    ans[p1] = pivot;
    ans[dr] = temp;
    if (st <= p1 - 1)
        quickSortM3(ans, st, p1 - 1 );
    if (p1 + 1 <= dr)
        quickSortM3(ans, p1 + 1 , dr);
}

bool quickSortM3(vector <ull> &v, vector<ull> &ans)
{
    int n = v.size();
    ull Max;
    if (n > 10000000)
        return 0;
    if (n == 0)
        return 1;
    Max = ans[0];
    for (int i = 0 ; i < n; i++)
    {
        Max = max(Max, ans[0]);
        ans[i] = v[i];
    }
    bool flag = 1;
    for (int i = 1; i < n; i++)
    {
        if (ans[i - 1] > ans[i])
            flag = 0;
    }
    if (flag == 1)
        return 1;
    if (n / Max >= 15000 and n >= 100000)
        return 0;
    quickSortM3(ans, 0, n - 1);
    return 1;
}

inline ull BFPRT_sort(ull*v, int st, int dr)
{
    int i,j;
    ull temp;
    for (i = st; i < dr; i++)
    {
        for (j = i + 1; j <= dr; j++)
        {
            if (v[i] > v[j])
            {
                temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
    return v[(st + dr)/2];
}

ull BFPRT(ull*v, int dr)
{
    if (dr <= 5)
     return BFPRT_sort(v, 0, dr);
    else{
        int i = 0;
        int cont = -1;
        int j;
        for (j = 5; j<= dr; j+=5)
        {
            cont ++;
            v[cont] = BFPRT_sort(v, i, j - 1);
            i += 5;
        }
        cont ++;
        v[cont] = BFPRT_sort(v, i, dr);
        return BFPRT(v, cont);
    }
}

void quickSortMedian(ull * v_aux,vector <ull> &ans, int st, int dr)
{
    if (st + 1 >= dr)
    {
        if (ans[st] > ans[dr])
            swap(ans[st], ans[dr]);
    }
    //-- prepare for finding the median
    for (int i = st; i<= dr; i++)
    {
        v_aux[i - st] = ans[i];
    }
    ull pivot, mid = (st + dr) / 2, temp;
    int p1 = st, p2 = dr;
    pivot = BFPRT(v_aux, dr - st);
    for (int i = st; i <= dr; i++)
    {
        if (ans[i] == pivot)
        {
            swap(ans[i], ans[dr]);
            break;
        }
    }
    //-- the pivot is in the last pozition now
    pivot = ans[dr];
    p1 = st - 1;
    for (p2 = st; p2 < dr; p2++)
    {
        if (ans[p2] < pivot)
        {
            p1 ++;
            temp = ans[p1];
            ans[p1] = ans[p2];
            ans[p2] = temp;
        }
    }
    p1 ++;
    temp = ans[p1];
    ans[p1] = pivot;
    ans[dr] = temp;
    if (st <= p1 - 1)
        quickSortMedian(v_aux, ans, st, p1 - 1 );
    if (p1 + 1 <= dr)
        quickSortMedian(v_aux, ans, p1 + 1 , dr);
}

bool quickSortMedian(vector <ull> &v, vector<ull> &ans)
{
    int n = v.size();
    if (n > 5000000)
        return 0;
    if (n == 0)
        return 1;
    ull *v_aux = new ull[n + 1];
    ull Max = ans[0];
    for (int i = 0 ; i < n; i++)
    {
        Max = max(Max, ans[0]);
        ans[i] = v[i];
    }
    if (n / Max >= 15000 and n >= 100000)
        return 0;
    quickSortMedian(v_aux, ans, 0, n - 1);
    delete v_aux;
    return 1;
}

}