#include <iostream>
#include <string>
#include <vector>

class BigInteger {
  bool sign;
  static const int BASE = 1'000'000'000u;
  std::vector<unsigned int> number;

public:
  BigInteger();
  BigInteger(const BigInteger &x) = default;
  explicit BigInteger(const size_t &x);
  BigInteger(const int &x);
  explicit BigInteger(const bool &x);
  explicit operator bool() const;
  explicit operator int() const;
  BigInteger &operator=(const BigInteger &x) = default;
  BigInteger &operator=(const int &x);
  BigInteger &operator=(const bool &x);
  BigInteger &operator+=(const BigInteger &x);
  BigInteger &operator++();
  BigInteger operator++(int);
  BigInteger &operator-=(const BigInteger &x);
  BigInteger &operator--();
  BigInteger operator--(int);
  BigInteger operator-() const;
  BigInteger &operator*=(const BigInteger &x);
  BigInteger &operator/=(const BigInteger &x);
  BigInteger &operator/=(const int &x);
  BigInteger &operator%=(const BigInteger &x);

  friend std::istream &operator>>(std::istream &in, BigInteger &x);
  friend bool operator<(const BigInteger &x, const BigInteger &y);

  std::string toString() const;

private:
  std::vector<unsigned int> multiply(std::vector<unsigned int> x,
                                     std::vector<unsigned int> y) const;
};

std::istream &operator>>(std::istream &in, BigInteger &x);

std::ostream &operator<<(std::ostream &out, const BigInteger &x);

bool operator<(const BigInteger &x, const BigInteger &y);

bool operator>(const BigInteger &x, const BigInteger &y);

bool operator==(const BigInteger &x, const BigInteger &y);

bool operator!=(const BigInteger &x, const BigInteger &y);

bool operator<=(const BigInteger &x, const BigInteger &y);

bool operator>=(const BigInteger &x, const BigInteger &y);

BigInteger operator+(const BigInteger &x, const BigInteger &y);

BigInteger operator-(const BigInteger &x, const BigInteger &y);

BigInteger operator*(const BigInteger &x, const BigInteger &y);

BigInteger operator/(const BigInteger &x, const BigInteger &y);

BigInteger operator/(const BigInteger &x, const int &y);

BigInteger operator%(const BigInteger &x, const BigInteger &y);

//.............................................................

BigInteger::BigInteger() : sign(true) { number.emplace_back(0); }

BigInteger::BigInteger(const size_t &x) : sign(true) {
  size_t copy = x;
  if (x == 0) {
    number.emplace_back(0);
  }
  while (copy != 0) {
    number.emplace_back(copy % BASE);
    copy = copy / BASE;
  }
}

BigInteger::BigInteger(const int &x) {
  sign = x >= 0;
  if (x == 0) {
    number.emplace_back(0);
  }
  int copy = abs(x);
  while (copy != 0) {
    number.emplace_back(copy % BASE);
    copy = copy / BASE;
  }
}

BigInteger::BigInteger(const bool &x) : sign(true) {
  number.emplace_back(x ? 1 : 0);
}

BigInteger &BigInteger::operator=(const int &x) {
  number.clear();
  sign = x >= 0;
  if (x == 0) {
    number.emplace_back(0);
  }
  int copy = abs(x);
  while (copy != 0) {
    number.emplace_back(copy % BASE);
    copy = copy / BASE;
  }
  return *this;
}

BigInteger &BigInteger::operator=(const bool &x) {
  number.clear();
  sign = true;
  number.emplace_back(static_cast<unsigned int>(x));
  return *this;
}

BigInteger::operator bool() const {
  if (number.size() == 1 && number[0] == 0)
    return false;
  return true;
}

BigInteger::operator int() const {
  if (number.empty())
    return 0;
  if (number.size() == 1)
    return static_cast<int>(sign ? number[0] : -number[0]);
  if (number.size() > 2)
    throw std::exception();
  return static_cast<int>(sign ? number[0] + number[1] * BASE
                               : -(number[0] + number[1] * BASE));
}

BigInteger &BigInteger::operator+=(const BigInteger &x) {
  if (sign != x.sign) {
    BigInteger copy_this = *this;
    copy_this.sign = true;
    BigInteger copy_x = x;
    copy_x.sign = true;
    if (copy_x < copy_this) {
      copy_this -= copy_x;
      number = copy_this.number;
      return *this;
    } else {
      copy_x -= copy_this;
      number = copy_x.number;
      sign = (!sign || (*this == x && x == 0));
      return *this;
    }
  }
  unsigned int in_mind = 0;
  for (size_t i = 0;
       i < std::max(x.number.size(), number.size()) || in_mind != 0; ++i) {
    if (i >= number.size())
      number.emplace_back(0);
    number[i] += ((i < x.number.size() ? x.number[i] : 0) + in_mind);
    in_mind = number[i] / BASE;
    number[i] %= BASE;
  }
  return *this;
}

BigInteger &BigInteger::operator++() {
  *this += 1;
  return *this;
}

BigInteger BigInteger::operator++(int) {
  BigInteger copy = *this;
  ++*this;
  return copy;
}

BigInteger &BigInteger::operator-=(const BigInteger &x) {
  if (!sign && x.sign) {
    sign = true;
    *this += x;
    sign = false;
    return *this;
  }
  if (sign && !x.sign) {
    BigInteger copy = x;
    copy.sign = true;
    *this += copy;
    return *this;
  }
  BigInteger copy_this = *this;
  copy_this.sign = true;
  BigInteger copy_x = x;
  copy_x.sign = true;
  if (copy_this < copy_x) {
    sign = !sign;
    copy_x -= copy_this;
    number = copy_x.number;
    return *this;
  }
  unsigned int in_mind = 0;
  int temp = 0;
  for (size_t i = 0; i < x.number.size() || in_mind != 0; ++i) {
    temp = static_cast<int>(number[i]);
    temp -= static_cast<int>(in_mind + (i < x.number.size() ? x.number[i] : 0));
    in_mind = temp < 0;
    if (in_mind != 0)
      temp += BASE;
    number[i] = temp;
  }
  while (number.size() > 1 && number.back() == 0)
    number.pop_back();
  return *this;
}

BigInteger &BigInteger::operator--() {
  *this -= 1;
  return *this;
}

BigInteger BigInteger::operator--(int) {
  BigInteger copy = *this;
  --*this;
  return copy;
}

BigInteger BigInteger::operator-() const {
  BigInteger copy = *this;
  if (copy.number.size() == 1 && copy.number[0] == 0) {
    copy = 0;
  } else {
    copy.sign = !copy.sign;
  }
  return copy;
}

std::vector<unsigned int>
BigInteger::multiply(std::vector<unsigned int> x,
                     std::vector<unsigned int> y) const {
  if (x.size() == 1 || y.size() == 1) {
    std::vector<unsigned int> result(x.size() + y.size());
    for (size_t i = 0; i < x.size(); ++i) {
      for (unsigned int j = 0, in_mind = 0; j < y.size() || in_mind; ++j) {
        unsigned long long cur =
            result[i + j] + x[i] * 1ll * (j < y.size() ? y[j] : 0) + in_mind;
        result[i + j] = cur % BASE;
        in_mind = cur / BASE;
      }
    }
    return result;
  } else {
    while (x.size() < y.size())
      x.emplace_back(0);
    while (y.size() < x.size())
      y.emplace_back(0);
    if (x.size() % 2 == 1) {
      x.emplace_back(0);
      y.emplace_back(0);
    }
    std::vector<unsigned int> result(x.size() + y.size());
    size_t Size = x.size() / 2;
    std::vector<unsigned int> x_left(x.begin(), x.begin() + Size);
    std::vector<unsigned int> x_right(x.begin() + Size, x.end());
    std::vector<unsigned int> y_left(y.begin(), y.begin() + Size);
    std::vector<unsigned int> y_right(y.begin() + Size, y.end());

    std::vector<unsigned int> multiply_right = multiply(x_right, y_right);
    std::vector<unsigned int> multiply_left = multiply(x_left, y_left);

    std::vector<unsigned int> sum_x(Size);
    std::vector<unsigned int> sum_y(Size);
    for (unsigned int i = 0; i < Size; ++i) {
      sum_x[i] = x_left[i] + x_right[i];
      sum_y[i] = y_left[i] + y_right[i];
    }
    unsigned int in_mind = 0;
    for (size_t i = 0; i < sum_x.size() || in_mind != 0; ++i) {
      if (i >= sum_x.size())
        sum_x.emplace_back(0);
      sum_x[i] += in_mind;
      in_mind = sum_x[i] / BASE;
      sum_x[i] %= BASE;
    }
    in_mind = 0;
    for (size_t i = 0; i < sum_y.size() || in_mind != 0; ++i) {
      if (i >= sum_y.size())
        sum_y.emplace_back(0);
      sum_y[i] += in_mind;
      in_mind = sum_y[i] / BASE;
      sum_y[i] %= BASE;
    }
    std::vector<unsigned int> multiply_middle = multiply(sum_x, sum_y);

    in_mind = 0;
    int temp = 0;
    for (size_t i = 0; i < multiply_right.size() || in_mind != 0; ++i) {
      temp = static_cast<int>(multiply_middle[i]);
      temp -= static_cast<int>(
          in_mind + (i < multiply_right.size() ? multiply_right[i] : 0));
      in_mind = temp < 0;
      if (in_mind != 0)
        temp += BASE;
      multiply_middle[i] = temp;
    }

    in_mind = 0;
    temp = 0;
    for (size_t i = 0; i < multiply_left.size() || in_mind != 0; ++i) {
      temp = static_cast<int>(multiply_middle[i]);
      temp -= static_cast<int>(
          in_mind + (i < multiply_left.size() ? multiply_left[i] : 0));
      in_mind = temp < 0;
      if (in_mind != 0)
        temp += BASE;
      multiply_middle[i] = temp;
    }
    for (size_t i = 0; i < multiply_left.size(); ++i)
      result[i] = multiply_left[i];

    for (size_t i = Size * 2; i < Size * 2 + multiply_right.size(); ++i)
      result[i] = multiply_right[i - Size * 2];

    for (size_t i = Size; i < Size + multiply_middle.size(); ++i)
      result[i] += multiply_middle[i - Size];

    in_mind = 0;
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] += in_mind;
      in_mind = result[i] / BASE;
      result[i] %= BASE;
    }
    return result;
  }
}

BigInteger &BigInteger::operator*=(const BigInteger &x) {
  sign = (sign == x.sign || x == 0 || *this == 0);
  auto result = multiply(number, x.number);
  while (result.size() > 1 && result.back() == 0)
    result.pop_back();
  number = result;
  return *this;
}

BigInteger &BigInteger::operator/=(const int &x) {
  sign = (sign == (x > 0) || *this == 0);
  unsigned int in_mind = 0;
  for (int i = static_cast<int>(number.size()) - 1; i >= 0; --i) {
    size_t cur = number[i] + in_mind * 1ll * BASE;
    number[i] = static_cast<unsigned int>(cur / abs(x));
    in_mind = static_cast<unsigned int>(cur % abs(x));
  }
  while (number.size() > 1 && number.back() == 0)
    number.pop_back();
  return *this;
}

BigInteger &BigInteger::operator/=(const BigInteger &x) {
  BigInteger abs_x = x, abs_this = *this;
  abs_x.sign = true;
  abs_this.sign = true;
  if (abs_this < abs_x) {
    *this = 0;
    return *this;
  }
  BigInteger left = 0;
  BigInteger right = abs_this;
  while (left < right) {
    BigInteger middle = (right + left) / 2;
    if (middle * abs_x <= abs_this) {
      left = middle + 1;
    } else {
      right = middle;
    }
  }
  --left;
  left.sign = sign == x.sign;
  *this = left;
  return *this;
}

BigInteger &BigInteger::operator%=(const BigInteger &x) {
  *this = *this - (*this / x) * x;
  return *this;
}

std::string BigInteger::toString() const {
  std::string x;
  if (number.empty())
    return "";
  if (number.size() == 1 && number[0] == 0)
    return "0";
  if (!sign)
    x = "-";
  x += std::to_string(number.back());
  for (int i = static_cast<int>(number.size()) - 2; i >= 0; --i) {
    unsigned int copy = number[i];
    while (copy != 0 && copy < 100'000'000) {
      x += "0";
      copy *= 10;
    }
    if (copy == 0)
      x += "00000000";
    x += std::to_string(number[i]);
  }
  return x;
}

std::istream &operator>>(std::istream &in, BigInteger &x) {
  std::string s;
  in >> s;
  x.number.clear();
  x.sign = true;
  if (!s.empty() && s[0] == '-') {
    x.sign = false;
    s.erase(0, 1);
  }
  for (int i = static_cast<int>(s.size()) - 1; i >= 0; i -= 9) {
    if (i < 8)
      x.number.emplace_back(std::stoi(s.substr(0, i + 1)));
    else
      x.number.emplace_back(std::stoi(s.substr(i - 8, 9)));
  }

  return in;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &x) {
  out << x.toString();
  return out;
}

bool operator<(const BigInteger &x, const BigInteger &y) {
  if (!x.sign && y.sign)
    return true;
  if (x.sign && !y.sign)
    return false;
  if (x.sign && y.sign) {
    if (x.number.size() != y.number.size())
      return x.number.size() < y.number.size();
    for (int i = static_cast<int>(x.number.size()) - 1; i >= 0; --i) {
      if (x.number[i] != y.number[i])
        return x.number[i] < y.number[i];
    }
  } else {
    if (x.number.size() != y.number.size())
      return x.number.size() > y.number.size();
    for (int i = static_cast<int>(x.number.size()) - 1; i >= 0; --i) {
      if (x.number[i] != y.number[i])
        return x.number[i] > y.number[i];
    }
  }
  return false;
}

bool operator>(const BigInteger &x, const BigInteger &y) { return y < x; }

bool operator==(const BigInteger &x, const BigInteger &y) {
  return !(x < y || y < x);
}

bool operator!=(const BigInteger &x, const BigInteger &y) { return !(x == y); }

bool operator<=(const BigInteger &x, const BigInteger &y) { return !(x > y); }

bool operator>=(const BigInteger &x, const BigInteger &y) { return !(x < y); }

BigInteger operator+(const BigInteger &x, const BigInteger &y) {
  BigInteger copy = x;
  copy += y;
  return copy;
}

BigInteger operator-(const BigInteger &x, const BigInteger &y) {
  BigInteger copy = x;
  copy -= y;
  return copy;
}

BigInteger operator*(const BigInteger &x, const BigInteger &y) {
  BigInteger copy = x;
  copy *= y;
  return copy;
}

BigInteger operator/(const BigInteger &x, const BigInteger &y) {
  BigInteger copy = x;
  copy /= y;
  return copy;
}

BigInteger operator/(const BigInteger &x, const int &y) {
  BigInteger copy = x;
  copy /= y;
  return copy;
}

BigInteger operator%(const BigInteger &x, const BigInteger &y) {
  BigInteger copy = x;
  copy %= y;
  return copy;
}
