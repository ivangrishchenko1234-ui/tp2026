#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>

struct DataStruct {
    double key1;
    long long key2;
    std::string key3;
};

struct DelimiterIO {
    char exp;
};

struct DoubleIO {
    double& ref;
};

struct StringIO {
    std::string& ref;
};

struct LongLongIO {
    long long& ref;
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
std::istream& operator>>(std::istream& in, DoubleIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LongLongIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& os, const DataStruct& data);
bool compareDataStruct(const DataStruct& a, const DataStruct& b);

#endif
