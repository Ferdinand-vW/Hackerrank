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

    std::vector<int> myVec;

    while(n > 0) {
      int i;
      std::cin >> i;
      myVec.push_back(i);
      n--;
    }

    int q1,q2a,q2b;
    std::cin >> q1;
    myVec.erase(myVec.begin()+q1 - 1);

    std::cin >> q2a >> q2b;
    myVec.erase(myVec.begin()+q2a-1,myVec.begin()+ q2b-1);
    
    
    int vecSize = myVec.size();
    int k = 0;

    std::cout << myVec.size() << endl;
    while (k < myVec.size()) {
      std::cout << myVec[k] << " ";
      k++;
    }

    return 0;
}
