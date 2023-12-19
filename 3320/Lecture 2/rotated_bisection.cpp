
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

int FindK(vector<int> &A, int i, int j)
{
	int m = (i+j)/2;
	if (A[i]>A[m]) {
		return FindK(A, i, m);
	} else if (A[m+1]>A[j]) {
		return FindK(A, m+1, j); 
	} else {
		return m+1; 
	}
}


bool FindX(vector<int> &A, int i, int j, int k, int x)
{
	if (i>j) return false; 
	int n = A.size();
	if (i==j) {
		if (A[(i+k)%n]==x ){
			return true;
		} else {
			return false; 
		}
	}
	int m = (i+j)/2; 
	if (A[(m+k)%n] > x) {
		return FindX(A, i, m, k, x); 
	} else if (A[(m+k)%n] < x) {
		return FindX(A, m+1, j, k, x);
	} else {
		return true; 
	}
}


int main(){
	vector<int> A{9,13,16,18,19,23,28,31,37,42,1,3,4,5,7,8}; 

	int k = FindK(A, 0, A.size()-1); 
	cout << "k=" << k << endl;
	
	for (auto x : A) {
		cout << " found " << x << "? " << FindX(A,0, A.size()-1, k, x) << endl; 
	}

	cout << " found 2? " << FindX(A, 0, A.size()-1, k, 2) << endl; 
	cout << " found 20? " << FindX(A, 0, A.size()-1, k, 20) << endl; 
	cout << " found -1? " << FindX(A, 0, A.size()-1, k, -1) << endl; 
	cout << " found 43? " << FindX(A, 0, A.size()-1, k, 43) << endl; 

}