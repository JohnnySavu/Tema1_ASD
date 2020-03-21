#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
namespace count{
bool countSort(vector <ull> &v, vector <ull> &ans)
{
    int n = v.size();
    if (n == 0)
        return 1;
    if (n > 20000000)
        return 0;
    ull Max = v[0];
    ull Min = v[0];
    for (int i = 1; i < n; i++)
    {
        Max = max(Max, v[i]);
        Min = min(Min, v[i]);
    }
    if (Max - Min > 20000000)
        return 0;
    int* freq = new int [Max - Min + 1];
    for (int i = 0; i <= Max - Min; i ++)
        freq[i] = 0;
    for (int i = 0; i< n; i++)
    {
        freq[v[i] - Min] ++;
    }
    int poz =-1 ;
    for (int i = 0; i <= Max - Min; i++)
    {
        for(int j = 1; j <= freq[i]; j++)
        {
            poz ++;
            ans[poz] = i + Min;
        }
    }
    return 1;
}
    
}