#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>
using namespace std;

// Split string according to del(imiter)
vector<string> split_string(string s, string del = " ") {
  vector<string> result;
  int start, end = -1 * del.size();
  do {
    start = end + del.size();
    end = s.find(del, start);
    result.push_back(s.substr(start, end - start));
  } while (end != -1);

  return result;
}

// runing function
int aux(string file) {

  // Get file
  ifstream myfile(file);

  string myline;

  vector<int> cards;

  long unsigned int index_card;

  long unsigned int temp_index;

  vector<string> split_line;

  vector<string> numbers;

  vector<string> winning_numbers;

  vector<string> choosen_numbers;

  // Split lines then immediately compute everything
  if (myfile.is_open()) {
    while (myfile) {

      getline(myfile, myline);

      if (!myline.empty()) {

        split_line = split_string(myline, ": ");

        index_card =
            (long unsigned int)stoi(split_string(split_line[0], "Card")[1]);

        // Add the original card to the cards
        if (cards.size() < index_card) {
          cards.push_back(1);
        } else {
          cards[index_card - 1]++;
        }

        numbers = split_string(split_line[1], "|");

        winning_numbers = split_string(numbers[0]);

        choosen_numbers = split_string(numbers[1]);

        temp_index = 1;

        // Add the copies to the cards
        for (const auto &elem : winning_numbers) {
          if (elem != "") {
            if (find(choosen_numbers.begin(), choosen_numbers.end(), elem) !=
                choosen_numbers.end()) {
              if (cards.size() < index_card + temp_index) {
                cards.push_back(cards[index_card - 1]);
              } else {
                cards[index_card + temp_index - 1] += cards[index_card - 1];
              }

              temp_index++;
            }
          }
        }
      }
    }
  }

  // Get final result
  int result = accumulate(cards.begin(), cards.end(), 0);

  cout << "Result: " << result << endl;

  return result;
}

// Test for aux()
void test_aux() {
  // Test basic
  if (aux("example_part_two") == 30) {
    cout << "Test aux example success" << endl;
  } else {
    cout << "Test aux example failed" << endl;
  }

  // Test input
  if (aux("puzzle") == 6284877) {
    cout << "Test aux input success" << endl;
  } else {
    cout << "Test aux input failed" << endl;
  }
}

int main() {
  // cout << "what is the name of your file?" << endl;

  // string file;

  // cin >> file;

  test_aux();

  // cout << "Final result for part two: " << aux(file) << endl;

  return 0;
}
