#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
using namespace std;

// Iterate over the line and retrieve
int aux_index(string myline) {

  int result = 0;

  // Iterate over the line
  long unsigned int index = 0;

  string buffer = "";

  string current_colour;

  // Traverse the string
  while (index < myline.length()) {
    if (myline[index] == 'G') {
      index += 4;
    } else if (myline[index] == 'r') {
      if (stoi(buffer) > 12) {
        return 0;
      }
      index += 3;
      buffer = "";
    } else if (myline[index] == 'g') {
      if (stoi(buffer) > 13) {
        return 0;
      }
      index += 5;
      buffer = "";
    } else if (myline[index] == 'b') {
      if (stoi(buffer) > 14) {
        return 0;
      }
      index += 4;
      buffer = "";
    } else if (isdigit(myline[index])) {
      buffer.append(to_string(myline[index] - '0'));
    } else if (myline[index] == ':') {
      result = stoi(buffer);
      buffer = "";
    }

    index++;
  }

  return result;
}

// runing function
int aux(string file) {
  // Get file
  ifstream myfile(file);

  // Get final result
  int result = 0;

  // 12 red cubes
  // 13 green cubes
  // 14 blue cubes

  string myline;
  if (myfile.is_open()) {
    while (myfile) {
      getline(myfile, myline);

      result += aux_index(myline);
    }
  }

  return result;
}

// Test for aux()
void test_aux() {
  // Test basic
  if (aux("example_part_one") == 8) {
    cout << "Test aux example success" << endl;
  } else {
    cout << "Test aux example failed" << endl;
  }

  // Test input
  if (aux("puzzle") == 2528) {
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
