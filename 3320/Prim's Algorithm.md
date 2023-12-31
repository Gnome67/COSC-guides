# Time Complexity

- Adjacency Matrix Searching: O(Vertices^2)
- Binary Heap & Adjacency List: O(Vertices-log-Vertices + Edges-log-Vertices)

# Description

Prim's algorithm is a greedy algorithm that finds a minimum spanning tree for a weighted undirected graph.

This means it finds a subset of the edges that forms a tree that includes every vertex, where the total weight of all the edges in the tree is minimized.

The algorithm operates by building this tree one vertex at a time, from an arbitrary starting vertex, at each step adding the cheapest possible connection from the tree to another vertex.

The algorithm starts with an empty spanning tree. The idea is to maintain two sets of vertices. The first set contains the vertices already included in the MST, and the other set contains the vertices not yet included.

At every step, it considers all the edges that connect the two sets and picks the minimum weight edge from these edges. After picking the edge, it moves the other endpoint of the edge to the set containing MST. 

# Breakdown

Simple:

1. Initialize a tree with a single vertex, chosen arbitrarily from the graph.
2. Grow the tree by one edge: Of the edges that connect the tree to vertices not yet in the tree, find the minimum-weight edge, and transfer it to the tree.
3. Repeat step 2 (until all vertices are in the tree)

Intermediate:

Step 1: Determine an arbitrary vertex as the starting vertex of the MST.
Step 2: Follow steps 3 to 5 till there are vertices that are not included in the MST (known as fringe vertex).
Step 3: Find edges connecting any tree vertex with the fringe vertices.
Step 4: Find the minimum among these edges.
Step 5: Add the chosen edge to the MST if it does not form any cycle.
Step 6: Return the MST and exit

Detailed:

1. Associate with each vertex v of the graph a number C[v] (the cheapest cost of a connection to v) and an edge E[v] (the edge providing that cheapest connection). To initialize these values, set all values of C[v] to +∞ (or to any number larger than the maximum edge weight) and set each E[v] to a special flag value indicating that there is no edge connecting v to earlier vertices.
2. Initialize an empty forest F and a set Q of vertices that have not yet been included in F (initially, all vertices).
3. Repeat the following steps until Q is empty:
- Find and remove a vertex v from Q having the minimum possible value of C[v]
- Add v to F
- Loop over the edges vw connecting v to other vertices w. For each such edge, if w still belongs to Q and vw has smaller weight than C[w], perform the following steps:
- Set C[w] to the cost of edge vw
- Set E[w] to point to edge vw.
- Return F, which specifically includes the corresponding edges in E

As described above, the starting vertex for the algorithm will be chosen arbitrarily, because the first iteration of the main loop of the algorithm will have a set of vertices in Q that all have equal weights, and the algorithm will automatically start a new tree in F when it completes a spanning tree of each connected component of the input graph. The algorithm may be modified to start with any particular vertex s by setting C[s] to be a number smaller than the other values of C (for instance, zero), and it may be modified to only find a single spanning tree rather than an entire spanning forest (matching more closely the informal description) by stopping whenever it encounters another vertex flagged as having no associated edge.

Expert:

Follow the given steps to utilize the Prim’s Algorithm mentioned above for finding MST of a graph:

- Create a set mstSet that keeps track of vertices already included in MST.
- Assign a key value to all vertices in the input graph. Initialize all key values as INFINITE. Assign the key value as 0 for the first vertex so that it is picked first.
- While mstSet doesn’t include all vertices 
  - Pick a vertex u that is not there in mstSet and has a minimum key value. 
  - Include u in the mstSet. 
  - Update the key value of all adjacent vertices of u. To update the key values, iterate through all adjacent vertices. 
    - For every adjacent vertex v, if the weight of edge u-v is less than the previous key value of v, update the key value as the weight of u-v.

The idea of using key values is to pick the minimum weight edge from the cut. The key values are used only for vertices that are not yet included in MST, the key value for these vertices indicates the minimum weight edges connecting them to the set of vertices included in MST.

# Pseudocode

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/9adfba56-15c2-422e-ab21-00871e6fd5e1)

# Proof

- Let P be a connected, weighted graph
- At every iteration of Prim's algorithm, an edge must be found that connects a vertex in a subgraph to a vertex outside the subgraph
- Since P is connected, there will always be a path to every vertex
- The output Y of Prim's algorithm is a tree, because the edge and vertex added to tree Y are connected
- Let Y1 be a minimum spanning tree of graph P. If Y1=Y then Y is a minimum spanning tree
- Otherwise, let e be the first edge added during the construction of tree Y that is not in tree Y1, and V be the set of vertices connected by the edges added before edge e
- Then one endpoint of edge e is in set V and the other is not. Since tree Y1 is a spanning tree of graph P, there is a path in tree Y1 joining the two endpoints
- As one travels along the path, one must encounter an edge f joining a vertex in set V to one that is not in set V
- Now, at the iteration when edge e was added to tree Y, edge f could also have been added and it would be added instead of edge e if its weight was less than e, and since edge f was not added, we conclude that
  w(f) >= w(e)
- Let tree Y2 be the graph obtained by removing edge f from and adding edge e to tree Y1
- It is easy to show that tree Y2 is connected, has the same number of edges as tree Y1, and the total weights of its edges is not larger than that of tree Y1.
- Therefore it is also a minimum spanning tree of graph P and it contains edge e and all the edges added before it during the construction of set V
- Repeat the steps above and we will eventually obtain a minimum spanning tree of graph P that is identical to tree Y
- This shows Y is a minimum spanning tree. The minimum spanning tree allows for the first subset of the sub-region to be expanded into a smaller subset X, which we assume to be the minimum

# Visualization

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/371e12d0-c5c5-4304-b6e5-4694d7b7d4d9)

1. Pick an arbitrary node (for this example, we'll start with A. We'll add A to our visited list
- visited: {A}
2. Let's look at all possible edges reachable from A
- B: 2 away from A
- C: 3 away from A
- D: 3 away from A
3. Prim's is a greedy algorithm, so we will take route A -> B.
- visited: {A, B}
- cost: 2
4. Let's look at all possible edges reachable from A or B
- C: 3 away from A, 4 away from B
- D: 3 away from A
- E: 3 waay from B
5. Let's pick route A -> C
- visited: {A, B, C}
- cost: 5
6. Let's look at all possible edges reachable from A or B or C
- D: 3 away from A, 5 away from C
- E: 1 away from C, 3 away from B
- F: 6 away from F
7. Let's take route C -> E
- visited: {A, B, C, E}
- cost: 6
8. Let's look at all possible edges reachable from A or B or C or E
- D: 3 away from A, 5 away from C
- F: 6 away from C, 8 away from E
9. Let's take route A -> D
- visited: {A, B, C, E, D}
- cost: 9
10. At this point, B -> E is the smallest unique route in the graph that has not been taken. However, B and E are both visited, so we will skip this.
11. Let's look at all the possible routes reachable from A or B or C or E or D
- F: 6 away from C, 7 away from D, 8 away from E
12. Let's take route C -> F
- visited: {A, B, C, E, D, F}
- cost: 15
13. Finally, take route F -> G
- visited: {A, B, C, E, D, F, G}
- cost: 24

***NOTE: This MST ordering is not the only solution due to duplicate weights for routes. If every route had a unique weight, there would be only one solution.***

# Python Code

Provided by Michael Sambol

```py
import heapq

def prims(G, start='A'):
    unvisited = list(G.keys())
    visited = []
    total_cost = 0
    MST = []

    unvisited.remove(start)
    visited.append(start)

    heap = G[start]
    heapq.heapify(heap)

    while unvisited:
        (cost, n2, n1) = heapq.heappop(heap)
        new_node = None

        if n1 in unvisited and n2 in visited:
            new_node = n1
            MST.append((n2, n1, cost))

        elif n1 in visited and n2 in unvisited:
            new_node = n2
            MST.append((n1, n2, cost))

        if new_node != None:
            unvisited.remove(new_node)
            visited.append(new_node)
            total_cost += cost

            for node in G[new_node]:
                heapq.heappush(heap, node)

    return MST, total_cost
```
