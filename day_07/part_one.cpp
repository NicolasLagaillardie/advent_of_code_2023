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

vector<string> cards = {"A", "K", "Q", "J", "T", "9", "8",
                        "7", "6", "5", "4", "3", "2"};

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
  vector<string> string_time;
  vector<long int> int_time;

  vector<string> string_distance_line;
  vector<string> string_distance;
  vector<long int> int_distance;

  // Split lines then immediately compute everything
  if (myfile.is_open()) {
    while (myfile) {

      getline(myfile, myline);

      if (!myline.empty()) {

        if (myline.find("Time:") != string::npos) {
          string_time_line = split_string(myline, "Time:");
          string_time = split_string(string_time_line[1]);

          for (const auto &elem : string_time) {
            if (elem != "") {
              int_time.push_back(stol(elem));
            }
          }
        } else if (myline.find("Distance:") != string::npos) {
          string_distance_line = split_string(myline, "Distance:");
          string_distance = split_string(string_distance_line[1]);

          for (const auto &elem : string_distance) {
            if (elem != "") {
              int_distance.push_back(stol(elem));
            }
          }
        }
      }
    }
  }

  vector<long int> beaten_records;

  for (long unsigned int i = 0; i < int_time.size(); i++) {
    beaten_records.push_back(0);
    for (long unsigned int j = 0; j <= int_time[i]; j++) {
      beaten_records[i] += ((int_time[i] - j) * j > int_distance[i]);
    }
  }

  // Get final result
  int result = 1;

  for (const auto &elem : beaten_records) {
    result *= elem;
  }

  return result;
}

// Test for aux()
void test_aux() {
  // Test basic
  if (aux("example_part_one") == 6440) {
    cout << "Test aux example success" << endl;
  } else {
    cout << "Test aux example failed" << endl;
  }

  // // Test input
  // if (aux("puzzle") == 131376) {
  //   cout << "Test aux input success" << endl;
  // } else {
  //   cout << "Test aux input failed" << endl;
  // }
}

int main() {
  // cout << "what is the name of your file?" << endl;

  // string file;

  // cin >> file;

  test_aux();

  // cout << "Final result for part one: " << aux(file) << endl;

  return 0;
}
