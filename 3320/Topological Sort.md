- A sorting algorithm that can only be applied to directed acyclic graphs (DAGS). The algorithm will sort the nodes of a DAG into topological order.
- a topological order is one in which each node appears before each of the nodes its directed to. All edges are essentially ordered in the same direction.
- NOTE: a DAG can have more than one topological ordering. These orderings are **NOT** unique.

A Directed Acyclic Graph (DAG) is a graph in which there are NO cycles (hence the Acyclic in the name). In addition, to prevent cycles, all nodes are directed in such a way, that a single-direction path can be traced. A graph which contains a cycle cannot have a valid topological sort.

You can verify your graph is a DAG by using Tarjan's Strongly Connected Components algorithm.

![Graphs3](https://github.com/Gnome67/COSC-guides/assets/102388813/bbfb2124-d28a-406e-9c44-460346ab4a44)

Above is a DAG and one of its topological orderings. Notice how node 1 appears before both of the nodes it points to. This rule applies to the others. You also want to start with a node that doesn't have any dependencies on any other node, to establish a consistent order for nodes based on their dependencies.

By definition, all rooted trees have a topological ordering since they do not contain any cycles

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/13778810-f9c7-4814-a1f2-3cae8aa9887b)

The topological order for the above tree from left to right is: [A, C, D, E, B, G, H, K, J, F, I]

# Algorithm:
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

# Breakdown:
1. Pick an unvisited node
2. Do a DFS, beginning with the selected node and explore only the unvisited nodes.
3. On the recursive callback of the DFS, add the current node to the topological ordering in reverse order

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/6d8427a0-49c6-494e-b872-142e935f3bf6)

Topological Sort List: [?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?]

***NOTE: TOPOLOGICAL SORTS ARE NOT UNIQUE. THIS GRAPH HAS MANY SOLUTIONS. YOU ARE NOT WRONG IF YOU END UP WITH A DIFFERENT ORDERING THAN ME***

- Let's pick node H arbritrarily. Let's take path H -> J to begin with, and explore down that route.
- H -> J -> M
- There's nowhere else from M, so let's backtrack and make J, L, M (in that order) our final values in the topological sort
- [?, ?, ?, ?, ?, ?, ?, ?, ?, ?, J, L, M]
- Let's take route I. I is directed only towards L, which we have visited, so let's backtrack and add I to the end of the unknown topological sort
- [?, ?, ?, ?, ?, ?, ?, ?, ?, I, J, L, M]
- H can not visit any other unvisited nodes, so let's add it to the sort
- [?, ?, ?, ?, ?, ?, ?, ?, H, I, J, L, M]
- Let's arbitrarily pick E now, and start with path F.
- E -> F -> K.
- K visits J, which we already visited, so we add F and K to the end of our unknown topological sort.
- [?, ?, ?, ?, ?, ?, F, K, H, I, J, L, M]
- Let's backtrack and go through path D now.
- E -> D -> G.
- G can not visit any new nodes and neither can D, so let's add them to the end of our unknown topological sort.
- [?, ?, ?, ?, D, G, F, K, H, I, J, L, M]
- let's take path A, and it can't visit any new nodes, so we put E and A at the end
- [?, ?, E, A, D, G, F, K, H, I, J, L, M]
- Finally, I will arbitrarily choose C, which only goes to B as an unvisited node, so we'll add them
- [C, B, E, A, D, G, F, K, H, I, J, L, M]

Keep in mind there is more than one ordering of this set. An example of another set that could be used is [C, B, E, F, K, A, D, G, H, I, J, L, M].

Time Complexity: O(Vertices + Edges)

# Kahn's Algorithm

- Repeatedly removes nodes without dependencies from the graph and add them to the topological ordering.
- As nodes without dependencies (and their outgoing edges) are removed from the graph, new nodes without dependencies should become free.
- We repeat removing nodes without dependencies from the graph until all nodes are processed, or a cycle is discovered.

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/c894aa8a-3f77-4ffe-8cb1-89a473dc91b6)

Topological ordering: [?, ?, ?, ?, ?, ?]

***NOTE: TOPOLOGICAL SORTS ARE NOT UNIQUE. THIS GRAPH HAS MANY SOLUTIONS. YOU ARE NOT WRONG IF YOU END UP WITH A DIFFERENT ORDERING THAN ME***

- We start at node 2 because it has no dependencies. We add it to the sort and remove it from the graph.
- [2, ?, ?, ?, ?, ?]
- Node 0 and 4 don't have any dependencies since node 2 was removed from the graph, so choose to add either of them next but regardless of your choice, remove your selected node from the graph
- [2, 0, ?, ?, ?, ?] or [2, 4, ?, ?, ?, ?]
- Now add the node you didn't add (4 if you added 0, or 0 if you added 4) to the sort next and remove it from the graph
- [2, 0, 4, ?, ?, ?] or [2, 4, 0, ?, ?, ?]
- 3 and 5 both have no dependencies since 0 and 4 were removed, so choose to add either of them next
- [2, 0, 4, 3, ?, ?] or [2, 0, 4, 5, ?, ?] or [2, 4, 0, 3, ?, ?] or [2, 4, 0, 5, ?, ?]
- Then add the node you didn't add before (5 if you added 3, or 3 if you added 5) to the sort next and remove it from the graph.
- [2, 0, 4, 3, 5, ?] or [2, 0, 4, 5, 3, ?] or [2, 4, 0, 3, 5, ?] or [2, 4, 0, 5, 3, ?]
- 1 is left, so add it and remove from the graph.
- [2, 0, 4, 3, 5, 1] or [2, 0, 4, 5, 3, 1] or [2, 4, 0, 3, 5, 1] or [2, 4, 0, 5, 3, 1]

# Example of Kahn's Algorithm

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/2e1a1946-d8b4-4f4d-9e32-8f8cb2a60d1d)

Topological ordering: [?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?]

To make this easier, let's count how many dependencies each node has
0. 0
1. 1
2. 2
3. 1
4. 3
5. 1
6. 3
7. 1
8. 2
9. 0
10. 1
11. 1
12. 2
13. 0

Let's put the nodes that have no dependencies in the queue first.
- Queue: {0, 9, 13}
- Note: the queue will depend on which value you input first. You could also do {9, 0, 13} or {13, 0, 9} or {9, 13, 0}, etc. I chose in ascending order for simplicity sake
Let's add 0 (or 9 or 13) to our sort, and subtract 1 from the dependencies of any nodes that require 0 (or 9, but not 13 since nothing depends on it).
- [0, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?]
- [9, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?]
- [13, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?]

Dependency chart
1. 1
2. 1 (from 2 or 9, but not both at the same time YET)
3. 0 (if you chose 0)
4. 3
5. 1
6. 2 (if you chose 0)
7. 1
8. 2
10. 0 (if you chose 9)
11. 1
12. 2

Let's add the values that have 0 dependencies to the queue
- Queue: (if you chose 0) {9, 13, 3}
- Queue: (if you chose 9) {0, 13, 10}
- Queue: (if you chose 13) {0, 9}
- Note: for simplicity sake, since 13 has no dependencies and is not dependant on anything, I will put it at the front of either topological ordering as such:
- 0: [13, 0, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?]
- 9: [13, 9, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?]
- Now add the next values in the queue (which should be the value you didn't start with) and remove from the graph accordingly
- 0: [13, 0, 9, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?]
- 9: [13, 9, 0, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?]
- 0: [13, 0, 9, 3, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?]
- 9: [13, 9, 0, 10, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?]
- And update the dependency list accordingly since we are removing 3 or 10 from the list

1. 0 (if you chose 0 -> 3)
2. 0 (from 0 and 9 being removed)
4. 2 (if you chose 0 -> 3)
5. 1
6. 2 (if you chose 0 or 9 -> 10, but not both at the same time YET)
7. 1
8. 2
11. 1
12. 2

- The queue will be updated accordingly (since 9 has been added to the 0-start queue, 10 will be in the 0-start queue)
- Queue: (if you chose 0) {2, 10, 1}
- Queue: (if you chose 9) {2}
- Note: for sanity, going to remove the 9-start queue
- Now add the next values in the queue and remove them from the graph accordingly
- [13, 0, 9, 3, 2, ?, ?, ?, ?, ?, ?, ?, ?, ?]
- Update the dependency list

4. 2
5. 1
6. 1
7. 1
8. 2
11. 1
12. 2

- Update the queue
- Queue: {1}
- [13, 0, 9, 3, 2, 10, ?, ?, ?, ?, ?, ?, ?, ?]
- Update the dependency list

4. 2
5. 1
6. 0
7. 1
8. 2
11. 1
12. 2

- Update the queue
- Queue: {1, 6}
- [13, 0, 9, 3, 2, 10, 1, ?, ?, ?, ?, ?, ?, ?]
- Update the dependency list

4. 1
5. 1
7. 1
8. 2
11. 1
12. 2

- Update the queue
- Queue: {6}
- [13, 0, 9, 3, 2, 10, 1, 6, ?, ?, ?, ?, ?, ?]
- Update the dependency list

4. 1
5. 1
7. 0
8. 2
11. 0
12. 2

- Update the queue
- Queue: {7, 11}
- [13, 0, 9, 3, 2, 10, 1, 6, 7, ?, ?, ?, ?, ?]
- Update the dependency list

4. 0
5. 1
8. 2
12. 1

- Update the queue
- Queue: {11, 4}
- [13, 0, 9, 3, 2, 10, 1, 6, 7, 11, ?, ?, ?, ?]
- Update the dependency list

5. 1
8. 2
12. 0

- Update the queue
- Queue: {4, 12}
- [13, 0, 9, 3, 2, 10, 1, 6, 7, 11, 4, ?, ?, ?]
- Update the dependency list

5. 0
8. 1

- Update the queue
- Queue: {12, 5}
- [13, 0, 9, 3, 2, 10, 1, 6, 7, 11, 4, 12, ?, ?]
- Update the dependency list

8. 0

- Update the queue
- Queue: {5, 8}
- [13, 0, 9, 3, 2, 10, 1, 6, 7, 11, 4, 12, 5, ?]
- [13, 0, 9, 3, 2, 10, 1, 6, 7, 11, 4, 12, 5, 8]

### Pseudocode

```py
# 'g' is a directed acyclic graph represented as an adjacency list
function FindTopologicalOrdering(g):
  n = g.size();
  in_degree = [0, 0, ..., 0, 0] # size n
  for (i = 0; i < n; i++):
    for (to in g[i]):
      in_degree[to] = in_degree[to] + 1
# 'q' always contains the set nodes with no incoming edges.
q = ... # empty integer queue data structure
for (i = 0; i < n; i++):
  if (in_degree[i] == 0):
    q.enqueue(i)

index = 0
order = [0,0,...0,0] # size n
while (!q.isEmpty()):
  at = q.dequeue()
  order[index++] = at
  for (to in g[at])
  in_degree[tp] = in_degree[to] - 1
  if in_degree[to] == 0:
    q.enqueue(to)
if index != n:
  return null # Graph is Cyclic
return order
```

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

# Alien Dictionary (Leetcode 269)

You are given a list of strings `words` from a dictionary where the strings in `words` are sorted lexicographically. Return a string of the unique letters sorted in lexicographically increasing order. If there is no solution, return "". If there are multiple solutions, return any of them.

Example:

Input: words = ["wrt", "wrtf", "er", "ett", "rftt"]

Output: "wertf"

```py
def alienOrder(self, words: List[str]) -> str:
        adj = {char: set() for word in words for char in word}

        for i in range(len(words) - 1):
            w1, w2 = words[i], words[i + 1]
            minLen = min(len(w1), len(w2))
            if len(w1) > len(w2) and w1[:minLen] == w2[:minLen]:
                return ""
            for j in range(minLen):
                if w1[j] != w2[j]:
                    print(w1[j], w2[j])
                    adj[w1[j]].add(w2[j])
                    break

        visited = {}  # {char: bool} False visited, True current path
        res = []

        def dfs(char):
            if char in visited:
                return visited[char]

            visited[char] = True

            for neighChar in adj[char]:
                if dfs(neighChar):
                    return True

            visited[char] = False
            res.append(char)

        for char in adj:
            if dfs(char):
                return ""

        res.reverse()
        return "".join(res)
```
