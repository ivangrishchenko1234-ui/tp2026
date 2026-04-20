#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <complex>
#include <cctype>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <limits>

struct DataStruct {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
};

struct DelimiterIO {
    char exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) return in;
    char c = '\0';
    in.get(c);
    if (in && c != dest.exp)
        in.setstate(std::ios::failbit);
    return in;
}

struct UllHexIO {
    unsigned long long& ref;
};

std::istream& operator>>(std::istream& in, UllHexIO&& dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) return in;

    char c0 = '\0', c1 = '\0';
    in.get(c0);
    if (!in || c0 != '0') {
        in.setstate(std::ios::failbit);
        return in;
    }
    in.get(c1);
    if (!in || (c1 != 'x' && c1 != 'X')) {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string hexStr;
    char c = '\0';
    while (in.get(c)) {
        if (std::isxdigit(static_cast<unsigned char>(c)))
            hexStr.push_back(c);
        else {
            in.putback(c);
            break;
        }
    }

    if (hexStr.empty()) {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (hexStr.size() > 16) {
        in.setstate(std::ios::failbit);
        return in;
    }

    try {
        unsigned long long value = std::stoull(hexStr, nullptr, 16);
        dest.ref = value;
    }

    catch (const std::out_of_range&) {
        in.setstate(std::ios::failbit);
    }
    catch (const std::invalid_argument&) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

struct ComplexIO {
    std::complex<double>& ref;
};

std::istream& operator>>(std::istream& in, ComplexIO&& dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) return in;

    char h = '\0', c_char = '\0', paren = '\0';
    in.get(h);
    if (!in || h != '#') {
        in.setstate(std::ios::failbit);
        return in;
    }
    in.get(c_char);
    if (!in || (c_char != 'c' && c_char != 'C')) {
        in.setstate(std::ios::failbit);
        return in;
    }
    in.get(paren);
    if (!in || paren != '(') {
        in.setstate(std::ios::failbit);
        return in;
    }

    double re = 0.0, im = 0.0;
    in >> re;
    if (!in) return in;

    char sp = '\0';
    in.get(sp);
    if (!in || sp != ' ') {
        in.setstate(std::ios::failbit);
        return in;
    }

    in >> im;
    if (!in) return in;

    in >> DelimiterIO{ ')' };
    if (in)
        dest.ref = std::complex<double>(re, im);

    return in;
}

struct StringIO {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) return in;

    char c = '\0';
    in.get(c);
    if (c != '"') {
        in.setstate(std::ios::failbit);
        return in;
    }

    dest.ref.clear();
    while (in.get(c) && c != '"')
        dest.ref.push_back(c);

    if (!in)
        in.setstate(std::ios::failbit);
    return in;
}

struct IdentifierIO {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, IdentifierIO&& dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) return in;

    dest.ref.clear();
    char c = '\0';
    while (in.get(c) && (std::isalpha(static_cast<unsigned char>(c)) ||
        std::isdigit(static_cast<unsigned char>(c))))
        dest.ref.push_back(c);

    if (in && !in.eof())
        in.putback(c);

    if (dest.ref.empty())
        in.setstate(std::ios::failbit);
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    while (std::isspace(static_cast<unsigned char>(in.peek())))
        in.get();

    if (in.peek() != '(') {
        in.setstate(std::ios::failbit);
        return in;
    }

    DataStruct temp{};
    bool key1_set = false, key2_set = false, key3_set = false;

    in >> DelimiterIO{ '(' };
    if (!in) return in;

    while (in) {
        while (in.good() && std::isspace(static_cast<unsigned char>(in.peek())))
            in.get();

        if (!in) break;

        char next = static_cast<char>(in.peek());

        if (next == ':') {
            in.get();
            if (in.peek() == ')') {
                in >> DelimiterIO{ ')' };
                break;
            }

            std::string field;
            in >> IdentifierIO{ field };
            if (!in) return in;

            char sp = '\0';
            in.get(sp);
            if (!in || sp != ' ') {
                in.setstate(std::ios::failbit);
                return in;
            }

            if (field == "key1" && !key1_set) {
                in >> UllHexIO{ temp.key1 };
                key1_set = true;
            }
            else if (field == "key2" && !key2_set) {
                in >> ComplexIO{ temp.key2 };
                key2_set = true;
            }
            else if (field == "key3" && !key3_set) {
                in >> StringIO{ temp.key3 };
                key3_set = true;
            }
            else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        else {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    if (in && key1_set && key2_set && key3_set)
        dest = temp;
    else
        in.setstate(std::ios::failbit);

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;

    out << "(:key1 0x"
        << std::uppercase << std::hex << src.key1 << std::dec << std::nouppercase;

    out << ":key2 #c("
        << std::fixed << std::setprecision(1)
        << src.key2.real() << " " << src.key2.imag() << ")";

    out << ":key3 \"" << src.key3 << "\":)";

    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1)
        return a.key1 < b.key1;

    double magA = std::abs(a.key2);
    double magB = std::abs(b.key2);
    double eps = std::numeric_limits<double>::epsilon()
        * std::max({ 1.0, magA, magB });
    if (std::abs(magA - magB) > eps)
        return magA < magB;

    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::istringstream lineStream(line);
        while (lineStream) {
            while (lineStream.good() &&
                std::isspace(static_cast<unsigned char>(lineStream.peek())))
                lineStream.get();

            if (!lineStream || lineStream.peek() == EOF)
                break;

            DataStruct ds{};
            if (lineStream >> ds) {
                data.push_back(ds);
            }
            else {
                lineStream.clear();
                lineStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
