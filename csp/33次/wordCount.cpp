#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    // freopen("wordCountIn.txt","r",stdin);
    int pages,wordMax;
    cin >> pages;
    cin >> wordMax;

    vector<int> wordAppearCount (wordMax+1,0);
    vector<int> wordInPageCount (wordMax+1,0);
    //遍历所有文章
    for (int i = 0; i < pages; ++i) {
        int wordCount;
        cin >> wordCount;
        vector<bool> wordRecorded (wordMax+1,false);
        //遍历文章所有词号
        for (int j = 0; j < wordCount; ++j) {
            int wordNumber;
            cin >> wordNumber;
            wordAppearCount[wordNumber]++;//出现一次加1
            if (!wordRecorded[wordNumber]) {
                wordRecorded[wordNumber] = true;
                wordInPageCount[wordNumber]++;
            }
        }
    }
    for (int i = 1; i <= wordMax; ++i) {
        cout << wordInPageCount[i] << " " << wordAppearCount[i] << endl;
    }
    return 0;
}