#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// 辅助函数：将十六进制字符转换为整数
int hex2int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

// 读取一个字节（两个十六进制字符），自动跳过空白符
unsigned char readByte() {
    char h, l;
    // cin >> char 会自动跳过空格和换行符，这是最稳健的读法
    cin >> h >> l; 
    return (unsigned char)((hex2int(h) << 4) | hex2int(l));
}

// 全局输出缓冲区和计数器，用于控制每行8个字节的格式
vector<unsigned char> resultBuffer;
int printedCount = 0;

void appendAndPrint(unsigned char b) {
    resultBuffer.push_back(b);
    
    // 输出当前字节，控制格式
    // 使用 hex 输出，setw(2) 补零
    cout << hex << setfill('0') << setw(2) << (int)b;
    
    printedCount++;
    if (printedCount % 8 == 0) {
        cout << endl;
    } 
}

int main() {
    // 优化 I/O 效率
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int s;
    if (!(cin >> s)) return 0; // 读取总字节数 s

    // 解析引导区（计算原始数据长度）
    long long rawSize = 0;
    long long multiplier = 1;
    while (true) {
        unsigned char b = readByte();
        // 低7位是数值
        rawSize += (b & 0x7F) * multiplier;
        // 第8位是标记位
        if ((b & 0x80) == 0) {
            break; // 最高位为0，结束
        }
        multiplier *= 128;
    }

    // 主解压循环
    // 使用 resultBuffer.size() < rawSize 作为终止条件最安全
    while (resultBuffer.size() < rawSize) {
        unsigned char header = readByte();
        
        // 获取最低两位，判断类型
        int type = header & 0x03; 

        if (type == 0) { 
            // --- 字面量 ---
            int l_minus_1;
            int high6 = (header >> 2) & 0x3F; // 取高6位

            if (high6 <= 59) {
                l_minus_1 = high6;
            } else {
                // high6 为 60,61,62,63 对应 1,2,3,4 个字节存储长度
                int bytesForLen = high6 - 59;
                l_minus_1 = 0;
                int place = 1; // 小端序权重
                for (int i = 0; i < bytesForLen; ++i) {
                    unsigned char nextB = readByte();
                    l_minus_1 += nextB * place;
                    place *= 256;
                }
            }
            
            long long literalLen = l_minus_1 + 1;
            for (long long i = 0; i < literalLen; ++i) {
                appendAndPrint(readByte());
            }

        } else if (type == 1) {
            // --- 回溯引用 形式 1 (01) ---
            // 格式: [o_high3 | l-4 | 01] [o_low8]
            // l 占中间 3 位 (位 2-4)
            int l = ((header >> 2) & 0x07) + 4;
            
            // o 的高 3 位在 header 的高 3 位 (位 5-7)
            int o_high = (header >> 5) & 0x07;
            int o_low = readByte();
            int o = (o_high << 8) | o_low;

            // 复制数据
            // 注意：因为是逐个字节 push_back，所以可以处理 o < l 的重叠情况
            int startIdx = resultBuffer.size() - o;
            for (int i = 0; i < l; ++i) {
                appendAndPrint(resultBuffer[startIdx + i]);
                // 注意：这里用 startIdx + i 引用的是旧数据。
                // 如果 o < l，新写入的数据在后续迭代中会被作为“旧数据”引用到吗？
                // 题目定义：重复输出自偏移量 (p-o) 开始的字节。
                // 如果是逐字拷贝：
                // 比如 buffer="abc", o=1, l=3. p=3.
                // i=0: read buf[3-1]=buf[2]='c', append 'c'. buf="abcc"
                // i=1: read buf[4-1]=buf[3]='c', append 'c'. buf="abccc" ...
                // 所以我们需要用动态的 size 或者相对逻辑。
                // 正确的做法是每次读取 buffer[buffer.size() - o]
            }

        } else if (type == 2) {
            // --- 回溯引用 形式 2 (10) ---
            // 格式: [l-1 | 10] [o_low8] [o_high8]
            // l-1 在高 6 位
            int l = ((header >> 2) & 0x3F) + 1;
            
            int o_low = readByte();
            int o_high = readByte();
            int o = o_low | (o_high << 8); // 小端序

            for (int i = 0; i < l; ++i) {
                // 关键：每次取当前 buffer 长度 - o 处的数据
                // 这样自然处理了 o < l 的情况（重叠部分）
                appendAndPrint(resultBuffer[resultBuffer.size() - o]);
            }
        }
    }
    
    // 如果最后一行没满8个字节，需要补一个换行（虽然题目样例没有强制要求空行，但通常是个好习惯）
    if (printedCount % 8 != 0) {
        cout << endl;
    }

    return 0;
}