#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    std::cin >> n;

    std::set<int> ints;

    for (int i = 0; i < n;i++) {
      int t,q;

      std::cin >> t >> q;

      if     (t==1) { ints.insert(q); }
      else if(t==2) { ints.erase(q);  }
      else if(t==3 && ints.find(q) != ints.end()) {
        std::cout << "Yes" << endl;
      }
      else { std::cout << "No" << endl; }
    }
    
    return 0;
}
