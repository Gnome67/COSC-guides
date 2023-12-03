Clearly indicate the following structures from the given directed graph:
1. A depth first spanning tree rooted at R
2. A breadth first spanning tree rooted at R
3. A topological order
4. The strongly connected components

![graphs](https://github.com/Gnome67/COSC-guides/assets/102388813/95ff0c70-b9bd-4a82-acae-9c4ab07d1470)

# Traversal: DFS

When we apply DFS from starting node R, we have two neighbors.
- We add S before U into our stack in order to follow alphabetical order.
- We explore as far into graph as possible via S.
- Once we run out of unvisited neighbors, we backtrack.
  - And then we visit those neighbors.
    - This is how we first visit V and then U.

visited: [R,S,T,W,Z,Y,X]
stack: [U,V]

After applying DFS on the given directed graph with your source as node R, the resulting depth first spanning tree is:
R -> S -> T -> W -> Z -> Y -> X -> V -> U

# Traversal: BFS

When we applt BFS from starting node R, we have two neighbors.
- We add S before U into our queue in order to follow alphabetical order.
  - We add T into the queue and pop the front (whch is U)
  - Both W and Y were waiting in queue. W is ahead of Y because of alphabetical order, so we pop W first.

After applying the resulting breadth first spanning tree is:
R -> S -> U -> T -> V -> Z -> X - > W -> Y

# Strongly Connected Components

In a directed graph, a strongly connected component is a set of nodes in which every pair of nodes can reach each other. And you can't add any more nodes without ruining it's strong connection.
In other words, a strongly connected component is a portion of a directed graph in which there is a path from each vertex to another.

**Note: Strong Connectivity does not apply to undirected graphs.**

Notice what makes each of these compoents strongly connected.
- There's a cycle (**Note: Cycle != SCC**)
- Through this cycle, each node can reach the others through a directed path.
- Node 7 is an example of a sink, a vertex with no outgoing edges.
```
0 -> 1       5
v    v     /^ \v
3 <- 4 -> 4 <- 6 -> 7
```
```
0 -> 1
^   v
 \  v
  \ v        > 4 <- 7
    2 - > 3 /  v    ^
               5 -> 6
```

### Kosaraju's Algorithm

- DFS-based algorithm used to find strongly connected components in a graph.
- Do a DFS on the original graph. When a node finished push the node onto a stack.
- Let G_r be the graph with same graph with edges reveresed.
- Do a DFS on G_R in the reverse order of the stack.

Pseudocode:
```py
# DFS is modified to where when DFS returns the node, it is pushed onto a stack
function kosaraju():
  // stack has already been initialized
  dfs(G)
  G_r = reversed(G)
  components = []
  for node in reversed(stack):
    new_component = []
    if node not visited:
      append node to new_component
      dfs(node)
    append new_component to components
```
Breakdown:
- Call DFS on a graph to determine finish times (same as the stack).
- In reverse order of finish times, do dfs on the reversed graph.
- When DFS returns, all the processed nodes will belong to the same SCC.

# Topological Sort

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

## Course Scheduler (Leetcode 20)

## Single Source Longest Path
