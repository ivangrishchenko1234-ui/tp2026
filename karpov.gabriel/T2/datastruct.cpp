#include "datastruct.h"
#include <cctype>
#include <cmath>
#include <sstream>

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

std::istream& operator>>(std::istream& in, LongLongIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    in >> std::ws;

    std::string numberWithSuff;
    char currentChar;

    while (in.get(currentChar) && currentChar != ':') {
        numberWithSuff += currentChar;
    }

    in.putback(':');

    if (numberWithSuff.length() < 2) {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (numberWithSuff.length() == 3 && (numberWithSuff[0] == '-' || numberWithSuff[0] == '+')) {
        in.setstate(std::ios::failbit);
        return in;
    }

    size_t length = numberWithSuff.length();
    char firstSuffChar = std::tolower(numberWithSuff[length - 2]);
    char secondSuffChar = std::tolower(numberWithSuff[length - 1]);

    if (firstSuffChar == 'l' && secondSuffChar == 'l') {
        numberWithSuff.pop_back();
        numberWithSuff.pop_back();

        if (numberWithSuff.empty() || numberWithSuff == "-" || numberWithSuff == "+") {
            in.setstate(std::ios::failbit);
            return in;
        }

        std::stringstream converter(numberWithSuff);
        long long result = 0;

        if (converter >> result) {
            dest.ref = result;
            return in;
        }
    }
    in.setstate(std::ios::failbit);
    return in;
}

std::istream& operator>>(std::istream& in, DoubleIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    std::string mantissaBuffer;
    char expSign = '+';
    int expValue = 0;
    char ch;

    bool dotFound = false;
    bool hasDigitsBeforeDot = false;
    bool hasDigitsAfterDot = false;

    in >> std::ws;
    if (in.peek() == '-') {
        in.get(ch);
        mantissaBuffer += '-';
    } else if (in.peek() == '+') {
        in.get(ch);
    }

    while (in.get(ch)) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            mantissaBuffer += ch;
            if (dotFound) {
                hasDigitsAfterDot = true;
            } else {
                hasDigitsBeforeDot = true;
            }
        } else if (ch == '.' && !dotFound) {
            if (!hasDigitsBeforeDot) {
                in.setstate(std::ios::failbit);
                return in;
            }
            mantissaBuffer += ch;
            dotFound = true;
        } else if (ch == 'e' || ch == 'E') {
            break;
        } else {
            in.putback(ch);
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    if (!hasDigitsBeforeDot || !dotFound || !hasDigitsAfterDot) {
        in.setstate(std::ios::failbit);
        return in;
    }
    if (!in.get(expSign) || (expSign != '+' && expSign != '-')) {
        in.setstate(std::ios::failbit);
        return in;
    }

    in >> expValue;
    if (!in) {
        in.setstate(std::ios::failbit);
        return in;
    }

    double mantissa = std::stod(mantissaBuffer);
    int finalExp = (expSign == '-') ? -expValue : expValue;
    dest.ref = mantissa * std::pow(10.0, finalExp);

    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    DataStruct temp;
    bool key1_visible = false, key2_visible = false, key3_visible = false;

    if (!(in >> DelimiterIO{'('} >> DelimiterIO{':'})) {
        in.setstate(std::ios::failbit);
        return in;
    }

    for (size_t i = 0; i < 3; ++i) {
        std::string label;
        if (!(in >> label)) break;

        if (label == "key1") {
            if (!(in >> DoubleIO{temp.key1})) break;
            key1_visible = true;
        } else if (label == "key2") {
            if (!(in >> LongLongIO{temp.key2})) break;
            key2_visible = true;
        } else if (label == "key3") {
            if (!(in >> StringIO{temp.key3})) break;
            key3_visible = true;
        } else {
            in.setstate(std::ios::failbit);
            break;
        }

        if (i < 2 && !(in >> DelimiterIO{':'})) {
            in.setstate(std::ios::failbit);
            break;
        }
    }

    if (!(in >> DelimiterIO{':'} >> DelimiterIO{')'}) || !key1_visible || !key2_visible || !key3_visible) {
        in.setstate(std::ios::failbit);
        return in;
    }

    dest = std::move(temp);
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }
    iofmtguard fmtguard(out);

    double mantissa = data.key1;
    int exponent = 0;

    if (data.key1 == 0.0) {
        mantissa = 0.0;
        exponent = 0;
    } else {
        double absVal = std::abs(mantissa);

        while (absVal < 1.0 && absVal != 0.0) {
            absVal *= 10.0;
            exponent--;
        }
        while (absVal >= 10.0) {
            absVal /= 10.0;
            exponent++;
        }

        mantissa = (mantissa < 0) ? -absVal : absVal;
    }

    out << "(:";
    out << "key1 ";
    out << std::fixed << std::setprecision(1) << mantissa;
    if (exponent >= 0) {
        out << "e+" << exponent;
    } else {
        out << "e" << exponent;
    }
    out << ":key2 " << data.key2 << "ll";
    out << ":key3 \"" << data.key3 << "\"";
    out << ":)";
    return out;
}

iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s),
    width_(s.width()),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
{}

iofmtguard::~iofmtguard() {
    s_.width(width_);
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}
