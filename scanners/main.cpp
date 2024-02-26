/*
std::vector<std::string> regexes({"[ \t\n\v]", "if|else|while|fn|for|return"
                                  "[1-9][0-9]*", "[\+\-\*\/\=\>\<]",
                                  "[a-zA-Z_][a-zA-Z_0-9]*", "[({]", "[)}]"
                                  ":", ";"});
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <optional>

enum class StateType {
  start,
  regular,
  accepting,
};

enum class TransitionType {
  symbol,
  epsilon,
};

struct State {
  StateType type;
  std::optional<TransitionType> tr_type;
  std::optional<char> tr_sym;
  std::vector<State> transition;
};

struct NFA {
  State start;
  State end;
};

void epsilon_transition(State& from, State& to) {
  from.tr_type = TransitionType::epsilon;
  from.transition.push_back(to);
}

void symbol_transition(State& from, State& to, char symbol) {
  from.tr_type = TransitionType::symbol;
  from.tr_sym = symbol;
  from.transition.push_back(to);
}

NFA nfa_from_epsilon() {
  State start{.type = StateType::start};
  State end{.type = StateType::accepting};
  epsilon_transition(start, end);
  return {.start = start, .end = end};
}

NFA nfa_from_symbol(char symbol) {
  State start{.type = StateType::start};
  State end{.type = StateType::accepting};
  symbol_transition(start, end, symbol);
  return {.start = start, .end = end};
}

NFA nfa_concat(NFA& first, NFA& second) {
  first.end.type = StateType::regular;
  second.start.type = StateType::regular;
  epsilon_transition(first.end, second.start);
  return {.start = first.start, .end = second.end};
}

NFA nfa_union(NFA& first, NFA& second) {
  first.start.type = StateType::regular;
  first.end.type = StateType::regular;
  second.start.type = StateType::regular;
  second.start.type = StateType::regular;
  State start{.type = StateType::start};
  State end{.type = StateType::accepting};
  epsilon_transition(start, first.start);
  epsilon_transition(start, second.start);
  epsilon_transition(first.end, end);
  epsilon_transition(second.end, end);
  return {.start = start, .end = end};
}

NFA nfa_closure(NFA& nfa) {
  nfa.start.type = StateType::regular;
  nfa.end.type = StateType::regular;
  State start{.type = StateType::start};
  State end{.type = StateType::accepting};

  epsilon_transition(start, end);
  epsilon_transition(start, nfa.start);
  epsilon_transition(nfa.end, end);
  epsilon_transition(nfa.end, nfa.start);
  return {.start = start, .end = end};
}

int op_precedence(char ch) {
  int result;
  switch (ch) {
    case '|': result = 0;
    case '.': result = 1;
    case '?': result = 2;
    case '*': result = 2;
    case '+': result = 2;
  }
  return result;
}

std::string insert_concat_operator(const std::string& reg) {
  std::string output;
  for (size_t i = 0; i < reg.size(); ++i) {
    char ch = reg[i];
    output += ch;
    if (ch == '(' || ch == '|') { continue; }

    if (i < reg.size() - 1) {
      char ahead = reg[i + 1];
      if (ahead == '*' || ahead == '?' || ahead == '+' || ahead == '|' ||
          ahead == ')') { continue; }
      output += '.';
    }
  }
  return output;
}

std::string to_postfix(const std::string& reg) {
  std::string exp = insert_concat_operator(reg);
  std::string output = "";
  std::vector<char> op_stack;
  for (auto&& ch: exp) {
    if (ch == '.' || ch == '|' || ch == '*' || ch == '?' || ch == '+') {
      while (op_stack.size() && op_stack.back() != '(' && 
             op_precedence(op_stack.back()) >= op_precedence(ch)) {
        output += op_stack.back();
        op_stack.pop_back();
      }
      op_stack.push_back(ch);
    } else if (ch == '(' || ch == ')') {
      if (ch == '(') {
        op_stack.push_back(ch);
      } else {
        while (op_stack.size() && op_stack.back() != '(') {
          output += op_stack.back();
          op_stack.pop_back();
        }
        if (op_stack.size()) { op_stack.pop_back(); }
      }
    } else {
      output += ch;
    }
  }

  while (op_stack.size()) {
    output += op_stack.back();
    op_stack.pop_back();
  }
  return output;
}

NFA to_nfa(const std::string& postfix) {
  // if (postfix == "") {
  //   return nfa_from_epsilon();
  // }

  std::vector<NFA> stack;
  for (auto&& ch: postfix) {
    switch (ch) {
      case '*': {
        NFA back = stack.back();
        stack.pop_back();
        stack.push_back(nfa_closure(back));
        break;
      }
      case '|': {
        NFA right = stack.back(); stack.pop_back();
        NFA left = stack.back(); stack.pop_back();
        stack.push_back(nfa_union(left, right));
        break;
      }
      case '.': {
        NFA right = stack.back(); stack.pop_back();
        NFA left = stack.back(); stack.pop_back();
        stack.push_back(nfa_concat(left, right));
        break;
      }
      default: {
        stack.push_back(nfa_from_symbol(ch));
        break;
      }
    }
  }

  return stack.back();
}

int main(/*int argc, char* argv[]*/) {
  // if (argc == 1) { return 1; }
  // std::vector<std::string> args(argv, argv + argc);
  std::string reg = "(a|b)*c";
  return 0;
}
