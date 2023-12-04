- A sorting algorithm that can only be applied to directed acrylic graphs (DAGS). The algorithm will sort the nodes of a DAG into topological order.
- a topological order is one in which each node appears before each of the nodes its directed to. All edges are essentially ordered in the same direction.
- NOTE: a DAG can have more than one topological ordering. These orderings are **NOT** unique.

![Graphs3](https://github.com/Gnome67/COSC-guides/assets/102388813/bbfb2124-d28a-406e-9c44-460346ab4a44)

Above is a DAG and one of its topological orderings. Notice how node 1 appears before both of the nodes it points to. This rule applies to the others.

Algorithm:
```py
# Requirement: G is a DAG and stored in an adjacency list
function topsort(G):
  visited = [false, ..., false]
  ordering = [0, ..., 0]
  for each v in V:
    if visited[v] is false:
      dfs(v, visited, ordering, G)
  return ordering

# Executes Depth First Search DFS, inserts a node directly inside the next valid position of the array and returns the next position, pos-1, as we are going in reverse order.
function dfs(v, visited, ordering, G):
  visited[v] = true
  E = G.getEdges(v) # edges tell us the neighbors
  for each e in E:
    if visited[e] is false:
      dfs(e, visited, ordering, G)
  ordering.append(v)
```

Breakdown:
1. Pick an unvisited node
2. Do a DFS, beginning with the selected node and explore only the unvisited nodes.
3. On the recursive callback of the DFS, add the current node to the topological ordering in reverse order

Time Complexity: O(Vertices + Edges)

# Course Scheduler (Leetcode 20)

There are a total of n courses you have to take, labeled from 0 to n - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
- For example, the pair [0,1] indicates that to take course 0 you have to first take course 1.

Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

### Solution:

For this problem, we'll first build an adjacency list. For each node we will need to know their prerequisites (neighbors).

List:
[Node, [Prereqs]]
1. [1336, []]
2. [1437, [1336]]
3. [2436, [1437]]
4. [2425, [1437]]
5. [3320, [2436]]
6. [3360, [2436, 2425]]
7. [4353, [3320]]

We are then going to run DFS on every single node. As we traverse, we'll need to keep track of two things.
1. visited neighbors.
2. Any cycles (reject)
```
DAG: [1336] <- [1437] <- [2436] <- [3320] <- [4353]
                    ^         ^
                    ^           \
                    ^ - [2425] <- [3360]
```
After we run this DAG through our topological sorting algorithm, we get the resulting ordering:

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/92315e04-1175-49d9-a1c6-8fd07f8349bc)

However, this is not unique.

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/3240835e-6346-4874-9307-aa79f03287dd)

### Pseudocode:

```py
function plancourse(numCourse, prerequisites):
  # build an adjacency list prereq from input_ARRAY
  output = [0, ..., 0]
  visited = [false, ..., false]
  cycled = [false, ..., false]
  # inner dfs function below
  function dfs(course):
    if cycled[course]:
      return false
    if visited[course]:
      return true
    cycled[course] = true # cycled
    for each class in prereq[course]:
      if dfs(course) == false:
        return false
    cycled[course] = false # not cycled
    visited[course] = true # visited
    output/append(course)
    return true
  return order
```
Breakdown:
1. Build an adjacency list
2. Create the arrays: visited, cycled
3. Declare the inner function for DFS
- Reject cycles
- Accept visited courses
4. For each prerequisite:
- Recurse (if cyclical, false)
- Otherwise, unmark the node as cycled
- Mark as visited and append
