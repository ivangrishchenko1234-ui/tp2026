#include "DataStruct.h"

#include <algorithm>
#include <vector>
#include <iterator>
#include <limits>
#include <string>


int main() {
    std::vector<DataStruct> data;
    std::string line;

    while (std::getline(std::cin, line)) {

        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        DataStruct temp;

        if (ss >> temp) {
            data.push_back(temp);
        }
    }

    std::sort(data.begin(), data.end(), compareDataStruct);
    std::copy(
        std::begin(data),
        std::end(data),
        std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
