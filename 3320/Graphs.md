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

# Bellman-Ford Algorithm

The Bellman–Ford algorithm is an algorithm that computes shortest paths from a single source vertex to all of the other vertices in a weighted directed graph. It is slower than Dijkstra's algorithm for the same problem, but more versatile, as it is capable of handling graphs in which some of the edge weights are negative numbers.

### Breakdown

Like Dijkstra's algorithm, Bellman–Ford proceeds by relaxation, in which approximations to the correct distance are replaced by better ones until they eventually reach the solution. In both algorithms, the approximate distance to each vertex is always an overestimate of the true distance, and is replaced by the minimum of its old value and the length of a newly found path.

However, Dijkstra's algorithm uses a priority queue to greedily select the closest vertex that has not yet been processed, and performs this relaxation process on all of its outgoing edges; by contrast, the Bellman–Ford algorithm simply relaxes all the edges, and does this | V | − 1 |V|-1 times, where | V | |V| is the number of vertices in the graph. In each of these repetitions, the number of vertices with correctly calculated distances grows, from which it follows that eventually all vertices will have their correct distances.

This method allows the Bellman–Ford algorithm to be applied to a wider class of inputs than Dijkstra. The intermediate answers depend on the order of edges relaxed, but the final answer remains the same.

### Pseudocode

```py
function BellmanFord(list vertices, list edges, vertex source):
  # This implementation takes in a graph, represented as lists of vertices (represented as integers [0..n-1]) and edges, and fills two arrays (distance and predecessor) holding the shortest path from the source to each vertex
  distance = list of size n
  predecessor = list of size n

# Step 1: initialize graph
  for vertex v in vertices:
    distance[v] = inf      # Initialize the distance to all vertices to infinity
    predecessor[v] = null  # And having a null predecessor

  distance[source] = 0 # The distance from the source to itself is zero

# Step 2: relax edges repeatedly
  repeat |V|−1 times:
  for edge (u, v) with weight w in edges:
    if distance[u] + w < distance[v]:
      distance[v] = distance[u] + w
      predecessor[v] = u

# Step 3: check for negative-weight cycles
  for edge (u, v) with weight w in edges:
    if distance[u] + w < distance[v]:
      predecessor[v] = u
      # A negative cycle exist; find a vertex on the cycle 
      visited = list of size n initialized with false
      visited[v] = true
      while not visited[u]:
        visited[u] = true
        u = predecessor[u]
      # u is a vertex in a negative cycle, find the cycle itself
      ncycle = [u]
      v = predecessor[u]
      while v != u:
        ncycle = concatenate([v], ncycle)
        v = predecessor[v]
      # error "Graph contains a negative-weight cycle", ncycle
  return distance, predecessor
```

### Pseudocode Breakdown

Simply put, the algorithm initializes the distance to the source to 0 and all other nodes to infinity. Then for all edges, if the distance to the destination can be shortened by taking the edge, the distance is updated to the new lower value.

The core of the algorithm is a loop that scans across all edges at every loop. For every i ≤ | V | − 1 {\displaystyle i\leq |V|-1}, at the end of the i i-th iteration, from any vertex v, following the predecessor trail recorded in predecessor yields a path that has a total weight that is at most distance[v], and further, distance[v] is a lower bound to the length of any path from source to v that uses at most i edges.

Since the longest possible path without a cycle can be | V | − 1 |V|-1 edges, the edges must be scanned | V | − 1 |V|-1 times to ensure the shortest path has been found for all nodes. A final scan of all the edges is performed and if any distance is updated, then a path of length | V | |V| edges has been found which can only occur if at least one negative cycle exists in the graph.

The edge (u, v) that is found in step 3 must be reachable from a negative cycle, but it isn't necessarily part of the cycle itself, which is why it's necessary to follow the path of predecessors backwards until a cycle is detected. The above pseudo-code uses a boolean array (visited) to find a vertex on the cycle, but any cycle finding algorithm can be used to find a vertex on the cycle.

### Proof

The correctness of the algorithm can be shown by induction:

Lemma. After i repetitions of for loop,

- if Distance(u) is not infinity, it is equal to the length of some path from s to u; and
- if there is a path from s to u with at most i edges, then Distance(u) is at most the length of the shortest path from s to u with at most i edges.

Proof: For the base case of induction, consider i=0 and the moment before for loop is executed for the first time. Then, for the source vertex, source.distance = 0, which is correct. For other vertices u, u.distance = infinity, which is also correct because there is no path from source to u with 0 edges.

For the inductive case, we first prove the first part. Consider a moment when a vertex's distance is updated by v.distance := u.distance + uv.weight. By inductive assumption, u.distance is the length of some path from source to u. Then u.distance + uv.weight is the length of the path from source to v that follows the path from source to u and then goes to v.

For the second part, consider a shortest path P (there may be more than one) from source to v with at most i edges. Let u be the last vertex before v on this path. Then, the part of the path from source to u is a shortest path from source to u with at most i-1 edges, since if it were not, then there must be some strictly shorter path from source to u with at most i-1 edges, and we could then append the edge uv to this path to obtain a path with at most i edges that is strictly shorter than P—a contradiction. By inductive assumption, u.distance after i−1 iterations is at most the length of this path from source to u. Therefore, uv.weight + u.distance is at most the length of P. In the ith iteration, v.distance gets compared with uv.weight + u.distance, and is set equal to it if uv.weight + u.distance is smaller. Therefore, after i iterations, v.distance is at most the length of P, i.e., the length of the shortest path from source to v that uses at most i edges.

If there are no negative-weight cycles, then every shortest path visits each vertex at most once, so at step 3 no further improvements can be made. Conversely, suppose no improvement can be made. Then for any cycle with vertices v[0], ..., v[k−1],

v[i].distance <= v[i-1 (mod k)].distance + v[i-1 (mod k)]v[i].weight

Summing around the cycle, the v[i].distance and v[i−1 (mod k)].distance terms cancel, leaving

0 <= sum from 1 to k of v[i-1 (mod k)]v[i].weight

I.e., every cycle has nonnegative weight. 

### Python Code

Provided by Michael Sambol

```py
def bellman_ford(G, start):
    shortest_paths = {}
    
    for node in G:
        shortest_paths[node] = infinity

    shortest_paths[start] = 0
    size = len(G)

    for _ in range(size - 1):
        for node in G:
            for edge in G[node]:
                cost = edge[0]
                to_node = edge[1]
                if shortest_paths[node] + cost < shortest_paths[to_node]:
                    shortest_paths[to_node] = shortest_paths[node] + cost

    # iterate once more and check for negative cycle
    for node in G:
        for edge in G[node]:
            cost = edge[0]
            to_node = edge[1]
            if shortest_paths[node] + cost < shortest_paths[to_node]:
                return 'INVALID - negative cycle detected'

    return shortest_paths
```
