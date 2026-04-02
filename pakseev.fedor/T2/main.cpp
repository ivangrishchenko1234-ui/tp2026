#include "DataStruct.hpp"

#include <algorithm>
#include <vector>
#include <iterator>
#include <limits>

// --- 4 ---
int main() {
    std::vector<DataStruct> vec;
    while (!std::cin.eof()) {
        std::copy(std::istream_iterator<DataStruct>(std::cin),
                  std::istream_iterator<DataStruct>(),
                  std::back_inserter(vec));
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(vec.begin(), vec.end(), comparator);
    std::copy(
        std::begin(vec),
        std::end(vec),
        std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
