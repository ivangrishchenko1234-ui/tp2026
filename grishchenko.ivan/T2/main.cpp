#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <complex>
#include <iomanip>
#include <sstream>

struct DataStruct {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;

    double key2_abs() const {
        return std::abs(key2);
    }
};

bool parse_ull_hex(const std::string& s, unsigned long long& value) {
    if (s.length() < 3 || s[0] != '0' || (s[1] != 'x' && s[1] != 'X')) return false;
    try {
        value = std::stoull(s.substr(2), nullptr, 16);
        return true;
    } catch (...) {
        return false;
    }
}

bool parse_complex(const std::string& s, std::complex<double>& value) {
    if (s.length() < 5 || s.substr(0, 3) != "#c(" || s.back() != ')') return false;
    std::string inner = s.substr(3, s.length() - 4);
    size_t space = inner.find(' ');
    if (space == std::string::npos) return false;
    try {
        double re = std::stod(inner.substr(0, space));
        double im = std::stod(inner.substr(space + 1));
        value = std::complex<double>(re, im);
        return true;
    } catch (...) {
        return false;
    }
}

std::string extract_quoted(const std::string& s, size_t start) {
    size_t first_quote = s.find('"', start);
    if (first_quote == std::string::npos) return "";
    size_t second_quote = s.find('"', first_quote + 1);
    if (second_quote == std::string::npos) return "";
    return s.substr(first_quote + 1, second_quote - first_quote - 1);
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

    std::string content = line.substr(start + 1, line.length() - start - 2);

    unsigned long long k1 = 0;
    std::complex<double> k2(0, 0);
    std::string k3;

    bool found1 = false, found2 = false, found3 = false;

    size_t pos = 0;
    while (pos < content.length()) {
        size_t colon = content.find(':', pos);
        if (colon == std::string::npos) break;

        size_t space = content.find(' ', colon + 1);
        if (space == std::string::npos) break;

        std::string key = content.substr(colon + 1, space - colon - 1);

        size_t next_colon = content.find(':', space + 1);
        std::string value;
        if (next_colon == std::string::npos) {
            value = content.substr(space + 1);
        } else {
            value = content.substr(space + 1, next_colon - space - 1);
        }

        if (key == "key1") {
            if (parse_ull_hex(value, k1)) found1 = true;
        } else if (key == "key2") {
            if (parse_complex(value, k2)) found2 = true;
        } else if (key == "key3") {
            k3 = extract_quoted(content, space + 1);
            if (!k3.empty()) found3 = true;
        }

        if (next_colon == std::string::npos) break;
        pos = next_colon;
    }

    if (!found1 || !found2 || !found3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    ds.key1 = k1;
    ds.key2 = k2;
    ds.key3 = k3;
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
