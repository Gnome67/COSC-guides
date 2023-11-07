A recurrence relation is an equation we use to model an algorithm's runtime. Recurrences describes function in terms of value on smaller inputs.
`Ex. Merge Sort often has a time complexity of T(n) = 2*T(n/2) + n`
2* = two recursive calls
T(n/2) = recursive division
+ n = conquer (combine)

A recurrence tree draws successive expansions of recurrences in the diagram, modelling the costs (time) of recursive execution.
Ex. T(n) = T(n/2) + 1, T(1)
```
         T(n)
        /    \
    T(n/2)    1
    /    \
T(n/4)    1
```
Observe the level by level summation of the tree:
1. The first level equals n
2. The second level equals n/2 + 1
3. The third level equals n/4 + 1
Solving af(n/b) = cf(n) yields that c = 1

Ex. T(n) = 2T(n/2) + n, T(1) = 1
```

                                    T(n)
                                  /      \
                             T(n/2)        T(n/2)
                           /        \     /       \
                       T(n/4)    T(n/4)  T(n/4)   T(n/4)
                      /     \    /     \ /     \  /     \
                  T(n/8)    ..  ..     ...      ...     ..
```
1. The first level equals p
2. The second level equals 2(n/2) = p
3. The third level equals 4(n/4) = n

Ex. T(n) = 3(n/2) + n, T(1) = 1
```
                 T(n)
            /      |       \
        T(n/2)     T(n/2) T(n/2)
       /  |   \     / | \ / | \
T(n/4) T(n/4) T(n/4) ... ... ... ...
```
1. The first level equals n
2. The second level equals 3(n/2)
3. The third level equals 9(n/4)
Solving af(n/b) = cf(n) yields that c > 1

# Recurrence Relations (Plug & Chug)

Given T(1) = 4, (base case) T(n) = 2T(n/2) + 4n (recurrence equation); find complexity
Work:
```
1. Substitute all n with n/2 => T(n/2) = 2T(n/4) + 4(n/2)
2. Plug in the substituted values into the original equation => T(n) = 2[2T(n/4) + 4(n/2)] + 4n
3. Simplify: 2^2 * T(n/4) + 4n + 4n
4. Substitute all n/2 with n/4 => T(n/4) = 2T(n/8) + 4(n/4)
5. Plug in the substituted values: 2^2[2T(n/8) + 4 (n/4)] + 4n + 4n
6. Simplify: 2^3 * T(n/8) + 4n + 4n + 4n
...
7. Final version should be 2^i * T(n/(2^i)) + i(4n)
8. Our base case is T(1) = 4, so we need to set the n in T(n/(2^i)) = 1
9. Solve for n/(2^i) = 1 => n = 2^i => log2(n) = i
10. plug in log2(n) for all i in 2^i * T(n/(2^i)) + i(4n) => 2^(log2(n)) * T(1) + log2(n)(4n)
11. we know T(1) = 4 AND 2 ^ log2(n) = n log2(2) = n, which means our simplified equation is => 4n + log2(n)(4n)
12. This simplifies to O(n * logn)
```

# Recurrence Relations (Recurrence Tree)
T(1) = 4, (base case) T(n) = 2T(n/2) + 4n (recurrence equation); find complexity
```
                            4n
                          /    \
                       4n/2     4n/2
                      /    \    /   \
                    4n/4   4n/4 ..  ..
                   /    \  /  \ /\  /\
                 4n/8 4n/8 .  . ..  ..
                 / \  /\  /\ /\ /\  /\
          4n/(2^i) . . . . .. .. . . .
```
log2(n) levels 4n times with a sum of 4n each level => 4n * log2(n) + 4n

# Recurrence Relations

```cpp
void test(int n)
{
  if(n > 0)
  {
    cout << n; //+ 1
    test(n-1); //T(n-1)
  }
}
```
```
The recurrence equation of the above function is T(n) = T(n-1) + 1
T(n) = { 1          if n = 0 <---------------------------------------
       { T(n-1) + 1 if n > 0                                        |
                                                                    |
You can solve T(n) if you solve T(n-1) => T(n-1) = T(n-2) + 1       |
T(n) = [T(n-2)+1]+1 = T(n) = T(n-2) + 2, repeat k times             |
T(n) = T(n-k) + k                                                   |
                                                                    |
Assume n - k = 0 => n = k                                           |
T(n) = T(n-n) + n                                                   |
T(n) = T(0) + n                                                     |
T(n) = 1 + n (look back at the piecewise function)------------------|
```

# Recurrence Relations
```cpp
void test(int n)
{
  if(n > 0)
  {
    for(i = 0; i < n; i++)
    {
      cout << n;
    }
    test(n-1);
  }
}
```
```
The recurrence equation of the above function is T(n) = T(n-1) + 2n + 2
Remove all constants: T(n) = T(n-1) + n
T(n) = { 1            if n = 0
       { T(n-1) + n   if n > 0

        T(n)
       /    \
      n      T(n-1)
             /     \
           n-2     T(n-3)

1 + 2 + ... + n - 2 + n - 1 + n = n (n + 1) / 2 => O(n^2)

Substitution

T(n) = T(n-1) + n
solve for n-1: T(n-1) = T(n-2) + (n-1)
solve for n-2 ... n-k: T(n) = T(n-k) + (n - (k - 1)) + (n - (k - 2)) + ... + (n-1) + n
Assume n-k = 0, so n = k
T(n) = T(n-n) + (n-n+1) + (n-n+2) + ... + (n-1) + n
T(n) = T(0) + 1 + 2 + 3 + ... + (n-1) + n
T(n) = T(0) = 1 + n(n+1) / 2 (REMOVE CONSTANT SO REMOVE 1 +)
Time complexity = O(n^2)
```

# Recurrence Relations

```cpp
void test(int n)
{
  if(n > 1)
  {
    for(i = 0; i < n; i++)
    {
      somsthing();
    }
    Test(n/2);
    Test(n/2);
  }
}
```

```
The recurrence equation of the above function is T(n) = 2T(n/2) + n
T(n) = { 1             if n = 1
       { 2T(n/2) + n   if n > 1

        n
     /    \
   n/2         n/2
  /  \        /    \
 n/4  n/4    ..    ..
/  \   /\    /\    /\
n/8 n/8 ..............
/\  /\
n/2^k ................

There are k levels so it is O(nlogn)

Substitution

T(n) = 2T(n/2) + n, solve for T(n/2)
T(n/2) = 2T(n/4) + n/2, solve for T(n/3) ... T(n/k)
T(n) = 2^k * T(n/(2^k)) + kn
Assume T(n/2^k) = T(1), n/2^k = 1, n = 2^k, k = logn
T(n) = n*T(1) + nlogn
T(n) = n*1 + nlogn
T(n) = nlogn
```

# Recurrence Relations

```cpp
void Test(int n)
{
  if(n > 0)
  {
    cout << n;
    Test(n-1);
    Test(n-1);
  }
}
```
```
The above recurrence equation is T(n) = 2T(n-1)+1

                    T(n)
             /        |        \
           T(n-1)     1       T(n-1)
         /    |    \        /  |  \
       ..     1     ..      ..  1   ..
  /    |   \      / | \ / | \   / | \
T(n-n) 1 T(n-n) ......................

Simplifies to = 2^(k+1) - 1
Assume n - k = 0, n = k
O = (2^n)

Substitution

Solve T(n-k) => T(n) = 2^k * T(n-k) + 2^(k-1) + 2^(k-2) + ... + 2^2 + 2 + 1
Assume n - k = 0, n = k
2^n * T(0) + 1 + 2 + 2^2 + ... + 2^(k-1)
2^n * 1 + 2^k - 1
= 2^n + 2^n - 1
2^(n+1) - 1
O(2^n)
```

# Recurrence Relations

```cpp
void Test(int n)
{
    if(n > 1)
    {
      cout << n;
      test(n/2);
    }
}
```
```
Above recurrence is T(n/2) + 1
T(n) = { 1          if n = 1
       { T(n/2) + 1 if n > 1

  T(n)
 /    \
1      T(n)
      /   \
     1     T(n/2^2)
           /      \
         1      T(n/2^3)
                /      \
              1        T(n/(2^k))

log(n) levels with constant subtrees = O(logn)

Substitution

Solve for T(n) ... T(n/k)
T(n) = T(n/(2^k))+k
Assume n/2^k = 1, n = 2^k and k = logn
T(n) = T(1) + logn = 1 + logn = O(logn)
```
