We'll first find the medians and denote as Ma and Mb. We'll compare the median values before eliminating the values in [Ma, Mb].
1. If Ma > Mb then we can ignore the right half of array A, and ignore the left half of array B. We'll then be left with A:[0, Ma] and B:[Mb, n]
2. If Ma < Mb then we can ignore the left half of array A, and ignore the right half of array B. We'll then be left with A:[Ma, n] and B:[0, Mb]

Base case: Ma = Mb
Recursive case:
- If both arrays are two elements, return: max(A[0], B[0]) + min(A[1], B[1]) / 2
- Follow a similar pattern as binary search

---

Ex. Print all subsets
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
