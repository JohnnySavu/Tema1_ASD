#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

void generareVector(int no_elem, vector <ull> &v, vector<ull> &ans, ull val_max)
{
    ull aux;
    srand(time(NULL));
    int seed = rand() * rand();
    mt19937_64 rnd(seed);
    uniform_int_distribution<ull> distr;
    for (int i = 0 ;i < no_elem - 1; i++)
    {
        aux = 1ULL * distr(rnd) % val_max;
        v.push_back(aux);
        ans.push_back(aux);
    }
    v.push_back(val_max);
    ans.push_back(val_max);
}

bool testSortare(vector <ull> &v, vector <ull> &ans)
{
    unordered_map<ull, int> map1, map2;
    if (v.size() != ans.size())
        return 0;
    if (v.size() <= 1000000)
    {
        for (int i = 0; i < v.size(); i++)
        {
            map1[v[i]] += 1;
            map2[ans[i]] += 1;
        }
        for (auto &it : map1)
        {
            if (it.second != map2[it.first])
                return 0;
        }
    }
    
    for (int i = 1; i < ans.size(); i++)
    {
        if (ans[i - 1] > ans[i]) 
            return 0;
    }
    return 1;
}

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


void pushFunctions(vector<bool (*)(vector<ull> &, vector<ull> &)> &func, vector<string> &func_name)
{
    func.push_back(bubbleSort);
    func.push_back(radixSortBase256);
    func.push_back(radixSortBase16);
    func.push_back(mergeSort);
    func.push_back(countSort);
    func.push_back(quickSortM3);
    func.push_back(quickSortMedian);

    func_name.push_back("Bubble Sort");
    func_name.push_back("Radix Sort Base 256");
    func_name.push_back("Radix Sort Base 16");
    func_name.push_back("Merge Sort");
    func_name.push_back("Count Sort");
    func_name.push_back("Quick Sort Median of Three");
    func_name.push_back("Quick Sort BFPRT");
}


int main()
{
    using namespace std::chrono;
    auto start = high_resolution_clock::now(); 
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
    double time_passed;
    bool flag;
    vector <ull> v;
    vector <ull> ans;
    vector<bool (*)(vector<ull> &, vector<ull> &)> func;
    vector<string> func_name;

    ull n, no_elem, val_max;
    
    pushFunctions(func, func_name);

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    //citesc numarul de teste din input
    
    fin >> n;
    
    //citesc inputul
    for (int i = 0; i < n; i++)
    {
        fin >>no_elem >> val_max;
        generareVector(no_elem, v, ans, val_max);
        fout <<"Test "<< i + 1 <<"\n";
        fout<<"No elements: "<<no_elem<<". Maximum Value: "<<val_max<<"\n";
        for (int j = 0; j < func.size(); j++)
        {
            fout<<func_name[j]<<". ";
            start = high_resolution_clock::now(); 
            flag = func[j](v, ans);
            stop = high_resolution_clock::now(); 
            duration = duration_cast<microseconds>(stop - start); 
            time_passed = (double) duration.count()/1000000.0;
            if (flag == 0)
            {
                
                fout<<"Not executed \n";
                continue;
            }
            fout<<"Execution time: " <<time_passed;
            fout<<". ";
            if (testSortare(v, ans) == 1)
                fout<<" Ok.\n";
            else 
                fout<<" Failed.\n";
        }
        if(no_elem <= 10000000){
            fout<<"STL Sort. Execution time ";
            start = high_resolution_clock::now(); 
            sort(v.begin(),v.end());
            stop = high_resolution_clock::now(); 
            duration = duration_cast<microseconds>(stop - start); 
            time_passed = (double) duration.count()/1000000.0;
            fout<<time_passed<<"s. Ok.\n\n";
        }
        else
        {
            fout<<"STL Sort. Not executed\n";
        }
        v.clear();
        ans.clear();
        cout<<"Test "<<i + 1<<" ok\n";
    }
    
    fin.close();
    fout.close();

    return 0;
}