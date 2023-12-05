Kruskal's algorithm finds a minimum spanning forest of an undirected edge-weighted graph. If the graph is connected, it finds a minimum spanning tree. It is a greedy algorithm that in each step adds to the forest the lowest-weight edge that will not form a cycle. The key steps of the algorithm are sorting and the use of a disjoint-set data structure to detect cycles. Its running time is dominated by the time to sort all of the graph edges by their weight.

A minimum spanning tree of a connected weighted graph is a connected subgraph, without cycles, for which the sum of the weights of all the edges in the subgraph. For a disconnected graph, a minimum spanning forest is composed of a minimum spanning tree for each connected component.

# Algorithm Breakdown

In Kruskal’s algorithm, sort all edges of the given graph in increasing order. Then it keeps on adding new edges and nodes in the MST if the newly added edge does not form a cycle. It picks the minimum weighted edge at first and the maximum weighted edge at last. Thus we can say that it makes a locally optimal choice in each step in order to find the optimal solution.

Simple:

1. Sort all the edges in non-decreasing order of their weight. 
2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If the cycle is not formed, include this edge. Else, discard it. 
3. Repeat step#2 until there are (V-1) edges in the spanning tree.

Detailed:

The algorithm performs the following steps:
1. Create a forest (a set of trees) initially consisting of a separate single-vertex tree for each vertex in the input graph.
2. Sort the graph edges by weight.
3. Loop through the edges of the graph, in ascending sorted order by their weight. For each edge:
- Test whether adding the edge to the current forest would create a cycle
- If not, add the edge to the forest, combining two trees into a single tree

At the termination of the algorithm, the forest forms a minimum spanning forest of the graph. If the graph is connected, the forest has a single component and forms a minimum spanning tree.
Kruskal’s algorithm to find the minimum cost spanning tree uses the greedy approach. The Greedy Choice is to pick the smallest weight edge that does not cause a cycle in the MST constructed so far.

# Pseudocode

The following code is implemented with a disjoint-set data structure. It represents the forest F as a set of undirected edges, and uses the disjoint-set data structure to efficiently determine whether two vertices are part of the same tree.
```py
function kruskal(G):
  F = 0
  for each in v in G(v):
    make_set(v)
  for each {u, v} in G(E) ordered by weight({u, v}), increasing:
    if FIND_SET(u) not = FIND_SET(v):
      F = F & { {u, v} }
      union(FIND_SET(u)
  return F
```

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/d2df87e2-463f-4877-bb44-205d32b492c0)

# Proof:

The proof consists of two parts. First, it is proved that the algorithm produces a spanning tree. Second, it is proved that the constructed spanning tree is of minimal weight.

1. Spanning tree
- Let G be a connected, weighted graph and let Y be the subgraph of G produced by the algorithm
- Y cannot have a cycle, as by definition an edge is not added if it results in a cycle
- Y cannot be disconnected, since the first encountered edge that joins two components of Y would have been added by the algorithm
- Thus, Y is a spanning tree of G

Minimality
- We show that the following proposition P is true by induction:
- If F is the set of edges chosen at any stage of the algorithm, then there is some minimum spanning tree that contains F and none of the edges rejected by the algorithm
- Clearly P is true at the beginning, when F is empty: any minimum spanning tree will do, and there exists one because a weighted connected graph always has a minimum spanning tree
- Now assume P is true for some non-final edge set F and let T be a minimum spanning tree that contains F
- If the next chosen edge e is also in T, then P is true for F + e
- Otherwise, if e is not in T then T + e has a cycle C. This cycle contains edges which do not belong to F, since e does not form a cycle when added to F but does in T
- Let f be an edge which is in C but not in F + e. Note that f also belongs to T, and by P, it has not been considered by the algorithm
- f must therefore have a weight at least as large as e
- Then T − f + e is a tree, and it has the same or less weight as T
- However since T is a minimum spanning tree then this new graph has the same weight as T, otherwise we get a contradiction and T would not be a minimum spanning tree
- So T − f + e is a minimum spanning tree containing F + e and again P holds.
- Therefore, by the principle of induction, P holds when F has become a spanning tree, which is only possible if F is a minimum spanning tree itself

# Python Code

Provided by Michael Sambol
```py
from unionfind import unionfind

def kruskals(G):
    total_cost = 0
    MST = []

    num_nodes, edges = load_edges(G)
    uf = unionfind(num_nodes)

    for edge in edges:
        cost, n1, n2 = edge[0], edge[1], edge[2]

        if not uf.issame(conv_char(n1), conv_char(n2)):
            total_cost += cost
            uf.unite(conv_char(n1), conv_char(n2))
            MST.append((n1, n2, cost))

    return MST, total_cost
```
