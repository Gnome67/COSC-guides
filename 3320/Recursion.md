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

# Binary Search

We'll first find the medians and denote as Ma and Mb. We'll compare the median values before eliminating the values in [Ma, Mb].
1. If Ma > Mb then we can ignore the right half of array A, and ignore the left half of array B. We'll then be left with A:[0, Ma] and B:[Mb, n]
2. If Ma < Mb then we can ignore the left half of array A, and ignore the right half of array B. We'll then be left with A:[Ma, n] and B:[0, Mb]

Base case: Ma = Mb
Recursive case:
- If both arrays are two elements, return: max(A[0], B[0]) + min(A[1], B[1]) / 2
- Follow a similar pattern as binary search

# Python

Provided by Michael Sambol

```py
def binary_search(array, target):
    left = 0
    right = len(array) - 1

    while (left <= right):
        mid = (right + left) // 2

        if array[mid] == target:
            return mid
        elif array[mid] < target: 
            left = mid + 1
        else:
            right = mid - 1

    return -1
```

# Print all subsets
Give an algorithm to print out all possible subsets of an n-element set, such as {1,2,3...n}

Solution: We recursively make the decision of including or excluding each element in our subset.
- If we include the current index of the given array we push it into our subset then return a recursive call on the next index.
- If we exclude an index of the array, we just pop the current number, reversing the operation we had just finished prior. Then we make our recursive call on the next index.
Until we stop at the base case where the current index is greater than the length of the array.

Base case: index > array length
Recursive case:
- push subset
- increment index in your function call
- undo your push (backtrack)
- call your function again
