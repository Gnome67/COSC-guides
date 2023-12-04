Note: a subsequence is a substring of a sequence that is not necessarily contiguous

Example: [1,2,3,4,5,6]

[1,2,3] and [4,5,6] are subsequences, but [1,3,5] and [2,4,6] can also be subsequences.

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

# Longest Bitonic Subsequences Continued

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

# Longest Common Subsequences

Find the length of the longest common subsequence of two strings

Example:
- s1: "ABCDGH"
- s2: "AEDFHR"

Solution:
- s1: "__A__BC__D__G__H__"
- s2: "__A__E__D__F__H__R"

The longest common subsequence is "ADH" since both strings have an A, a D, and a H in the same order, so we return 3

Example:
- s1: "AGGTAB"
- s2: "GXTXAYB"

Solution:
- s1: "AG__GTAB__"
- s2: "__G__X__T__X__A__Y__B__"

The longest common subsequence is "GTAB" since both strings have a G, a T, an A, and a B in the same order, so we return 4
