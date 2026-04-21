#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <iomanip>
#include <complex>
#include <algorithm>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <sstream>

struct DataStruct {
    long long key1;
    std::complex<double> key2;
    std::string key3;
};

struct DelimiterIO {
    char exp;
};

struct SllIO {
    long long& ref;
};

struct CmpIO {
    std::complex<double>& ref;
};

struct StrIO {
    std::string& ref;
};

class iofmtguard {
public:
    explicit iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
private:
    std::basic_ios<char>& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, SllIO&& dest);
std::istream& operator>>(std::istream& in, CmpIO&& dest);
std::istream& operator>>(std::istream& in, StrIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

bool compareDataStruct(const DataStruct& a, const DataStruct& b);

int main() {
    std::vector<DataStruct> data;
    std::string line;
    
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        DataStruct tmp;
        if (ss >> tmp) {
            data.push_back(tmp);
        }
    }
    
    std::sort(data.begin(), data.end(), compareDataStruct);
    
    for (const auto& d : data) {
        std::cout << d << "\n";
    }
    
    return EXIT_SUCCESS;
}

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in, false);
    if (!sentry) return in;

    char c = in.get();
    if (in && c != dest.exp) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, SllIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    if (!(in >> dest.ref)) {
        return in;
    }

    std::streampos pos = in.tellg();
    char c1, c2;
    if (in.get(c1) && in.get(c2)) {
        if ((c1 == 'l' || c1 == 'L') && (c2 == 'l' || c2 == 'L')) {
            char next = in.peek();
            if (next != ':' && next != ')' && !std::isspace(next)) {
                in.setstate(std::ios::failbit);
            }
        } else {
            in.clear();
            in.seekg(pos);
        }
    } else {
        in.clear();
        in.seekg(pos);
    }
    return in;
}

std::istream& operator>>(std::istream& in, CmpIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    double re = 0.0, im = 0.0;
    in >> DelimiterIO{ '#' } >> DelimiterIO{ 'c' } >> DelimiterIO{ '(' } >> re >> im >> DelimiterIO{ ')' };
    if (in) {
        dest.ref = std::complex<double>(re, im);
    }
    return in;
}

std::istream& operator>>(std::istream& in, StrIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    if (!(in >> DelimiterIO{ '"' })) {
        return in;
    }
    std::getline(in, dest.ref, '"');
    if (!in || in.eof()) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct input;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

    in >> std::ws;
    in >> DelimiterIO{ '(' };
    if (!in) return in;

    while (in && in.peek() != ')') {
        in >> DelimiterIO{ ':' };
        if (!in) return in;

        std::string key;
        char ch;
        while (in.get(ch) && std::isalpha(static_cast<unsigned char>(ch))) {
            key += ch;
        }
        if (key != "key1" && key != "key2" && key != "key3") {
            in.setstate(std::ios::failbit);
            return in;
        }
        if (ch != ' ') {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (key == "key1" && !hasKey1) {
            in >> SllIO{ input.key1 };
            hasKey1 = true;
        } else if (key == "key2" && !hasKey2) {
            in >> CmpIO{ input.key2 };
            hasKey2 = true;
        } else if (key == "key3" && !hasKey3) {
            in >> StrIO{ input.key3 };
            hasKey3 = true;
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (!in) return in;

        in >> std::ws;
        if (in.peek() == ':') {
            continue;
        } else if (in.peek() == ')') {
            break;
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    in >> DelimiterIO{ ')' };

    if (in && hasKey1 && hasKey2 && hasKey3) {
        dest = std::move(input);
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;

    iofmtguard guard(out);
    out << "(:key1 " << src.key1
        << ":key2 #c(" << src.key2.real() << " " << src.key2.imag() << ")"
        << ":key3 \"" << src.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    double absA = std::abs(a.key2);
    double absB = std::abs(b.key2);
    const double eps = 1e-9;
    if (std::abs(absA - absB) > eps) return absA < absB;
    return a.key3.length() < b.key3.length();
}

iofmtguard::iofmtguard(std::basic_ios<char>& s)
    : s_(s), fill_(s.fill()), precision_(s.precision()), fmt_(s.flags()) {}

iofmtguard::~iofmtguard() {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}

