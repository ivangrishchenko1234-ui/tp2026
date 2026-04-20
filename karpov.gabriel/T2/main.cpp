#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <iostream>
#include "datastruct.h"

bool compare(const DataStruct& a, const DataStruct& b) {
    if (std::abs(a.key1 - b.key1) > 1e-10)
        return a.key1 < b.key1;
    if (a.key2 != b.key2)
        return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty())
            continue;
        std::istringstream iss(line);
        std::copy(
            std::istream_iterator<DataStruct>(iss),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );
    }
    std::sort(data.begin(), data.end(), compare);
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );
    return 0;
}
