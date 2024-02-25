#ifndef MY_REGEX_HPP
#define MY_REGEX_HPP

#include <memory>
#include <optional>
#include <string>
#include <vector>

enum class StateType {
  start,
  regular,
  accepting,
};

enum class TransitionType {
  symbol,
  epsilon,
};

struct State final {
  StateType type;
  std::optional<TransitionType> tr_type;
  std::optional<char> tr_sym;
  std::vector<std::unique_ptr<State>> next;
};

class Regex final {
  std::string regex_;
  std::string postfix_;
  std::unique_ptr<State> start;
  std::unique_ptr<State> end;

  void make_postfix(const std::strign& regex) {
    /* TODO */
  }

  void thompsons_construct(const std::string& postfix) {
    /* TODO */
  }

 public:
  Regex() = default;

  Regex(std::string& regex) : regex_(regex) {
    make_postfix(regex_);
    thompsons_construct(postfix_);
  }

  Regex(char* regex) : regex_(regex) {
    make_postfix(regex_);
    thompsons_construct(postfix_);
  }
};

#endif
