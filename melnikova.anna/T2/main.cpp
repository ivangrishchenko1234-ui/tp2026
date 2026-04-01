#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <cmath>

namespace nspace {
    struct DataStruct {
        double key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };
    struct DelimiterIO {
        char exp;
    };
    struct DoubleLitIO {
        double& ref;
    };
    struct RationalLspIO {
        std::pair<long long, unsigned long long>& ref;
    };
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        char c = ' ';
        in >> c;
        if (in && (std::tolower(c) != std::tolower(dest.exp))) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, DoubleLitIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        return in >> dest.ref >> DelimiterIO{ 'd' };
    }
    std::istream& operator>>(std::istream& in, RationalLspIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        return in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' } >> DelimiterIO{ 'n' }
            >> dest.ref.first >> DelimiterIO{ ':' } >> DelimiterIO{ 'd' }
        >> dest.ref.second >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
    }
    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        DataStruct input;
        if (!(in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' })) return in;
        for (int i = 0; i < 3; ++i) {
            std::string key;
            in >> key;
            if (key == "key1") in >> DoubleLitIO{ input.key1 };
            else if (key == "key2") in >> RationalLspIO{ input.key2 };
            else if (key == "key3") {
                in >> DelimiterIO{ '"' };
                std::getline(in, input.key3, '"');
            }
            in >> DelimiterIO{ ':' };
        }
        in >> DelimiterIO{ ')' };
        if (in) dest = input;
        return in;
    }
    std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
        std::ostream::sentry sentry(out);
        if (!sentry) return out;
        out << "(:key1 " << std::fixed << std::setprecision(1) << src.key1 << "d";
        out << ":key2 (:N " << src.key2.first << ":D " << src.key2.second << ":)";
        out << ":key3 \"" << src.key3 << "\":)";
        return out;
    }
    bool compareData(const DataStruct& a, const DataStruct& b) {
        if (std::abs(a.key1 - b.key1) > 1e-9) {
            return a.key1 < b.key1;
        }
        double rat1 = static_cast<double>(a.key2.first) / a.key2.second;
        double rat2 = static_cast<double>(b.key2.first) / b.key2.second;
        if (std::abs(rat1 - rat2) > 1e-9) return rat1 < rat2;
        return a.key3.length() < b.key3.length();
    }
}

int main() {
    std::vector<nspace::DataStruct> data;
    while (!std::cin.eof()) {
        std::copy(
            std::istream_iterator<nspace::DataStruct>(std::cin),
            std::istream_iterator<nspace::DataStruct>(),
            std::back_inserter(data)
        );
        if (std::cin.fail() && !std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::sort(data.begin(), data.end(), nspace::compareData);
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<nspace::DataStruct>(std::cout, "\n")
    );
    return 0;
}
