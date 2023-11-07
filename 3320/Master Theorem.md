Let T(n) = aT(n/b) + cn^k, and let T(1) = c
where a, b, c, and k are all constants, solve to:
1. T(n) E Theta-O(n^k)        if a < b^k
2. T(n) E Theta-O(n^k logn)   if a = b^k
3. T(n) E Theta-O n(logb(a))  if a > b^k

DC Recurrence Theorem

Let T(n) = aT(n/b) + f(n) where a >= 1 and b > 1 are constants and f(n) is a function. Let T(1) = Theta-O(1).
Suppose there's a constant c such that af(n/b) = cf(n). Then the solution for the above recurrence T(n) is:
1. if c < 1 (decreasing) then T(n) = Theta-O(f(n))
2. if c > 1 (increasing) then T(n) = Theta-O(n^logb(a))
3. if c = 1 then T(n) = Theta-O(f(n)logb(n))

Ex. T(n) = T(n/2) + 1, T(1)
The runtime of this algorithm can be written out as a piecewise function shown below:
T(n) = { 1            if n = 1
       { T(n/2) + 1   if n > 1

The recurrence relation we're given is a dividing function:
- The algorithm takes T(n) time
- As long as n > 1 we recursively call T(n) once.
- For each level of the tree we divide by 2.

Observe the level by level summation of the tree:
1. The first level equals n
2. The second level equals n/2 + 1
3. The third level equals n/4 + 1
Solving af(n/b) = cf(n) yields that c = 1
Our recurrence is Theta-O(f(n)logb(n))

Ex. T(n) = 2T(n/2) + n, T(1) = 1
Piecewise representation:
T(n) =  { 1            if n = 1
        { 2T(n/2) + n  if n > 1

1. The first level equals p
2. The second level equals 2(n/2) = p
3. The third level equals 4(n/4) = n
Solving af(n/b) = cf(n) yields that c = 1
Our recurrence is Theta-O(f(n)logb(n))

Ex. 3(n/2) + n, T(1) = 1

1. The first level equals n
2. The second level equals 3(n/2)
3. The third level equals 9(n/4)
Solving af(n/b) = cf(n) yields that c > 1.
Our recurrenceis Theta-O(n^log2(3)) where a = 3, b = 2

Using the Master Theorem

T(n) = 3(n/2) + n, T(1) = 1;
where a = 3, b = 2, k = 1

- Since a > b^k, 3 > 2, wWe can apply the following case of the Master Theorem:
T(n) = Theta-O(n^logb(a)) = Theta-O(n^log3(2))
