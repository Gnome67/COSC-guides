![image](https://github.com/Gnome67/COSC-guides/assets/102388813/9a02332e-2081-44a2-b35a-1bf518cf2321)

# Text Segmentation

```cpp
bool wordBreak(string s)
{
    int n = s.size();
    if (n == 0)
        return true;
// Create the DP table to store results of subproblems. The value dp[i] will be true if str[0..i] can be segmented into dictionary words, otherwise false.
    vector<bool> dp(n + 1, 0); // Initialize all values as false.
 
// matched_index array represents the indexes for which dp[i] is true. Initially only -1 element is present in this array.
    vector<int> matched_index;
    matched_index.push_back(-1); 
    for (int i = 0; i < n; i++) {
        int msize = matched_index.size();
// Flag value which tells that a substring matches with given words or not.
        int f = 0; 
// Check all the substring from the indexes matched earlier. If any of that substring matches than make flag value = 1;
        for (int j = msize - 1; j >= 0; j--) {
// sb is substring starting from matched_index[j] + 1  and of length i - matched_index[j]
            string sb = s.substr(matched_index[j] + 1, i - matched_index[j]);
            if (dictionaryContains(sb)) {
                f = 1;
                break;
            }
        } 
// If substring matches than do dp[i] = 1 and push that index in matched_index array.
        if (f == 1) {
            dp[i] = 1;
            matched_index.push_back(i);
        }
    }
    return dp[n - 1];
}
Longest Increasing Subsequence
int lis(int arr[], int n)
{
    int lis[n];
    lis[0] = 1;
    for (int i = 1; i < n; i++) {
        lis[i] = 1;
        for (int j = 0; j < i; j++)
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
                lis[i] = lis[j] + 1;
    }
    return *max_element(lis, lis + n);
}
```

# Longest Increasing Subsequence

```py
function longest_increasing_subsequence(n, nums):
  LIS = n length array initialized to [0...0]
  LIS[0] = 1
  for i from 1 to n:
    for j in i:
      if nums[j] < nums[i] and LIS[j] > LIS[i]:
        LIS[i] = LIS[j]
      LIS[i] += 1
  return LIS
```

# Edit Distance

```cpp
    int editDistance(string str1, string str2)
    {
        int m = str1.size();
        int n = str2.size();
        int previous;
        vector<int> curr(n + 1, 0);
 
        for (int j = 0; j <= n; j++) {
            curr[j] = j;
        }
        for (int i = 1; i <= m; i++) {
            previous = curr[0];
            curr[0] = i;
            for (int j = 1; j <= n; j++) {
                int temp = curr[j];
                if (str1[i - 1] == str2[j - 1]) {
                    curr[j] = previous;
                }
                else {
                    curr[j] = 1
                              + min({ previous, curr[j - 1],
                                      curr[j] });
                }
                previous = temp;
            }
        }
        return curr[n];
    }
```

# Leetcode 53

```cpp
int maxSubArray(vector<int>& n) {
        int ma=INT_MIN;
        int sum=0;
        for(int i=0;i<n.size();i++){
            sum+=n[i];
            ma=max(ma,sum);
            if(sum<0){
                sum=0;
            }
        }
        return ma;
    }
```

# Leetcode 97

```cpp
bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(),n2 = s2.size(),n3 = s3.size();
        if(n1+n2!=n3)return false;
        if((s1==s3 && n2==0) || (s2==s3 && n1==0))return true;
        vector<int> dp(n2+1,-1);
        if(s3[0]==s1[0])dp[0] = 1;
        if(s3[0]==s2[0])dp[1] = 0;
        
        for(int i=1;i<n3;i++)
        {
            for(int j=n2;j>=0;j--)
            {
                if(dp[j]==-1)continue;
                if(j+1<= n2 && s2[j]==s3[i])
                    dp[j+1] = max(dp[j+1],dp[j]);
                if(s1[dp[j]]==s3[i])
                    dp[j] = dp[j]+1;
            }
        }
```

# Leetcode 647

```cpp
int countSubstrings(string s) {
        int n=s.size();
        vector<vector<int>>dp(n,vector<int>(n+1,0));
        int count=n;
        for(int i=0; i<n ; i++){
            dp[i][i]=1;
        }
        for(int i=n-2 ; i>=0 ; i--){
            for(int j=i+1 ; j<n ;j++){
                if(s[j]==s[i] && (dp[i+1][j-1] ||abs(i-j)==1)){
                    dp[i][j]=1;
                    count++;
                }
            }
        }
        return count;
    }
```

# N-Queens (Leetcode 51)

```cpp
vector<vector<string>>ans;
    bool check(vector<string>&v ,int ind ,int n){
        if(v.empty()) return true;
        for(int i=0 ; i<v.size() ; i++){
            if(v[i][ind]=='Q') return false;
        }
        int y=ind-1;
        int x =v.size()-1;
        while(x>=0 && y>=0){
            if(v[x][y] == 'Q') return false;
            x--;y--;
        }
        y=ind+1;
        x =v.size()-1;
        while(x>=0 && y<n){
            if(v[x][y] == 'Q') return false;
            x--;y++;
        }
        return true;
    }
    void recur(int n,string &s , vector<string>&v ){
        if(v.size() == n) {ans.push_back(v); return;}
        for(int i=0 ; i<n ; i++){
                
            if(check(v, i, n)){
                s[i] = 'Q';
                v.push_back(s);
                s[i] = '.';
                recur(n,s,v);
                v.pop_back();
            }
        }

    }
    vector<vector<string>> solveNQueens(int n) {
        string s="";
        for(int i=0 ; i<n; i++) s+='.';
        vector<string>v;
        recur(n,s,v );
        return ans;
    }
```

# Sudoku

```cpp
bool SolveSudoku(int grid[N][N], int i, int j)
{
    // Set the initial values
    if (!seted)
        seted = true, setInitialValues(grid);
 
    if (i == N - 1 && j == N)
        return true;
    if (j == N)
        j = 0, i++;
 
    if (grid[i][j])
        return SolveSudoku(grid, i, j + 1);
 
    for (int nr = 1; nr <= N; nr++) {
        if (isSafe(i, j, nr)) {
            /*  Assign nr in the
                current (i, j)
                position and
                add nr to each bitmask
            */
            grid[i][j] = nr;
            row[i] |= 1 << nr;
            col[j] |= 1 << nr;
            box[getBox(i, j)] |= 1 << nr;
 
            if (SolveSudoku(grid, i, j + 1))
                return true;
 
            // Remove nr from each bitmask
            // and search for another possibility
            row[i] &= ~(1 << nr);
            col[j] &= ~(1 << nr);
            box[getBox(i, j)] &= ~(1 << nr);
        }
 
        grid[i][j] = 0;
    }
 
    return false;
}
```

# Programming Challenge P1 (Ways to place chess pieces)

```cpp
bool isSafe(int temp[], int n, int i, int start)
{ // if "i" column contains a chess piece(#)
    for(int j=0; j<start; j++)
    {
        if(temp[j] == i)
        { return false; }
    }
    return true;
}
int req_function(string arr[], int temp[], int n, int k, int start, int count)
{ // If you have already ploced k pieces, then return
    if(count == k) { return 1; } // If start is n, then there is no row to place pieces
    if(start == n) { return 0; }
    int totalWays = 0; // Start placing in "start" row
    for(int i=0;i<n;i++)
    { // If # exists and position is safe
        if(arr[start][i] == '#' && isSafe(temp, n, i, start))
        {
            temp[start] = i; // Call recursively to place pieces in the further rows
            totalWays = totalWays + req_function(arr, temp, n, k, start + 1, count + 1); // Backtrack and remmove i from position[start]                     
            temp[start] = -1;             
        }     
    } // We are not placing any peice in the "start" row     
    totalWays = totalWays + req_function(arr, temp, n, k, start + 1, count);          
    return totalWays; 
}  
```

# Leetcode 1593

```cpp
unordered_set<string>st;
int ans=INT_MIN;

int maxUniqueSplit(string s) 
{
  int count=0;
  fun(s,count);
  return ans;
}

void fun(string s,int count)
{
  if(s.length()==0)
  {
  ans=max(ans,count);
  return;
  }
  string first="";
  string second="";
  for(int i=0;i<s.length();i++)
  {
    first.push_back(s[i]);
    if(st.find(first)==st.end())   //first entry of this type of string
    {
      st.insert(first);
      second = s.substr(i+1,s.length());
      fun(second,count+1);
      st.erase(first);         //backtraing
    }	
    else
    {
      continue;
    }
  }
}
```

# BFS, Shortest Path

```cpp
vector<int> bfs_shortest_path(vector<vector<int> >& graph, int start)
{
    deque<int> queue; // Create a queue for BFS
    queue.push_back(start);
    // Create a vector to keep track of distances from the starting vertex to all other vertices
    vector<int> distances(graph.size(), numeric_limits<int>::max());
    distances[start] = 0; // Distance to the start vertex is 0
    set<int> visited; // Create a set to keep track of visited vertices

    // Perform BFS
    while (!queue.empty()) {
        int vertex = queue.front(); // Dequeue the next vertex
        queue.pop_front();
        visited.insert(vertex); // Mark the vertex as visited
        // Update the distances of neighbors
        for (int neighbor : graph[vertex]) {
            if (visited.find(neighbor) == visited.end()) { // Check if the neighbor has not been visited
                distances[neighbor] = distances[vertex] + 1; // Update the distance from the starting vertex
                queue.push_back(neighbor); // Enqueue the neighbor for further exploration
            }
        }
    }
    return distances; // Return the distances from the start vertex to all other vertices
}
```

# DFS

```py
def dfs(graph, node):
    visited = []
    stack = []

    visited.append(node)
    stack.append(node) 

    while stack:
        s = stack.pop()
        print(s, end = " ")

        # reverse iterate through edge list so results match recursive version
        for n in reversed(graph[s]):
            if n not in visited:
                visited.append(n)
                stack.append(n)
```

# Topological Sort

```py
def topologicalSortUtil(self,v,visited,stack):
  visited[v] = True # Mark the current node as visited.
  for i in self.graph[v]: # Recur for all the vertices adjacent to this vertex
      if visited[i] == False:
          self.topologicalSortUtil(i,visited,stack)
  stack.insert(0,v) # Push current vertex to stack which stores result

# The function to do Topological Sort. It uses recursive topologicalSortUtil()
def topologicalSort(self):
  visited = [False]*self.V # Mark all the vertices as not visited
  stack =[]
# Call the recursive helper function to store Topological Sort starting from all vertices one by one
  for i in range(self.V):
    if visited[i] == False:
      self.topologicalSortUtil(i,visited,stack)
```

# Finding Strong Components

```py
def findSCC(self, n, a):
  ans = [] # Stores all the strongly connected components.
  is_scc = [0] * (n + 1) # Stores whether a vertex is a part of any Strongly Connected Component
  adj = [[] for _ in range(n + 1)]
  for i in range(len(a)):
      adj[a[i][0]].append(a[i][1])
  # Traversing all the vertices
  for i in range(1, n + 1):
      if not is_scc[i]:
          # If a vertex i is not a part of any SCC, insert it into a new SCC list and check for other vertices whether they can be part of this list.
          scc = [i]
          for j in range(i + 1, n + 1):
              # If there is a path from vertex i to vertex j and vice versa, put vertex j into the current SCC list.
              if not is_scc[j] and self.isPath(i, j, adj) and self.isPath(j, i, adj):
                  is_scc[j] = 1
                  scc.append(j)
          ans.append(scc) # Insert the SCC containing vertex i into the final list.
  return ans
```

# Minimum Spanning Tree (Boruvka's)

Time Complexity: O(E log V)

Code:

```cpp
void boruvkaMST()
{
    vector<int> parent(V); // An array to store index of the cheapest edge of subset. It store [u,v,w] for each component
    vector<int> rank(V);
    vector<vector<int> > cheapest(V, vector<int>(3, -1));
    int numTrees = V; // Initially there are V different trees. Finally there will be one tree that will be MST
    int MSTweight = 0;

// Create V subsets with single elements
    for (int node = 0; node < V; node++)
    {
        parent[node] = node;
        rank[node] = 0;
    }

// Keep combining components (or sets) until all components are not combined into single MST
    while (numTrees > 1) {
        // Traverse through all edges and update cheapest of every component
        for (int i = 0; i < graph.size(); i++) {
            // Find components (or sets) of two corners of current edge
            int u = graph[i][0], v = graph[i][1], w = graph[i][2];
            int set1 = find(parent, u), set2 = find(parent, v);

// If two corners of current edge belong to same set, ignore current edge. Else check if current edge is closer to previous cheapest edges of set1 and set2
            if (set1 != set2) {
                if (cheapest[set1][2] == -1 || cheapest[set1][2] > w) {
                    cheapest[set1] = { u, v, w };
                }
                if (cheapest[set2][2] == -1 || cheapest[set2][2] > w) {
                    cheapest[set2] = { u, v, w };
                }
            }
        }

// Consider the above picked cheapest edges and add them to MST
        for (int node = 0; node < V; node++) {
            // Check if cheapest for current set exists
            if (cheapest[node][2] != -1) {
                int u = cheapest[node][0], v = cheapest[node][1], w = cheapest[node][2];
                int set1 = find(parent, u), set2 = find(parent, v);
                if (set1 != set2) {
                    MSTweight += w;
                    unionSet(parent, rank, set1, set2);
                    numTrees--;
                }
            }
        }
        for (int node = 0; node < V; node++) {
            cheapest[node][2] = -1; // reset cheapest array
        }
    }
}
```

# Minimum Spanning Tree (Kruskal's)

Time Complexity: O(E log V)

Code:

```cpp
void kruskals_mst() 
{ 
  // Sort all edges 
  sort(edgelist.begin(), edgelist.end()); 
  // Initialize the DSU 
  DSU s(V); 
  int ans = 0; 
  for (auto edge : edgelist) { 
    int w = edge[0]; 
    int x = edge[1]; 
    int y = edge[2]; 
    // Take this edge in MST if it does  not forms a cycle 
    if (s.find(x) != s.find(y)) { 
        s.unite(x, y); 
        ans += w; 
    } 
  }
}
```

# Minimum Spanning Tree (Prim's)

Time Complexity: O(E log V)

Code:

```cpp
void primMST(int graph[V][V])
{
    int parent[V];                                                       // Array to store constructed MST
    int key[V];                                                          // Key values used to pick minimum weight edge in cut
    bool mstSet[V];                                                      // To represent set of vertices included in MST
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;                             // Initialize all keys as INFINITE
    key[0] = 0;                                                          // Always include first 1st vertex in MST. Make key 0 so that this vertex is picked as first vertex.
    parent[0] = -1;                                                      // First node is always root of MST
    for (int count = 0; count < V - 1; count++) {                        // The MST will have V vertices
        int u = minKey(key, mstSet);                                     // Pick the minimum key vertex from the set of vertices not yet included in MST
        mstSet[u] = true;                                                // Add the picked vertex to the MST Set
        for (int v = 0; v < V; v++)                                      // Update key value and parent index of the adjacent vertices of the picked vertex.
          if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) // Consider only those vertices which are not yet included in MST
            parent[v] = u, key[v] = graph[u][v];
    }
                                                                         // graph[u][v] is non zero only for adjacent vertices of m
                                                                         // mstSet[v] is false for vertices not yet included in MST
                                                                         // Update the key only if graph[u][v] is smaller than key[v]
}
```

# Single Source Shortest Path on a Directed Acyclic Graph

```cpp
void Graph::shortestPath(int s)
{
  stack<int> Stack;
  int dist[V];
  bool *visited = new bool[V]; // Mark all the vertices as not visited
  for (int i = 0; i < V; i++)
      visited[i] = false;
// Call the recursive helper function to store Topological Sort starting from all vertices  one by one
  for (int i = 0; i < V; i++)
      if (visited[i] == false)
          topologicalSortUtil(i, visited, Stack);
// Initialize distances to all vertices as infinite and distance to source as 0
  for (int i = 0; i < V; i++)
      dist[i] = INF;
  dist[s] = 0;
  while (Stack.empty() == false) { // Process vertices in topological order
    int u = Stack.top();           // Get the next vertex from topological order
    Stack.pop();

// Update distances of all adjacent vertices
    list<AdjListNode>::iterator i;
    if (dist[u] != INF)
    {
      for (i = adj[u].begin(); i != adj[u].end(); ++i)
         if (dist[i->getV()] > dist[u] + i->getWeight())
            dist[i->getV()] = dist[u] + i->getWeight();
    }
  }
}
```

# Single Source Longest Path on a Directed Acyclic Graph

```cpp
void Graph::longestPath(int s) 
{ 
  stack<int> Stack; 
  int dist[V]; 
  bool* visited = new bool[V]; // Mark all the vertices as not visited 
  for (int i = 0; i < V; i++) 
      visited[i] = false; 
 
// Call the recursive helper function to store Topological  Sort starting from all vertices one by one 
  for (int i = 0; i < V; i++) 
      if (visited[i] == false) 
          topologicalSortUtil(i, visited, Stack); 

  for (int i = 0; i < V; i++) 
      dist[i] = NINF; // Initialize distances to all vertices as infinite and distance to source as 0 
  dist[s] = 0;  
  while (Stack.empty() == false) { // Process vertices in topological order 
    int u = Stack.top();           // Get the next vertex from topological order 
    Stack.pop(); 
 
// Update distances of all adjacent vertices 
    list<AdjListNode>::iterator i; 
    if (dist[u] != NINF) { 
      for (i = adj[u].begin(); i != adj[u].end(); ++i){ 
        if (dist[i->getV()] < dist[u] + i->getWeight()) 
          dist[i->getV()] = dist[u] + i->getWeight();
      }
    } 
  } 
}
```
