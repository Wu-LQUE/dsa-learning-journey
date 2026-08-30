#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

struct Block {
    long long NN, MM, nn, mm;
    vector<string> old_frag;
    vector<string> new_frag;
    long long actual_NN;
};

// 平台兼容处理：防止某些环境自带回车符而导致判断和文本匹配出错
void trim_cr(string& s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
}

int main() {
    // 提升 I/O 流效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    if (!getline(cin, line)) return 0;
    trim_cr(line);
    long long n = stoll(line);

    vector<string> originFile;
    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        trim_cr(line);
        originFile.push_back(line);
    }

    // 第一步：读取所有随后的补丁，丢弃 '#' 领头的注释行
    vector<string> patch_lines;
    while (getline(cin, line)) {
        trim_cr(line);
        if (!line.empty() && line[0] == '#') continue;
        patch_lines.push_back(line);
    }

    vector<Block> blocks;
    int i = 0;
    
    // 寻找第一个 '@' 开始的块起步
    while (i < patch_lines.size() && patch_lines[i][0] != '@') {
        i++;
    }

    if (i == patch_lines.size()) {
        cout << "Patch is damaged.\n";
        return 0;
    }

    // 正则表达式匹配 @@ -NN,MM +nn,mm @@
    regex head_regex("^@@ -([1-9][0-9]*),([1-9][0-9]*) \\+([1-9][0-9]*),([1-9][0-9]*) @@$");

    // 阶段一：解析所有补丁块并在格式上进行严格验证
    while (i < patch_lines.size()) {
        int start = i;
        int j = i + 1;
        while (j < patch_lines.size() && patch_lines[j][0] != '@') {
            j++;
        }

        Block b;
        smatch match;
        if (!regex_match(patch_lines[start], match, head_regex)) {
            cout << "Patch is damaged.\n";
            return 0;
        }
        b.NN = stoll(match[1].str());
        b.MM = stoll(match[2].str());
        b.nn = stoll(match[3].str());
        b.mm = stoll(match[4].str());

        if (!blocks.empty()) {
            const Block& prev = blocks.back();
            // 在不包括累加 δ 前检查其原本标注 NN 是否发生越界
            if (b.NN < prev.NN + prev.MM) {
                cout << "Patch is damaged.\n";
                return 0;
            }
        }

        int old_cnt = 0, new_cnt = 0;
        for (int k = start + 1; k < j; ++k) {
            if (patch_lines[k].empty()) {
                cout << "Patch is damaged.\n";
                return 0;
            }
            char c = patch_lines[k][0];
            if (c != '-' && c != '+' && c != ' ') {
                cout << "Patch is damaged.\n";
                return 0;
            }
            if (c == '-') {
                b.old_frag.push_back(patch_lines[k].substr(1));
                old_cnt++;
            } else if (c == '+') {
                b.new_frag.push_back(patch_lines[k].substr(1));
                new_cnt++;
            } else if (c == ' ') {
                b.old_frag.push_back(patch_lines[k].substr(1));
                b.new_frag.push_back(patch_lines[k].substr(1));
                old_cnt++;
                new_cnt++;
            }
        }

        if (old_cnt != b.MM || new_cnt != b.mm) {
            cout << "Patch is damaged.\n";
            return 0;
        }

        blocks.push_back(b);
        i = j;
    }

    // 阶段二：计算 δ 偏移，尝试将旧片段逐一匹配原文本
    long long tot_delta = 0;
    for (int idx = 0; idx < blocks.size(); ++idx) {
        Block& b = blocks[idx];
        bool found = false;
        long long best_delta = 0;

        vector<long long> deltas;
        for (long long d = 0; d < b.MM; ++d) {
            deltas.push_back(-d);
            if (d != 0) deltas.push_back(d);
        }

        for (long long d : deltas) {
            long long current_NN = b.NN + tot_delta + d;

            // 越界检查
            if (current_NN < 1 || current_NN + b.MM - 1 > n) continue;

            // 块区域不重叠保证
            if (idx > 0) {
                const Block& prev = blocks[idx - 1];
                if (current_NN < prev.actual_NN + prev.MM) continue;
            }

            bool match = true;
            for (long long k = 0; k < b.MM; ++k) {
                if (originFile[current_NN - 1 + k] != b.old_frag[k]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                found = true;
                best_delta = d;
                b.actual_NN = current_NN;
                break;
            }
        }

        if (!found) {
            cout << "Patch is damaged.\n";
            return 0;
        }

        tot_delta += best_delta;
    }

    // 阶段三：补丁完好无损，输出构建拼合后的替换版本文本
    long long p = 0;
    for (int idx = 0; idx < blocks.size(); ++idx) {
        Block& b = blocks[idx];
        long long start_idx = b.actual_NN - 1;
        while (p < start_idx) {
            cout << originFile[p] << "\n";
            p++;
        }
        for (const string& s : b.new_frag) {
            cout << s << "\n";
        }
        p += b.MM;
    }
    // 打印可能剩余的未遭替换覆盖的末端尾行
    while (p < n) {
        cout << originFile[p] << "\n";
        p++;
    }

    return 0;
}