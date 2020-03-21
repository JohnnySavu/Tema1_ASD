#pragma once
#include <bits/stdc++.h>
#include "sortari/bubbleSort.h"
#include "sortari/countSort.h"
#include "sortari/radixSort.h"
#include "sortari/mergeSort.h"
#include "sortari/quickSort.h"
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
void pushFunctions(vector<bool (*)(vector<ull> &, vector<ull> &)> &func, vector<string> &func_name)
{
    func.push_back(bubble::bubbleSort);
    func.push_back(radix::radixSortBase256);
    func.push_back(radix::radixSortBase16);
    func.push_back(merge::mergeSort);
    func.push_back(count::countSort);
    func.push_back(quick::quickSortM3);
    func.push_back(quick::quickSortMedian);

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