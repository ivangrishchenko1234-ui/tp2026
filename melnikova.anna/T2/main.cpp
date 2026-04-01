#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <cmath>
#include <limits>

namespace nspace {
    const double EPS = 1e-9;
    struct DataStruct {
        double key1 = 0;
        std::pair<long long, unsigned long long> key2{};
        std::string key3;
    };
    struct DelimiterIO {
        char exp;
    };
    struct DoubleLitIO {
        double& ref;
    };
    struct KeyIO {
        int& ref;
    };
    struct RationalLspIO {
        std::pair<long long, unsigned long long>& ref;
    };

    std::istream& operator>>(std::istream& in, KeyIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        char k, e, y, n;
        in >> k >> e >> y >> n;
        if (in && (k != 'k' || e != 'e' ||
            y != 'y' || !(n >= '1' && n <= '3'))) {
            in.setstate(std::ios::failbit);
        }
        else {
            dest.ref = n - '0';
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        char c;
        in >> c;
        if (in && std::tolower(c) != std::tolower(dest.exp)) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DoubleLitIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        std::string temp;
        char c;
        while (in >> std::ws && in.get(c) && std::tolower(c) != 'd') {
            temp += c;
        }
        size_t dotPos = temp.find('.');
        if (dotPos == std::string::npos || dotPos == 0 || dotPos == temp.length() - 1) {
            in.setstate(std::ios::failbit);
            return in;
        }
        try {
            dest.ref = std::stod(temp);
        }
        catch (...) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, RationalLspIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        return in >> DelimiterIO{ '(' }
            >> DelimiterIO{ ':' }
            >> DelimiterIO{ 'n' }
            >> dest.ref.first
            >> DelimiterIO{ ':' }
            >> DelimiterIO{ 'd' }
            >> dest.ref.second
            >> DelimiterIO{ ':' }
        >> DelimiterIO{ ')' };
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        DataStruct input;
        if (!(in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' })) return in;

        bool has[3] = { false, false, false };

        for (int i = 0; i < 3; i++) {
            int keyNum = 0;
            in >> KeyIO{ keyNum };
            if (keyNum == 1 && !has[0]) {
                in >> DoubleLitIO{ input.key1 };
                has[0] = true;
            }
            else if (keyNum == 2 && !has[1]) {
                in >> RationalLspIO{ input.key2 };
                has[1] = true;
            }
            else if (keyNum == 3 && !has[2]) {
                in >> DelimiterIO{ '"' };
                std::getline(in, input.key3, '"');
                has[2] = true;
            }
            else {
                in.setstate(std::ios::failbit);
            }
            in >> DelimiterIO{ ':' };
        }
        in >> DelimiterIO{ ')' };
        if (in && has[0] && has[1] && has[2]) dest = input;
        return in;
    }


    std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
        std::ostream::sentry sentry(out);
        if (!sentry) return out;
        out << "(:key1 " << std::fixed << std::setprecision(10) << src.key1 << "d";
        out << ":key2 (:N " << src.key2.first << ":D " << src.key2.second << ":)";
        out << ":key3 \"" << src.key3 << "\":)";
        return out;
    }

    bool compareData(const DataStruct& a, const DataStruct& b) {
        if (std::abs(a.key1 - b.key1) > EPS) {
            return a.key1 < b.key1;
        }
        double r1 = static_cast<double>(a.key2.first) / a.key2.second;
        double r2 = static_cast<double>(b.key2.first) / b.key2.second;
        if (std::abs(r1 - r2) > EPS) {
            return r1 < r2;
        }
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
