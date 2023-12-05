# Problem 1: Recurrence Relations

Solve the following recurrences by finding a Big-Theta form for T (n). Justify your work. You may assume the existence of base cases T (0) = T (1) = 1. You may use the master theorem if applicable, or mathematical induction.

- T(n) = T(n/2) + 5
- T(n) = 7T(n/2) + 10n^2
- T(n) = 2T(n - 1) + 1
- T(n) = 2T(n/8) + sqrt(n)

# Problem 2: Divide & Conquer

You are given n stones (assume that n is a power of 2) each having a distinct weight. You are also given a two-pan balance scale (no weights are given). For example, given two stones, you can use the scale to compare which one is lighter by placing the two stones on the two different pans. The goal is the find the heaviest and the lightest stone by using as few weighings as possible. Give a divide and conquer strategy that uses 3n/2 - 2 weightings. Justify algorithm correctness and the number of steps taken.

# Problem 3: Binary Search

You are given an n * n matrix represented as a 2-dimensional array A[1 . . . n][1 . . . n] (there are totally n^2 elements). Each row of A is sorted in increasing order and each column is sorted in increasing order. Your goal is to find whether some given element x is in A or not. Note that you can do only comparisons between elements (no hash table, or any other set data structures). Give an algorithm that takes O(n) comparisons.
[Hint: try to start on one some corner, and eliminate one row/column per move].

# Problem 4: Dynamic Programming

You are given an array A of n integers, both positive and negative. The maximum possible sum of contiguous elements of the array is the maximum value of Sum(i, j) = A[i] + A[i + 1] + . . . A[j − 1] + A[j] over any i, j satisfying 0 <= i <= j < n.

For example, the array [1, −5, 7, 10, −3, 15] has maximum sum 29, which is represented by the subarray [7, 10, −3, 15].

Define a dynamic programming algorithm which can find the maximum value of Sum(i, j) in O(n) time (note we don’t need to know the i, j values that make it maximum for the final solution).

Provide the base cases, recursive subproblems and the recursive formula that defines the solutions of larger subproblems in terms of smaller ones.


[Hint: The first and most difficult step is finding out the recursive relationship of larger problems in terms of smaller ones. If we have the solution on the range [0, i], it matters whether the subarray that yields the maximum sum includes i or does not, when determining whether it is relevant to a solution on [0, i + 1]. These distinctions can be solved by adding additional subproblems.]

# Problem 5: Backtracking

Given an array of distinct integers A, describe an algorithm to print out all permutations of the array

# Problem 6: Backtracking

Given an array of possibly non-distinct integers A, describe an algorithm to print out all unique permutations of the array.

# Problem 7: Binary Search

You are given a sorted array consisting of numbers, each of which appears twice in the array, except for one number which appears only once. Describe an O(log n) algorithm to find the value of the number which appears only once.

# Problem 8: Backtracking / Dynamic Programming

Let’s play a game. You have a n * n square grid. Initially you must place a token on a square in the first row. In each turn, you move your token to one square to the right, or one square down. The game ends when you move your token out of the board. Each square on the grid has a numerical value, which could be positive, zero, or negative. You start with 0 score. Whenever the token lands on a square, you add its value to your score. You try to score as many points as possible.

For example, given the grid below, and placing initial token on 1st row 2nd column, and moving down, down, right, down, down, the game ends and you have score -9 (which is not the maximum possible):

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/1af8c673-7a34-4000-badf-29a04a3868c2)

Describe an algorithm to compute the maximum score, given a board A[1 . . . ][1 . . . n], and analyze its time complexity.

# Problem 9: Divide & Conquer

You are a contestant on the hit game show ”Beat Your Neighbors!” You are presented with an length n array of boxes, each containing a unique number. Your goal is to find a box whose number is larger than its neighbors in the array (left and right). Describe an algorithm that finds a number that is bigger than either of its neighbors, by opening no more than O(log n) boxes.

# Problem 10: Dynamic Programming Algorithm

A string of parentheses or brackets w is balanced if it satisfies one of the following conditions:
- w is the empty string
- w = (x) where x is a balanced string
- w = [x] where x is a balanced string
- x = xy where x and y are balanced strings

Example: w = ([()][])[()()] is balanced, where x = ([()][]), y = [()()] are balanced.

For this problem, develop and analyze two algorithms:
- An algorithm which returns true if an input string w is balanced, and false otherwise
- An algorithm which computes the length of the longest balanced substring of the input (which can be the whole input string if the input is itself balanced).

An example: the second algorithm can run on w = [((())([] would yield 4, based on the substring (()).

# Problem 11: Graphs

Given the following directed graph:
- Construct a DFS spanning forest for this graph, by performing DFS starting at a given node, and repeating until all nodes are visited. You may pick whichever starting nodes you want; which trees you get will differ depending on which nodes you start from.
- Find the strong component DAG of this graph.
- Provide a topological sorting on the strong component DAG.

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/8a2ae2c8-c90e-4119-9996-9efd5b2d0875)

# Problem 12: Graphs

Given the following undirected weighted graph:
- Construct a BFS search tree for the graph starting at node f
- Calculate a minimum spanning tree
- Calculate the single-source shortest paths for source node a

For the MST, additionally consider why the edges which are added at each step of the algorithm are safe edges.

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/76bc409b-b8a5-4aea-8c74-8ff9e893c95e)
