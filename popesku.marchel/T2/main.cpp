#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cctype>

struct DataStruct {
    unsigned long long key1 = 0;
    unsigned long long key2 = 0;
    std::string key3;
};

struct SavedBinary {
    DataStruct data;
    std::string text;
};

std::vector<SavedBinary> savedBinaries;

bool sameData(const DataStruct &a, const DataStruct &b) {
    return a.key1 == b.key1 &&
           a.key2 == b.key2 &&
           a.key3 == b.key3;
}

void rememberBinary(const DataStruct &data, const std::string &text) {
    savedBinaries.push_back({data, text});
}

std::string takeBinary(const DataStruct &data) {
    for (size_t i = 0; i < savedBinaries.size(); ++i) {
        if (sameData(savedBinaries[i].data, data)) {
            std::string result = savedBinaries[i].text;
            savedBinaries.erase(savedBinaries.begin() + static_cast<long long>(i));
            return result;
        }
    }
    return "";
}

void printBinary(std::ostream &out, unsigned long long val) {
    out << "0b";
    if (val == 0) {
        out << "0";
        return;
    }
    std::string s;
    unsigned long long temp = val;

    while (temp > 0) {
        s += (temp % 2 == 0) ? '0' : '1';
        temp /= 2;
    }

    std::reverse(s.begin(), s.end());
    out << s;
}

struct DelimiterIO {
    char exp;
};

std::istream &operator>>(std::istream &in, DelimiterIO &&dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) {
        return in;
    }

    char c = '\0';
    in.get(c);

    if (!in || c != dest.exp) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

struct KeyIO {
    std::string &ref;
};

std::istream &operator>>(std::istream &in, KeyIO &&dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) {
        return in;
    }

    dest.ref.clear();

    while (in) {
        int next = in.peek();
        if (next == std::char_traits<char>::eof()) {
            break;
        }

        if (!std::isalnum(static_cast<unsigned char>(next))) {
            break;
        }

        dest.ref += static_cast<char>(in.get());
    }

    if (dest.ref.empty()) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct ULLLiteralIO {
    unsigned long long &ref;
};

std::istream &operator>>(std::istream &in, ULLLiteralIO &&dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) {
        return in;
    }

    std::string token;

    while (in) {
        int next = in.peek();
        if (next == std::char_traits<char>::eof() || next == ':') {
            break;
        }
        token += static_cast<char>(in.get());
    }

    if (token.size() < 4) {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string suffix = token.substr(token.size() - 3);
    if (suffix != "ull" && suffix != "ULL") {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string numberPart = token.substr(0, token.size() - 3);
    if (numberPart.empty()) {
        in.setstate(std::ios::failbit);
        return in;
    }

    for (char c: numberPart) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    try {
        dest.ref = std::stoull(numberPart);
    } catch (...) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

struct BinUllIO {
    unsigned long long &ref;
    std::string &raw;
};

std::istream &operator>>(std::istream &in, BinUllIO &&dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) {
        return in;
    }

    std::string token;

    while (in) {
        int next = in.peek();
        if (next == std::char_traits<char>::eof() || next == ':') {
            break;
        }
        token += static_cast<char>(in.get());
    }

    if (token.size() < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (token[0] != '0' || (token[1] != 'b' && token[1] != 'B')) {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string numberPart = token.substr(2);
    if (numberPart.empty()) {
        in.setstate(std::ios::failbit);
        return in;
    }

    for (char c: numberPart) {
        if (c != '0' && c != '1') {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    try {
        dest.ref = std::stoull(numberPart, nullptr, 2);
        dest.raw = numberPart;
    } catch (...) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct StringIO {
    std::string &ref;
};

std::istream &operator>>(std::istream &in, StringIO &&dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) {
        return in;
    }

    char c = '\0';
    in.get(c);

    if (!in || c != '"') {
        in.setstate(std::ios::failbit);
        return in;
    }

    dest.ref.clear();

    while (in.get(c) && c != '"') {
        dest.ref += c;
    }

    if (!in) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::istream &operator>>(std::istream &in, DataStruct &dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    while (in && std::isspace(in.peek())) {
        in.get();
    }

    DataStruct temp;
    std::string key2Raw;

    bool key1Set = false;
    bool key2Set = false;
    bool key3Set = false;

    if (!(in >> DelimiterIO{'('} >> DelimiterIO{':'})) {
        return in;
    }

    for (int i = 0; i < 3; ++i) {
        std::string key;
        in >> KeyIO{key};
        if (!in) {
            return in;
        }

        if (!(in >> DelimiterIO{' '})) {
            return in;
        }

        if (key == "key1" && !key1Set) {
            in >> ULLLiteralIO{temp.key1};
            key1Set = true;
        } else if (key == "key2" && !key2Set) {
            in >> BinUllIO{temp.key2, key2Raw};
            key2Set = true;
        } else if (key == "key3" && !key3Set) {
            in >> StringIO{temp.key3};
            key3Set = true;
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (!(in >> DelimiterIO{':'})) {
            return in;
        }
    }

    if (!(in >> DelimiterIO{')'})) {
        return in;
    }

    if (in && key1Set && key2Set && key3Set) {
        dest = temp;
        rememberBinary(dest, key2Raw);
    } else {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream &operator<<(std::ostream &out, const DataStruct &src) {
    out << "(:key1 " << src.key1 << "ull";
    out << ":key2 ";

    std::string raw = takeBinary(src);
    if (!raw.empty()) {
        out << "0b" << raw;
    } else {
        printBinary(out, src.key2);
    }

    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct &a, const DataStruct &b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    return a.key3.length() < b.key3.length();
}


int main() {
    std::vector<DataStruct> data;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream lineStream(line);

        std::copy(
            std::istream_iterator<DataStruct>(lineStream),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );
    }

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
