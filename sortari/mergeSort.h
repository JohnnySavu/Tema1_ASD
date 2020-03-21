#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
namespace merge{
    void mergeSort(vector <ull> &v, ull* v_aux, int st, int dr)
{
    if (st + 1 >= dr)
    {
        if (v[st] > v[dr])
            swap(v[st],  v[dr]);
        return;
    }
    int mid = st + dr;
    mid /= 2;
    int p1 = st, p2 = mid + 1, i;
    mergeSort(v, v_aux, st, mid);
    mergeSort(v, v_aux, mid + 1, dr);
    for (i = 0; i < dr - st + 1; i++)
    {
        if (p1 > mid or (v[p1] > v[p2] and p2 <= dr))
        {
            v_aux[i] = v[p2];
            p2++;
        }
        else
        {
            v_aux[i] = v[p1];
            p1 ++;
        }
    }
    for (i = 0; i < dr - st + 1; i++)
        v[i + st] = v_aux[i];

}


bool mergeSort(vector <ull> &v, vector<ull> & ans)
{
    int n = v.size();
    if (n > 10000000)
        return 0;
    if (n == 0)
        return 1;
    for (int i = 0; i < n; i++)
    {
        ans[i] = v[i];
    }
    ull* v_aux = new ull [n + 1];
    mergeSort(ans, v_aux, 0, n - 1);
    return 1;
}
}