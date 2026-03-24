# C++ Ford-Johnson Sort

Implementation of the **Ford-Johnson merge-insert sort** algorithm (also known as the *Patience Sort variant*), achieving a theoretically optimal number of comparisons — applied to two container types (`std::vector` and `std::deque`) with performance benchmarking.

## Algorithm

The Ford-Johnson algorithm minimizes the number of comparisons required to sort n elements. It operates in three phases:

1. **Pair and sort pairs** — divide elements into pairs, sort each pair (⌊n/2⌋ comparisons)
2. **Recursive sort** — recursively sort the larger element of each pair using the same algorithm
3. **Binary insertion** — insert the smaller elements (the "pend" chain) in an order determined by **Jacobsthal numbers** to minimize binary search depth

### Jacobsthal Insertion Order
```
J(n): 0, 1, 1, 3, 5, 11, 21, 43, 85, ...
Insert pend elements in groups of size J(k) - J(k-1),
working backwards within each group.
```
This order guarantees that each binary insertion touches at most `k` comparisons, where `2^k - 1` covers the current sorted sequence length.

## Benchmark Output

```
./PmergeMe 3 5 9 7 4 2 1
Before:  3 5 9 7 4 2 1
After:   1 2 3 4 5 7 9
Time to process a range of 7 elements with std::vector : 0.00031 us
Time to process a range of 7 elements with std::deque  : 0.00042 us
```

## Build & Run

```bash
make
./PmergeMe $(shuf -i 1-3000 -n 3000 | tr n 
