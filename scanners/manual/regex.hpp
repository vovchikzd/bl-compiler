#ifndef MY_REGEX_HPP
#define MY_REGEX_HPP

#include <vector>
#include <optional>
#include <string>

class Regex {
  std::string regex_;
  std::string postfix_;
  State start;
  State end;

  make_postfix(const std::strign& regex) {}

public:
  Regex() = default;

  Regex(std::string& regex): regex_(regex) {
  }

  Regex(char* regex): regex_(regex) {}
};

#endif
