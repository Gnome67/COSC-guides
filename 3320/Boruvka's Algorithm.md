Boruvka's algorithm is a greedy algorithm for finding a minimum spanning tree in a graph with distinct edge weights (in which none of the edges have the same value), or a minimum spanning forest in the case of a graph that is not connected.
The goal of the algorithm is to connect “components” using the shortest edge between components. It begins with all of the vertices considered as separate components.

# Algorithm Breakdown:

1. Input is a connected, weighted and un-directed graph.
2. Initialize all vertices as individual components (or sets).
3. Initialize MST as empty.
4. While there are more than one components, do following for each component.
      -  Find the closest weight edge that connects this component to any other component.
      -  Add this closest edge to MST if not already added.  
5. Return MST.

The algorithm begins by finding the minimum-weight edge incident to each vertex of the graph, and adding all of those edges to the forest. Then, it repeats a similar process of finding the minimum-weight edge from each tree constructed so far to a different tree, and adding all of those edges to the forest. Each repetition of this process reduces the number of trees, within each connected component of the graph, to at most half of this former value, so after logarithmically many repetitions the process finishes. When it does, the set of edges it has added forms the minimum spanning forest. 

# Pseudocode

The following pseudocode illustrates a basic implementation of Borůvka's algorithm. In the conditional clauses, every edge uv is considered cheaper than "None". The purpose of the completed variable is to determine whether the forest F is yet a spanning forest.

If edges do not have distinct weights, then a consistent tie-breaking rule must be used, e.g. based on some total order on vertices or edges. This can be achieved by representing vertices as integers and comparing them directly; comparing their memory addresses; etc. A tie-breaking rule is necessary to ensure that the created graph is indeed a forest, that is, it does not contain cycles. For example, consider a triangle graph with nodes {a,b,c} and all edges of weight 1. Then a cycle could be created if we select ab as the minimal weight edge for {a}, bc for {b}, and ca for {c}. A tie-breaking rule which orders edges first by source, then by destination, will prevent creation of a cycle, resulting in the minimal spanning tree {ab, bc}.

```py
# input: A weighted undirected graph G = (V, E).
# output: F, a minimum spanning forest of G.
# Initialize a forest F to (V, E') where E' = {}.

completed = false
while completed == false:
  Find the connected components of F and assign to each vertex its component
  Initialize the cheapest edge for each component to "None"
  for each edge uv in E: # where u and v are in different components of F
    let wx be the cheapest edge for the component of u
    if is_preferred_over(uv, wx):
      Set uv as the cheapest edge for the component of u
    let yz be the cheapest edge for the component of v
    if is_preferred_over(uv, yz):
      Set uv as the cheapest edge for the component of v
  if all components have cheapest edge set to "None":
    completed = true # no more trees can be merged -- we are finished
  else
    completed = false
    for each component whose cheapest edge is not "None":
      Add its cheapest edge to E'

function is_preferred_over(edge1, edge2):
  return (edge2 is "None") or (weight(edge1) < weight(edge2)) or (weight(edge1) = weight(edge2) and tie_breaking_rule(edge1, edge2))

function tie_breaking_rule(edge1, edge2):
  The tie-breaking rule; returns true if and only if edge1 is preferred over edge2 in the case of a tie.
```

As an optimization, one could remove from G each edge that is found to connect two vertices in the same component, so that it does not contribute to the time for searching for cheapest edges in later components.

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/ec0a1c26-87fc-4923-9936-3bcf304e4209)

# Proof

Boruvka’s Algorithm is based upon the following lemma:

Let v ∈ V be any vertex in G. The minimum spanning tree for G must contain the edge (v, w) that is the minimum weight edge incident on v.
This can be proved by contradiction. Assume the MST does not contain the minimum weight edge incident on v. If so, there must be another edge connecting v to our MST. However, if we remove that edge, and add the minimum weight edge (we need to prevent cycles, this is an MST
