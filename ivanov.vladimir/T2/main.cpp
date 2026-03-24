#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <limits>
#include <cctype>

struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;

    DataStruct() : key1(0), key2(0), key3("") {}
    DataStruct(const DataStruct&) = default;
    DataStruct(DataStruct&&) = default;
    DataStruct& operator=(const DataStruct&) = default;
    DataStruct& operator=(DataStruct&&) = default;
    ~DataStruct() = default;
};

struct DelimiterIO {
    char exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c = '0';
    in >> c;
    if (in && (std::tolower(c) != std::tolower(dest.exp))) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct UllLitIO {
    unsigned long long& ref;
};

std::istream& operator>>(std::istream& in, UllLitIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    unsigned long long val;
    in >> val;
    char s1 = ' ', s2 = ' ', s3 = ' ';
    in >> s1 >> s2 >> s3;
    if (in && ((std::tolower(s1) == 'u' && std::tolower(s2) == 'l' && std::tolower(s3) == 'l'))) {
        dest.ref = val;
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct UllBinIO {
    unsigned long long& ref;
};

std::istream& operator>>(std::istream& in, UllBinIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char p1 = ' ', p2 = ' ';
    in >> p1 >> p2;
    if (in && p1 == '0' && (std::tolower(p2) == 'b')) {
        unsigned long long val = 0;
        char c = in.peek();
        bool has_digits = false;
        while (in && (c == '0' || c == '1')) {
            has_digits = true;
            in.get(c);
            val = (val << 1) | (c - '0');
            c = in.peek();
        }
        if (has_digits) {
            dest.ref = val;
        } else {
            in.setstate(std::ios::failbit);
        }
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct StringIO {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c;
    in >> c;
    if (in && c == '"') {
        std::getline(in, dest.ref, '"');
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    DataStruct temp;
    in >> DelimiterIO{'('} >> DelimiterIO{':'};
    bool k1 = false, k2 = false, k3 = false;
    for (int i = 0; i < 3; ++i) {
        std::string key;
        in >> key;
        if (key == "key1") {
            in >> UllLitIO{temp.key1};
            k1 = true;
        } else if (key == "key2") {
            in >> UllBinIO{temp.key2};
            k2 = true;
        } else if (key == "key3") {
            in >> StringIO{temp.key3};
            k3 = true;
        } else {
            in.setstate(std::ios::failbit);
        }
        in >> DelimiterIO{':'};
    }
    in >> DelimiterIO{')'};
    if (in && k1 && k2 && k3) {
        dest = std::move(temp);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;
    out << "(:key1 " << src.key1 << "ull:key2 0b";

    unsigned long long k2 = src.key2;
    if (k2 == 0) {
        out << "0";
    } else if (k2 == 1) {
        out << "01";
    } else {
        std::string bin = "";
        while (k2 > 0) {
            bin = char('0' + (k2 % 2)) + bin;
            k2 /= 2;
        }
        out << bin;
    }

    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}

bool compareDS(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;
    while (!std::cin.eof()) {
        std::copy(std::istream_iterator<DataStruct>(std::cin),
                  std::istream_iterator<DataStruct>(),
                  std::back_inserter(data));
        if (std::cin.fail() && !std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(data.begin(), data.end(), compareDS);
    std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
