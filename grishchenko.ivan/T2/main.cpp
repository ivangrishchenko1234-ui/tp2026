#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <complex>
#include <iomanip>
#include <sstream>
#include <cctype>
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
    if (s.length() < 3 || s[0] != '0' || (s[1] != 'x' && s[1] != 'X')) return false;
    try {
        value = std::stoull(s.substr(2), nullptr, 16);
        return true;
    } catch (...) {
        return false;
    }
}

bool parse_complex(const std::string& s, std::complex<double>& value) {
    std::regex cmplx_regex(R"(#c\(([+-]?\d*\.?\d+)\s+([+-]?\d*\.?\d+)\))");
    std::smatch match;
    if (!std::regex_match(s, match, cmplx_regex)) return false;
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

    size_t end = line.find_last_not_of(" \t");
    if (end == std::string::npos) {
        in.setstate(std::ios::failbit);
        return in;
    }
    line = line.substr(start, end - start + 1);

    if (line.empty() || line.front() != '(' || line.back() != ')') {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string content = line.substr(1, line.length() - 2);

    ds.key1 = 0;
    ds.key2 = std::complex<double>(0, 0);
    ds.key3 = "";
    bool found1 = false, found2 = false, found3 = false;

    size_t pos = 0;
    while (pos < content.length()) {
        if (content[pos] != ':') {
            pos++;
            continue;
        }
        pos++;

        std::string key;
        while (pos < content.length() && std::isalnum(content[pos])) {
            key += content[pos];
            pos++;
        }

        while (pos < content.length() && content[pos] == ' ') {
            pos++;
        }

        if (key == "key1") {
            size_t hex_start = pos;
            while (pos < content.length() && content[pos] != ':' && content[pos] != ' ') {
                pos++;
            }
            std::string hex_val = content.substr(hex_start, pos - hex_start);
            if (parse_ull_hex(hex_val, ds.key1)) {
                found1 = true;
            } else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        else if (key == "key2") {
            if (content[pos] != '#') {
                in.setstate(std::ios::failbit);
                return in;
            }
            size_t complex_start = pos;
            int paren_count = 0;
            while (pos < content.length()) {
                if (content[pos] == '(') paren_count++;
                if (content[pos] == ')') {
                    paren_count--;
                    if (paren_count == 0) {
                        pos++;
                        break;
                    }
                }
                pos++;
            }
            std::string complex_val = content.substr(complex_start, pos - complex_start);
            if (parse_complex(complex_val, ds.key2)) {
                found2 = true;
            } else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        else if (key == "key3") {
            if (content[pos] != '"') {
                in.setstate(std::ios::failbit);
                return in;
            }
            size_t first_quote = pos;
            size_t second_quote = content.find('"', first_quote + 1);
            if (second_quote == std::string::npos) {
                in.setstate(std::ios::failbit);
                return in;
            }
            ds.key3 = content.substr(first_quote + 1, second_quote - first_quote - 1);
            found3 = true;
            pos = second_quote + 1;
        }
        else {
            in.setstate(std::ios::failbit);
            return in;
        }

        while (pos < content.length() && content[pos] == ' ') {
            pos++;
        }
    }

    if (!found1 || !found2 || !found3) {
        in.setstate(std::ios::failbit);
        return in;
    }

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
    if (std::abs(abs_a - abs_b) > 1e-9) return abs_a < abs_b;
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;
    DataStruct temp;
    while (std::cin >> temp) {
        data.push_back(temp);
    }
    std::sort(data.begin(), data.end(), comparator);
    for (const auto& item : data) {
        std::cout << item << "\n";
    }
    return 0;
}
