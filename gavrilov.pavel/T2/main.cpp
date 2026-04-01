#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

namespace nspace
{
    struct DataStruct
    {
        double key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct DoubleLitIO
    {
        double& ref;
    };

    struct RationalIO
    {
        std::pair<long long, unsigned long long>& ref;
    };

    struct StringIO
    {
        std::string& ref;
    };

    class iofmtguard
    {
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
    std::istream& operator>>(std::istream& in, DoubleLitIO&& dest);
    std::istream& operator>>(std::istream& in, RationalIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}

nspace::iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s),
    width_(s.width()),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
{}

nspace::iofmtguard::~iofmtguard()
{
    s_.width(width_);
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}

std::istream& nspace::operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& nspace::operator>>(std::istream& in, DoubleLitIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    double value;
    char suffix;
    in >> value >> suffix;
    if (in && (suffix == 'd' || suffix == 'D'))
    {
        dest.ref = value;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& nspace::operator>>(std::istream& in, RationalIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    long long numerator;
    unsigned long long denominator;
    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' } >> DelimiterIO{ 'N' };
    in >> numerator;
    in >> DelimiterIO{ ':' } >> DelimiterIO{ 'D' };
    in >> denominator;
    in >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
    if (in && denominator != 0)
    {
        dest.ref = std::make_pair(numerator, denominator);
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& nspace::operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& nspace::operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    std::string line;
    if (!std::getline(in, line))
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::istringstream iss(line);

    DataStruct input;
    bool key1Set = false;
    bool key2Set = false;
    bool key3Set = false;

    char openBracket;
    iss >> openBracket;
    if (openBracket != '(')
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    while (iss)
    {
        char c;
        iss >> c;
        if (c == ')')
        {
            break;
        }
        iss.putback(c);

        std::string fieldName;
        iss >> fieldName;
        if (!iss) break;

        char colon;
        iss >> colon;
        if (colon != ':') break;

        if (fieldName == "key1")
        {
            double value;
            char suffix;
            iss >> value >> suffix;
            if (iss && (suffix == 'd' || suffix == 'D'))
            {
                input.key1 = value;
                key1Set = true;
            }
            else
            {
                break;
            }
        }
        else if (fieldName == "key2")
        {
            char openParen;
            iss >> openParen;
            if (openParen != '(') break;

            char colon1, n, colon2, d, colon3;
            long long numerator;
            unsigned long long denominator;

            iss >> colon1 >> n >> colon2;
            if (colon1 != ':' || n != 'N' || colon2 != ':') break;

            iss >> numerator;
            iss >> colon3;
            if (colon3 != ':') break;

            iss >> d >> colon2;
            if (d != 'D' || colon2 != ':') break;

            iss >> denominator;
            iss >> colon3;
            if (colon3 != ':') break;

            char closeParen;
            iss >> closeParen;
            if (closeParen != ')') break;

            if (denominator == 0) break;

            input.key2 = std::make_pair(numerator, denominator);
            key2Set = true;
        }
        else if (fieldName == "key3")
        {
            char quote;
            iss >> quote;
            if (quote != '"') break;

            std::string value;
            std::getline(iss, value, '"');
            input.key3 = value;
            key3Set = true;
        }
        else
        {
            break;
        }
    }

    if (key1Set && key2Set && key3Set)
    {
        dest = std::move(input);
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream& nspace::operator<<(std::ostream& out, const DataStruct& src)
{
    std::ostream::sentry sentry(out);
    if (!sentry) return out;
    nspace::iofmtguard fmtguard(out);

    out << "(:key1 " << std::fixed << std::setprecision(1) << src.key1 << "d";
    out << ":key2 (:N " << src.key2.first << ":D " << src.key2.second << ":)";
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}

int main()
{
    std::vector<nspace::DataStruct> dataVector;

    std::istream_iterator<nspace::DataStruct> inputBegin(std::cin);
    std::istream_iterator<nspace::DataStruct> inputEnd;
    std::copy(inputBegin, inputEnd, std::back_inserter(dataVector));

    std::sort(dataVector.begin(), dataVector.end(),
        [](const nspace::DataStruct& a, const nspace::DataStruct& b) {
            if (a.key1 != b.key1) {
                return a.key1 < b.key1;
            }
            double aKey2Value = static_cast<double>(a.key2.first) / a.key2.second;
            double bKey2Value = static_cast<double>(b.key2.first) / b.key2.second;
            if (std::abs(aKey2Value - bKey2Value) > 1e-12) {
                return aKey2Value < bKey2Value;
            }
            return a.key3.length() < b.key3.length();
        });

    std::ostream_iterator<nspace::DataStruct> outputBegin(std::cout, "\n");
    std::copy(dataVector.begin(), dataVector.end(), outputBegin);

    return 0;
}
