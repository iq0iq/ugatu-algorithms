#include <climits>
#include <iostream>
#include <string>
#include <vector>

std::vector<size_t> suffix_array(const std::string &text) {
  const uint16_t alphabet = UCHAR_MAX + 1;
  std::vector<size_t> s_array(text.size());
  std::vector<size_t> classes(text.size());
  std::vector<size_t> pockets(alphabet);
  for (char symbol : text) {
    ++pockets[symbol];
  }

  for (size_t i = 1; i < alphabet; ++i)
    pockets[i] += pockets[i - 1];
  for (int64_t i = text.size() - 1; i >= 0; --i)
    s_array[--pockets[text[i]]] = i;
  classes[pockets[0]] = 0;
  size_t number_of_classes = 1;
  for (size_t i = 1; i < text.size(); ++i) {
    if (text[s_array[i]] != text[s_array[i - 1]])
      ++number_of_classes;
    classes[s_array[i]] = number_of_classes - 1;
  }

  for (size_t step = 0; (1 << step) < text.size(); ++step) {
    std::vector<size_t> new_s_array(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
      new_s_array[i] = (s_array[i] + text.size() - (1 << step)) % text.size();
    }
    pockets = std::vector<size_t>(number_of_classes);
    for (auto &s_array_element : new_s_array)
      ++pockets[classes[s_array_element]];
    for (size_t i = 1; i < number_of_classes; ++i)
      pockets[i] += pockets[i - 1];
    for (int64_t i = text.size() - 1; i >= 0; --i)
      s_array[--pockets[classes[new_s_array[i]]]] = new_s_array[i];
    std::vector<size_t> new_classes(text.size());
    new_classes[s_array[0]] = 0;
    number_of_classes = 1;

    for (size_t i = 1; i < text.size(); ++i) {
      if (classes[s_array[i]] != classes[s_array[i - 1]] ||
          classes[(s_array[i] + (1 << step)) % text.size()] !=
              classes[(s_array[i - 1] + (1 << step)) % text.size()]) {
        ++number_of_classes;
      }
      new_classes[s_array[i]] = number_of_classes - 1;
    }
    classes = std::move(new_classes);
  }
  return s_array;
}

std::vector<size_t> kasai(const std::string &text,
                          const std::vector<size_t> &s_array) {
  std::vector<size_t> reverse_s_array(s_array.size());
  for (size_t i = 0; i < s_array.size(); ++i)
    reverse_s_array[s_array[i]] = i;
  std::vector<size_t> lcp(text.size());
  size_t current_lcp = 0;
  for (size_t i = 0; i < text.size(); ++i) {
    for (; text[i + current_lcp] ==
           text[s_array[(reverse_s_array[i] + 1) % text.size()] + current_lcp];
         ++current_lcp) {
    }
    lcp[reverse_s_array[i]] = current_lcp;
    if (current_lcp != 0)
      --current_lcp;
  }
  return lcp;
}

size_t number_of_substrings(const std::string &text) {
  auto s_array = suffix_array(text);
  auto lcp = kasai(text, s_array);
  size_t sum = text.size() - s_array[0];
  for (size_t i = 1; i < text.size(); ++i)
    sum += text.size() - s_array[i] - lcp[i - 1];
  return sum;
}

int main() {
  std::string text;
  std::cin >> text;
  std::cout << number_of_substrings(text) << std::endl;
  return 0;
}
