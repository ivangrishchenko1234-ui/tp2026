#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <complex>
#include <cctype>
#include <iomanip>
#include <regex>

struct DataStruct {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;

    double key2_abs() const {
        return std::abs(key2);
    }
};

bool parse_ull_hex(const std::string& s, unsigned long long& value) {
    if (s.empty()) return false;
    std::string tmp = s;
    if (tmp.front() == ':') tmp.erase(0, 1);
    if (tmp.back() == ':') tmp.pop_back();

    std::regex hex_regex(R"(^(0[xX][0-9A-Fa-f]+)$)", std::regex::ECMAScript);
    std::smatch match;
    if (!std::regex_match(tmp, match, hex_regex)) return false;

    try {
        value = std::stoull(match[1].str(), nullptr, 16);
        return true;
    } catch (...) {
        return false;
    }
}

bool parse_complex(const std::string& s, std::complex<double>& value) {
    std::regex cmplx_regex(R"(#c\(([+-]?\d*\.?\d+)\s+([+-]?\d*\.?\d+)\))");
    std::smatch match;
    if (!std::regex_search(s, match, cmplx_regex)) return false;
    try {
        double re = std::stod(match[1].str());
        double im = std::stod(match[2].str());
        value = std::complex<double>(re, im);
        return true;
    } catch (...) {
        return false;
    }
}

std::istream& operator>>(std::istream& in, DataStruct& ds) {
    std::string line;
    if (!std::getline(in, line)) return in;

    size_t start = line.find_first_not_of(" \t");
    if (start == std::string::npos) {
        in.setstate(std::ios::failbit);
        return in;
    }
    if (line[start] != '(' || line.back() != ')') {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::regex key1_regex(R"(:key1\s+(0[xX][0-9A-Fa-f]+))");
    std::regex key2_regex(R"(:key2\s+(#c\([^)]+\)))");
    std::regex key3_regex(R"(:key3\s+\"([^\"]*)\")");

    std::smatch m1, m2, m3;
    std::string whole(line.begin() + 1, line.end() - 1);

    bool ok1 = std::regex_search(whole, m1, key1_regex);
    bool ok2 = std::regex_search(whole, m2, key2_regex);
    bool ok3 = std::regex_search(whole, m3, key3_regex);

    if (!ok1 || !ok2 || !ok3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    unsigned long long k1;
    std::complex<double> k2;
    if (!parse_ull_hex(m1[1].str(), k1) || !parse_complex(m2[1].str(), k2)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    ds.key1 = k1;
    ds.key2 = k2;
    ds.key3 = m3[1].str();
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    out << "(:key1 0x" << std::uppercase << std::hex << ds.key1 << std::dec << std::nouppercase;
    out << ":key2 #c(" << std::fixed << std::setprecision(1) << ds.key2.real()
        << " " << ds.key2.imag() << ")";
    out << ":key3 \"" << ds.key3 << "\":)";
    return out;
}

bool comparator(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    double abs_a = a.key2_abs();
    double abs_b = b.key2_abs();
    if (abs_a != abs_b) return abs_a < abs_b;
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;

    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(data));

    std::sort(data.begin(), data.end(), comparator);

    std::copy(data.begin(), data.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
