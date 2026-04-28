#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>
#include <iomanip>
#include <sstream>
#include <map>

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
        value <<= 4;
        if (c >= '0' && c <= '9') value += (c - '0');
        else if (c >= 'a' && c <= 'f') value += (c - 'a' + 10);
        else if (c >= 'A' && c <= 'F') value += (c - 'A' + 10);
        else return false;
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
            i++;
            result += str[i];
            i++;
        } else if (str[i] == '"') {
            end_pos = i;
            return result;
        } else {
            result += str[i];
            i++;
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
    std::map<std::string, std::string> fields;

    size_t pos = 0;
    while (pos < content.length()) {
        size_t field_start = content.find(':', pos);
        if (field_start == std::string::npos) break;

        size_t key_end = field_start + 1;
        while (key_end < content.length() && content[key_end] != ' ' && content[key_end] != ':') {
            key_end++;
        }

        std::string key = content.substr(field_start, key_end - field_start);

        size_t value_start = key_end;
        while (value_start < content.length() && content[value_start] == ' ') {
            value_start++;
        }

        size_t value_end;
        std::string value;

        if (key == ":key3") {
            size_t quote_start = value_start;
            if (quote_start >= content.length() || content[quote_start] != '"') {
                return false;
            }

            std::string unquoted = parse_quoted_string(content, quote_start, value_end);
            if (value_end == quote_start) {
                return false;
            }

            value = content.substr(quote_start, value_end - quote_start + 1);
            value_end++;
        } else {
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
        }

        fields[key] = value;
        pos = value_end;

        if (pos < content.length() && content[pos] == ':') {
            pos++;
        }
    }

    if (fields.find(":key1") == fields.end() ||
        fields.find(":key2") == fields.end() ||
        fields.find(":key3") == fields.end()) {
        return false;
    }

    if (!parse_ull_hex(fields[":key1"], ds.key1)) return false;
    if (!parse_complex(fields[":key2"], ds.key2)) return false;

    size_t dummy;
    ds.key3 = parse_quoted_string(fields[":key3"], 0, dummy);

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
        if (a.key2.real() != b.key2.real())
            return a.key2.real() < b.key2.real();
        return a.key2.imag() < b.key2.imag();
    });

    for (const auto& ds : data) {
        std::cout << "(:key1 0x" << std::hex << std::uppercase << ds.key1 << std::dec << std::nouppercase;
        std::cout << ":key2 #c(" << std::fixed << std::setprecision(1) << ds.key2.real() << " " << ds.key2.imag() << ")";
        std::cout << ":key3 \"" << ds.key3 << "\":)" << std::endl;
    }

    return 0;
}
