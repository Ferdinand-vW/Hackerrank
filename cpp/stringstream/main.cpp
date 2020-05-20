#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> parseInts(string str) {
	// Complete this function
  std::vector<int> ints;
  std::stringstream ss(str);
  int n;
  ss >> n;
  ints.push_back(n);
  char ch;
  while (ss >> ch) {
    ss >> n;
    ints.push_back(n);
  }

  return ints;

}

int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    return 0;
}