A BFS is an algorithm for searching all vertices of a graph or tree data structure while avoiding cycles.

As you traverse, nodes are categorized as:
1. Visited
2. Unvisited
The algorithm uses a queue to traverse in a level order traversal.

Implementation:
- Queue: O(Vertices + Edges)
- Priority Queue: O(Vertices + Edges * log(Edges))

# Iterative Implementation
1. Push a vertex into the queue
2. Pop from the front of the queue and add it to the visited list.
3. Create a list of the vertex's adjacent nodes. Add the unvisited to the queue.
4. Repeat steps 2 and 3 until the queue is empty.

Pseudocode:
```py
# create a queue Q
function bfs(v):
  visited[v] = true
  push v into Q
  while Q is not empty:
    u = q.pop()
    if u is not visited:
      visited[u] = true
    for node in neighbors(u):
      q.push(node)
```

# Recursive Implementation
1. Pass a queue of vertices
2. Iterate across each node in a level of the graph.
3. Visit all of that node's unvisited neighbors.
4. Add the visited neighbors to the next queue.
5. Recurse to the next level.

```py
level = [v]
function bfs(level):
  next_level = []
  for node in level:
    for neighbor in neighbors(node):
      if node is visited:
        visited[neighbor] = true
        next_level.append(neighbor)
  bfs(next_level)
```

# Tracing

Use the FIFO Property of the queue to trace the level order of a BFS.

![Graph2](https://github.com/Gnome67/COSC-guides/assets/102388813/720a6b52-f43b-4965-8eaf-4edd36643c7d)

visited: [0]
- We first add our source node into the visited array

queue: [1,2,3]
- All adjacent nodes are added to the queue

visited: [0,1]
- We pop the front of the queue and add it to the visited array

queue: [2,3]

visited: [0,1,2]

queue: [3]

visited: [0,1,2,3]

queue: [4]

visited: [0,1,2,3,4]

queue: []
