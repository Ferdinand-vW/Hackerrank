#include <iostream>
#include <vector>
using namespace std;

// Enter your code for reversed_binary_value<bool...>()
template <bool...digits>
int reversed_binary_value() {
    std::vector<int> binary = {digits...};

		int res = 0;
		int power = 1;
    for (int i = 0; i < binary.size(); i++) {
			if (binary[i] == 1) { res += power; }
			power *= 2;
    }

		return res;
}



template <int n, bool...digits>
struct CheckValues {
  	static void check(int x, int y)
  	{
    	CheckValues<n-1, 0, digits...>::check(x, y);
    	CheckValues<n-1, 1, digits...>::check(x, y);
  	}
};

template <bool...digits>
struct CheckValues<0, digits...> {
  	static void check(int x, int y)
  	{
    	int z = reversed_binary_value<digits...>();
    	std::cout << (z+64*y==x);
  	}
};

int main()
{
  	int t; std::cin >> t;

  	for (int i=0; i!=t; ++i) {
		int x, y;
    	cin >> x >> y;
    	CheckValues<6>::check(x, y);
    	cout << "\n";
  	}
}
