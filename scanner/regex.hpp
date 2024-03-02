#ifndef MY_REGEX_HPP
#define MY_REGEX_HPP

#include <memory>
#include <optional>
#include <string>
#include <vector>

enum class TokenType {
  /* for future tokenization */
};

enum class StateType {
  start,
  regular,
  accepting,
};

enum class TransitionType {
  symbol,
  epsilon,
};

struct State_ final {
  StateType type_;
  std::optional<TokenType> token_;
  std::optional<TransitionType> tr_type_;
  std::optional<char> tr_sym_;
  std::vector<std::unique_ptr<State_>> next_;
};

class nfa_automaton_ final {
  std::unique_ptr<State_> start_;
  std::unique_ptr<State_> end_;
  /* TODO */
};

class dfa_automaton_ final {
  /* TODO */
};

class Regex final {
  std::string regex_;
  std::string postfix_;
  std::optional<dfa_automaton_> dfa_;

  std::string insert_explicit_concat_operator_() {
    std::string result = "";

    for (size_t index = 0, end = regex_.size(); index < end; ++index) {
      char ch = regex_[index];
      result += ch;

      if (ch == '(' || ch == '|') { continue; }

      if (index < end - 1) {
        char ahead = regex_[index + 1];
        if (ahead == '*' || ahead == '?' || ahead == '+' || ahead == '|'
            || ahead == ')') {
          continue;
        }
        result += '.';
      }
    }

    return result;
  }

  size_t operator_precedence_(char ch) {
    size_t result;
    switch (ch) {
      case '|': result = 0; break;
      case '.': result = 1; break;
      case '?': result = 2; break;
      case '*': result = 2; break;
      case '+': result = 2; break;
    }
    return result;
  }

  void make_postfix_() {
    std::string explicit_concat = insert_explicit_concat_operator_();
    std::string result          = "";
    std::string stack           = "";

    for (char& ch: explicit_concat) {
      if (ch == '.' || ch == '|' || ch == '*' || ch == '?' || ch == '+') {
        while (!stack.empty() && stack.back() != '('
               && operator_precedence_(stack.back())
                      >= operator_precedence_(ch)) {
          result += stack.back();
          stack.pop_back();
        }
        stack.pop_back();

      } else if (ch == '(') {
        stack += ch;
      } else if (ch == ')') {
        while (!stack.empty() && stack.back() != '(') {
          result += stack.back();
          stack.pop_back();
        }
        if (!stack.empty()) { stack.pop_back(); }

      } else {
        result += ch;
      }
    }

    while (!stack.empty()) {
      result += stack.back();
      stack.pop_back();
    }

    postfix_ = std::move(result);
  }

public:
  Regex() = default;

  Regex(const std::string& regex): regex_(regex) {
    make_postfix_();
    // nfa_ = nfa_automaton_(postfix_);
    // dfa_ = dfa_automaton_(nfa_);
  }

  Regex(const char* regex): regex_(regex) {
    make_postfix_();
    // nfa_ = nfa_automaton_(postfix_);
    // dfa_ = dfa_automaton_(nfa_);
  }

  void compile(const std::string& regex) {
    regex_ = regex;
    make_postfix_();
    // nfa_ = nfa_automaton_(postfix_);
    // dfa_ = dfa_automaton_(nfa_);
  }

  void compile(const char* regex) {
    regex_ = regex;
    make_postfix_();
    // nfa_ = nfa_automaton_(postfix_);
    // dfa_ = dfa_automaton_(nfa_);
  }
};

#endif
