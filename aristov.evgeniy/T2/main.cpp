#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <iomanip>
#include <complex>
#include <algorithm>
#include <limits>
#include <cmath>

struct DataStruct {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
};

struct DelimiterIO {
    char exp;
};

struct UllIO {
    unsigned long long& ref;
};

struct CmpIO {
    std::complex<double>& ref;
};

struct StrIO {
    std::string& ref;
};

class iofmtguard {
public:
    iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
private:
    std::basic_ios<char>& s_;
    std::streamsize width_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, UllIO&& dest);
std::istream& operator>>(std::istream& in, CmpIO&& dest);
std::istream& operator>>(std::istream& in, StrIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

bool compareDataStruct(const DataStruct& a, const DataStruct& b);

int main() {
    std::vector<DataStruct> data;

    while (std::cin) {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );
        if (std::cin.fail() && !std::cin.eof()) {
            std::cin.clear();
            std::streamsize maxBufferSize = std::numeric_limits<std::streamsize>::max();
            std::cin.ignore(maxBufferSize, '\n');
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

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    char delimiterChar = '0';
    in >> delimiterChar;

    if (in && (delimiterChar != dest.exp)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, UllIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    in >> dest.ref;

    char suffixU = in.get();
    char suffixL1 = in.get();
    char suffixL2 = in.get();

    bool isU = (suffixU == 'u' || suffixU == 'U');
    bool isL1 = (suffixL1 == 'l' || suffixL1 == 'L');
    bool isL2 = (suffixL2 == 'l' || suffixL2 == 'L');

    if (!(in && isU && isL1 && isL2)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, CmpIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    double realPart = 0.0;
    double imagPart = 0.0;

    in >> DelimiterIO{'#'};
    in >> DelimiterIO{'c'};
    in >> DelimiterIO{'('};
    in >> realPart;
    in >> imagPart;
    in >> DelimiterIO{')'};

    if (in) {
        dest.ref = std::complex<double>(realPart, imagPart);
    }
    return in;
}

std::istream& operator>>(std::istream& in, StrIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    if (in >> DelimiterIO{'"'}) {
        std::getline(in, dest.ref, '"');
    }
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    DataStruct input;
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    in >> DelimiterIO{'('};

    for (int i = 0; i < 3; ++i) {
        in >> DelimiterIO{':'};

        std::string label;
        in >> label;

        if (!in) {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (label == "key1" && !hasKey1) {
            in >> UllIO{input.key1};
            hasKey1 = true;
        } else if (label == "key2" && !hasKey2) {
            in >> CmpIO{input.key2};
            hasKey2 = true;
        } else if (label == "key3" && !hasKey3) {
            in >> StrIO{input.key3};
            hasKey3 = true;
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    in >> DelimiterIO{':'};
    in >> DelimiterIO{')'};

    if (in && hasKey1 && hasKey2 && hasKey3) {
        dest = std::move(input);
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

    iofmtguard fmtguard(out);
    out << "(:key1 " << src.key1 << "ull:key2 #c(" << std::fixed;
    out << std::setprecision(1) << src.key2.real() << " ";
    out << src.key2.imag() << "):key3 \"" << src.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    double absA = std::abs(a.key2);
    double absB = std::abs(b.key2);
    if (std::abs(absA - absB) > 1e-9) {
        return absA < absB;
    }
    return a.key3.length() < b.key3.length();
}

iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s),
    width_(s.width()),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags()) {
}

iofmtguard::~iofmtguard() {
    s_.width(width_);
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}
