# Van Emde Boas Tree Implementation
### Van Emde Boas Tree Implementation in C++ with application to Kruskal and compare with respect to AVL tree

Reasons to use Van Emde Boas for kruskal implementation:

* Van Emde Boas Tree is a tree data structure which supports insert and delete operations in O(log log u), 'u' being the universe size 

* Van Emde Boas Tree works with O(1) time-complexity for minimum and maximum query

* Due to above 2 reasons, Van Emde Boas tree is faster than any of related data structures like binary search tree, AVL tree etc which is required in Kruskal to implement minheap

## Execution Instructions:
```
g++ kruskal_avl.cpp
./a.out
<Enter no of vertices>
<Enter no of edges>
<---Add all edges in (wt vertex1 vertex2) format--->
```
## Output:
![output_img](https://github.com/manikgupta11/van-Emde-Boas-Tree-Implementation/blob/master/mst-output.png)
