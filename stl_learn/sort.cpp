#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<ll> arr = {2,4,-1,5,2,7,3};
    sort(arr.begin(),arr.end());
    sort(arr.begin(),arr.end(),[](const ll &a,const ll &b){
        return a > b;
    });
    srand(time(nullptr));
    vector<pair<ll,ll>> testArr(10);
    for (int i = 0; i < testArr.size(); ++i) {
        ll x,y; x = rand() % 100; y = rand() % 100;
        testArr[i] = {x,y};
    }
    sort(testArr.begin(),testArr.end(),
    [](const pair<ll,ll> &a,const pair<ll,ll> &b){
        return a.first > b.first;
    });
    vector<int> v = {10, 20, 20, 20, 30, 30, 40, 50};
    auto pos = lower_bound(v.begin(),v.end(),20);//>=20
    cout << (pos-v.begin()) << endl;//1
    pos = upper_bound(v.begin(),v.end(),20);//>20
    cout << (pos-v.begin()) << endl;//4
    ll numOf20 = 4-1;

    vector<pair<ll, ll>> arr2 = {
        {10, 5}, {20, 3}, {20, 8}, {20, 12}, 
        {30, 7}, {40, 2}, {50, 9}
    };
    
    // 数组必须已排序（这里按first排序）
    sort(arr2.begin(), arr2.end());
    //二分查找first
    auto pos2 = lower_bound(arr2.begin(),arr2.end(),make_pair((ll)20,LLONG_MIN));//>=
    pos2 = upper_bound(arr2.begin(),arr2.end(),make_pair((ll)20,LLONG_MAX));    
}