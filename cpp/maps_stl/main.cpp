#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    std::cin >> n;

    std::map<string,int> studentMarks;

    for (int i = 0; i < n;i++) {
      int t,m;
      string student;

      std::cin >> t >> student;

      if (t==1) {
        std::cin >> m;
        auto studentM = studentMarks.find(student);

        if(studentM != studentMarks.end()) {
          studentM->second = studentM->second + m;
        } else { 
          studentMarks.insert({ student, m }); 
        }
         
      }
      else if(t==2) { studentMarks.erase(student);  }

      else if(t==3) {
        auto studentM = studentMarks.find(student);
        
        if(studentM != studentMarks.end()) {
          std::cout << studentM->second << endl;
        } else {
          std::cout << 0 << endl;
        }
      }
    }
    
    return 0;
}
