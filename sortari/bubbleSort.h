#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
namespace bubble{
    bool bubbleSort(vector <ull> &v, vector <ull> &ans)
{
    int n = v.size();
    if (n == 0) 
        return 1;
    if (n > 12000)
        return 0;

    for (int i = 0; i < n ; i++)
    {
        ans [i] = v[i];
    }
    bool flag = 1;
    while (flag)
    {
        flag = 0;
        for (int i = 1; i < n; i++)
        {
            if (ans[i-1] > ans[i])
            {
                flag = 1;
                swap(ans[i-1], ans[i]);
            }
        }
    }
    return 1;
}
}