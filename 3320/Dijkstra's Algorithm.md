# Time Complexity

- Fibonacci Heap: O(|Edges| + |Vertices|log|Vertices|)

# Description

The idea is to generate a SPT (shortest path tree) with a given source as a root. Maintain an Adjacency Matrix with two sets, 
- one set contains vertices included in the shortest-path tree, 
- other set includes vertices not yet included in the shortest-path tree. 

At every step of the algorithm, find a vertex that is in the other set (set not yet included) and has a minimum distance from the source.

- Create a set sptSet (shortest path tree set) that keeps track of vertices included in the shortest path tree, i.e., whose minimum distance from the source is calculated and finalized. Initially, this set is empty. 
- Assign a distance value to all vertices in the input graph. Initialize all distance values as INFINITE. Assign the distance value as 0 for the source vertex so that it is picked first. 
- While sptSet doesn’t include all vertices 
  - Pick a vertex u that is not there in sptSet and has a minimum distance value. 
  - Include u to sptSet. 
  - Then update the distance value of all adjacent vertices of u. 
    - To update the distance values, iterate through all adjacent vertices. 
    - For every adjacent vertex v, if the sum of the distance value of u (from source) and weight of edge u-v, is less than the distance value of v, then update the distance value of v. 

# Visualization

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/d443df48-2739-4fc6-b6bf-8eca22dfb9f6)

1. We are going to keep track of the unvisited nodes.
- unvisited: {A, B, C, D, E}
2. We are going to choose an arbitrary node A
- unvisited: {B, C, D, E}
- visited: {A}
3. Even though we know the weights of the routes from A, we will notarize them as infinity as such:
- unvisited: {B: inf, C: inf, D: inf, E: inf}
4. Let's update the unvisited table with the weights of all the nodes that can be directly reached by A in one trip.
- unvisited: {B: 4, C: 2, D: inf, E: inf}
5. Let's pick the smallest node we can reach. C's 2 is less than B's 4, which is less than D and E's infinity, so let's pick C.
- unvisited: {B: 4, ~~C: 2~~, D: inf, E: inf}
- visited: {A, C}
- cost: 2
6. We notice that B can be reached by A and C. A -> B is a cost of 4, while A -> C -> B is a cost of 2 + 1 = 3, so let's update our unvisited chart to reflect this
- unvisited: {B: 3, C: 2, D: inf, E: inf}
7. C can also reach E and D, so let's update the table. We are going to add 2 to D and E since to reach D and E from A, we need to travel through C
- unvisited: {B: 3, ~~C: 2,~~ D: 6, E: 7}
8. Now let's visit B from A -> C
- unvisited: {~~B: 4, C: 2,~~ D: 6, E: 7}
- visited: {A, C, B}
- cost: 3
9. B can also visit D and E, so let's compare the costs of going from A -> C -> D / E compared to A -> C -> B -> D / E
- unvisited: {~~B: 4, C: 2,~~ D: 5, E: 6}
10. As we can see, it's cheaper to go through A -> C -> B -> D / E, than to go A -> C -> D / E
11. Now that D is the cheapest, let's choose D
- unvisited: {~~B: 4, C: 2, D: 5,~~ E: 6}
- visited: {A, C, B, D}
- cost: 5
12. Finally, take B -> E
- unvisited: {~~B: 4, C: 2, D: 5, E: 6~~}
- visited: {A, C, B, D, E}
- cost: 8

# Explanation:

Suppose you would like to find the shortest path between two vertexs on a city graph: a starting point and a destination.

Dijkstra's algorithm initially marks the distance (from the starting point) to every other vertex on the graph with infinity.

This is done not to imply that there is an infinite distance, but to note that those vertexs have not been visited yet. Some variants of this method leave the vertexs' distances unlabeled.

Now select the current vertex at each iteration.

For the first iteration, the current vertex will be the starting point, and the distance to it (the vertex's label) will be zero.

For subsequent iterations (after the first), the current vertex will be a closest unvisited vertex to the starting point (this will be easy to find).

From the current vertex, update the distance to every unvisited vertex that is directly connected to it.

This is done by determining the sum of the distance between an unvisited vertex and the value of the current vertex and then relabeling the unvisited vertex with this value (the sum) if it is less than the unvisited vertex's current value.

In effect, the vertex is relabeled if the path to it through the current vertex is shorter than the previously known paths.

To facilitate shortest path identification, in pencil, mark the edge with an arrow pointing to the relabeled vertex if you label/relabel it, and erase all others pointing to it.

After you have updated the distances to each neighboring vertex, mark the current vertex as visited and select an unvisited vertex with minimal distance (from the starting point) – or the lowest label—as the current vertex.

Vertexes marked as visited are labeled with the shortest path from the starting point to it and will not be revisited or returned to.

Continue this process of updating the neighboring vertexs with the shortest distances, marking the current vertex as visited, and moving onto a closest unvisited vertex until you have marked the destination as visited.

Once you have marked the destination as visited (as is the case with any visited vertex), you have determined the shortest path to it from the starting point and can trace your way back following the arrows in reverse.

In the algorithm's implementations, this is usually done (after the algorithm has reached the destination node) by following the nodes' parents from the destination node up to the starting node; that's why we also keep track of each node's parent.

This algorithm makes no attempt of direct "exploration" towards the destination as one might expect. Rather, the sole consideration in determining the next "current" vertex is its distance from the starting point.

This algorithm therefore expands outward from the starting point, interactively considering every node that is closer in terms of shortest path distance until it reaches the destination.

When understood in this way, it is clear how the algorithm necessarily finds the shortest path. However, it may also reveal one of the algorithm's weaknesses: its relative slowness in some topologies. 

# Algorithm

Let the node at which we are starting be called the initial node. Let the distance of node Y be the distance from the initial node to Y. Dijkstra's algorithm will initially start with infinite distances and will try to improve them step by step.
1. Mark all nodes unvisited. Create a set of all the unvisited nodes called the unvisited set.
2. Assign to every node a tentative distance value: set it to zero for our initial node and to infinity for all other nodes. During the run of the algorithm, the tentative distance of a node v is the length of the shortest path discovered so far between the node v and the starting node. Since initially no path is known to any other vertex than the source itself (which is a path of length zero), all other tentative distances are initially set to infinity. Set the initial node as current.[17]
3. For the current node, consider all of its unvisited neighbors and calculate their tentative distances through the current node. Compare the newly calculated tentative distance to the one currently assigned to the neighbor and assign it the smaller one. For example, if the current node A is marked with a distance of 6, and the edge connecting it with a neighbor B has length 2, then the distance to B through A will be 6 + 2 = 8. If B was previously marked with a distance greater than 8 then change it to 8. Otherwise, the current value will be kept.
4. When we are done considering all of the unvisited neighbors of the current node, mark the current node as visited and remove it from the unvisited set. A visited node will never be checked again (this is valid and optimal in connection with the behavior in step 6.: that the next nodes to visit will always be in the order of 'smallest distance from initial node first' so any visits after would have a greater distance).
5. If the destination node has been marked visited (when planning a route between two specific nodes) or if the smallest tentative distance among the nodes in the unvisited set is infinity (when planning a complete traversal; occurs when there is no connection between the initial node and remaining unvisited nodes), then stop. The algorithm has finished.
6. Otherwise, select the unvisited node that is marked with the smallest tentative distance, set it as the new current node, and go back to step 3.

When planning a route, it is actually not necessary to wait until the destination node is "visited" as above: the algorithm can stop once the destination node has the smallest tentative distance among all "unvisited" nodes (and thus could be selected as the next "current"). 

# Pseudocode

In the following pseudocode algorithm, dist is an array that contains the current distances from the source to other vertices, i.e. dist[u] is the current distance from the source to the vertex u.
The prev array contains pointers to previous-hop nodes on the shortest path from source to the given vertex (equivalently, it is the next-hop on the path from the given vertex to the source).
The code u <- vertex in Q with min dist[u], searches for the vertex u in the vertex set Q that has the least dist[u] value.
Graph.Edges(u, v) returns the length of the edge joining (i.e. the distance between) the two neighbor-nodes u and v.
The variable alt on line 14 is the length of the path from the root node to the neighbor node v if it were to go through u. If this path is shorter than the current shortest path recorded for v, that current path is replaced with this alt path.

```py
function Dijkstra(graph, source):
  for each vertex v in Graph.Vertices:
    dist[v] <- INFINITY
    prev[v] <- UNDEFINED
    add v to Q
  dist[source] <- 0

  while Q is not empty:
    u <- vertex in Q with min dist[u]
    remove u from Q

    for each neighbor v of u still in Q:
      alt <- dist[u] + graph.edges(u, v)
      if alt < dist[v]:
        dist[v] = alt
        prev[v] = u

  return dist[], prev[]
```

If we are only interested in a shortest path between vertices source and target, we can terminate the search after line 10 if u = target. Now we can read the shortest path from source to target by reverse iteration: 

```py
S = empty sequence
u = target
if prev[u] is defined or u = source: # Do something only if the vertex is reachable
    while u is defined:              # Construct the shortest path with a stack S
      insert u at the beginning of S # Push the vertex onto the stack
      u = prev[u]                    # Traverse from target to source
```

### Priority Queue

```py
function dijkstra(graph, source):
  dist[source] = 0

  create vertex priority queue Q

  for each vertex v in graph.vertices:
    if v not = source
      dist[v] = INFINITY
      prev[v] = UNDEFINED

    Q.add_with_priority(v, dist[v])

  while Q is not empty:
    u = Q.extract_min()
    for each neighbor v of u:
      alt <- dist[u] + graph.edges(u, v)
      if alt < dist[v]:
        dist[v] = alt
        prev[v] = u
        Q.decrease_priority(v, alt)

  return dist, prev
```

Now sequence S is the list of vertices constituting one of the shortest paths from source to target, or the empty sequence if no path exists.

A more general problem would be to find all the shortest paths between source and target (there might be several different ones of the same length). Then instead of storing only a single node in each entry of prev[] we would store all nodes satisfying the relaxation condition. For example, if both r and source connect to target and both of them lie on different shortest paths through target (because the edge cost is the same in both cases), then we would add both r and source to prev[target]. When the algorithm completes, prev[] data structure will actually describe a graph that is a subset of the original graph with some edges removed. Its key property will be that if the algorithm was run with some starting node, then every path from that node to any other node in the new graph will be the shortest path between those nodes in the original graph, and all paths of that length from the original graph will be present in the new graph. Then to actually find all these shortest paths between two given nodes we would use a path finding algorithm on the new graph, such as depth-first search. 

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/ca7f3f21-3605-4243-819a-15a293a606bf)

# Proof

Proof of Dijkstra's algorithm is constructed by induction on the number of visited nodes.

Invariant hypothesis: For each visited node v, dist[v] is the shortest distance from source to v, and for each unvisited node u, dist[u] is the shortest distance from source to u when traveling via visited nodes only, or infinity if no such path exists.

(Note: we do not assume dist[u] is the actual shortest distance for unvisited nodes, while dist[v] is the actual shortest distance)

The base case is when there is just one visited node, namely the initial node source, in which case the hypothesis is trivial.

Next, assume the hypothesis for k-1 visited nodes. Next, we choose u to be the next visited node according to the algorithm. We claim that dist[u] is the shortest distance from source to u.

To prove that claim, we will proceed with a proof by contradiction. If there were a shorter path, then there can be two cases, either the shortest path contains another unvisited node or not.

In the first case, let w be the first unvisited node on the shortest path.

By the induction hypothesis, the shortest path from source to u and w through visited node only has cost dist[u] and dist[w] respectively.

That means the cost of going from source to u through w has the cost of at least dist[w] + the minimal cost of going from w to u. As the edge costs are positive, the minimal cost of going from w to u is a positive number.

Also dist[u] < dist[w] because the algorithm picked u instead of w.

Now we arrived at a contradiction that dist[u] < dist[w] yet dist[w] + a positive number < dist[u].

In the second case, let w be the last but one node on the shortest path. That means dist[w] + Graph.Edges[w,u] < dist[u].

That is a contradiction because by the time w is visited, it should have set dist[u] to at most dist[w] + Graph.Edges[w,u].

For all other visited nodes v, the induction hypothesis told us dist[v] is the shortest distance from source already, and the algorithm step is not changing that.

After processing u it will still be true that for each unvisited node w, dist[w] will be the shortest distance from source to w using visited nodes only because if there were a shorter path that doesn't go by u we would have found it previously, and if there were a shorter path using u we would have updated it when processing u.

After all nodes are visited, the shortest path from source to any node v consists only of visited nodes, therefore dist[v] is the shortest distance.

# Python Code

Provided by Michael Sambol

```py
import heapq

infinity = float("inf")

def dijkstras_heap(G, start='A'):
    shortest_paths = {} 
    visited = {}
    heap = []

    for node in list(G.keys()):
        shortest_paths[node] = infinity
        visited[node] = False

    shortest_paths[start] = 0 
    visited[start] = True

    heapq.heappush(heap, (0, start))

    while heap:
        (distance, node) = heapq.heappop(heap)
        visited[node] = True

        for edge in G[node]:
            cost = edge[0]
            to_node = edge[1]

            if (not visited[to_node]) and (distance + cost < shortest_paths[to_node]):
                shortest_paths[to_node] = distance + cost
                heapq.heappush(heap, (shortest_paths[to_node], to_node))

    return shortest_paths
```
