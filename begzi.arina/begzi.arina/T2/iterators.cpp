#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cctype>

struct DataStruct {
    double key1 = 0.0;
    unsigned long long key2 = 0;
    std::string key3;
};

struct DelimiterIO { char exp; };
struct KeyIO { std::string& ref; };
struct DoubleSciIO { double& ref; };
struct BinUllIO { unsigned long long& ref; };
struct StringIO { std::string& ref; };

struct iofmtguard {
    iofmtguard(std::ostream& s) : s_(s), fill_(s.fill()), precision_(s.precision()), fmt_(s.flags()) {}
    ~iofmtguard() { s_.fill(fill_); s_.precision(precision_); s_.flags(fmt_); }
private:
    std::ostream& s_; char fill_; std::streamsize precision_; std::ios::fmtflags fmt_;
};

void printBinary(std::ostream& out, unsigned long long val) {
    out << "0b";
    if (val == 0) { out << "0"; return; }
    std::string s;
    unsigned long long temp = val;
    while (temp > 0) {
        s += (temp & 1 ? '1' : '0');
        temp >>= 1;
    }
    std::reverse(s.begin(), s.end());
    out << s;
}

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c;
    if (!(in >> c) || std::tolower(static_cast<unsigned char>(c)) != std::tolower(static_cast<unsigned char>(dest.exp))) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, KeyIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    char c0, c1, c2, c3;
    if (in >> c0 >> c1 >> c2 >> c3) {
        if (c0 == 'k' && c1 == 'e' && c2 == 'y' && (c3 == '1' || c3 == '2' || c3 == '3')) {
            dest.ref = std::string("key") + c3;
        }
        else {
            in.setstate(std::ios::failbit);
        }
    }
    return in;
}

std::istream& operator>>(std::istream& in, DoubleSciIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    std::string s;
    bool has_dot = false, has_e = false;
    int dig_before = 0, dig_after = 0;

    if (in.peek() == '+' || in.peek() == '-') {
        s += static_cast<char>(in.get());
    }

    while (in.peek() != EOF && std::isdigit(in.peek())) {
        s += static_cast<char>(in.get());
        dig_before++;
    }

    if (in.peek() == '.') {
        s += static_cast<char>(in.get());
        has_dot = true;
        while (in.peek() != EOF && std::isdigit(in.peek())) {
            s += static_cast<char>(in.get());
            dig_after++;
        }
    }

    int p = in.peek();
    if (p == 'e' || p == 'E') {
        s += static_cast<char>(in.get());
        has_e = true;
        if (in.peek() == '+' || in.peek() == '-') {
            s += static_cast<char>(in.get());
        }
        while (in.peek() != EOF && std::isdigit(in.peek())) {
            s += static_cast<char>(in.get());
        }
    }

    if (!has_dot || !has_e || dig_before == 0 || dig_after == 0) {
        in.setstate(std::ios::failbit);
    }
    else {
        try { dest.ref = std::stod(s); }
        catch (...) { in.setstate(std::ios::failbit); }
    }
    return in;
}

std::istream& operator>>(std::istream& in, BinUllIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    char c1, c2;
    if (!(in >> c1 >> c2) || c1 != '0' || std::tolower(static_cast<unsigned char>(c2)) != 'b') {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string s;
    while (in.peek() == '0' || in.peek() == '1') {
        s += static_cast<char>(in.get());
    }

    if (s.empty()) {
        in.setstate(std::ios::failbit);
    }
    else {
        try { dest.ref = std::stoull(s, nullptr, 2); }
        catch (...) { in.setstate(std::ios::failbit); }
    }
    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c;
    if (!(in >> c) || c != '"') {
        in.setstate(std::ios::failbit);
        return in;
    }
    std::getline(in, dest.ref, '"');
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    while (true) {
        char ch;
        while (in >> ch && ch != '(') {}
        if (!in) return in;

        DataStruct temp;
        bool error = false;
        bool k1 = false, k2 = false, k3 = false;

        if (!(in >> DelimiterIO{ ':' })) error = true;

        for (int i = 0; i < 3 && !error; ++i) {
            std::string key;
            if (!(in >> KeyIO{ key })) { error = true; break; }

            if (key == "key1") {
                if (k1) error = true;
                else if (!(in >> DoubleSciIO{ temp.key1 })) error = true;
                k1 = true;
            }
            else if (key == "key2") {
                if (k2) error = true;
                else if (!(in >> BinUllIO{ temp.key2 })) error = true;
                k2 = true;
            }
            else if (key == "key3") {
                if (k3) error = true;
                else if (!(in >> StringIO{ temp.key3 })) error = true;
                k3 = true;
            }

            if (!(in >> DelimiterIO{ ':' })) error = true;
        }

        if (!error && k1 && k2 && k3 && (in >> DelimiterIO{ ')' })) {
            dest = temp;
            return in;
        }

        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), ')');
    }
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    iofmtguard guard(out);
    std::ostringstream oss;
    oss << std::scientific << std::setprecision(1) << std::nouppercase << src.key1;
    std::string res = oss.str();

    size_t e_pos = res.find('e');
    if (e_pos != std::string::npos) {
        size_t sign_pos = e_pos + 1;
        while (res.size() > sign_pos + 2 && res[sign_pos + 1] == '0') {
            res.erase(sign_pos + 1, 1);
        }
    }

    out << "(:key1 " << res << ":key2 ";
    printBinary(out, src.key2);
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}

bool compare_data(const DataStruct& a, const DataStruct& b) {
    if (a.key1 < b.key1) return true;
    if (a.key1 > b.key1) return false;
    if (a.key2 < b.key2) return true;
    if (a.key2 > b.key2) return false;
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> vec;

    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(vec)
    );

    std::sort(vec.begin(), vec.end(), compare_data);

    std::copy(
        vec.begin(),
        vec.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
