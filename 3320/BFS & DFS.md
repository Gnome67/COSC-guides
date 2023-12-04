# DFS

- Utilizes a stack. Either our own or the call stack via recursion (Last In First Out)
- Utilizes backtracking, complete search, exhausing possible paths
- Goes Deep
- Time: O(|Vertices| + |Edges|)
- Space: O(|Vertices|)

Code:
```java
public static void dfs Print(Node start)
{
  Stack<Node> stack = new Stack<>();
  Set<Node> seen = new HashSet<>(); //Choose the data structure
  stack.push(start); //Add start to the search
  While(!stack.isEmpty())
  {
    Node curr = stack.pop(); //pull a node
    if(!seen.contains(curr)) //process if not seen
    {
      seen.add(curr);
      System.out.println(curr);
    }
    for(Node adjacent : curr.adjacents) //add unseen children
    {
      if(!seen.contains(adjacent)
      {
        stack.push(adjacent);
      }
    }
  }
}
```

Visualization:

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/72253854-fae0-4811-9667-2c007585ab6f)

- We start at A, so we mark it as seen.
- seen: {A}
- output: {A}
- We add B, C, D, E to the stack because they are next.
- stack: (from top to bottom) {B, C, D, E}
- B (the top of the stack) has not yet been processed, so we traverse to B and add it to seen and output, and pop from stack
- seen: {A, B}
- output: {A, B}
- stack: (from top to bottom) {C, D, E}
- B has three nodes it can visit: A, C, and G. We have already processed A, so we add C and G to the stack
- stack: (from top to bottom) {C, G, C, D, E}
- Note: We have two C's. We don't need to worry about this because we will never process more than one of any letter, due to us using a set.
- C (the top of the stack) has not yet been processed, so we traverse to C and add it to seen and output, and pop from stack
- seen: {A, B, C}
- output: {A, B, C}
- stack: {G, C, D, E}
- C has three nodes it can visit: A, B, and D. We have already processed A and B, so we add D to the stack.
- stack: {D, G, C, D, E}
- D (the top of the stack) has not yet been processed, so we traverse to D and add it to seen and output, and pop from stack
- seen: {A, B, C, D}
- output: {A, B, C, D}
- stack: {G, C, D, E}
- D has four nodes it can visit: A, C, E, H. We have already processed A and C, so we add E and H to the stack.
- stack: {E, H, G, C, D, E}
- E (the top of the stack) has not yet been processed, so we traverse to E and add it to seen and output, and pop from stack
- seen: {A, B, C, D, E}
- output: {A, B, C, D, E}
- stack: {H, G, C, D, E}
- E has three nodes it can visit: A, D, F. We have already process A and D, so we can add F to the stack.
- stack: {F, H, G, C, D, E}
- F (the top of the stack) has not yet been processed, so we traverse to F and add it to seen and output, and pop from stack
- seen: {A, B, C, D, E, F}
- output: {A, B, C, D, E, F}
- stack: {H, G, C, D, E}
- F has three nodes it can visit: G and H, neither of which have been processed. So let's add them to our stack
- stack: {G, H, H, G, C, D, E}
- G (the top of our stack) has not yet been processed, so we traverse to G and add it to the seen and output, and pop from stack
- seen: {A, B, C, D, E, F, G}
- output: {A, B, C, D, E, F, G}
- stack: {H, H, G, C, D, E}
- Both of the nodes G can visit have already been processed so we just move to H (the top of our stack)
- H (the top of our stack) has not yet been processed, so we traverse to H and add it to the seen and output, and pop from stack
- seen: {A, B, C, D, E, F, G, H}
- output: {A, B, C, D, E, F, G, H}
- stack: {H, G, C, D, E}
- Both of the nodes H can visit have already been processed, so we just move on to the next value in the stack.
- The rest of the values have been processed so we empty out the stack
- stack: {}
- final seen: {A, B, C, D, E, F, G, H}
- final output: {A, B, C, D, E, F, G, H}

# BFS
- Iterative with a Queue (First In First Out)
- Utilizes checking for a path between nodes, finding "hops" or distance out, or "levels" away
- Goes Wide
- Time: O(|Vertices| + |Edges|)
- Space: O(|Vertices|)

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/f49b84f1-609c-4cd4-bb4d-5f2c8356941b)

In BFS, we start at the root C, and then expand one layer out to B, D, E, F. We then expand one layer out further to A, G, and H.

Code:
```java
public static void bfsPrint(Node start)
{
  Queue<Node> queue = new LinkedList<>();
  Set<Node> seen = new HashSet<>(); //choose the data structure
  queue.add(start)
  while(!queue.isEmpty())
  {
    Node curr = queue.poll(); //pull a node
    if(!seen.contains(curr)) //process if not seen
    {
      seen.add(curr);
      System.out.println(curr);
    }
    for(Node adjacent: curr.adjacents) //Add unseen children
    {
      if(!seen.contains(adjacent))
      {
        queue.add(adjacent);
      }
    }
  }
}
```

Visualization:

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/72253854-fae0-4811-9667-2c007585ab6f)

- We start at node A
- seen: {A}
- output: {A}
- queue: (from back to front) {E, D, C, B}
- B is in front of the queue, so we process B and remove it from the queue
- seen: {A, B}
- output: {A, B}
- queue: (from back to front) {E, D, C}
- B can visit A, C, and G. A has already been processed, so we add C and G to the queue
- queue: (from back to front) {G, C, E, D, C}
- Note: We have two C's. We don't need to worry about this because we will never process more than one of any letter, due to us using a set.
- C is in front of the queue, so we process C and remove it from the queue
- seen: {A, B, C}
- output: {A, B, C}
- queue: (from back to front) {G, C, E, D}
- C can visit A, B, and D. A and B have already been processed, so we add them to the queue.
- queue: (from back to front) {D, G, C, E, D}
- D (the front of the queue) has not yet been processed, so we process it and add it to seen and output, and pop it from the queue.
- seen: {A, B, C, D}
- output: {A, B, C, D}
- queue: (from back to front) {D, G, C, E}
- D can visit A, C, E, and H. A and C have been processed, so we add E and H to the queue
- queue: (from back to front) {H, E, D, G, C, E}
- E (the front of the queue) has not yet been processed, so we add it to seen/output, and pop from queue
- seen: {A, B, C, D, E}
- output: {A, B, C, D, E}
- queue: (from back to front) {H, E, D, G, C}
- E can visit A, D, and F, A and D have already been processed so we just add F.
- queue: (from back to front) {F, H, E, D, G, C}
- C has been processed, so we remove it
- queue: (from back to front) {F, H, E, D, G}
- G has NOT been processed, so we process it and remove from queue.
- seen: {A, B, C, D, E, G}
- output: {A, B, C, D, E, G}
- queue: (from back to front) {F, H, E, D}
- G can visit B and F, and F has not been processed while B has, so we only add F to the queue
- queue: (from back to front) {F, F, H, E, D}
- skip D and E as they've already been processed
- queue: (from back to front) {F, F, H}
- We add F and then H (hopefully you can do this part yourself)
- seen: {A, B, C, D, E, G, H, F}
- output: {A, B, C, D, E, G, H, F}
- queue: {}

![image](https://github.com/Gnome67/COSC-guides/assets/102388813/8388fae7-f0fa-4dc6-9495-9337f0b0d914)


