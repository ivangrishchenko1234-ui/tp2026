#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>

namespace nspace {
    struct DataStruct {
        double key1 = 0;
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
        if(s.back()=='1') out<<'0'<<s;
        else out << s;
    }

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        char c;
        in >> c;
        if (in && std::tolower(c) != std::tolower(dest.exp)) in.setstate(std::ios::failbit);
        return in;
    }

    std::istream& operator>>(std::istream& in, KeyIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        dest.ref.clear();
        char c;
        while (in >> c && std::isalnum(c)) {
            dest.ref += c;
            if (!std::isalnum(in.peek())) break;
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DoubleSciIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        in >> std::ws;
        std::string temp;
        std::getline(in,temp,':');
        in.putback(':');
        if(temp.find('e') == std::string::npos && temp.find('E') == std::string::npos) in.setstate(std::ios::failbit);
        else dest.ref=std::stod(temp);
        return in;
    }

    std::istream& operator>>(std::istream& in, BinUllIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        in >> std::ws;
        std::string temp;
        char c1, c2;
        if (in >> c1 >> c2 && (c1 == '0' && std::tolower(c2) == 'b')) {
            std::getline(in,temp,':');
            in.putback(':');
            dest.ref=std::stoull(temp,nullptr,2);
        } else in.setstate(std::ios::failbit);
        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        char c;
        if (!(in >> c) || c != '"') return in.setstate(std::ios::failbit), in;
        std::getline(in, dest.ref, '"');
        return in;
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        DataStruct temp;
        if (!(in >> DelimiterIO{'('} >> DelimiterIO{':'})) return in;

        for (int i = 0; i < 3; ++i) {
            std::string key;
            in >> KeyIO{key};
            if (key == "key1") in >> DoubleSciIO{temp.key1};
            else if (key == "key2") in >> BinUllIO{temp.key2};
            else if (key == "key3") in >> StringIO{temp.key3};
            else { in.setstate(std::ios::failbit); break; }

            if (!(in >> DelimiterIO{':'})) break;
        }
        if (in >> DelimiterIO{')'}) dest = temp;
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
        iofmtguard guard(out);
        std::ostringstream oss;
        oss << std::scientific << std::setprecision(1) << std::nouppercase << src.key1;
        std::string res = oss.str();
        size_t e_pos = res.find('e');
        if (e_pos != std::string::npos && res.size() > e_pos + 2) {
            if (res[e_pos + 2] == '0' && std::isdigit(res.back())) res.erase(e_pos + 2, 1);
        }
        out << "(:key1 " << res<<":key2 ";
        printBinary(out,src.key2);
        out << ":key3 \"" << src.key3 << "\":)";
        return out;
    }

    bool compare_data(const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1) return a.key1 < b.key1;
        if (a.key2 != b.key2) return a.key2 < b.key2;
        return a.key3.length() < b.key3.length();
    }
}

int main() {
    std::vector<nspace::DataStruct> vec;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        nspace::DataStruct temp;
        if (iss >> temp) {
            vec.push_back(temp);
        }
    }

    std::sort(vec.begin(), vec.end(), nspace::compare_data);

    std::copy(
        vec.begin(),
        vec.end(),
        std::ostream_iterator<nspace::DataStruct>(std::cout, "\n")
    );

    return 0;
}
