#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <complex>
#include <cmath>
#include <iomanip>
#include <cctype>
#include <sstream>

namespace nspace
{
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

    struct LabelIO
    {
        std::string exp;
    };

    struct UllHexIO
    {
        unsigned long long& ref;
    };

    struct ComplexIO
    {
        std::complex<double>& ref;
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
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, UllHexIO&& dest);
    std::istream& operator>>(std::istream& in, ComplexIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);

    std::ostream& operator<<(std::ostream& out, const DataStruct& src);

    bool compareDataStruct(const DataStruct& a, const DataStruct& b);
}

int main()
{
    using nspace::DataStruct;

    std::vector<DataStruct> data;

    // Чтение данных с использованием итераторов
    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
    );

    // Сортировка
    std::sort(data.begin(), data.end(), nspace::compareDataStruct);

    // Вывод результатов
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}

namespace nspace
{
    iofmtguard::iofmtguard(std::basic_ios<char>& s) :
        s_(s),
        width_(s.width()),
        fill_(s.fill()),
        precision_(s.precision()),
        fmt_(s.flags())
    {
    }

    iofmtguard::~iofmtguard()
    {
        s_.width(width_);
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        std::string label;
        in >> label;

        if (in && label != dest.exp)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, UllHexIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        std::string hexStr;
        in >> hexStr;

        if (in)
        {
            // Проверка формата шестнадцатеричного литерала
            if (hexStr.length() > 2 && (hexStr[0] == '0' && (hexStr[1] == 'x' || hexStr[1] == 'X')))
            {
                unsigned long long value = 0;
                bool valid = true;

                for (size_t i = 2; i < hexStr.length(); i++)
                {
                    char c = hexStr[i];
                    if (c >= '0' && c <= '9')
                    {
                        value = value * 16 + (c - '0');
                    }
                    else if (c >= 'A' && c <= 'F')
                    {
                        value = value * 16 + (c - 'A' + 10);
                    }
                    else if (c >= 'a' && c <= 'f')
                    {
                        value = value * 16 + (c - 'a' + 10);
                    }
                    else
                    {
                        valid = false;
                        break;
                    }
                }

                if (valid)
                {
                    dest.ref = value;
                }
                else
                {
                    in.setstate(std::ios::failbit);
                }
            }
            else
            {
                in.setstate(std::ios::failbit);
            }
        }

        return in;
    }

    std::istream& operator>>(std::istream& in, ComplexIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        double real, imag;

        in >> DelimiterIO{ '#' };
        in >> DelimiterIO{ 'c' };
        in >> DelimiterIO{ '(' };
        in >> real;
        in >> imag;
        in >> DelimiterIO{ ')' };

        if (in)
        {
            dest.ref = std::complex<double>(real, imag);
        }

        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        DataStruct input;
        bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

        // Чтение открывающей скобки
        in >> DelimiterIO{ '(' };
        if (!in) return in;

        in >> DelimiterIO{ ':' };

        // Чтение полей в произвольном порядке
        while (in)
        {
            std::string label;
            if (!(in >> label))
                break;

            in >> DelimiterIO{ ' ' };

            if (label == "key1")
            {
                in >> UllHexIO{ input.key1 };
                hasKey1 = true;
            }
            else if (label == "key2")
            {
                in >> ComplexIO{ input.key2 };
                hasKey2 = true;
            }
            else if (label == "key3")
            {
                in >> StringIO{ input.key3 };
                hasKey3 = true;
            }
            else
            {
                in.setstate(std::ios::failbit);
                break;
            }

            if (!in) break;

            char nextChar;
            in >> nextChar;

            if (nextChar == ':')
            {
                continue;
            }
            else if (nextChar == ')')
            {
                break;
            }
            else
            {
                in.setstate(std::ios::failbit);
                break;
            }
        }

        if (in && hasKey1 && hasKey2 && hasKey3)
        {
            dest = std::move(input);
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

        iofmtguard fmtguard(out);

        out << "(:";

        out << "key1 ";
        out << "0x" << std::uppercase << std::hex << src.key1;

        out << ":key2 #c(";
        out << std::fixed << std::setprecision(1) << src.key2.real();
        out << " ";
        out << std::fixed << std::setprecision(1) << src.key2.imag();
        out << ")";

        out << ":key3 \"" << src.key3 << "\"";

        out << ":)";

        return out;
    }

    bool compareDataStruct(const DataStruct& a, const DataStruct& b)
    {
        if (a.key1 != b.key1)
        {
            return a.key1 < b.key1;
        }

        double modA = std::abs(a.key2);
        double modB = std::abs(b.key2);
        if (std::abs(modA - modB) > 1e-10)
        {
            return modA < modB;
        }

        return a.key3.length() < b.key3.length();
    }
}
