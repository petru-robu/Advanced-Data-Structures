# Advanced Data Structures
This repository contains implementations for **Skip-Lists**, **Splay-Trees** and **B-Trees** data structures. The program tests the structures against different 
tests and distributions of queries to find the best and worst case scenarios for each data structure. <br>
The correctness of our implementations is tested on the problem here: [abce](https://www.infoarena.ro/problema/abce), where our structures get 100p.
## Skip Lists

**Skip Lists** are probabilistic data structures that allow fast search, insertion, and deletion within an ordered sequence of elements. 
They augment a linked list with multiple "levels" of forward pointers, enabling binary-search-like performance by skipping over large portions of the list.

## Splay Trees
**Splay Trees** are binary search trees that have the proprety that recently accesed items are accesed quickly every time. This is done
by introducing a new operation, *splaying*, which is based on rotations, that moves a key up the tree while also mantaining an almost balanced strcuture.

## B-Trees
**B-Trees** are self-balancing tree data structures commonly used in databases and file systems to manage large blocks of sorted data efficiently.
Unlike binary search trees, B-Trees can have more than two children per node. Nodes are kept balanced through controlled insertions and deletions that split or merge nodes when necessary.

## Time Complexity
Here are the time complexities of our structures:

| Data Structure | Operation  | Average Case      | Worst Case          |
|----------------|------------|-------------------|---------------------|
| **Skip List**  | Search     | `O(log n)`        | `O(n)`              |
|                | Insert     | `O(log n)`        | `O(n)`              |
|                | Delete     | `O(log n)`        | `O(n)`              |
| **Splay Tree** | Search     | `O(log n)` amort. | `O(n)`              |
|                | Insert     | `O(log n)` amort. | `O(n)`              |
|                | Delete     | `O(log n)` amort. | `O(n)`              |
| **B-Tree**     | Search     | `O(log n)`        | `O(log n)`          |
|                | Insert     | `O(log n)`        | `O(log n)`          |
|                | Delete     | `O(log n)`        | `O(log n)`          |

### Notes:
- **Skip Lists** use randomized levels; worst-case performance occurs with poor level distribution.
- **Splay Trees** provide amortized efficiency through rotations but may degrade to linear time in skewed cases.
- **B-Trees** maintain balanced structure and consistent logarithmic performance across all operations.

## Average Times (in seconds)
The structures were tested against different types of tests: 
-  **insertion_heavy** (80% insertions, 10% deletions, 10% searches)
-  **insert_remove_heavy** (45% insertions, 45% deletions, 10% searches)
-  **search_heavy** (15% insertions, 5% deletions, 80% searches)
-  **average** (25% insertions, 25% deletions, 50% searches).

| Test Category         | Splay   | Skip    | BTree   |
|-----------------------|---------|---------|---------|
| Insertion Heavy       | 0.9831  | 6.4496  | 1.3195  |
| Insertion and removal heavy   | 0.5572 | 3.1343  | 0.6317  |
| Search heavy          | 1.3579 | 7.6694  | 1.4928  |
| Average               | 1.4561  | 8.1279  | 1.5692  |
 
*Note: The results are obtained by taking the average on multiple tests in the same category.*

## Compilation instructions
To use the application, you need to compile *main.cpp*:
```
g++ main.cpp -o main.out
```
If you wish, you can generate your own tests by editing *generator.py*:
```
python3 main.py
```
