#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
ll ignoreLineCnt = 0;
ll outLineCnt = 0;
void printByte(string &byteStr,string &buffer) {
    cout << byteStr;
    buffer.append(byteStr);
    outLineCnt+=2;
    if (outLineCnt == 16) {
        outLineCnt = 0;
        cout << endl;
    }
}

void readByte(string &byteTmp) {
    char tmp[2];
    cin >> tmp[0] >> tmp[1];//会自动跳过空字符
    byteTmp.assign(tmp,2);    
}

void readByteSet(bitset<8> &byteSet,bool &readSuccess) {
    readSuccess = true;
    string byteTmp;
    readByte(byteTmp);
    unsigned long tmp = stoul(byteTmp,NULL,16); 
    byteSet = bitset<8> (tmp);
    
}

void backtrack(string &buffer,ull o,ull l) {
    ull cur = buffer.size();
    ull pos = cur - o*2;//两个字符为一个字节
    while (l > 0) {
        string tmpByte = buffer.substr(pos,2);
        printByte(tmpByte,buffer);
        pos+=2;
        if (pos == cur) pos = cur - o*2;
        l--;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("unzip.txt","r",stdin);
    //读总字节数
    ll totalBytes; cin >> totalBytes;
    // cin.ignore();
    //行数
    ll totalLine = totalBytes / 8; totalLine += ((totalBytes % 8) != 0);
    string byteTmp;
    
    //读引导
    int endBoot = false;
    ll bootPow = 1;
    ll rawSize = 0;
    do{
        readByte(byteTmp);
        unsigned long tmp = stoul(byteTmp,NULL,16); 
        bitset<8> byteSet(tmp);
        if (byteSet[7]==0) {//最后一个
            endBoot = true;
            rawSize += tmp * bootPow;
        }else {
            rawSize += (tmp - 128) * bootPow;
        }
        bootPow *= 128;
    }while(!endBoot);
    //原始长度rawSize
    string buffer;
    bitset<8> elemStart;
    //解压缩
    while (buffer.size()/2 < rawSize) {
        bool readed;
        readByteSet(elemStart,readed);
        if (!readed) continue;
        if (elemStart[1] == 0 && elemStart[0] == 0) {//字面量
            ull high6 = (elemStart >> 2).to_ullong();
            int literalLen = 0;
            if (high6 <= 59) {
                literalLen = high6+1;
            }else if (high6 >= 60) {
                int nextN = high6 - 59;
                vector<string> lenBytes(nextN);
                while (nextN > 0) {//读n个字节
                    readByte(byteTmp);
                    lenBytes[nextN-1] = byteTmp;
                    nextN--;
                }
                string literalBytes;
                for (int i = 0; i < lenBytes.size(); ++i) {
                    literalBytes.append(lenBytes[i]);
                }
                literalLen = stoi(literalBytes,NULL,16)+1;
            }
            //读字面量
            while(literalLen>0) {
                readByte(byteTmp);
                printByte(byteTmp,buffer);
                literalLen--;
            }
        }else if (elemStart[1] == 0 && elemStart[0] == 1){//回溯1
            //4≤l≤11,0<o≤2047
            bitset<11> oSet;
            bitset<8> nextSet;
            readByteSet(nextSet,readed);
            for (int i = 0; i < 11; ++i) {
                if (i < 8) {//0-7
                    oSet[i] = nextSet[i];
                }else {//8-10 -> 5-7
                    oSet[i] = elemStart[i-3];
                }
            }
            ull o = oSet.to_ullong();
            ull l = (elemStart[2] * 1 + elemStart[3] * 2 +elemStart[4] * 4) + 4;
            backtrack(buffer,o,l);
        }else if (elemStart[1] == 1 && elemStart[0] == 0){//回溯2 1≤l≤64,0<o≤65535
            ull l = (elemStart >> 2).to_ullong() + 1;
            string sub1; readByte(sub1);
            string sub2; readByte(sub2);
            ull o = stoull(sub2+sub1,NULL,16);
            backtrack(buffer,o,l);
        }else {
            cout << "fuck!!!" << endl;
            break;
        }
    }
}