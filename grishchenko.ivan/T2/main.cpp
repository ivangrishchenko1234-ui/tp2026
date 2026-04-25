#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>
#include <iomanip>
#include <regex>
#include <sstream>

struct DataStruct {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
};

bool parse_ull_hex(const std::string& s, unsigned long long& value) {
    std::regex hex_regex(R"(0[xX][0-9A-Fa-f]+)");
    if (!std::regex_match(s, hex_regex)) return false;
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

bool parse_line(const std::string& line, DataStruct& ds) {
    std::regex record_regex(R"(\(:key1\s+([^:]+):key2\s+([^:]+):key3\s+"([^"]*)"\))");
    std::smatch match;
    if (!std::regex_match(line, match, record_regex)) return false;
    
    if (!parse_ull_hex(match[1].str(), ds.key1)) return false;
    if (!parse_complex(match[2].str(), ds.key2)) return false;
    ds.key3 = match[3].str();
    return true;
}

int main() {
    std::vector<DataStruct> data;
    std::string line;
    bool has_supported = false;
    
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        
        DataStruct ds;
        if (parse_line(line, ds)) {
            data.push_back(ds);
            has_supported = true;
        }
    }
    
    if (!has_supported) {
        std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped" << std::endl;
        return 0;
    }
    
    std::sort(data.begin(), data.end(), [](const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1) return a.key1 < b.key1;
        double abs_a = std::abs(a.key2);
        double abs_b = std::abs(b.key2);
        if (abs_a != abs_b) return abs_a < abs_b;
        return a.key3.length() < b.key3.length();
    });
    
    for (const auto& ds : data) {
        std::cout << "(:key1 0x" << std::hex << std::uppercase << ds.key1 << std::dec << std::nouppercase;
        std::cout << ":key2 #c(" << std::fixed << std::setprecision(1) << ds.key2.real() << " " << ds.key2.imag() << ")";
        std::cout << ":key3 \"" << ds.key3 << "\":)" << std::endl;
    }
    
    return 0;
}
