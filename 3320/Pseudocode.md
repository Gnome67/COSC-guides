Code in Python:
```py
def distance(node, source, destination):
  def getLevel(node, key, level: int) -> int:
    if node is None:
      return -1
    if node.value == key:
      return level

    if key < node.value:
      return getLevel(node.left, key, level+1)
    elif key > node.value:
      return getLevel(node.right, key, level+1)

  ancestor = lowestCommonAncestor(node, source, destination)
  distanceFromSource: int = getLevel(ancestor, source, 0)
  distanceFromDestination: int = getLevel(ancetor, destination, 0)
  totalDistance = distanceFromSource + distanceFromDestination
  return totalDistance
```
Code in Pseudocode:
```py
function distance(node, source, destination)
  function getLevel(node, key, level)
    if node is null
      return -1
    if value of node == key
      return level

    if key < value of node
      recurse left and increment level
    if key > value of node
      recurse right and increment level

  ancestor = lowestCommonAncestor(node, source, destination)
  distanceFromSource = getLevel(ancestor, source, 0)
  distanceFromDestination = getLevel(ancestor, destination, 0)
  totalDistance = distanceFromSource + distanceFromDestination
  return totalDestination
```

Ex. Median of Two Sorted Arrays
```py
function findMedianOfUnion(array A, array B):
  if median of A == median of B:
    return median of A
  else if size of A == 2 and size of B == 2
    return (max(A[0], B[0]) + min(A[1], B[1])) / 2
  else if median of A > median of B
    findMedianOfUnion(A[0....median of A], B[median of B...M])
  else
    findMedianOfUnion(A[median of A... .N], B[0...median of b])
```

Ex. Print all subsets
```py
function powersets(index, array, subset, result)
  if index > length of array
    result.append(subset)
  subset.append(array)
  powersets(index+1, array, subset, result)
  pop from subset
  powersets(index+1, array, subset, result)
```
