#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>
using namespace std;

// Split string according to del(imiter)
vector<string> split_string(string s, string del = " ") {
  vector<string> result;
  int start, end = -1 * (int)del.size();
  do {
    start = end + (int)del.size();
    end = (int)s.find(del, (long unsigned int)start);
    result.push_back(
        s.substr((long unsigned int)start,
                 (long unsigned int)end - (long unsigned int)start));
  } while (end != -1);

  return result;
}

// runing function
int aux(string file) {

  // Get final result
  int result = 0;

  // Get file
  ifstream myfile(file);

  string myline;

  // Split lines then immediately compute everything
  if (myfile.is_open()) {
    while (myfile) {

      getline(myfile, myline);

      if (!myline.empty()) {

        vector<string> split_line = split_string(myline, ": ");

        vector<string> numbers = split_string(split_line[1], "|");

        vector<string> winning_numbers = split_string(numbers[0]);

        vector<string> choosen_numbers = split_string(numbers[1]);

        int temp_result = -1;

        for (const auto &elem : winning_numbers) {
          if (elem != "") {
            if (find(choosen_numbers.begin(), choosen_numbers.end(), elem) !=
                choosen_numbers.end()) {
              result += (int)pow(2, (max(0, temp_result)));
              temp_result++;
            }
          }
        }
      }
    }
  }

  return result;
}

// Test for aux()
void test_aux() {
  // Test basic
  if (aux("example_part_one") == 13) {
    cout << "Test aux example success" << endl;
  } else {
    cout << "Test aux example failed" << endl;
  }

  // Test input
  if (aux("puzzle") == 26443) {
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

  cout << "Final result for part one: " << aux(file) << endl;

  return 0;
}
