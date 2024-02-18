#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

template <typename T, size_t N>
size_t array_size(const T (&)[N]) { return N; }

int error[128]{};
int endline[128]{};
int templ[128]{};

void fill_table(std::vector<std::vector<int>>& table, const std::string& str) {
  table.push_back({error, error + 128});
  for (auto&& ch: str) {
    std::vector<int> to_push(templ, templ + 128);
    to_push[ch] = table.size() + 1;
    table.push_back(std::move(to_push));
  }
  endline[127] = table.size() + 1;
  table.push_back({endline, endline + 128});
}

bool is_match(std::vector<std::vector<int>>& table, const std::string& str) {
  int state = 1;
  for (auto&& ch: str) {
    state = table[state][ch];

    if (state == 0 || state >= table.size()) {
      break;
    }
  }

  if (state == 0) { return false; }
  else if (state == table.size() - 1) { return true; }
  else { return false; }
}

int main(int argc, char* argv[]) {
  --argc; ++argv;
  if (argc < 1) { return 1; }
  std::vector<std::string> args(argv, argv + argc);
  std::vector<int> test(templ, templ + 128);
  std::cout << std::boolalpha;

  std::vector<std::vector<int>> table;
  // table.reserve(128);

  fill_table(table, args[0]);

  for (size_t ind = 0; ind < 128; ++ind) {
    std::cout << ind << "\t=> ";
    for (size_t in_ind = 0, end = table.size(); in_ind < end; ++in_ind) {
      std::cout << table[in_ind][ind] << ' ';
    }
    std::cout << '\n';
  }

  for (auto&& str: args) {
    std::cout << str << "\t=> " << is_match(table, str) << '\n';
  }

  return 0;
}
