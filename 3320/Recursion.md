# 5 Steps
1. Find the simplest possible input
2. Visualize and use examples
3. Relate hard cases to simpler cases
4. Generalize the pattern
5. Combine recursive pattern with base case

```
Divide and Conquer (int p):
{
  if(small(P))
  {
    solve directly(P);
  }
  else
  {
    divide P into P1, P2, P3... Pk
    Apply Divide and Conquer(P1), Divide and Conquer(P2), ...
    Combine Divide and Conquer(P1), Divide and Conquer(P2), ...
  }
}
```

# Divide and Conquer

Split the problem into two subproblems
Split the two subproblems into two subproblems
etc. until you reach n (where n is the smallest subproblem possible)
Then solve 2 n, merge together, and work your way back up

Basically explains why merge sort is O(n*log(n))
n* is because there are n leaves for an array of size n
e.g. if n is 8 [1,4,5,6,7,8,2,3] then it will make 8 subarrays [1][4][5][6][7][8][2][3]
log(n) refers to how many levels there will be
e.g. if n is 8 [1,4,5,6,7,8,2,3] there will be 3 sublevels:
1st sublevel: [1,4,5,6][7,8,2,3]
2nd sublevel: [1,4][5,6][7,8][2,3]
3rd sublevel: [1][4][5][6][7][8][2][3]

notice how the size of each subarray is the previous array / 2. and notice how theres 3 levels
2^3 = 8 and log2(8) = 3

Proof of Correctness for Merge Sort (prove Merge Sort works)
(using loop invariant method)

```
Merge(Arr, low, mid, high)
1. L = Arr[low:mid] // L is a new array copied from Arr[low:mid]
2. R = Arr[mid+1, high] // R
3. i = 1, j = 1
4. for k = low to high:
5.   if L[i] < R[j]
6.     A[k] = L[i]
7.     i = i + 1
8.   else
9.     A[k] = R[j]
10.   j = j + 1
```
