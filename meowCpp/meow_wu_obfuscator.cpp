#include <bits/stdc++.h>
using namespace std;

// Simple UTF-8 friendly checks: treat any non-ASCII byte as identifier part.
// This avoids breaking Unicode identifiers and lets us safely pass-through.
static inline bool isIdentStart(unsigned char c) {
    return (c=='_') || (c>=128) || std::isalpha(c);
}
static inline bool isIdentCont(unsigned char c) {
    return (c=='_') || (c>=128) || std::isalnum(c);
}

// Detect beginning of a preprocessor directive at line start: optional spaces then '#'
static bool isPPLineStart(const string& s, size_t i, size_t bol) {
    size_t j = bol;
    while (j < i && (s[j] == ' ' || s[j] == '\t')) ++j;
    return (j < i && s[j] == '#');
}

struct Mapping {
    string token; // original token text (e.g., "if", "&&", "(")
    string alias; // alias composed of 喵/呜 (identifier)
};

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc < 2 || argc > 3) {
        cerr << "Usage: " << argv[0] << " <input.cpp> [output.cpp]\n";
        return 1;
    }

    // Read entire input file
    string inputPath = argv[1];
    ifstream fin(inputPath, ios::binary);
    if (!fin) {
        cerr << "Failed to open input file: " << inputPath << "\n";
        return 1;
    }
    string code((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    fin.close();

    // Keywords and alternative tokens to replace
    unordered_set<string> keywords = {
        // C++ keywords
        "alignas","alignof","asm","auto","break","case","catch","class","const",
        "consteval","constexpr","constinit","continue","co_await","co_return","co_yield",
        "decltype","default","delete","do","else","enum","explicit","export","extern",
        "false","for","friend","goto","if","inline","mutable","namespace","new","noexcept",
        "nullptr","operator","private","protected","public","register","reinterpret_cast",
        "return","sizeof","static","static_assert","static_cast","struct","switch","template",
        "this","thread_local","throw","true","try","typedef","typeid","typename","union",
        "using","virtual","void","volatile","wchar_t","while","char","char8_t","char16_t","char32_t",
        "bool","short","int","long","float","double","signed","unsigned",
        // Alternative tokens
        "and","and_eq","bitand","bitor","compl","not","not_eq","or","or_eq","xor","xor_eq"
    };

    // Punctuators/operators, longest-first
    vector<string> punct = {
        // 4-char (rare)
        ">>=>", // not a real token; placeholder to keep stable algorithm (won't match)
        // 3-char
        ">>=","<<=","->*","...",":::", // ":::": not real; place-holder to avoid accidental
        // 2-char
        "->","++","--","<<",">>","<=",">=","==","!=","&&","||","*=","/=","%=","+=","-=","&=","^=","|=","::",".*",
        // 1-char
        "{","}","[","]","(",")",";",":",",",".","~","!","-","+","*","/","%","&","|","^","=","<",">","?"
    };
    // Remove non-real placeholders
    punct.erase(remove(punct.begin(), punct.end(), ">>=>"), punct.end());
    punct.erase(remove(punct.begin(), punct.end(), ":::"), punct.end());

    // For fast first-character lookup to speed scanning
    unordered_map<char, vector<string>> punctByFirst;
    for (auto& p : punct) {
        punctByFirst[p[0]].push_back(p);
    }
    for (auto& kv : punctByFirst) {
        sort(kv.second.begin(), kv.second.end(), [](const string& a, const string& b){
            return a.size() > b.size(); // longest-first
        });
    }

    // Alias generator using 喵/呜 sequences
    auto nextAlias = [state = size_t(1)]() mutable -> string {
        // generate sequences of length increasing: 1-bit, then 2-bit, then ...
        // interpret state as counter starting from 1
        size_t x = state;
        // compute length = floor(log2(state)) + 1
        int len = 0;
        size_t t = x;
        while (t) { ++len; t >>= 1; }
        // build alias by len bits of (x-2^{len-1})
        size_t base = (size_t(1) << (len - 1));
        size_t idx = x - base;
        string s;
        s.reserve(len * 3);
        for (int i = len - 1; i >= 0; --i) {
            bool bit = (idx >> i) & 1U;
            if (bit) s += u8"呜";
            else     s += u8"喵";
        }
        ++state;
        return s;
    };

    // Mappings: token -> alias, and preserve insertion order for printing
    unordered_map<string, string> tok2alias;
    vector<Mapping> ordered;

    auto getAliasFor = [&](const string& tok) -> string {
        auto it = tok2alias.find(tok);
        if (it != tok2alias.end()) return it->second;
        string alias;
        do {
            alias = nextAlias();
        } while (tok2alias.end() != find_if(tok2alias.begin(), tok2alias.end(),
             [&](const auto& kv){ return kv.second == alias; }));
        tok2alias[tok] = alias;
        ordered.push_back(Mapping{tok, alias});
        return alias;
    };

    // First pass: we will simultaneously build transformed body, but macros need to be emitted before body.
    string outBody;
    outBody.reserve(code.size() * 12 / 10);

    size_t n = code.size();
    size_t i = 0;
    size_t bol = 0; // begin-of-line index
    bool atLineStart = true;

    auto appendChar = [&](char c){
        outBody.push_back(c);
        if (c == '\n') {
            atLineStart = true;
            bol = outBody.size(); // for PP output, but we track input BOL separately
        } else {
            atLineStart = false;
        }
    };

    while (i < n) {
        char c = code[i];

        // Track BOL on input side to detect preprocessor lines
        static bool inputAtLineStart = true;
        static size_t inputBOL = 0;
        if (i == 0 || code[i-1] == '\n') {
            inputAtLineStart = true;
            inputBOL = i;
        }

        // Handle preprocessor lines: optional spaces then '#'
        if (inputAtLineStart) {
            size_t j = i;
            while (j < n && (code[j] == ' ' || code[j] == '\t')) ++j;
            if (j < n && code[j] == '#') {
                // Capture the whole line first
                size_t lineStart = i;
                while (i < n) {
                    char d = code[i++];
                    if (d == '\n') break;
                }
                string line = code.substr(lineStart, i - lineStart); // includes '\n'
                // Parse directive name
                size_t p = 0; while (p<line.size() && (line[p]==' '||line[p]=='\t')) ++p;
                if (p<line.size() && line[p]=='#') ++p; while (p<line.size() && (line[p]==' '||line[p]=='\t')) ++p;
                size_t q = p; while (q<line.size() && (std::isalpha((unsigned char)line[q]) || line[q]=='_')) ++q;
                string dir = line.substr(p, q-p);
                if (dir == "include") {
                    p = q; while (p<line.size() && (line[p]==' '||line[p]=='\t')) ++p;
                    string headerTok; size_t hdrEnd = p;
                    if (p<line.size() && line[p]=='<') {
                        size_t r = p+1; while (r<line.size() && line[r] != '>') ++r; if (r<line.size()) ++r; // include '>'
                        headerTok = line.substr(p, r-p);
                        hdrEnd = r;
                    } else if (p<line.size() && line[p]=='"') {
                        size_t r = p+1; while (r<line.size() && line[r] != '"') { if (line[r]=='\\' && r+1<line.size()) r+=2; else ++r; } if (r<line.size()) ++r; // include closing quote
                        headerTok = line.substr(p, r-p);
                        hdrEnd = r;
                    } else {
                        size_t r = p; while (r<line.size() && (std::isalnum((unsigned char)line[r]) || line[r]=='_')) ++r;
                        headerTok = line.substr(p, r-p);
                        hdrEnd = r;
                    }
                    string alias = getAliasFor(headerTok);
                    string rest = line.substr(hdrEnd); // keep trailing comments/spaces/newline
                    outBody += string("#include ") + alias + rest;
                } else {
                    outBody += line;
                }
                continue;
            }
        }

        // Comments (we obfuscate content inside comments, preserving //, /*, */ and newlines)
        if (c == '/') {
            if (i + 1 < n && code[i+1] == '/') {
                // line comment
                outBody += "//";
                i += 2;
                // Replace non-whitespace (except newline) with 喵/呜 pattern
                bool toggle = false;
                while (i < n) {
                    char d = code[i++];
                    if (d == '\n') { outBody.push_back(d); break; }
                    if (std::isspace((unsigned char)d)) {
                        outBody.push_back(d);
                    } else {
                        outBody += (toggle ? u8"呜" : u8"喵");
                        toggle = !toggle;
                    }
                }
                continue;
            } else if (i + 1 < n && code[i+1] == '*') {
                // block comment
                outBody += "/*";
                i += 2;
                bool toggle = false;
                while (i + 1 < n) {
                    if (code[i] == '*' && code[i+1] == '/') {
                        outBody += "*/";
                        i += 2;
                        break;
                    }
                    char d = code[i++];
                    if (d == '\n') {
                        outBody.push_back(d);
                    } else if (std::isspace((unsigned char)d)) {
                        outBody.push_back(d);
                    } else {
                        outBody += (toggle ? u8"呜" : u8"喵");
                        toggle = !toggle;
                    }
                }
                continue;
            }
        }

        // String literal (normal) -> replaced by alias macro
        if (c == '"') {
            size_t start = i;
            ++i; // skip opening quote
            bool esc = false;
            while (i < n) {
                char d = code[i++];
                if (esc) { esc = false; continue; }
                if (d == '\\') { esc = true; continue; }
                if (d == '"') break;
            }
            size_t end = i; // one past closing quote
            string literal = code.substr(start, end - start);
            string alias = getAliasFor(literal);
            if (!outBody.empty() && !isspace((unsigned char)outBody.back())) outBody.push_back(' ');
            outBody += alias;
            outBody.push_back(' ');
            continue;
        }
        // Raw string literal R"delim( ... )delim" -> alias macro
        if (c == 'R' && i + 1 < n && code[i+1] == '"') {
            size_t start = i;
            i += 2; // R"
            string delim;
            while (i < n && code[i] != '(') {
                delim.push_back(code[i]);
                ++i;
            }
            if (i < n && code[i] == '(') ++i; // skip '('
            // find )delim"
            while (i < n) {
                if (code[i] == ')') {
                    size_t j = i + 1;
                    bool match = true;
                    for (char ch : delim) { if (j >= n || code[j] != ch) { match = false; break; } ++j; }
                    if (match && j < n && code[j] == '"') { i = j + 1; break; }
                }
                ++i;
            }
            size_t end = i;
            string literal = code.substr(start, end - start);
            string alias = getAliasFor(literal);
            if (!outBody.empty() && !isspace((unsigned char)outBody.back())) outBody.push_back(' ');
            outBody += alias;
            outBody.push_back(' ');
            continue;
        }

        // Character literal -> alias macro
        if (c == '\'') {
            size_t start = i;
            ++i;
            bool esc = false;
            while (i < n) {
                char d = code[i++];
                if (esc) { esc = false; continue; }
                if (d == '\\') { esc = true; continue; }
                if (d == '\'') break;
            }
            size_t end = i;
            string literal = code.substr(start, end - start);
            string alias = getAliasFor(literal);
            if (!outBody.empty() && !isspace((unsigned char)outBody.back())) outBody.push_back(' ');
            outBody += alias;
            outBody.push_back(' ');
            continue;
        }

        // Identifier or keyword (including alternative tokens like 'and')
        if (isIdentStart((unsigned char)c)) {
            size_t j = i + 1;
            while (j < n && isIdentCont((unsigned char)code[j])) ++j;
            string ident = code.substr(i, j - i);

            // Decide whether to replace this identifier
            // Replace all identifiers (keywords already in set) except those we intentionally skip (none currently)
            string alias = getAliasFor(ident);
            if (!outBody.empty() && !isspace((unsigned char)outBody.back())) outBody.push_back(' ');
            outBody += alias;
            outBody.push_back(' ');
            i = j;
            continue;
        }

        // Number literal: now replaced with alias macro
        if (std::isdigit((unsigned char)c) || (c=='.' && i+1<n && std::isdigit((unsigned char)code[i+1]))) {
            size_t j = i;
            bool seenDot = false;
            while (j < n) {
                char d = code[j];
                if (std::isalnum((unsigned char)d) || d=='_' || d=='.' || d=='\'') {
                    if (d=='.') {
                        if (seenDot) break; seenDot = true;
                    }
                    ++j;
                } else break;
            }
            string numlit = code.substr(i, j - i);
            string alias = getAliasFor(numlit);
            if (!outBody.empty() && !isspace((unsigned char)outBody.back())) outBody.push_back(' ');
            outBody += alias;
            outBody.push_back(' ');
            i = j;
            continue;
        }

        // Punctuators/operators
        auto itv = punctByFirst.find(c);
        if (itv != punctByFirst.end()) {
            const auto& cands = itv->second;
            bool matched = false;
            for (const auto& p : cands) {
                size_t len = p.size();
                if (i + len <= n && strncmp(&code[i], p.c_str(), len) == 0) {
                    // Found a punctuator
                    string alias = getAliasFor(p);
                    // Surround alias with spaces to prevent merging with neighboring identifiers or numbers
                    if (!outBody.empty() && !isspace((unsigned char)outBody.back())) outBody.push_back(' ');
                    outBody += alias;
                    outBody.push_back(' ');
                    i += len;
                    matched = true;
                    break;
                }
            }
            if (matched) continue;
        }

        // Fallback: copy single char
        appendChar(code[i++]);
    }

    // Prepare output stream
    // Use a raw pointer to an ostream and an optional ofstream for file output.
    // This avoids incorrect unique_ptr reset/deleter usage and keeps ownership clear.
    ostream* fout = &cout;
    ofstream foutFile;
    if (argc == 3) {
        foutFile.open(argv[2], ios::binary);
        if (!foutFile) {
            cerr << "Failed to open output file: " << argv[2] << "\n";
            return 1;
        }
        fout = &foutFile;
    } else {
        fout = &cout;
    }

    // Emit header with macro mappings
    // We use object-like macros mapping alias back to the original token text.
    // Note: macros are emitted before body so they are in scope for the entire file.
    (*fout) << u8"// Generated by meow_wu_obfuscator: replace tokens with 喵/呜 aliases\n";
    (*fout) << u8"// This file remains compilable by virtue of the macros below.\n\n";

    for (const auto& m : ordered) {
        // For safety, add a space after macro name and before replacement.
        // Replacement is the raw token text; spaces ensure token separation where needed.
        (*fout) << "#define " << m.alias << " " << m.token << "\n";
    }
    if (!ordered.empty()) (*fout) << "\n";

    // Compress whitespace in outBody (simple pass):
    // 1. Collapse multiple spaces/tabs into single space.
    // 2. Remove spaces directly before punctuation characters ;,(){}[],+-*/%&|^!=<>?:,
    // 3. Trim each line's leading/trailing spaces.
    string compressed;
    compressed.reserve(outBody.size());
    bool inSpace = false;
    for (size_t k=0; k<outBody.size(); ++k) {
        char ch = outBody[k];
        if (ch==' ' || ch=='\t') {
            if (!inSpace) { compressed.push_back(' '); inSpace = true; }
        } else {
            inSpace = false;
            compressed.push_back(ch);
        }
    }
    // Remove spaces before punct set
    string punctSet = ";(){}[],+-*/%&|^!=<>?:,";
    string cleaned;
    cleaned.reserve(compressed.size());
    for (size_t k=0; k<compressed.size(); ++k) {
        char ch = cleaned.empty()? '\0' : cleaned.back();
        char cur = compressed[k];
        if (cur!=' ' || (ch!=' ' && punctSet.find(cur)==string::npos)) {
            cleaned.push_back(cur);
        } else if (cur==' ') {
            // lookahead: if next is punctuation or newline, skip
            if (k+1<compressed.size()) {
                char nxt = compressed[k+1];
                if (punctSet.find(nxt)!=string::npos || nxt=='\n') continue;
            }
            cleaned.push_back(' ');
        }
    }
    // Final pass (safe):
    // 1. Split into lines
    // 2. Trim leading/trailing spaces per line
    // 3. Remove completely empty lines (except keep first two header lines and macro block spacing)
    // This avoids collapsing newlines which previously caused comments to swallow code.
    vector<string> lines;
    {
        string tmp;
        for (char ch : cleaned) {
            if (ch == '\n') { lines.push_back(tmp); tmp.clear(); }
            else tmp.push_back(ch);
        }
        if (!tmp.empty()) lines.push_back(tmp);
    }
    // Trim and filter
    auto trim = [](string& s){
        size_t a=0; while (a<s.size() && (s[a]==' '||s[a]=='\t')) ++a;
        size_t b=s.size(); while (b> a && (s[b-1]==' '||s[b-1]=='\t')) --b;
        if (a==0 && b==s.size()) return; s = s.substr(a, b-a);
    };
    string finalOut;
    finalOut.reserve(cleaned.size());
    int lineIndex=0;
    bool inMacroBlock=true; // until first non-#define after header comment region
    for (auto& L : lines) {
        trim(L);
        bool isDefine = L.rfind("#define",0)==0;
        if (!isDefine && !L.empty() && L[0] != '#') inMacroBlock = false;
        if (L.empty()) {
            // keep one blank line between macro block and body, or between header comments and first define
            if (inMacroBlock) continue; // skip blank lines inside macro block to compress
            continue; // skip other blank lines for now
        }
        finalOut += L;
        finalOut.push_back('\n');
        ++lineIndex;
    }
    (*fout) << finalOut;

    // If writing to file, flush explicitly
    if (argc == 3) foutFile.flush();

    return 0;
}