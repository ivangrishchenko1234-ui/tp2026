#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <utility>

struct DataStruct
{
    char key1;
    std::pair<long long, unsigned long long> key2;
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

struct CharLiteralIO
{
    char& ref;
};

std::istream& operator>>(std::istream& in, CharLiteralIO&& dest)
{
    std::istream::sentry sentry(in, true);
    if (!sentry)
    {
        return in;
    }
    char c;
    in >> DelimiterIO{ '\'' } >> c >> DelimiterIO{ '\'' };
    if (in)
    {
        dest.ref = c;
    }
    return in;
}

struct RationalIO
{
    std::pair<long long, unsigned long long>& ref;
};

std::istream& operator>>(std::istream& in, RationalIO&& dest)
{
    std::istream::sentry sentry(in, true);
    if (!sentry)
    {
        return in;
    }

    long long numerator;
    long long denominator_signed;

    in >> DelimiterIO{ '(' }
    >> DelimiterIO{ ':' } >> DelimiterIO{ 'N' };
    if (!in)
    {
        return in;
    }

    if (!std::isspace(in.peek()))
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    in.get();

    in >> numerator;
    if (!in)
    {
        return in;
    }

    in >> DelimiterIO{ ':' } >> DelimiterIO{ 'D' };
    if (!in)
    {
        return in;
    }

    if (!std::isspace(in.peek()))
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    in.get();

    in >> denominator_signed;
    if (!in)
    {
        return in;
    }

    if (denominator_signed <= 0)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    unsigned long long denominator = static_cast<unsigned long long>(denominator_signed);

    in >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };

    if (in && denominator != 0)
    {
        dest.ref = { numerator, denominator };
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
            in >> CharLiteralIO{ temp.key1 };
            key1_set = true;
        }
        else if (field_name == "key2" && !key2_set)
        {
            in >> RationalIO{ temp.key2 };
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

    out << "(:key1 '" << src.key1 << "':key2 (:N "
        << src.key2.first << ":D " << src.key2.second
        << ":):key3 \"" << src.key3 << "\":)";

    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1)
    {
        return a.key1 < b.key1;
    }
    double valA = static_cast<double>(a.key2.first) / static_cast<double>(a.key2.second);
    double valB = static_cast<double>(b.key2.first) / static_cast<double>(b.key2.second);
    if (valA != valB)
    {
        return valA < valB;
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

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
