Dynamic programming is an algorithmic technique where the problem is broken down into subproblems whose results are saved in order to help us solve the overall problem.

Memoization:
- Top-Down approach
- Check if the value has already been calculated
- If so, output it, otherwise, calculate and store in a lookup table
- Save the solutions as you approach your base case
- Start from the final problem, recursively compute the subproblems when needed

Tabulation
- Bottom-Up approach
- Initialize a table for lookup
- Determine the execution order of your algorithm (e.g. row by row)
- Fill up the table in the execution order
- Start from 1, cache each of the results and continue to iterate until we reach n
- Build towards the solution as you continually compute each subresult


Example of Naive Solution vs Dynamic Programming

Naive Solution (Time Complexity = O(2^n))
```py
function fibonacci(n)
  if n <= 2
    result = 1
  else
    result = fibonacci(n-1) + fibonacci(n-2)
```

Dynamic Programming (Memoization)
```py
function fibonacci(n)
  if n not in memo:
    memo[n] = fibonacci(n - 1) + fibonacci(n-2)
  return memo[n]
```

Dynamic Programming (Tabulation)
```py
function fibonacci(n)
  lookup_table[0, 1, 0, 0, ..., n, n+1] # length n + 1 table
  for i from 2 to n:
    lookup_table[i] = lookup_table[i - 1] + lookup_table[i - 2]
  return lookup_table[n]
```

Example: __Coin Problem: Minimum Bills__
In a strange country (Algostan), the currency is available in the following denominations: $1, $4, $7, $13, $28, $52, $91, $365. Find the minimum bills that add up to a given sum $k.
```py
function change(k)
  if k < 0:
    return infinity
  if k not in memo:
    lookup[k] = infinity
    for coin in coins:
      lookup[k] = min(change(k - coin), k)+1
  return lookup[k]
```
