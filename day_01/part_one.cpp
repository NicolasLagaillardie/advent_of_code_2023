#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

// runing function
int aux(string file) {
  // Get file
  ifstream myfile(file);

  // Get final result
  int result = 0;

  string myline;
  if (myfile.is_open()) {
    while (myfile) {
      string temp_result_start;
      string temp_result_end;

      getline(myfile, myline);

      // Stores address of a character of str
      string::iterator it;

      // Traverse the string
      for (it = myline.begin(); it != myline.end(); it++) {
        // If string is digit,
        // assig  it to temp_resultS
        if (isdigit(*it)) {
          if (temp_result_start.empty()) {
            temp_result_start = *it;
          }

          temp_result_end = *it;
        }
      }

      // Concat temp_resultS and translate to string
      if (!temp_result_start.empty()) {
        temp_result_start.append(temp_result_end);

        result += stoi(temp_result_start);
      }
    }
  }

  return result;
}

// Test for aux()
void test_aux() {
  // Test basic
  if (aux("example_part_one") == 142) {
    cout << "Test aux example success" << endl;
  } else {
    cout << "Test aux example failed" << endl;
  }
  
  // Test input
  if (aux("puzzle") == 55172) {
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
