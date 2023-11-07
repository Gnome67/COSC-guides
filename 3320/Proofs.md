Proofs

For any algorithm we need to prove it will behave as intended. For an algorithm to be correct it must always perform as we desire it to.
- It will always return the desired output.
- Always reach its base case if recursive.
- For all possible inputs there is a valid output

Proof Techniques:

1. Proof by Induction
- Prove the algorithm is correct for the base case.
- Assume it is correct for all inputs of size < n.
- Show that it is then correct for an input of size n.

2. Proof by Loop Invariant
- Define a loop invariant - a property that holds true throughout the algorithm's execution.
- Show by induction that the loop invariant is true at each iteration.

Ex. Median of Two Sorted Arrays (induction)
Proof: Clearly, if n = 1, our algorithm is correct. Assume that our algorithm is correct for all n < k. Then, for all n = k, our algorithm determines Ma and Mb. If Ma < Mb, then the elements A[0:n/2] are all less than Mb. Similarly, the elements B[n/2:n] are all greater than Mb. Thus, our median lies in A[n/2:n] or B[0:n/2]. These subarrays aare of length n/2 < n, hence our algorithm correctly finds the median of these subarrays by our induction hypothesis.
