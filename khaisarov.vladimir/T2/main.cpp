#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <limits>

namespace nspace {
    struct DataStruct {
        double key1;
        unsigned long long key2;
        std::string key3;

        bool operator<(const DataStruct& other) const {
            if (key1 != other.key1) return key1 < other.key1;
            if (key2 != other.key2) return key2 < other.key2;
            return key3.length() < other.key3.length();
        }
    };

    struct DelimiterIO {
        char exp;
    };

    struct DoubleLitIO {
        double& ref;
    };

    struct UllHexIO {
        unsigned long long& ref;
    };

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
        double val;
        if (!(in >> val)) return in;
        char suffix;
        if (!(in >> suffix) || std::tolower(suffix) != 'd') {
            in.setstate(std::ios::failbit);
        } else {
            dest.ref = val;
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, UllHexIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        char c1, c2;
        if (!(in >> c1 >> c2) || c1 != '0' || std::tolower(c2) != 'x') {
            in.setstate(std::ios::failbit);
            return in;
        }
        if (!std::isxdigit(in.peek())) {
            in.setstate(std::ios::failbit);
            return in;
        }
        return in >> std::hex >> dest.ref >> std::dec;
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) return in;
        DataStruct input;
        if (!(in >> DelimiterIO{'('})) return in;
        for (int i = 0; i < 3; ++i) {
            if (!(in >> DelimiterIO{':'})) return in;
            std::string key;
            if (!(in >> key)) return in;
            if (key == "key1") {
                if (!(in >> DoubleLitIO{input.key1})) return in;
            } else if (key == "key2") {
                if (!(in >> UllHexIO{input.key2})) return in;
            } else if (key == "key3") {
                if (!(in >> DelimiterIO{'"'})) return in;
                std::getline(in, input.key3, '"');
            } else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        if (!(in >> DelimiterIO{':'} >> DelimiterIO{')'})) return in;
        dest = input;
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
        std::ostream::sentry sentry(out);
        if (!sentry) return out;
        out << "(:key1 " << std::fixed << std::setprecision(1) << src.key1 << "d";
        out << ":key2 0x" << std::uppercase << std::hex << src.key2 << std::dec;
        out << ":key3 \"" << src.key3 << "\":)";
        return out;
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
    std::sort(data.begin(), data.end());
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<nspace::DataStruct>(std::cout, "\n")
    );
    return 0;
}
