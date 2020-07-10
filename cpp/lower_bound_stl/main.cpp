#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    std::cin >> n;

    std::vector<int> numbers;

    while (n > 0) {
      int i;
      std::cin >> i;
      numbers.push_back(i);
      n--;
    }

    int q;
    std::cin >> q;
    while (q > 0) {
      int i;
      std::cin >> i;

      auto it = std::lower_bound(numbers.begin(),numbers.end(),i);
      
      if (*it == i) {
        std::cout << "Yes " << (it - numbers.begin() + 1) << endl;
      } else {
        std::cout << "No " << (it - numbers.begin() + 1) << endl;
      }
    q--;
    }
    
    return 0;
}
