Clearly indicate the following structures from the given directed graph:
1. A depth first spanning tree rooted at R
2. A breadth first spanning tree rooted at R
3. A topological order
4. The strongly connected components

![graphs](https://github.com/Gnome67/COSC-guides/assets/102388813/95ff0c70-b9bd-4a82-acae-9c4ab07d1470)

### Tracing

Tracing a graph using DFS is all about going as far ahead as possible and backtracking

Graph:
![Graph2](https://github.com/Gnome67/COSC-guides/assets/102388813/720a6b52-f43b-4965-8eaf-4edd36643c7d)

visited: [0]
- We first add our source node into the visited array

stack: [1,2,3]
- All adjacent nodes are added to the stack

visited: [0,1]
- We pop the front of the stack and add it to the visited array

stack: [2,3]

visited: [0,1,2]

stack: [4,3]
- Node 2 has an unvisited neighbor so we add it to the stack

visited: [0,1,2,4]

stack: [3]
- When we discovered 2, we had discovered a node to add to our stack. Now we backtrack to last unvisited neighbor of 0.

visited: [0,1,2,4,3]

stack: []

# Strongly Connected Components


### Kosaraju's Algorithm

# Topological Sort

## Course Scheduler (Leetcode 20)

## Single Source Longest Path
