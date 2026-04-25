#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <complex>
#include <iomanip>

using namespace std;

struct DataStruct {
    unsigned long long key1;
    complex<double> key2;
    string key3;
};

istream& operator>>(istream& in, DataStruct& ds) {
    string line;
    if (!getline(in, line)) return in;
    
    ds.key1 = 0;
    ds.key2 = complex<double>(0,0);
    ds.key3 = "";
    
    size_t pos = line.find('(');
    if (pos == string::npos) {
        in.setstate(ios::failbit);
        return in;
    }
    
    pos++;
    while (pos < line.length() && line[pos] != ')') {
        if (line[pos] != ':') { pos++; continue; }
        pos++;
        
        string field;
        while (pos < line.length() && line[pos] != ' ') {
            field += line[pos];
            pos++;
        }
        while (pos < line.length() && line[pos] == ' ') pos++;
        
        if (field == "key1") {
            if (line[pos] == '0' && (line[pos+1] == 'x' || line[pos+1] == 'X')) {
                ds.key1 = stoull(line.substr(pos+2), nullptr, 16);
            }
            while (pos < line.length() && line[pos] != ':') pos++;
        }
        else if (field == "key2") {
            if (line[pos] == '#' && line[pos+1] == 'c' && line[pos+2] == '(') {
                pos += 3;
                string re_str, im_str;
                while (pos < line.length() && line[pos] != ' ') {
                    re_str += line[pos];
                    pos++;
                }
                while (pos < line.length() && line[pos] == ' ') pos++;
                while (pos < line.length() && line[pos] != ')') {
                    im_str += line[pos];
                    pos++;
                }
                if (line[pos] == ')') pos++;
                ds.key2 = complex<double>(stod(re_str), stod(im_str));
            }
            while (pos < line.length() && line[pos] != ':') pos++;
        }
        else if (field == "key3") {
            if (line[pos] == '"') {
                pos++;
                while (pos < line.length() && line[pos] != '"') {
                    ds.key3 += line[pos];
                    pos++;
                }
                if (line[pos] == '"') pos++;
            }
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const DataStruct& ds) {
    out << "(:key1 0x" << uppercase << hex << ds.key1 << dec << nouppercase;
    out << ":key2 #c(" << fixed << setprecision(1) << ds.key2.real() 
        << " " << ds.key2.imag() << ")";
    out << ":key3 \"" << ds.key3 << "\":)";
    return out;
}

bool cmp(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    double aa = abs(a.key2);
    double bb = abs(b.key2);
    if (aa != bb) return aa < bb;
    return a.key3.length() < b.key3.length();
}

int main() {
    vector<DataStruct> v;
    copy(istream_iterator<DataStruct>(cin),
         istream_iterator<DataStruct>(),
         back_inserter(v));
    sort(v.begin(), v.end(), cmp);
    copy(v.begin(), v.end(), ostream_iterator<DataStruct>(cout, "\n"));
    return 0;
}
