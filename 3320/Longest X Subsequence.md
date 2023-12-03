# Longest Bitonic Subsequences

Call a sequence X[1..n] of numbers if there is an index i with 1 < i < n, such that the prefix X[1..i] is increasing and the suffix X [i .. n] is decreasing.
Describe an efficient algorithm to compute the length of the longest bitonic subsequence of an arbitrary array X of integers.

Input format:
first line is a single number n
the following line consists of n numbers that is the array A[1..n]

This problem requires two other important Dynamic Programming Algorithms:
- Longest Increasing Subsequence (LISC)
- Longest Decreasing Subsequence (LDS)

We’ll calculate the longest increasing subsequence for A[0...i]. And then calculate the longest decreasing subsequence for A[i....N].

# Longest Increasing Subsequences

Given an integer n, and an array nums, return the length of the longest increasing subsequence.

A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements.

For example: the LIS of [10, 9, 2, 5, 3, 7, 101, 18] is [2, 3, 7, 101]

1. We can create a cache of the length n.
2. Then iterate through each element in nums from i = 1 to i = n-1.?
- For each element at index i, iterate through the elements before it, [0... i-1]
  - Check if nums[i] < nums[j]
  - Check if LIS[j] > LIS[i]
    - If true, this results in a longer subsequence
3. Increment the LIS value at i
- Return the LIS value.

```py
function longest_increasing_subsequence(n, nums):
  LIS = n length array initialized to [0...0]
  LIS[0] = 1
  for i from 1 to n:
    for j in i:
      if nums[j] < nums[i] and LIS[j] > LIS[i]:
        LIS[i] = LIS[j]
      LIS[i] += 1
  return LIS
```

# Longest Decreasing Subsequences

Follow the same algorithm as the longest increasing subsequence, but this time reverse both iterations.
- Outer for loop: from n-1 to 0
- Inner for loop: from n to i + 1

```py
function longest_decreasing_subsequence(n, nums):
  LDS = n length array initialized to [0...0]
  LDS[0] = 1
  for i from n to 0:
    for j from n to i+1:
      if nums[j] < nums[i] and LDS[j] > LDS[i]:
        LDS[i] = LDS[j]
      LDS[i] += 1
  return LDS
```

# Longest Bitonic Subsequences

Recall that the Longest Bitonic Subsequence is the LIS from A[0...i] and the LDS from [i...N]
- So the length of the longest bitonic subsequence is the length of the LIS[i] and LDS[i] subtracted by 1, as A[i] is included in both.

We can thus understand the Longest Bitonic Subsequence as the following definition: `LBS = max(LBS, LIS[i] + LDS[i]-1)`

```py
function longest_bitonic_subsequence(n, nums):
  if n == 0:
    return 0

  LIS = longest_increasing_subsequence(n,nums)
  LDS = longest_decreasing_subsequence(n, nums)

  LBS = 1
  for i in n:
    LBS = max(LBS, LIS[i] + LDS[i] - 1)
  return LBS
```
