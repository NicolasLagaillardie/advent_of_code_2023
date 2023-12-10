#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

string digits[] = {"one", "two",   "three", "four", "five",
                   "six", "seven", "eight", "nine"};

// Assign correct number to temp_result_start and temp_result_end
void match(string *myline, string *temp_result_start, string *temp_result_end,
           int digit, long unsigned int dist) {
  if (myline->substr(dist, digits[digit - 1].length()) == digits[digit - 1]) {
    if (temp_result_start->empty()) {
      *temp_result_start = to_string(digit);
    }

    *temp_result_end = to_string(digit);
  }
}

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

        switch (isdigit(*it)) {
        case true:
          if (temp_result_start.empty()) {
            temp_result_start = *it;
          }

          temp_result_end = *it;
          break;
        case false: {
          long unsigned int dist =
              (long unsigned int)distance(myline.begin(), it);

          if (*it == 'o') {
            match(&myline, &temp_result_start, &temp_result_end, 1, dist);
          } else if (*it == 't') {
            match(&myline, &temp_result_start, &temp_result_end, 2, dist);
            match(&myline, &temp_result_start, &temp_result_end, 3, dist);
          } else if (*it == 'f') {
            match(&myline, &temp_result_start, &temp_result_end, 4, dist);
            match(&myline, &temp_result_start, &temp_result_end, 5, dist);
          } else if (*it == 's') {
            match(&myline, &temp_result_start, &temp_result_end, 6, dist);
            match(&myline, &temp_result_start, &temp_result_end, 7, dist);
          } else if (*it == 'e') {
            match(&myline, &temp_result_start, &temp_result_end, 8, dist);
          } else if (*it == 'n') {
            match(&myline, &temp_result_start, &temp_result_end, 9, dist);
          }
          break;
        }
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
  if (aux("example_part_two") == 281) {
    cout << "Test aux example success" << endl;
  } else {
    cout << "Test aux example failed" << endl;
  }
  // Test input
  if (aux("puzzle") == 54925) {
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
