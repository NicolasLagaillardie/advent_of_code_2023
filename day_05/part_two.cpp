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
  vector<string> saved_transfo;
  vector<tuple<long unsigned int, long unsigned int>> interval_seeds;
  vector<vector<string>> validated_transfo_seeds;
  vector<string> string_intervals;
  vector<long unsigned int> intervals;
  vector<tuple<long unsigned int, long unsigned int>> current_converter;
  vector<long unsigned int> temp_seed;

  string current_name_transfo;

  long unsigned int saved_lower_bound, saved_upper_bound;

  long unsigned int i;

  long unsigned int index = 0;

  long unsigned int max_size = interval_seeds.size();

  // Split lines then immediately compute everything
  if (myfile.is_open()) {
    while (myfile) {

      getline(myfile, myline);

      index++;

      if (!myline.empty()) {

        if (myline.find("seeds: ") != string::npos) {
          line_seeds = split_string(myline, "seeds: ");
          string_seeds = split_string(line_seeds[1]);

          temp_seed.clear();

          for (const auto &elem : string_seeds) {
            if (elem != "") {
              temp_seed.push_back(stoul(elem));
            }
          }

          i = 0;

          while (i < temp_seed.size()) {
            interval_seeds.push_back(
                make_tuple(temp_seed[i], temp_seed[i] + temp_seed[i + 1] - 1));
            validated_transfo_seeds.push_back(vector<string>());

            i += 2;
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

          max_size = interval_seeds.size();

          // We check the bounds, not all the values within the bounds
          for (long unsigned int j = 0; j < max_size; j++) {

            saved_lower_bound = get<0>(interval_seeds[j]);
            saved_upper_bound = get<1>(interval_seeds[j]);

            // If upper bound of the seed is above the lower bound of the
            // transfo and if lower bound of the seed is below the upper bound
            // of the transfo
            if (saved_lower_bound < intervals[1] + intervals[2] &&
                saved_upper_bound >= intervals[1]) {

              // If the seed interval is within the transfo interval,
              // update the bounds of the seed interval
              if (saved_lower_bound >= intervals[1] &&
                  saved_upper_bound < intervals[1] + intervals[2]) {

                if (find(validated_transfo_seeds[j].begin(),
                         validated_transfo_seeds[j].end(),
                         current_name_transfo) ==
                    validated_transfo_seeds[j].end()) {
                  get<0>(interval_seeds[j]) += intervals[0] - intervals[1];
                  get<1>(interval_seeds[j]) += intervals[0] - intervals[1];
                  validated_transfo_seeds[j].push_back(current_name_transfo);
                }

                // If the seed interval is partially on the right of the transfo
                // interval, split the seed interval in two and update only the
                // one within the transfo interval.
              } else if (saved_lower_bound >= intervals[1] &&
                         saved_upper_bound >= intervals[1] + intervals[2]) {

                if (find(validated_transfo_seeds[j].begin(),
                         validated_transfo_seeds[j].end(),
                         current_name_transfo) ==
                    validated_transfo_seeds[j].end()) {
                  saved_transfo = validated_transfo_seeds[j];

                  get<0>(interval_seeds[j]) += intervals[0] - intervals[1];
                  get<1>(interval_seeds[j]) = intervals[0] + intervals[2] - 1;
                  validated_transfo_seeds[j].push_back(current_name_transfo);

                  interval_seeds.push_back(make_tuple(
                      intervals[1] + intervals[2], saved_upper_bound));
                  validated_transfo_seeds.push_back(saved_transfo);
                }

                // If the seed interval is partially on the left of the transfo
                // interval, split the seed interval in two and update only the
                // one within the transfo interval.
              } else if (saved_lower_bound < intervals[1] &&
                         saved_upper_bound < intervals[1] + intervals[2]) {

                if (find(validated_transfo_seeds[j].begin(),
                         validated_transfo_seeds[j].end(),
                         current_name_transfo) ==
                    validated_transfo_seeds[j].end()) {
                  saved_transfo = validated_transfo_seeds[j];
                  validated_transfo_seeds[j].push_back(current_name_transfo);

                  get<0>(interval_seeds[j]) = intervals[0];
                  get<1>(interval_seeds[j]) += intervals[0] - intervals[1];

                  interval_seeds.push_back(
                      make_tuple(saved_lower_bound, intervals[1] - 1));
                  validated_transfo_seeds.push_back(saved_transfo);
                }

                // If the seed interval is partially on the left of the transfo
                // interval, split the seed interval in three and update only
                // the one within the transfo interval.
              } else if (saved_lower_bound < intervals[1] &&
                         saved_upper_bound >= intervals[1] + intervals[2]) {

                if (find(validated_transfo_seeds[j].begin(),
                         validated_transfo_seeds[j].end(),
                         current_name_transfo) ==
                    validated_transfo_seeds[j].end()) {
                  saved_transfo = validated_transfo_seeds[j];
                  validated_transfo_seeds[j].push_back(current_name_transfo);

                  get<0>(interval_seeds[j]) = intervals[0];
                  get<1>(interval_seeds[j]) = intervals[0] + intervals[2] - 1;

                  interval_seeds.push_back(
                      make_tuple(saved_lower_bound, intervals[1] - 1));
                  interval_seeds.push_back(make_tuple(
                      intervals[1] + intervals[2], saved_upper_bound));
                  validated_transfo_seeds.push_back(saved_transfo);
                  validated_transfo_seeds.push_back(saved_transfo);
                }
              }
            }
          }
        }
      }
    }
  }

  // Get final result
  long unsigned int result = get<0>(interval_seeds[0]);

  for (const auto &elem : interval_seeds) {
    result = min(min(result, get<0>(elem)), get<1>(elem));
  }

  return result;
}

// Test for aux()
void test_aux() {
  // Test basic
  if (aux("example_part_two") == 46) {
    cout << "Test aux example success" << endl;
  } else {
    cout << "Test aux example failed" << endl;
  }

  // // Test input
  // if (aux("puzzle") == 22956580) {
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

  cout << "Final result for part two: " << aux("puzzle") << endl;

  return 0;
}
