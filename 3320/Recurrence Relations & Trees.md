A recurrence relation is an equation we use to model an algorithm's runtime.
Ex. Merge Sort often has a time complexity of T(n) = 2*T(n/2) + n
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
