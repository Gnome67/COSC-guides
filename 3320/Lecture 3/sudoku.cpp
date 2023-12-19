// To compile on Linux/MacOS/Windows WSL: 
// g++ -std=c++17 sudoku.cpp -o sudoku
// To run: 
// cat s16.txt | ./sudoku
// sudoku data files can be obtained from http://lipas.uwasa.fi/~timan/sudoku/
#include <queue>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

using namespace std; 
class ProfileTimer {
public:
std::chrono::high_resolution_clock::time_point t1, t2;

ProfileTimer() {
    t1 = std::chrono::high_resolution_clock::now();
}

~ProfileTimer() {
    t2 = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "takes " << ms.count() << "ms " << std::endl;
}

};

bool found = false; 
int cnt = 0; 
void find_candidates(int A[9][9], pair<int,int> pos, vector<int> &candidates)
{
	int i = pos.first;
	int j = pos.second; 
	vector<bool> candidates_mask(10, true); 
	for(int k=0; k<9; k++) {
		candidates_mask[A[i][k]] = false;
		candidates_mask[A[k][j]] = false; 
	}
	for (int ii=i/3*3; ii<i/3*3+3; ii++) {
		for (int jj=j/3*3; jj<j/3*3+3; jj++) {
			candidates_mask[A[ii][jj]] = false; 
		}
	}
	candidates.clear(); 
	for (int k=1; k<=9; k++) 
		if (candidates_mask[k]) 
			candidates.push_back(k); 
}

pair<int,int> find_next_open_most_constrained(int A[9][9]) 
{
	vector<int> candidates; 
	int current_min_candidates = 100; 
	int min_i = -1, min_j = -1; 
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (A[i][j] != 0) continue; 
			find_candidates(A, {i,j}, candidates); 
			if (candidates.size() < current_min_candidates) {
				current_min_candidates = candidates.size(); 
				min_i = i; min_j = j; 
			}
		}
	}
	return {min_i, min_j}; // no open squares left; 
}
pair<int,int> find_next_open_random(int A[9][9]) 
{
	vector<pair<int,int>> open_squares; 
	int current_min_candidates = 100; 
	int min_i = -1, min_j = -1; 
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (A[i][j]==0) open_squares.push_back({i,j}); 
		}
	}
	if (open_squares.empty()) return {-1,-1}; 
	else {
		int d = rand() % open_squares.size(); 
		cout << d << "/" << open_squares.size() << endl; 
		return open_squares[d]; 
	}
}
pair<int,int> find_next_open(int A[9][9]) 
{
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (A[i][j] == 0) {
				return {i,j}; 
			}
		}
	}
	return {-1,-1}; // no open squares left; 
}

void sudoku(int A[9][9]) 
{
	vector<int> candidates; 
	auto next = find_next_open(A); 
	if (next.first == -1) {
		found = true; 
		return; 
	}
	find_candidates(A, next, candidates); 
	int i = next.first, j = next.second; 
	for (auto num : candidates) {
		A[i][j] = num; 
		cnt++; 
		sudoku(A); 
		if (found) return; 
		A[i][j] = 0; 
	}
}

int main()
{
	int A[9][9]; 
	for(int i=0; i<9; i++) 
		for (int j=0; j<9; j++) 
			cin >> A[i][j];
	for(int i=0; i<9; i++) {
		for (int j=0; j<9; j++) cout << A[i][j] << " ";
		cout << endl;
	}
	{
		ProfileTimer t; 
		sudoku(A); 
	}
	cout << "called sudoku " << cnt << " times" << endl;
	if (found) {
		for(int i=0; i<9; i++) {
			for (int j=0; j<9; j++) cout << A[i][j] << " ";
			cout << endl;		
		}
	}	
	return 0; 
}
