# Time Complexity

O(|Vertices| * |Edges|)

# Description

The Bellman–Ford algorithm is an algorithm that computes shortest paths from a single source vertex to all of the other vertices in a weighted directed graph. It is slower than Dijkstra's algorithm for the same problem, but more versatile, as it is capable of handling graphs in which some of the edge weights are negative numbers.

# Breakdown

Like Dijkstra's algorithm, Bellman–Ford proceeds by relaxation, in which approximations to the correct distance are replaced by better ones until they eventually reach the solution. In both algorithms, the approximate distance to each vertex is always an overestimate of the true distance, and is replaced by the minimum of its old value and the length of a newly found path.

However, Dijkstra's algorithm uses a priority queue to greedily select the closest vertex that has not yet been processed, and performs this relaxation process on all of its outgoing edges; by contrast, the Bellman–Ford algorithm simply relaxes all the edges, and does this | V | − 1 |V|-1 times, where | V | |V| is the number of vertices in the graph. In each of these repetitions, the number of vertices with correctly calculated distances grows, from which it follows that eventually all vertices will have their correct distances.

This method allows the Bellman–Ford algorithm to be applied to a wider class of inputs than Dijkstra. The intermediate answers depend on the order of edges relaxed, but the final answer remains the same.

# Visualization

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/9e23a7a2-70a0-4d4c-80f8-e0ccbeb68375)

Note: This has 6 vertices, so it will have at most 5 iterations

### Iteration 1
1. We are going to make s our starting node
2. Let's make our table of distances. Keep in mind even though we have defined distances to A and E from S, we will initialize everything as a distance of infinity to begin with.
- unvisited: {A: inf, B: inf, C: inf, D: inf, E: inf}
- visited: {S}
- cost: 0
3. Let's update the table of distances with the two currently reachable nodes from S, E and A
- unvisited: {A: 10, B: inf, C: inf, D: inf, E: 8}
4. We know from A, we can reach C with an additional cost of 2, for a total cost of 10 + 2 = 12, so let's update the table
- unvisited: {A: 10, B: inf, C: 12, D: inf, E: 8}
5. We can get to B from C with a cost of -2, for a total cost of 10 + 2 - 2 = 10, so let's update the table
- unvisited: {A: 10, B: 10, C: 12, D: inf, E: 8}
6. We can get to D from E with a cost of 1, for a total cost of 8 + 1 = 9, so let's update our table
- unvisited: {A: 10, B: 10, C: 12, D: 9, E: 8}

### Iteration 2
7. If we look at S -> E -> D, we see that D has a path to both A (-4 for a total of 8 + 1 - 4 = 5) and C (-1 for a total of 8 + 1 - 1 = 8) that are more cost-effective than the current paths we have (S -> A = 10) and (S -> A -> C = 12). Let's update our table accordingly
- unvisited: {A: 5, B: 10, C: 8, D: 9, E: 8}

### Iteration 3

8. Now that we know A can be reached with a cost of 5 from S -> E -> D -> A, we can update C with route S - > E -> D -> A -> C for a total cost of (8 + 1 - 4 + 2 = 7). Let's update our table as such:
- unvisited: {A: 5, B: 10, C: 7, D: 9, E: 8}
9. In addition, S -> E -> D -> A -> C -> B is reduced to 8 + 1 - 4 + 2 - 2 = 5. Let's update our table as such:
- unvisited: {A: 5, B: 5, C: 7, D: 9, E: 8}

### Iteration 4

10. We can stop here. Even though the algorithm takes at most v - 1 iterations, we have reached the end of the minimizing of our paths throughout our graph.

# Pseudocode

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/fc1158f2-fa56-4f67-8b1d-8ca3f0bbe730)

Regarding the algorithm:
- At most we will iterate v - 1 times
- Each iteration will update along all edges

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

# Pseudocode Breakdown

Simply put, the algorithm initializes the distance to the source to 0 and all other nodes to infinity. Then for all edges, if the distance to the destination can be shortened by taking the edge, the distance is updated to the new lower value.

The core of the algorithm is a loop that scans across all edges at every loop. For every i ≤ | V | − 1 {\displaystyle i\leq |V|-1}, at the end of the i i-th iteration, from any vertex v, following the predecessor trail recorded in predecessor yields a path that has a total weight that is at most distance[v], and further, distance[v] is a lower bound to the length of any path from source to v that uses at most i edges.

Since the longest possible path without a cycle can be | V | − 1 |V|-1 edges, the edges must be scanned | V | − 1 |V|-1 times to ensure the shortest path has been found for all nodes. A final scan of all the edges is performed and if any distance is updated, then a path of length | V | |V| edges has been found which can only occur if at least one negative cycle exists in the graph.

The edge (u, v) that is found in step 3 must be reachable from a negative cycle, but it isn't necessarily part of the cycle itself, which is why it's necessary to follow the path of predecessors backwards until a cycle is detected. The above pseudo-code uses a boolean array (visited) to find a vertex on the cycle, but any cycle finding algorithm can be used to find a vertex on the cycle.

# Proof

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

# Python Code

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
