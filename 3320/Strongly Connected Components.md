# Description

In a directed graph, a strongly connected component is a set of nodes in which every pair of nodes can reach each other. And you can't add any more nodes without ruining it's strong connection.

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/56c3a5df-8979-455d-96c5-586dca33f2c1)

In other words, a strongly connected component is a portion of a directed graph in which there is a path from each vertex to another.

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/914d1bde-aa4f-4120-ab59-05421b9c877c)

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

# Kosaraju's Algorithm

DFS-based algorithm used to find strongly connected components in a graph.
- Do a DFS on the original graph. When a node is finished, push the node onto a stack.
- Create G_r, a transpose of the original graph with edges reversed.
- Do a DFS on G_r in the reverse order of the stack.

***If not all vertices are visited in either DFS, the graph is not strongly connected***

Pseudocode:
```py
# DFS is modified to where when DFS returns the node, it is pushed onto a stack
function kosaraju():
  stack = []
  dfs(G)
  G_r = reversed(G)
  components = []
  for node in reversed(stack):
    new_component = []
    if node not visited:
      new_component.append(node)
      dfs(node)
    components.append(new_component)
```
Breakdown:
- Call DFS on a graph to determine finish times (same as the stack).
- In reverse order of finish times, do dfs on the reversed graph.
- When DFS returns, all the processed nodes will belong to the same SCC.
