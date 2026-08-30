#include <iostream>
#include <string>
#include <memory>
#include <bitset>
#include <vector>
#include <map>
using namespace std;

//恢复哈夫曼树
struct Node {
    char data;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    Node(char d) : data(d), left(nullptr), right(nullptr) {}
    Node() : data('\0'), left(nullptr), right(nullptr) {}
};

shared_ptr<Node> rebuildHuffmanTree(const string& s, int& index) {
    if (index >= s.length()) return nullptr;

    if (s[index] == '1') {
        index++; // 跳过'1'
        char ch = s[index++]; // 读取字符
        return make_shared<Node>(ch);
    } else if (s[index] == '0') {
        index++; // 跳过'0'
        auto node = make_shared<Node>();
        node->left = rebuildHuffmanTree(s, index);
        node->right = rebuildHuffmanTree(s, index);
        return node;
    }
    return nullptr;
}

// 辅助函数：打印树结构（前序遍历）
void printTree(const shared_ptr<Node>& root, string prefix = "") {
    if (!root) return;

    if (root->data != '\0') {
        cout << prefix << "Leaf: " << root->data << endl;
    } else {
        cout << prefix << "Internal Node" << endl;
    }
    printTree(root->left, prefix + "  ");
    printTree(root->right, prefix + "  ");
}

#define printBitset(b1,bitsLen) \
	{ \
	for (int i = 0; i < bitsLen; ++i) { \
		cout << b1[i] << " "; \
	} \
	cout << endl; \
	}


bool isLeaf(shared_ptr<Node> &node) {
    return (node->data != '\0');
}
unsigned int hexToNum(char ch) {
    if ('0'<=ch&&ch<='9') return ch-'0';
    else if ('a'<=ch&&ch<='f') return 10 + ch - 'a';
    else return -1;
}
string parseString(string str,const shared_ptr<Node>& root) {
    if (str[0]=='H'&&str[1]=='H') {
        return str.substr(1);
    } else if (str[0]=='H') {
        //解析哈夫曼编码
        //H898007
        //10001001 1 0000000
        
        str = str.substr(1);//去掉H
        int zeroEndNum = stoi(str.substr(str.size()-2,2));//补0个数
        size_t bitsLen = (str.size()-2)*4 - zeroEndNum;//总共的bit数
        vector<unsigned int> bitArr(bitsLen);
        int bitIdx = 0;
        for (int i = 0; i < str.size()-2;++i) {
            //一个hex对应4bit
            unsigned int hexNum = hexToNum(str.at(i));
            for (int j = 0; j < 4 && bitIdx < bitsLen;++j) {
                unsigned int bit = (hexNum >> (3-j)) & 0x1;
                bitArr[bitIdx++] = bit;
            }
        }

        // unsigned long bits = stoul(str.substr(0,str.size()-2),nullptr,16) >> zeroEndNum;可能溢出
        // bitset<4096> bitArr(bits);//可能溢出
        // printBitset(bitArr,bitsLen);//1 1 0 0 1 0 0 0 1 
        
        
        //对bitArr做哈夫曼解码
        shared_ptr<Node> curNode;
        bool parseStarted = false;
        string parsedStr;
        for (int pos = 0; pos <= bitsLen;++pos) {
            if (!parseStarted) {
                curNode=root;
                parseStarted=true;
            }
            //解析完一个字符
            if (isLeaf(curNode)) {
                parsedStr.insert(parsedStr.end(),curNode->data);
                parseStarted=false;
                if(pos!=bitsLen) --pos;
            }else {
                if (bitArr[pos]==0) {
                    curNode = curNode->left;
                }else {
                    curNode = curNode->right;
                }
            }
        }
        return parsedStr;
    }else {
        return str;
    }
}

void testStrParse() {
    freopen("strIn.txt","r",stdin);
    //读一颗树
    string encodedTree;
    cin >> encodedTree;
    int index = 0;
    auto root = rebuildHuffmanTree(encodedTree, index);
    cout << "Rebuilt Huffman Tree:" << endl;
    printTree(root);
    string inStr;
    cin >> inStr;
    string decodeStr = parseString(inStr,root);
    cout << decodeStr << endl;
    decodeStr = parseString("inStr",root);
    cout << decodeStr << endl;
    decodeStr = parseString("HHinStr",root);
    cout << decodeStr << endl;
}

struct kvPair
{
    string key;
    string value;
};

kvPair getPair(int idx,const vector<kvPair> &stable,const vector<kvPair> &dtable) {
    if (1<=idx&&idx<=stable.size()) {
        return stable[idx-1];
    } else {
        return dtable[idx-stable.size()-1];
    }
}
//将新的条目插入到动态表格的最前面
//并将原有的条目依次向后移动一个位置。当动态表格中的条目数超过限制时，则去掉编号最大的条目。
void insertToDTable(kvPair pair,vector<kvPair> &dtable,int limitNum) {
    dtable.insert(dtable.begin(),pair);
    if (dtable.size()>limitNum) dtable.pop_back();
}

int main() {
    // testStrParse();
    // return 0;
    freopen("input.txt","r",stdin);
    int stableLen,dtableLen;
    cin >> stableLen; cin >> dtableLen;
    //读静态表
    vector<kvPair> stable;
    for (int i = 0; i < stableLen; ++i) {
        kvPair p;
        cin >> p.key;
        cin >> p.value;
        stable.push_back(p);
    }
    //读哈夫曼树
    string encodedTree;
    cin >> encodedTree;
    int index = 0;
    auto root = rebuildHuffmanTree(encodedTree, index);
    //读动态指令数
    int insNum;
    cin >> insNum;
    //操作码，参数
    int opcode;
    int arg1;
    string arg2;
    string arg3;
    kvPair pair;
    //处理每条指令
    vector<kvPair> dtable;
    for (int i = 0; i < insNum; ++i) {
        cin >> opcode;
        cin >> arg1;
        switch (opcode)
        {
        case 1:
            //表格引用指令：1 i，其中 i 是一个正整数，表示引用编号为i 的条目
            pair = getPair(arg1,stable,dtable);
            cout << pair.key << ": " << pair.value << endl;
            break;
        case 2:
            //字面量并索引指令：2 0 k v 或 2 i v，其中 i 是一个正整数，表示使用编号为 i 的条目的字段名；
            //k 和 v 是字符串或 Huffman 编码的字符串，分别表示字段名和字段值；
            if (arg1 == 0) {
                cin >> arg2; cin >> arg3;
                cout << parseString(arg2,root) << ": " << parseString(arg3,root) << endl;
                kvPair tmp;
                tmp.key = parseString(arg2,root);
                tmp.value = parseString(arg3,root);
                insertToDTable(tmp,dtable,dtableLen);
            }else {
                cin >> arg2;
                pair = getPair(arg1,stable,dtable);
                cout << pair.key << ": " << parseString(arg2,root) << endl;
                kvPair tmp;
                tmp.key = pair.key;
                tmp.value = parseString(arg2,root);
                insertToDTable(tmp,dtable,dtableLen);
            }
            break;
        case 3:
            //字面量不索引指令：该指令与字面量并索引指令类似，但不会将该键值对插入到动态表格中。
            //3 0 k v 或 3 i v，其中 i 是一个正整数,表示使用编号为 i 的条目的字段名；
            //k 和 v 是字符串或 Huffman 编码的字符串，分别表示字段名和字段值。
            if (arg1 == 0) {
                cin >> arg2; cin >> arg3;
                cout << parseString(arg2,root) << ": " << parseString(arg3,root) << endl;
            }else {
                cin >> arg2;
                pair = getPair(arg1,stable,dtable);
                cout << pair.key << ": " << parseString(arg2,root) << endl;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}
