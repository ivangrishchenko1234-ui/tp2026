#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <cctype>

struct DataStruct {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
};

bool parse_ull_hex(const std::string& s, unsigned long long& value) {
    if (s.length() < 3 || s[0] != '0' || (s[1] != 'x' && s[1] != 'X'))
        return false;
    value = 0;
    for (size_t i = 2; i < s.length(); ++i) {
        char c = s[i];
        if (c >= '0' && c <= '9')
            value = (value << 4) + (c - '0');
        else if (c >= 'a' && c <= 'f')
            value = (value << 4) + (c - 'a' + 10);
        else if (c >= 'A' && c <= 'F')
            value = (value << 4) + (c - 'A' + 10);
        else
            return false;
    }
    return true;
}

bool parse_complex(const std::string& s, std::complex<double>& value) {
    size_t start = s.find("#c(");
    if (start == std::string::npos) return false;
    size_t end = s.rfind(')');
    if (end == std::string::npos || end <= start + 3) return false;
    std::string inner = s.substr(start + 3, end - (start + 3));
    std::istringstream iss(inner);
    double re, im;
    if (!(iss >> re >> im)) return false;
    char leftover;
    if (iss >> leftover) return false;
    value = std::complex<double>(re, im);
    return true;
}

std::string parse_quoted_string(const std::string& str, size_t start_pos, size_t& end_pos) {
    if (start_pos >= str.length() || str[start_pos] != '"') {
        end_pos = start_pos;
        return "";
    }
    std::string result;
    size_t i = start_pos + 1;
    while (i < str.length()) {
        if (str[i] == '\\' && i + 1 < str.length()) {
            ++i;
            result += str[i];
            ++i;
        }
        else if (str[i] == '"') {
            end_pos = i;
            return result;
        }
        else {
            result += str[i];
            ++i;
        }
    }
    end_pos = start_pos;
    return "";
}

bool parse_line(const std::string& line, DataStruct& ds) {
    if (line.empty() || line[0] != '(' || line.length() < 3 ||
        line.substr(line.length() - 2) != "):") {
        return false;
    }
    std::string content = line.substr(1, line.length() - 3);
    std::string key1_str, key2_str, key3_str;
    bool has_key1 = false, has_key2 = false, has_key3 = false;
    size_t pos = 0;
    while (pos < content.length()) {
        size_t field_start = content.find(':', pos);
        if (field_start == std::string::npos) break;
        size_t key_end = field_start + 1;
        while (key_end < content.length() && key_end - field_start <= 5 &&
            ((content[key_end] >= 'a' && content[key_end] <= 'z') ||
                (content[key_end] >= '0' && content[key_end] <= '9'))) {
            ++key_end;
        }
        std::string key = content.substr(field_start, key_end - field_start);
        size_t value_start = key_end;
        while (value_start < content.length() && content[value_start] == ' ') {
            ++value_start;
        }
        size_t value_end;
        std::string value;
        if (key == ":key3") {
            if (value_start >= content.length() || content[value_start] != '"') {
                return false;
            }
            size_t quote_end = value_start + 1;
            while (quote_end < content.length()) {
                if (content[quote_end] == '\\' && quote_end + 1 < content.length()) {
                    quote_end += 2;
                }
                else if (content[quote_end] == '"') {
                    break;
                }
                else {
                    ++quote_end;
                }
            }
            if (quote_end >= content.length()) {
                return false;
            }
            value = content.substr(value_start, quote_end - value_start + 1);
            value_end = quote_end + 1;
            key3_str = value;
            has_key3 = true;
        }
        else {
            value_end = content.find(':', value_start);
            if (value_end == std::string::npos) {
                value_end = content.length();
            }
            value = content.substr(value_start, value_end - value_start);
            size_t val_start = value.find_first_not_of(" \t");
            if (val_start != std::string::npos) {
                size_t val_end = value.find_last_not_of(" \t");
                value = value.substr(val_start, val_end - val_start + 1);
            }
            if (key == ":key1") {
                key1_str = value;
                has_key1 = true;
            }
            else if (key == ":key2") {
                key2_str = value;
                has_key2 = true;
            }
        }
        pos = value_end;
        if (pos < content.length() && content[pos] == ':') {
            ++pos;
        }
    }
    if (!has_key1 || !has_key2 || !has_key3) {
        return false;
    }
    if (!parse_ull_hex(key1_str, ds.key1)) return false;
    if (!parse_complex(key2_str, ds.key2)) return false;
    size_t dummy;
    ds.key3 = parse_quoted_string(key3_str, 0, dummy);
    if (dummy == 0) return false;
    return true;
}

std::istream& operator>>(std::istream& in, DataStruct& ds) {
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        if (parse_line(line, ds)) {
            return in;
        }
    }
    in.setstate(std::ios::failbit);
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    out << "(:key1 0x" << std::hex << std::uppercase << ds.key1 << std::dec << std::nouppercase;
    out << ":key2 #c(" << std::fixed << std::setprecision(1) << ds.key2.real() << " " << ds.key2.imag() << ")";
    out << ":key3 \"" << ds.key3 << "\":)";
    return out;
}

bool compare(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    double abs_a = std::abs(a.key2);
    double abs_b = std::abs(b.key2);
    if (abs_a != abs_b) return abs_a < abs_b;
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;
    std::istream_iterator<DataStruct> in_iter(std::cin);
    std::istream_iterator<DataStruct> end_iter;
    std::copy_if(in_iter, end_iter, std::back_inserter(data),
        [](const DataStruct&) { return true; });
    if (data.empty()) {
        std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped" << std::endl;
        return 0;
    }
    std::sort(data.begin(), data.end(), compare);
    std::ostream_iterator<DataStruct> out_iter(std::cout, "\n");
    std::copy(data.begin(), data.end(), out_iter);
    return 0;
}
