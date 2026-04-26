#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <complex>
#include <cmath>
#include <cstdio>

struct DataStruct {
    std::complex<double> key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& d) {
    std::string line; double r,i; long long n; unsigned long long dn; char str[1000];
    while (std::getline(in, line))
        if (sscanf(line.c_str(), "(:key1 #c(%lf %lf):key2 (:n %lld:d %llu:):key3 \"%[^\"]\"", &r, &i, &n, &dn, str) == 5 ||
            sscanf(line.c_str(), "(:key2 (:n %lld:d %llu:):key1 #c(%lf %lf):key3 \"%[^\"]\"", &n, &dn, &r, &i, str) == 5 ||
            sscanf(line.c_str(), "(:key3 \"%[^\"]\":key1 #c(%lf %lf):key2 (:n %lld:d %llu:):", str, &r, &i, &n, &dn) == 5) {
            d.key1 = std::complex<double>(r, i);
            d.key2 = {n, dn};
            d.key3 = str;
            return in;
        }
    in.setstate(std::ios::failbit);
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& d) {
    out << "(:key1 #c(" << d.key1.real() << " " << d.key1.imag() << "):key2 (:n " 
        << d.key2.first << ":d " << d.key2.second << ":):key3 \"" << d.key3 << "\":)";
    return out;
}

int main() {
    std::vector<DataStruct> v;
    std::copy(std::istream_iterator<DataStruct>(std::cin), std::istream_iterator<DataStruct>(), std::back_inserter(v));
    if (v.empty()) return 1;
    std::sort(v.begin(), v.end(), [](const DataStruct& a, const DataStruct& b) {
        double ma = std::abs(a.key1);
        double mb = std::abs(b.key1);
        if (ma != mb) return ma < mb;
        double ra = static_cast<double>(a.key2.first) / a.key2.second;
        double rb = static_cast<double>(b.key2.first) / b.key2.second;
        if (ra != rb) return ra < rb;
        return a.key3.size() < b.key3.size();
    });
    std::copy(v.begin(), v.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    return 0;
}
