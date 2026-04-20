#include "DataStruct.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <limits>
#include <sstream>
#include <cmath>

bool cmp(const DataStruct& a, const DataStruct& b) {
    const double EPS = 1e-9;
    if (std::fabs(a.key1 - b.key1) > EPS) {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    if (a.key3.size() != b.key3.size()) {
        return a.key3.size() < b.key3.size();
    }
    return a.key3 < b.key3;
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
        return 0;
    }

    std::sort(data.begin(), data.end(), cmp);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
