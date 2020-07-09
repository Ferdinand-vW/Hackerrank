#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    std::vector<int> v;
    int q;
    int k = 0;
    std::cin >> q;
    while (q > 0) {
      int i;
      std::cin >> i;
      v.push_back(i);
      q--;
      k++;
    }
    sort(v.begin(),v.end(),greater<int>());
  while(k > 0) {
    std::cout << v[k-1] << " ";
    k--;
  }

    return 0;
}
