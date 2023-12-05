Like BFS, DFS is an algorithm used for searching all the vertices of a graph while avoiding cycles. The difference is that DFS uses a backtracking and a stack.
- You move forward down a path until there are no more nodes.
- Move backwards on the same path until you find neighboring nodes to traverse.
- All the nodes will be visited on the current path till all the unvisited nodes have been traversed.

Implementation:
- Queue: O(Vertices + Edges)

# Recursive Implementation

```py
function dfs(v):
  if v is unvisited:
    visited[v] = true
  for each node in neighbors(v):
    dfs(node)
```

# Iterative Implementation

```py
function dfs v:
  # let S be a stack
  S.push(v)
  visited[v] = true
  while S is not empty:
    u = S.top()
    S.pop()
    for each node in neighbors(v):
    if node is unvisited:
      S.push(node)
      visited[node]
```

# Tracing

Tracing a graph using DFS is all about going as far ahead as possible and backtracking

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

# Backtracking

Depth First Search is an example of a backtracking algorithm.
- It involves exhaustive searches of all of the nodes in the graph.
- You move as deep down a branch as you can.
- If there are no more unvisited nodes, you move backwards on the same path to find more nodes.

```py
function dfs(v):
  if v is visited:
    visited[v] = true
  for each node in neighbors(v) do:
    dfs(node)
```

In fact, all backtracking algorithms can be thought of as DFS on a tree.
- The root is an empty solution
- Internal nodes are partial candidate solutions
- Leaves are full solutions (both valid and invalid solutions)

```py
def backtracking(problem):
  def children(candidate):
    # yields the next partial candidate solutions from candidate
  def reject(candidate):
    # returns True if the partial candidate solution can be rejected AND the candidate is a full solution, else False

  result = [] # stores all solutions
  def dfs(node):
    if reject(node):
      return
    if accept(node):
      result.append(node)
      return
    for child in children(node):
      dfs(child)

  root = ... # root node, whose form depends on problem/implementaiton
  dfs(root)
  return result
```

# Python code

Provided by Michael Sambol

```py
def dfs(graph, node):
    visited = []
    stack = []

    visited.append(node)
    stack.append(node) 

    while stack:
        s = stack.pop()
        print(s, end = " ")

        # reverse iterate through edge list so results match recursive version
        for n in reversed(graph[s]):
            if n not in visited:
                visited.append(n)
                stack.append(n)
```
