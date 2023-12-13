#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
using namespace std;

// Iterate over the line and retrieve
int aux_index(string myline) {

  int max_red = 0;
  int max_green = 0;
  int max_blue = 0;

  // Iterate over the line
  long unsigned int index = 0;

  string buffer = "";

  string current_colour;

  // Traverse the string
  while (index < myline.length()) {
    if (myline[index] == 'G') {
      index += 4;
    } else if (myline[index] == 'r') {
      max_red = max(stoi(buffer), max_red);
      index += 3;
      buffer = "";
    } else if (myline[index] == 'g') {
      max_green = max(stoi(buffer), max_green);
      index += 5;
      buffer = "";
    } else if (myline[index] == 'b') {
      max_blue = max(stoi(buffer), max_blue);
      index += 4;
      buffer = "";
    } else if (isdigit(myline[index])) {
      buffer.append(to_string(myline[index] - '0'));
    } else if (myline[index] == ':') {
      buffer = "";
    }

    index++;
  }

  return max_red * max_green * max_blue;
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
  if (aux("example_part_two") == 2286) {
    cout << "Test aux example success" << endl;
  } else {
    cout << "Test aux example failed" << endl;
  }

  // Test input
  if (aux("puzzle") == 67363) {
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
