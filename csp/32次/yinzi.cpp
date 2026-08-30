#include <bits/stdc++.h>
using namespace std;
#define ll long long
int isSuNum(ll num) {
    int isSu = 1;
    for (ll div = 2; div <= sqrt(num); ++div) {
        if (num % div == 0) {
            isSu = 0;
            break;
        }
    }
    return isSu;
}
const ll MAXSIZE = (ll)10e5;
ll suNums[MAXSIZE];
int main(){
    freopen("yinzi.txt","r",stdin);
    int n; cin >> n;
    int totalSuNum = 0;//size of arr
    for (ll i = 2; i <= 10e5; ++i) {
        if(isSuNum(i)) {
            suNums[totalSuNum++] = i;
        }
    }

    for (int i = 0; i < n; ++i) {
        ll num,k;
        cin >> num >> k;
        ll maxLimit = num / 2;
        ll tmpNum = num;
        // if (find(suNums,suNums+totalSuNum,num)!=suNums+totalSuNum){
        //     cout << 1 << endl;
        //     continue;
        // }
        int isPrime = 1;
        for (ll j = 0; j < totalSuNum ; ++j) {
            ll div = suNums[j];
            if (div > maxLimit) {
                break;
            }else if (num % div != 0) {
                continue;
            }
            isPrime = 0;
            ll divK =  (ll) pow(div,k);
            do {
                tmpNum /= div;
            }while(tmpNum % div == 0);
            isPrime = 1;
            if (num % divK != 0) {
                do {
                    num /= div;
                }while(num % div == 0);
            }
            maxLimit = tmpNum / 2;
            // isPrime = 1;
            // j = -1;
        }
        if (isPrime) cout << num/tmpNum << endl;
        else cout << num << endl;
    }
}