#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
	int T; cin >> T;
	cout << setiosflags(ios::uppercase);
	cout << setw(0xf) << internal;
	while(T--) {
		double A; cin >> A;
		double B; cin >> B;
		double C; cin >> C;

		/* Enter your code here */
    printf("%#lx\n",(unsigned long)A);
    
    char c[15];
    int n = sprintf(c,"%+.2f",B);
    std::string s = std::string(15-n,'_') + c;
    std::cout << s << std::endl;

    printf("%.9E\n",C);

	}
	return 0;

}