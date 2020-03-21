#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
namespace radix{
    bool radixSortBase256(vector <ull> &v_in, vector<ull> &ans)
    {
    unsigned int base = 256, i, j;
    unsigned int mod = 1, poz, flag = 1;
    int shmt = 0, fr[base + 2], n;
    n = v_in.size();
    if (n == 0)
        return 1;
    if (n > 20000000)
        return 0;
    ull* v = new ull [n];
    for (i = 0; i < n; i++)
    {
        ans[i] = v_in[i];
        v[i] = v_in[i];
    }
    while (flag)
    {
        flag = 0;
        for (i = 0; i <= base; i++)
        {
            fr[i] = 0;
        }
        for (i = 0; i < n; i++)
        {
            poz = ans[i] >> shmt;
            poz = poz & 255;
            fr[poz + 1] ++ ;
            if (poz != 0)
                flag = 1;
        }
        for (i = 1; i <= base; i++)
        {
            fr[i] += fr[i-1];
        }
        for (i = 0; i < n; i++)
        {
            poz = ans[i] >> shmt;
            poz = poz & 255;
            v[fr[poz] ] = ans[i];
            fr[poz] ++;
        }
        for (i = 0; i < n; i++)
        {
            ans[i] = v[i];
        }
        shmt += 8;
    }
    delete v;
    return 1;
}

bool radixSortBase16(vector <ull> &v_in, vector<ull> &ans)
{
    unsigned int base = 16, i, j;
    unsigned int mod = 1, poz, flag = 1;
    int shmt = 0, fr[base + 2], n;
    n = v_in.size();
    if (n > 20000000)
        return 0;
    if (n == 0)
        return 1;
    ull* v = new ull [n];
    for (i = 0; i < n; i++)
    {
        ans[i] = v_in[i];
        v[i] = v_in[i];
    }
    while (flag)
    {
        flag = 0;
        for (i = 0; i <= base; i++)
        {
            fr[i] = 0;
        }
        for (i = 0; i < n; i++)
        {
            poz = ans[i] >> shmt;
            poz = poz & 15;
            fr[poz + 1] ++ ;
            if (poz != 0)
                flag = 1;
        }
        for (i = 1; i <= base; i++)
        {
            fr[i] += fr[i-1];
        }
        for (i = 0; i < n; i++)
        {
            poz = ans[i] >> shmt;
            poz = poz & 15;
            v[fr[poz] ] = ans[i];
            fr[poz] ++;
        }
        for (i = 0; i < n; i++)
        {
            ans[i] = v[i];
        }
        shmt += 4;
    }
    delete v;
    return 1;
}

}