#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <limits>

struct DataStruct {
  unsigned long long key1;
  size_t key1_width;
  std::complex<double> key2;
  std::string key3;
};

struct DelimiterIO {
  char exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) return in;
  char c;
  in >> c;
  if (in && std::tolower(c) != std::tolower(dest.exp)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

struct KeyIO {
  std::string& key;
};

std::istream& operator>>(std::istream& in, KeyIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) return in;

  if (!(in >> DelimiterIO{ ':' })) return in;

  dest.key.clear();
  char c;
  while (in >> c && std::isalpha(c)) {
    dest.key += c;
    if (!std::isalpha(in.peek())) break;
  }
  if (in && std::isdigit(in.peek())) {
    in >> c;
    dest.key += c;
  }
  return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) return in;

  DataStruct input{ 0, 0, {0.0, 0.0}, "" };
  if (!(in >> DelimiterIO{ '(' })) return in;

  for (int i = 0; i < 3; ++i) {
    std::string key;
    if (!(in >> KeyIO{ key })) break;

    if (key == "key1") {
      in >> DelimiterIO{ '0' } >> DelimiterIO{ 'b' };
      std::string bin;
      while (in.peek() == '0' || in.peek() == '1') {
        char c; in >> c; bin += c;
      }
      if (!bin.empty()) {
        input.key1 = std::stoull(bin, nullptr, 2);
        input.key1_width = bin.length();
      }
      else {
        in.setstate(std::ios::failbit);
      }
    }
    else if (key == "key2") {
      double re, im;
      in >> DelimiterIO{ '#' } >> DelimiterIO{ 'c' } >> DelimiterIO{ '(' } >> re >> im >> DelimiterIO{ ')' };
      input.key2 = { re, im };
    }
    else if (key == "key3") {
      in >> DelimiterIO{ '"' };
      std::getline(in, input.key3, '"');
    }
  }
  in >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };

  if (in) dest = input;
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
  std::ostream::sentry sentry(out);
  if (!sentry) return out;

  out << "(:key1 0b";
  std::string b;
  unsigned long long n = src.key1;
  if (n == 0) {
    b = "0";
  }
  else {
    while (n > 0) {
      b += (n % 2 ? '1' : '0');
      n /= 2;
    }
  }
  while (b.length() < src.key1_width) {
    b += '0';
  }
  std::reverse(b.begin(), b.end());
  out << b;

  out << ":key2 #c(" << std::fixed << std::setprecision(1)
    << src.key2.real() << " " << src.key2.imag() << "):key3 \""
    << src.key3 << "\":)";
  return out;
}

int main() {
  std::vector<DataStruct> data;

  while (!std::cin.eof()) {
    std::copy(
      std::istream_iterator<DataStruct>(std::cin),
      std::istream_iterator<DataStruct>(),
      std::back_inserter(data)
    );

    if (std::cin.fail() && !std::cin.eof()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end(), [](const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (std::abs(std::abs(a.key2) - std::abs(b.key2)) > 1e-9)
      return std::abs(a.key2) < std::abs(b.key2);
    return a.key3.length() < b.key3.length();
    });

  std::copy(data.begin(), data.end(),
    std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}
