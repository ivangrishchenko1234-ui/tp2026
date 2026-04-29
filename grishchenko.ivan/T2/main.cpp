#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <complex>
#include <iomanip>

struct DataStruct
{
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
};

struct DelimiterIO
{
    char exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in, true);
    if (!sentry)
    {
        return in;
    }
    char c = '0';
    in.get(c);
    if (in && c != dest.exp)
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct UllHexIO
{
    unsigned long long& ref;
};

std::istream& operator>>(std::istream& in, UllHexIO&& dest)
{
    std::istream::sentry sentry(in, true);
    if (!sentry)
    {
        return in;
    }

    in >> DelimiterIO{ '0' };
    if (!in)
    {
        return in;
    }

    char c;
    in.get(c);
    if (c != 'x' && c != 'X')
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    dest.ref = 0;
    while (in.get(c) && std::isxdigit(static_cast<unsigned char>(c)))
    {
        dest.ref <<= 4;
        if (c >= '0' && c <= '9')
        {
            dest.ref += (c - '0');
        }
        else if (c >= 'a' && c <= 'f')
        {
            dest.ref += (c - 'a' + 10);
        }
        else if (c >= 'A' && c <= 'F')
        {
            dest.ref += (c - 'A' + 10);
        }
    }

    if (!in && !in.eof())
    {
        in.setstate(std::ios::failbit);
    }
    else
    {
        in.clear();
    }

    return in;
}

struct ComplexIO
{
    std::complex<double>& ref;
};

std::istream& operator>>(std::istream& in, ComplexIO&& dest)
{
    std::istream::sentry sentry(in, true);
    if (!sentry)
    {
        return in;
    }

    in >> DelimiterIO{ '#' } >> DelimiterIO{ 'c' } >> DelimiterIO{ '(' };
    if (!in)
    {
        return in;
    }

    double re, im;
    in >> re >> im;
    if (!in)
    {
        return in;
    }

    in >> DelimiterIO{ ')' };
    if (in)
    {
        dest.ref = std::complex<double>(re, im);
    }
    return in;
}

struct StringIO
{
    std::string& ref;
};

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in, true);
    if (!sentry)
    {
        return in;
    }

    char c;
    in.get(c);
    if (c != '"')
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    dest.ref.clear();
    while (in.get(c) && c != '"')
    {
        if (c == '\\' && in.peek() == '"')
        {
            in.get(c);
        }
        dest.ref.push_back(c);
    }

    if (!in)
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    return in;
}

struct IdentifierIO
{
    std::string& ref;
};

std::istream& operator>>(std::istream& in, IdentifierIO&& dest)
{
    std::istream::sentry sentry(in, true);
    if (!sentry)
    {
        return in;
    }

    dest.ref.clear();
    char c = '0';
    while (in.get(c) && (std::isalpha(static_cast<unsigned char>(c)) ||
        std::isdigit(static_cast<unsigned char>(c))))
    {
        dest.ref.push_back(c);
    }

    if (dest.ref.empty())
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    while (std::isspace(in.peek()))
    {
        in.get();
    }

    if (in.peek() != '(')
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    DataStruct temp;
    bool key1_set = false;
    bool key2_set = false;
    bool key3_set = false;

    in >> DelimiterIO{ '(' };
    if (!in)
    {
        return in;
    }

    while (in && in.peek() != ')')
    {
        if (in.peek() == ':')
        {
            in.get();
        }

        std::string field_name;
        in >> IdentifierIO{ field_name };
        if (!in)
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (in.peek() == ' ')
        {
            in.get();
        }

        if (field_name == "key1" && !key1_set)
        {
            in >> UllHexIO{ temp.key1 };
            key1_set = true;
        }
        else if (field_name == "key2" && !key2_set)
        {
            in >> ComplexIO{ temp.key2 };
            key2_set = true;
        }
        else if (field_name == "key3" && !key3_set)
        {
            in >> StringIO{ temp.key3 };
            key3_set = true;
        }
        else
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (!in)
        {
            return in;
        }

        if (in.peek() == ':')
        {
            in.get();
        }
        else if (in.peek() != ')')
        {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    in >> DelimiterIO{ ')' };

    if (in && key1_set && key2_set && key3_set)
    {
        dest = temp;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }

    out << "(:key1 0x" << std::hex << std::uppercase << src.key1 << std::dec;
    out << ":key2 #c(" << std::fixed << std::setprecision(1) << src.key2.real() << " " << src.key2.imag() << ")";
    out << ":key3 \"" << src.key3 << "\":)";

    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1)
    {
        return a.key1 < b.key1;
    }
    double abs_a = std::abs(a.key2);
    double abs_b = std::abs(b.key2);
    if (abs_a != abs_b)
    {
        return abs_a < abs_b;
    }
    return a.key3.length() < b.key3.length();
}

int main()
{
    std::vector<DataStruct> data;
    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::istringstream lineStream(line);
        std::copy(
            std::istream_iterator<DataStruct>(lineStream),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );
    }

    if (data.empty())
    {
        std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped" << std::endl;
        return 0;
    }

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
