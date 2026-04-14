#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <sstream>

struct DataStruct {
    unsigned long long key1;
    char key2;
    std::string key3;
};

struct SeparatorIO {
    char expected_char;
};

std::istream& operator>>(std::istream& in, SeparatorIO&& dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) {
        return in;
    }
    char c = '0';
    in.get(c);
    if (in && c != dest.expected_char) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct CharDataIO {
    char& ref;
};

std::istream& operator>>(std::istream& in, CharDataIO&& dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) {
        return in;
    }
    char c;
    in >> SeparatorIO{'\''} >> c >> SeparatorIO{'\''};
    if (in) {
        dest.ref = c;
    }
    return in;
}

struct StringDataIO {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, StringDataIO&& dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) {
        return in;
    }

    char c;
    in.get(c);
    if (c != '"') {
        in.setstate(std::ios::failbit);
        return in;
    }

    dest.ref.clear();
    while (in.get(c) && c != '"') {
        dest.ref.push_back(c);
    }

    if (!in) {
        in.setstate(std::ios::failbit);
        return in;
    }
    return in;
}

struct FieldLabelIO {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, FieldLabelIO&& dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) {
        return in;
    }

    dest.ref.clear();
    char c = '0';
    while (in.get(c) && std::isalnum(static_cast<unsigned char>(c))) {
        dest.ref.push_back(c);
    }

    if (dest.ref.empty()) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct OctalDataIO {
    unsigned long long& ref;
};

std::istream& operator>>(std::istream& in, OctalDataIO&& dest) {
    std::istream::sentry sentry(in, true);
    if (!sentry) {
        return in;
    }

    unsigned long long value = 0;
    char c;
    in >> std::ws;
    c = in.peek();
    if (c != '0') {
        in.setstate(std::ios::failbit);
        return in;
    }
    in.get();

    while (in.get(c) && c >= '0' && c <= '7') {
        value = value * 8 + (c - '0');
    }

    if (!in && !in.eof()) {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (in) {
        in.unget();
    } else if (in.eof()) {
        in.clear();
    }

    if (in) {
        dest.ref = value;
    }
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    while (std::isspace(in.peek())) {
        in.get();
    }

    if (in.peek() != '(') {
        in.setstate(std::ios::failbit);
        return in;
    }

    DataStruct parsed_data;
    bool has_k1 = false;
    bool has_k2 = false;
    bool has_k3 = false;

    in >> SeparatorIO{'('};
    if (!in) {
        return in;
    }

    while (in && in.peek() != ')') {
        if (in.peek() == ':') {
            in.get();
        }

        std::string label;
        in >> FieldLabelIO{label};
        if (!in) {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (in.peek() == ' ') {
            in.get();
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (label == "key1" && !has_k1) {
            in >> OctalDataIO{parsed_data.key1};
            has_k1 = true;
        }
        else if (label == "key2" && !has_k2) {
            in >> CharDataIO{parsed_data.key2};
            has_k2 = true;
        }
        else if (label == "key3" && !has_k3) {
            in >> StringDataIO{parsed_data.key3};
            has_k3 = true;
        }
        else {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (!in) {
            return in;
        }

        if (in.peek() == ':') {
            in.get();
        }
        else if (in.peek() != ')') {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    in >> SeparatorIO{')'};

    if (in && has_k1 && has_k2 && has_k3) {
        dest = parsed_data;
    }
    else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }

    out << "(:key1 0" << std::oct << src.key1 << std::dec
        << ":key2 '" << src.key2
        << "':key3 \"" << src.key3 << "\":)";

    return out;
}

bool compareRecords(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (std::all_of(line.begin(), line.end(), [](char c) {
            return std::isspace(static_cast<unsigned char>(c));
        })) {
            continue;
        }

        std::istringstream lineStream(line);
        std::copy(
            std::istream_iterator<DataStruct>(lineStream),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );
    }

    std::sort(data.begin(), data.end(), compareRecords);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
