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

  void make_postfix_() {
    /* TODO */
  }

public:
  Regex() = default;
  
  Regex(const std::string& regex): regex_(regex) {
    make_postfix_();
    nfa_ = nfa_automaton_(postfix_);
    // dfa_ = dfa_automaton_(nfa_);
  }

  Regex(const char* regex): regex_(regex) {
    make_postfix_();
    nfa_ = nfa_automaton_(postfix_);
    // dfa_ = dfa_automaton_(nfa_);
  }
  
  void compile(const std::string& regex) {
    regex_ = regex;
    make_postfix_();
    nfa_ = nfa_automaton_(postfix_);
    // dfa_ = dfa_automaton_(nfa_);
  }

  void compile(const char* regex) {
    regex_ = regex;
    make_postfix_();
    nfa_ = nfa_automaton_(postfix_);
    // dfa_ = dfa_automaton_(nfa_);
  }
};

#endif
