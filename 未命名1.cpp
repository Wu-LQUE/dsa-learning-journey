#include<iostream>
#include <algorithm>
#include<cmath>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
//这是无序的map和set，节省一点时间
//用起来和正常的没什么区别，内部是hash表	 
#include <unordered_map>
#include <unordered_set>
//bit集合
#include <bitset> 
//cctype，提供便捷的字符处理函数,isalpha,tolower
#include <cctype>
using namespace std;


void testString() {
	//string用法
	string str1 = "hello";
	string str2 = " ";
	string str3 = "world!";
	string str4 = str1 + str2 + str3;
	cout << str4 << endl;

	cout << "input a string:";
	string tmp;
	cin >> tmp;
	tmp = str4 + tmp;
	cout << tmp << endl;

	//输入整行(cin>>只支持一个单词的输入)
	string a_line;
	cout << "please input a line:" << endl;
	getchar();//读取上一个输入遗留的\n
	getline(cin,a_line);
	cout << "your input is \"" << a_line << "\" and	 its length is " << a_line.length() << endl;

	//取子串
	string hlwd_str = "hello world";
	string sub_str = hlwd_str.substr(3,4);
	cout << sub_str << endl;
	cout << hlwd_str.substr(4) << endl;//不输入字符数就是拷贝后面的所有字符
}

void testBool() {
	bool flag1 = true;
	bool flag2 = -1;
	bool flag3 = 0;
	cout << flag1 << " " << flag2 << " " << flag3 << endl;
}

void testCinCout() {
	int n = 10;
	std::cin >> n;
	std::cout << "wo hao shauai!" << n << std::endl;

}

struct stu {
	string name;
	int score;
};

void testStruct() {
	//在c++里，结构体的使用可以不用前面那个struct
	struct stu a[10];
	stu b[5];//也是正确的
}


void modifyA(int &a) {
	int increase = 2;
	a += increase;
}
void testReference() {
	//在c++的方法参数里，可以使用&符号foo(int &a),在传入参数时叫做传入引用，
	//类似于传入地址，对a的修改都会反映到函数外面的a
	int num = -2;
	cout << "num before:" << num << endl;
	modifyA(num);
	cout << "num after(increase=2):" << num << endl;
}

//向量/边长数组
void testVector() {
	//需要#include <vector>
	//需要using namespace std;
	vector <int> v;
	cout << "v.size()=" << v.size() << endl;
	v.resize(10);//重新分配大小
	cout << "resize=" << v.size() << endl;
	for (int i = 0; i < 10; ++i) {
		v[i] = i;
	}
	for (int i = 0; i < 10; ++i) {
		cout << "v[" << i << "]=" << v[i];
		if (i < 9 ) cout << ", ";
	}
	cout << endl;

	//push_back是在末尾添加元素，会自动扩增
	v.push_back(10);
	cout << "v.size=" << v.size() << endl;
	for (int i = 0; i < v.size(); ++i) {
		cout << "v[" << i << "]=" << v[i];
		if (i < v.size()-1 ) cout << ", ";
	}
	cout << endl;

	//10个空间，都初始化为2（或者其他值）
	//不做初始化也行vector <int> v(20)，好像是默认初始化为0
	vector <int> v2(10,2);
	for (int i = 0; i < 10; ++i) {
		cout << v2[i];
		if (i < 9 ) cout << ", ";
	}
	cout << endl;

	//迭代器的用法，不用考虑开头和长度(c++11)
	//devcpp最高支持-std=c++14
	v2.push_back(114514);
	v2.push_back(1919810);
	for (auto p = v2.begin(); p!=v2.end(); p++) {
		cout << *p << " ";
	}
	//如果数组为0,1,2,3 p可以看成指针，begin()是0所在位置,end()是3后面一个位置
	cout << endl;
}

void testSet() {
	set <int> s;//创建一个集合，但不用分配空间，自动分配的
	//集合里的元素是互异的，按大小排序的
	s.insert(10);
	s.insert(8);
	s.insert(12);
	for (auto p = s.begin(); p != s.end(); ++p) {
		cout << *p << " ";
	}
	cout << endl;
	//查找返回的是指针位置,不等于end()则找到
	auto idxPtr = s.find(6);
	printf("%p\n",idxPtr);
	idxPtr = s.find(5);
	printf("%p\n",idxPtr);
	printf("上面是没找到的返回end() at %p\n",s.end());
	idxPtr = s.find(10);
	printf("find 10 at %p val: %d\n",idxPtr,*idxPtr);
	idxPtr = s.find(12);
	printf("find 12 at %p val: %d\n",idxPtr,*idxPtr);

	cout << "删除erase(10)" << endl;
	s.erase(10);
	for (auto p = s.begin(); p != s.end(); ++p) {
		cout << *p << " ";
	}
	cout << endl;
}

void testMap() {
	//map会自动按照key排序
	//string的话就是按照ascii码排序
	map <string, int> m;
	m["hello"] = 1;
	m["world"] = 2;
	m["hallo"] = 4;
	cout << m["hello"] << m["world"] << m["null"] << endl;//找不到会返回0
	m["null"] = 3;
	for (auto p = m.begin(); p != m.end(); ++p) {
		cout << p->first << " : " << p->second << endl;
		//map类似一个结构体数组
		/*
		struct s {
			string key;
			int data;
		}
		*/
	}
	cout << m.size() << endl;
}

void testStack() {
	stack <int> s;
	s.push(1);
	s.push(114514);
	s.push(1919810);
	//获取大小
	cout << "size:" << s.size() << endl;
	//访问栈顶
	cout << "top:" << s.top()  << endl;
	//出栈
	s.pop();//无返回值
	cout << "top:" << s.top() << endl;
	//栈无法使用迭代器遍历
}

void testQueue() {
	queue <int> q;
	q.push(114);
	q.push(514);
	q.push(1919810);
	cout << "size: " << q.size() << endl;
	cout << "front: " << q.front() << endl;
	cout << "back: " << q.back() << endl;
	q.pop();//先进先出
	cout << "remove front" << endl;
	cout << "size: " << q.size() << endl;
	cout << "front: " << q.front() << endl;
}

#define printBitset(b1) \
	{ \
	for (int i = 0; i < b1.size(); ++i) { \
		cout << b1[i] << " "; \
	} \
	cout << endl; \
	}

void testBitset() {
	//初始化10位为0
	bitset <10> b1;
	printBitset(b1);
	//用uint初始化5位 
	bitset <5> b2(3);
	//bitset是从数据的低位往高位排的
	//小端字节序这一块 
	printBitset(b2);
	//用字符串初始化,前面补0 
	bitset <6> b3("11010");
	printBitset(b3);
	//截取字符串不支持常量字符串截取，要用string 
//	bitset <3> b4("11010",1,3);
//	printBitset(b4);
	cout << "size: " << b3.size() << endl;	
	cout << "any()是否存在1: " << b3.any() << endl;
	cout << "none()不存在1吗: " << b3.none() << endl;
	cout << "count()1的个数: " << b3.count() << endl;
	cout << "test(2)2处是否为1: " << b3.test(2) << endl;
	cout << "test(3)3处是否为1: " << b3.test(3) << endl;
	cout << "set(2)2处设置为1: " << endl;
	b3.set(2);
	cout << "test(2)2处是否为1: " << b3.test(2) << endl;
	//reset() 所有位归零
	//reset(i) 第i位归零
	//flip() 所有位取反
	//flip(i) 第i位取反
	printBitset(b3);
	//转为unsigned 	long 
	unsigned long ul = b3.to_ulong();
	cout << "011110 to ul: " << ul << endl;
	string str = "011010";
	//从下标2开始，长度为 
	bitset <4> b4(str,2,4);
	printBitset(b4);
	
}
inline void printVector(vector<int> &v) {
	for (auto p = v.begin();p!=v.end();++p) {
		cout << *p << " ";
	}
	cout << endl;
}

//自定义比较函数：x在y前面的条件（当条件满足，x在y的前面），cmp的返回值只能是>或<，不能含有=
bool cmp(int x, int y) {
	return x > y;
}

void testSort() {
	vector<int> arr (10);
	for (int i = 10; i>=1;--i) {
		arr[10-i] = i;
	}
	printVector(arr);
	// 从小到大
	sort(arr.begin(),arr.end(),cmp);
	printVector(arr);
}

void testCCType() {
	char ch = 'A';
	cout << (!!isalpha(ch)) << endl;//判断是否字母，似乎返回1024，加个!!处理
	cout << islower(ch) << endl;
	cout << (!!isupper(ch)) << endl;
	char ch2 = tolower(ch);
	cout << ch << endl;
	cout << !!isalnum(ch) << endl;//判断是否字母或数字
	cout << isspace(ch) << endl;

}

void testIterator() {
	int a[5] = {1};
	//迭代器：值迭代，不可修改
	for (int i : a) {
		cout << i << " ";
	}
	cout << endl;
	//引用迭代，可以做修改
	for (int &i : a) {
		i += 1;
	}
	for (int i : a) {
		cout << i << " ";
	}
	cout << endl;
	//auto迭代vector
	vector<double> arr (6,2.5);
	for (auto a : arr) {
		cout << a << " ";
	}
	cout << endl;

	//to_string:把数字转换为string
	double db = 31.415;
	cout << to_string(db) << endl;//31.415000

	//stoi(string to int),stod(string to double)
	db = stod("1.14514");
	cout << db << endl;
	int num = stoi("1919810");
	cout << num << endl;
}

int main() {
//	testReference();
//	testVector();
//	testSet();
//	testMap();
//	testStack();
//	testQueue();
	// testBitset();
	// testSort();
	// testCCType();
	testIterator();
	return 0;
}
