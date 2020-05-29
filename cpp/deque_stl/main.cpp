#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

void printKMax(int arr[], int n, int k){
	//Write your code here.
  std::deque<int> subarray(arr,arr+k);
  int max = *std::max_element(subarray.begin(),subarray.end());
  int maxPos = 0;
  for (int i = 0; i <= n-k; i++) {
    std::cout << max << " ";

    int head = subarray[0];
    subarray.pop_front();
    subarray.push_back(arr[i+k]);
    
    if (head == max) {
      max = 0;
      for(int j = std::max(maxPos,i+1);j <= i + k;j++) {
        if (arr[j] >= max) {
          max = arr[j];
          maxPos = j;
        }
      }
    }

    if (arr[i+k] >= max) { 
      max = arr[i+k]; 
      maxPos = i + k; 
    }
  }

  std::cout << endl;
}

int main(){
  
	int t;
	cin >> t;
	while(t>0) {
		int n,k;
    	cin >> n >> k;
    	int i;
    	int arr[n];
    	for(i=0;i<n;i++)
      		cin >> arr[i];
    	printKMax(arr, n, k);
    	t--;
  	}
  	return 0;
}