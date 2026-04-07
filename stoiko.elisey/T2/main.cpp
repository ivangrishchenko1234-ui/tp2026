// var 5
// ULL OCT CMP LSP

#include <algorithm>
#include <cctype>
#include <ios>
#include <istream>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <string>
#include <complex>
#include <iostream>
#include <vector>

// (:key2 #c(1.0 -1.0):key1 076:key3 "data":)
// (:key1 01001:key3 "with : inside":key2 #c(2.0 -3.0):)
// (:key1 01001:key2 #c(2.0 -3.0):key3 "normal":)
struct DataStruct {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
};

struct DelimiterIO {
    char exp;
};

struct OctLiteralIO {
    unsigned long long& ref;
};

struct ComplexIO {
    std::complex<double>& ref;
};

struct StringIO {
    std::string& ref;
};

struct LabelIO {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, OctLiteralIO&& dest);
std::istream& operator>>(std::istream& in, ComplexIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);

std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    char c = '0';
    in >> c;

    if (in && (c != dest.exp)) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::istream& operator>>(std::istream& in, OctLiteralIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    if (in.peek() != '0') {
        in.setstate(std::ios::failbit);
        return in;
    }
    in.get();

    unsigned long long num = 0;

    while (true) {
        int digit = in.peek();
        if (digit >= '0' && digit <= '7') {
            in.get();
            num = num * 8 + (digit - '0');
        } else {
            break;
        }
    }

    dest.ref = num;
    return in;
}

std::istream& operator>>(std::istream& in, ComplexIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    double re;
    double im;

    in >> DelimiterIO{'#'} >> DelimiterIO{'c'} >> DelimiterIO{'('} >> re;
    if (!in) {
        return in;
    }

    if (!std::isspace(in.peek())) {
        in.setstate(std::ios::failbit);
        return in;
    }
    in.get();

    in >> im >> DelimiterIO{')'};
    if (in) {
        dest.ref = std::complex<double>(re, im);
    }

    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, LabelIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    dest.ref.clear();

    char c = '0';
    while (in.get(c) && !std::isspace(c)) {
        dest.ref.push_back(c);
    }

    if (!in || dest.ref.empty()) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

void cleanup_whitespaces(std::istream& in) {
    while (std::isspace(in.peek())) {
        in.get();
    }
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    cleanup_whitespaces(in);

    // if (in.peek() != '(') {
    //     in.setstate(std::ios::failbit);
    //     return in;
    // }

    DataStruct object;
    struct check_keys_status {
        bool key1 = false;
        bool key2 = false;
        bool key3 = false;

        bool is_set1() {
            return key1;
        }

        void set1() {
            key1 = true;
        }

        bool is_set2() {
            return key2;
        }

        void set2() {
            key2 = true;
        }

        bool is_set3() {
            return key3;
        }

        void set3() {
            key3 = true;
        }

        bool all_set() {
            return key1 && key2 && key3;
        }
    };

    in >> DelimiterIO{'('};
    if (!in) {
        return in;
    }

    check_keys_status keys;
    while (in && in.peek() != ')') {
        if (in.peek() == ':') {
            in.get();
        }

        std::string field_type;
        in >> LabelIO{field_type};
        if (!in) {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (in.peek() == ' ') {
            in.get();
        }

        if (field_type == "key1" && !keys.is_set1()) {
            in >> OctLiteralIO{object.key1};
            keys.set1();
        } else if (field_type == "key2" && !keys.is_set2()) {
            in >> ComplexIO{object.key2};
            keys.set2();
        } else if (field_type == "key3" && !keys.is_set3()) {
            in >> StringIO{object.key3};
            keys.set3();
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (!in) {
            return in;
        }

        if (in.peek() == ':') {
            in.get();
        } else if (in.peek() != ')') {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    in >> DelimiterIO{')'};

    if (in && keys.all_set()) {
        dest = std::move(object);
    } else {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }

    out << std::fixed << std::setprecision(1)
        << "(:key1 " << std::oct << std::showbase << src.key1 << std::dec
        << ":key2 #c(" << src.key2.real() << " " << src.key2.imag() << ")"
        << ":key3 \"" << src.key3 << "\":)";

    return out;
}

bool compare_keys(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }

    if (a.key2 != b.key2) {
        return std::abs(a.key2) < std::abs(b.key2);
    }

    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> objects;
    std::string raw;

    while (std::getline(std::cin, raw)) {
        if (raw.empty()) {
            continue;
        }

        std::istringstream iss(raw);

        std::copy(
            std::istream_iterator<DataStruct>(iss),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(objects)
        );
    }

    std::sort(
        objects.begin(),
        objects.end(),
        compare_keys
    );

    std::cout << "\n --- | --- | --- \n";

    std::copy(
        objects.begin(),
        objects.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
