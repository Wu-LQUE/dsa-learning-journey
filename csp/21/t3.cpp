#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
struct Dir;
struct File;
struct File {
    string name;
    ll size;
    Dir *parent;
};
struct Dir {
    string name;
    ll Setdirectsize;
    ll Setallsize;
    ll directsize;
    ll allsize;
    Dir *parent;
    unordered_map<string, Dir*> subdirs;
    unordered_map<string, File*> subfiles;
};
Dir root;
bool createFile(const string &fpath,ll fsize) {
    vector<string> parts;
    parts.push_back("root");
    File *target;
    ll start = 0;
    while (true) {
        ll end = fpath.find_first_of('/',start+1);
        ll r = end==string::npos?fpath.size()-1:end-1;
        parts.push_back(fpath.substr(start+1,r-start));
        if (end==string::npos) break;
        start = end;
    }
    const string fileName = parts.back();
    bool fileExists = false;
    Dir *curDir = &root;
    vector<Dir*> dirchain;
    dirchain.push_back(curDir);
    for (int i = 1; i < parts.size(); ++i) {
        string &tmp = parts[i];
        if (i < parts.size()-1) {
            if (curDir->subdirs.count(tmp)) {
                curDir = curDir->subdirs[tmp];
                dirchain.push_back(curDir);
            }else if (curDir->subfiles.count(tmp)) {
                return false;
            }else {
                break;
            }
        } else {
            if (curDir->subfiles.count(tmp)) {
                fileExists=true;
                target = curDir->subfiles[tmp];
            } else if (curDir->subdirs.count(tmp)){
                return false;
            }else {
                break;
            }
        }
    }
    //校验配额
    ll delta = fileExists ? fsize - target->size : fsize;
    for (int i = dirchain.size()-1; i >= 0; --i) {
        Dir *tmpdir = dirchain[i];
        if (i == dirchain.size()-1 && dirchain.size() == parts.size()-1) {
            if (tmpdir->Setdirectsize!=0) {
                if (tmpdir->directsize + delta > tmpdir->Setdirectsize) return false;
            }
            if (tmpdir->Setallsize != 0) {
                if (tmpdir->allsize + delta > tmpdir->Setallsize) return false;
            }
        }else {
            if (tmpdir->Setallsize != 0) {
                if (tmpdir->allsize + delta > tmpdir->Setallsize) return false;
            }
        }
    }
    //实际操作
    
    if (fileExists) {
        target->size = fsize;
    } else {
        //创建目录
        for (int i = dirchain.size(); i <= parts.size()-2; ++i) {
            Dir *newDir = new Dir(); dirchain.push_back(newDir);
            newDir->name = parts[i];
            newDir->parent = dirchain[i-1];
            dirchain[i-1]->subdirs[newDir->name] = newDir;
        }
        //创建文件
        File *newFile = new File();
        newFile->name = fileName;
        newFile->parent = dirchain.back();
        newFile->size = fsize;
        dirchain.back()->subfiles[fileName] = newFile;
    }
    //计算新配额
    for (int i = dirchain.size()-1; i >= 0; --i) {
        Dir *tmpdir = dirchain[i];
        if (i == dirchain.size()-1) {
            tmpdir->directsize += delta;
        }
        tmpdir->allsize += delta;
    }
    return true;
}
bool removeFile(const string &fpath) {
    vector<string> parts;
    ll start = 0;
    while (true) {
        ll end = fpath.find_first_of('/',start+1);
        ll r = end==string::npos?fpath.size()-1:end-1;
        parts.push_back(fpath.substr(start+1,r-start));
        if (end==string::npos) break;
        start = end;
    }
    const string targetName = parts.back();
    Dir *curDir = &root;
    vector<Dir*> dirchain;
    dirchain.push_back(curDir);
    for (int i = 0; i <= (int)parts.size()-2; ++i) {
        string &tmp = parts[i];
        if (curDir->subdirs.count(tmp)) {
            curDir = curDir->subdirs[tmp];
            dirchain.push_back(curDir);
        }else return true;
    }
    //计算新配额
    ll delta;
    for (int i = dirchain.size()-1; i >= 0; --i) {
        Dir *tmpdir = dirchain[i];
        if (i == dirchain.size()-1) {
            if (tmpdir->subfiles.count(targetName)) {
                File *f = tmpdir->subfiles[targetName];
                delta = 0-f->size;
                tmpdir->directsize += delta;
                tmpdir->allsize += delta;
                tmpdir->subfiles.erase(targetName);
            }else if (tmpdir->subdirs.count(targetName)) {
                Dir *d = tmpdir->subdirs[targetName];
                delta = 0-d->allsize;
                tmpdir->allsize += delta;
                tmpdir->subdirs.erase(targetName);
            }else {
                return true; //不存在
            }
        }else {
            tmpdir->allsize += delta;
        }
    }
    return true;
}
bool setSize(const string &fpath,ll ld,ll lr) {
    Dir *curDir;
    if (fpath=="/") {
        curDir = &root;
    }else {
        vector<string> parts;
        ll start = 0;
        while (true) {
            ll end = fpath.find_first_of('/',start+1);
            ll r = end==string::npos?fpath.size()-1:end-1;
            parts.push_back(fpath.substr(start+1,r-start));
            if (end==string::npos) break;
            start = end;
        }
        curDir = &root;
        for (int i = 0; i <= parts.size()-1; ++i) {
            string &tmp = parts[i];
            if (curDir->subdirs.count(tmp)) {
                curDir = curDir->subdirs[tmp];
            }else return false;
        }
    }
    if ((ld < curDir->directsize && ld != 0) || (lr < curDir->allsize && lr != 0)) return false;
    else {
        curDir->Setdirectsize = ld;
        curDir->Setallsize = lr;
    }
    return true;
}
int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    //freopen("t3.txt","r",stdin);
    cin >> n;
    root.name = "root";
    while (n--) {
        char op;string fpath;bool excRes;
        cin >> op >> fpath;
        if (op == 'C') {
            ll fsize; cin >> fsize;
            excRes = createFile(fpath,fsize);
        }else if (op == 'R') {
            excRes = removeFile(fpath);
        }else if (op == 'Q') {
            ll ld,lr; cin >> ld >> lr;
            excRes = setSize(fpath,ld,lr);
        }
        if (excRes) cout << 'Y' << '\n';
        else cout << 'N' << '\n';
    }
}