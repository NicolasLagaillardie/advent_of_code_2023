#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>
using namespace std;

// Check if at least one surrounding cell is the position of a symbol
bool check_if_symbol_as_neigh(vector<tuple<int, int>> positions_to_check,
                              vector<tuple<int, int>> positions_of_symbols) {

  for (const auto &position : positions_to_check) {
    if (find(positions_of_symbols.begin(), positions_of_symbols.end(),
             position) != positions_of_symbols.end()) {
      return true;
    }
  }

  return false;
}

// runing function
int aux(string file) {
  // Get file
  ifstream myfile(file);

  vector<tuple<int, vector<tuple<int, int>>>> positions_to_check;
  vector<tuple<int, int>> positions_of_symbols;

  string myline;

  long unsigned int index_row = 0;
  long unsigned int index_column;

  string buffer = "";
  vector<tuple<int, int>> temp_positions;

  // Create matrix
  if (myfile.is_open()) {
    while (myfile) {
      getline(myfile, myline);

      buffer = "";
      temp_positions.clear();
      index_column = 0;

      while (index_column < myline.length()) {
        if (isdigit(myline[index_column])) {
          buffer.append(to_string(myline[index_column] - '0'));
          temp_positions.insert(temp_positions.end(),
                                {make_tuple(index_row - 1, index_column),
                                 make_tuple(index_row, index_column - 1),
                                 make_tuple(index_row - 1, index_column - 1),
                                 make_tuple(index_row - 1, index_column + 1),
                                 make_tuple(index_row + 1, index_column - 1),
                                 make_tuple(index_row + 1, index_column + 1),
                                 make_tuple(index_row + 1, index_column),
                                 make_tuple(index_row, index_column + 1)});
        } else {
          if (!buffer.empty()) {
            positions_to_check.push_back(
                make_tuple(stoi(buffer), temp_positions));
            temp_positions.clear();
            buffer = "";
          }

          if (myline[index_column] != '.') {
            positions_of_symbols.insert(positions_of_symbols.end(),
                                        {make_tuple(index_row, index_column)});
          }
        }

        index_column++;
      }

      if (!buffer.empty()) {
        positions_to_check.push_back(make_tuple(stoi(buffer), temp_positions));
      }

      index_row++;
    }
  }

  // Get final result
  int result = 0;

  for (const auto &elem : positions_to_check) {
    if (check_if_symbol_as_neigh(get<1>(elem), positions_of_symbols)) {
      result += get<0>(elem);
    }
  }

  return result;
}

// Test for aux()
void test_aux() {
  // Test basic
  if (aux("example_part_one") == 4361) {
    cout << "Test aux example success" << endl;
  } else {
    cout << "Test aux example failed" << endl;
  }

  // Test input
  if (aux("puzzle") == 539433) {
    cout << "Test aux input success" << endl;
  } else {
    cout << "Test aux input failed" << endl;
  }
}

int main() {
  cout << "what is the name of your file?" << endl;

  string file;

  cin >> file;

  test_aux();

  cout << "Final result for part two: " << aux(file) << endl;

  return 0;
}
