#include <iostream>
#include <string>
using namespace std;

int main() {
	// Complete the program
  std::string a, b;
  std::cin >> a >> b;

  std::cout << a.length() << " " << b.length() << endl;
  std::cout << a << b << endl;
  const char tmp = a[0];
  a[0] = b[0];
  b[0] = tmp;
  std::cout << a << " " << b << endl;
    return 0;
}