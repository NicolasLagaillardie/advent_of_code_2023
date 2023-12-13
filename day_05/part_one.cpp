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
long unsigned int aux(string file) {

  // Get file
  ifstream myfile(file);

  string myline;

  vector<string> line_seeds;
  vector<string> string_seeds;
  vector<tuple<long unsigned int, vector<string>>> seeds;
  vector<string> string_intervals;
  vector<long unsigned int> intervals;
  vector<tuple<long unsigned int, long unsigned int>> current_converter;

  string current_name_transfo;

  // Split lines then immediately compute everything
  if (myfile.is_open()) {
    while (myfile) {

      getline(myfile, myline);

      if (!myline.empty()) {

        if (myline.find("seeds: ") != string::npos) {
          line_seeds = split_string(myline, "seeds: ");
          string_seeds = split_string(line_seeds[1]);

          for (const auto &elem : string_seeds) {
            if (elem != "") {
              seeds.push_back(make_tuple(stoul(elem), vector<string>()));
            }
          }
        } else if (myline.find("seed-to-soil map") != string::npos) {
          current_name_transfo = "seed-to-soil";
        } else if (myline.find("soil-to-fertilizer map") != string::npos) {
          current_name_transfo = "soil-to-fertilizer";
        } else if (myline.find("fertilizer-to-water map") != string::npos) {
          current_name_transfo = "fertilizer-to-water";
        } else if (myline.find("water-to-light map") != string::npos) {
          current_name_transfo = "water-to-light";
        } else if (myline.find("light-to-temperature map") != string::npos) {
          current_name_transfo = "light-to-temperature";
        } else if (myline.find("temperature-to-humidity map") != string::npos) {
          current_name_transfo = "temperature-to-humidity";
        } else if (myline.find("humidity-to-location map") != string::npos) {
          current_name_transfo = "humidity-to-location";
        } else {
          string_intervals = split_string(myline);
          intervals.clear();

          for (const auto &elem : string_intervals) {
            if (elem != "") {
              intervals.push_back(stoul(elem));
            }
          }

          for (auto &elem : seeds) {
            if (get<0>(elem) >= intervals[1] &&
                get<0>(elem) < intervals[1] + intervals[2]) {

              if (find(get<1>(elem).begin(), get<1>(elem).end(),
                       current_name_transfo) == get<1>(elem).end()) {
                get<0>(elem) += intervals[0] - intervals[1];
                get<1>(elem).push_back(current_name_transfo);
              }
            }
          }
        }
      }
    }
  }

  // Get final result
  long unsigned int result = get<0>(seeds[0]);

  for (const auto &elem : seeds) {
    result = min(result, get<0>(elem));
  }

  return result;
}

// Test for aux()
void test_aux() {
  // Test basic
  if (aux("example_part_one") == 35) {
    cout << "Test aux example success" << endl;
  } else {
    cout << "Test aux example failed" << endl;
  }

  // Test input
  if (aux("puzzle") == 31599214) {
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
