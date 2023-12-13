#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
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
long int aux(string file) {

  // Get file
  ifstream myfile(file);

  string myline;

  vector<string> string_time_line;
  vector<string> vec_time;
  string string_time;
  long int int_time;

  vector<string> string_distance_line;
  vector<string> vec_distance;
  string string_distance;
  long int int_distance;

  // Split lines then immediately compute everything
  if (myfile.is_open()) {
    while (myfile) {

      getline(myfile, myline);

      if (!myline.empty()) {

        if (myline.find("Time:") != string::npos) {
          string_time_line = split_string(myline, "Time:");
          vec_time = split_string(string_time_line[1]);

          for (const auto &elem : vec_time) {
            if (elem != "") {
              string_time += elem;
            }
          }

          int_time = stol(string_time);
        } else if (myline.find("Distance:") != string::npos) {
          string_distance_line = split_string(myline, "Distance:");
          vec_distance = split_string(string_distance_line[1]);

          for (const auto &elem : vec_distance) {
            if (elem != "") {
              string_distance += elem;
            }
          }

          int_distance = stol(string_distance);
        }
      }
    }
  }
  // Get final result
  long int result = 0;

  for (long int i = 0; i < int_time; i++) {
    result += ((int_time - i) * i >= int_distance);
  }

  return result;
}

// Test for aux()
void test_aux() {
  // Test basic
  if (aux("example_part_one") == 71503) {
    cout << "Test aux example success" << endl;
  } else {
    cout << "Test aux example failed" << endl;
  }

  // Test input
  if (aux("puzzle") == 34123437) {
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
