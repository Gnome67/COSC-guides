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

# Single Source Longest Path

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/a7baa6d9-8197-4189-8509-268454bc3312)

Given a weighted acrylic directed graph (DAG) with positive integer weights, and two nodes in the graph i, j, find the longest path from node i -> node j.
For example, the longest path between nodes 0 and 3 is 60.

Algorithm description:
Topologically sort the graph. To find the longest distance to a node v, recursively determine the longest distance to each of its incoming neighbors.

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/daaa6ad3-0117-4f62-a092-fc93f6b47bb0)

```py
function single_source_longest_path(start, end, adjacency_list, num_of_vertices):
  distances = [-1...-1] # size of num_of_vertices
  distances[start] = 0

  for node in topologcialSort(adjacency_list, num_of_vertices):
    if distances[node] == -1:
      continue
    for neighbor, weight in adjacency_list.get(node);
      distances[neighbor] = max(distances[neighbor], distances[node] + weight)
    return distances[end]
```

Breakdown:
1. initialize a list of distances to -1
2. Set distance[start] to 0
3. Call topological sort with our adjacency list
4. If distances[node] = -1, continue
5. Otherwise find the max of the incoming distances

Proof of Correctness:

Assume, without loss of generality, that the nodes are in some topological ordering.

We will show by induction that, when we visit a node v, the longest path to nodes 0, 1, ..., v (from s) have been correctly determined.

The base case is obvious: the longest path from s to s is 0. (Convince yourself that this is true -- G is a DAG.)

Suppose it is true for all nodes 0, 1, ..., v - 1 (IH).

Then, for node v, the longest path from s must pass through a node in {0, 1, ... v - 1} (since G is a DAG).

By our induction hypothesis, the longest path to each of these nodes has already been correctly determined.

Therefore, the longest path to v has already been determined.
